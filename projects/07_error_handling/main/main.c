#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "ERROR_HANDLING";

typedef enum {
    ERROR_NONE = 0,
    ERROR_DIVISION_BY_ZERO,
    ERROR_INVALID_INPUT,
    ERROR_OUT_OF_RANGE,
    ERROR_NEGATIVE_VALUE,
    ERROR_OVERFLOW,
    ERROR_UNDERFLOW
} error_code_t;

typedef struct {
    double result;
    error_code_t error;
    char message[100];
} calculation_result_t;

void show_ascii_art(error_code_t error) {
    switch(error) {
        case ERROR_NONE:
            ESP_LOGI(TAG, "   ✅ SUCCESS");
            ESP_LOGI(TAG, "     🎉🎉🎉");
            ESP_LOGI(TAG, "    สำเร็จแล้ว!");
            break;
        case ERROR_DIVISION_BY_ZERO:
            ESP_LOGI(TAG, "   🍕 ÷ 0 = ❌");
            ESP_LOGI(TAG, "   😱 โอ้ะโอ!");
            ESP_LOGI(TAG, "  ไม่มีลูกค้า!");
            break;
        case ERROR_INVALID_INPUT:
            ESP_LOGI(TAG, "   📝 ABC บาท?");
            ESP_LOGI(TAG, "   🤔 งง...");
            ESP_LOGI(TAG, "  ตัวเลขหายไป");
            break;
        case ERROR_OUT_OF_RANGE:
            ESP_LOGI(TAG, "   📈 ∞∞∞∞∞");
            ESP_LOGI(TAG, "   😵 เกินขีด!");
            ESP_LOGI(TAG, "  ใหญ่เกินไป");
            break;
        default:
            ESP_LOGI(TAG, "   ❓ ERROR");
            ESP_LOGI(TAG, "   🔧 แก้ไข");
            ESP_LOGI(TAG, "  ต้องตรวจสอบ");
    }
}

calculation_result_t safe_divide(double dividend, double divisor, const char* context) {
    calculation_result_t result = {0};

    ESP_LOGI(TAG, "\n🔍 ตรวจสอบการหาร: %s", context);
    ESP_LOGI(TAG, "📊 %.2f ÷ %.2f = ?", dividend, divisor);

    if (divisor == 0.0) {
        result.error = ERROR_DIVISION_BY_ZERO;
        snprintf(result.message, sizeof(result.message), "❌ หารด้วยศูนย์ไม่ได้!");
        ESP_LOGE(TAG, "%s", result.message);
        show_ascii_art(ERROR_DIVISION_BY_ZERO);
        ESP_LOGI(TAG, "💡 ตรวจสอบจำนวนลูกค้าก่อนแบ่งพิซซ่า");
        return result;
    }

    result.result = dividend / divisor;
    if (isinf(result.result)) {
        result.error = ERROR_OVERFLOW;
        snprintf(result.message, sizeof(result.message), "⚠️ ค่าผลลัพธ์เป็น Infinity!");
        ESP_LOGW(TAG, "%s", result.message);
        return result;
    }

    result.error = ERROR_NONE;
    snprintf(result.message, sizeof(result.message), "✅ สำเร็จ: %.2f ÷ %.2f = %.2f", dividend, divisor, result.result);
    ESP_LOGI(TAG, "%s", result.message);
    show_ascii_art(ERROR_NONE);

    return result;
}

calculation_result_t validate_money(double amount, const char* description) {
    calculation_result_t result = {0};

    ESP_LOGI(TAG, "\n💰 ตรวจสอบเงิน: %s", description);
    ESP_LOGI(TAG, "💵 จำนวน: %.2f บาท", amount);

    if (amount < 0) {
        result.error = ERROR_NEGATIVE_VALUE;
        snprintf(result.message, sizeof(result.message), "❌ จำนวนเงินต้องไม่ติดลบ!");
        ESP_LOGE(TAG, "%s", result.message);
        ESP_LOGI(TAG, "💡 ตรวจสอบการคิดเงินใหม่");
        return result;
    }

    if (amount > 1000000000000.0) {
        result.error = ERROR_OUT_OF_RANGE;
        snprintf(result.message, sizeof(result.message), "⚠️ จำนวนเงินเกินขีดจำกัด!");
        ESP_LOGW(TAG, "%s", result.message);
        show_ascii_art(ERROR_OUT_OF_RANGE);
        ESP_LOGI(TAG, "💡 แนะนำ: ใช้ระบบธนาคารกลาง");
        return result;
    }

    double rounded = round(amount * 100) / 100;
    if (fabs(amount - rounded) > 0.001) {
        ESP_LOGW(TAG, "⚠️ ปัดเศษจาก %.4f → %.2f บาท", amount, rounded);
        amount = rounded;
    }

    result.result = amount;
    result.error = ERROR_NONE;
    snprintf(result.message, sizeof(result.message), "✅ เงินถูกต้อง: %.2f บาท", amount);
    ESP_LOGI(TAG, "%s", result.message);

    return result;
}

calculation_result_t validate_number(const char* input, const char* field_name) {
    calculation_result_t result = {0};

    ESP_LOGI(TAG, "\n🔢 ตรวจสอบตัวเลข: %s", field_name);
    ESP_LOGI(TAG, "📝 ข้อมูลที่ป้อน: '%s'", input);

    if (input == NULL || strlen(input) == 0) {
        result.error = ERROR_INVALID_INPUT;
        snprintf(result.message, sizeof(result.message), "❌ ไม่มีข้อมูล!");
        ESP_LOGE(TAG, "%s", result.message);
        return result;
    }

    char* endptr;
    double value = strtod(input, &endptr);

    if (*endptr != '\0') {
        result.error = ERROR_INVALID_INPUT;
        snprintf(result.message, sizeof(result.message), "❌ '%s' ไม่ใช่ตัวเลข!", input);
        ESP_LOGE(TAG, "%s", result.message);
        show_ascii_art(ERROR_INVALID_INPUT);
        ESP_LOGI(TAG, "💡 ใช้เฉพาะตัวเลข 0-9 และจุดทศนิยม");
        return result;
    }

    if (isnan(value) || isinf(value)) {
        result.error = ERROR_INVALID_INPUT;
        snprintf(result.message, sizeof(result.message), "❌ ตัวเลขไม่ถูกต้อง!");
        ESP_LOGE(TAG, "%s", result.message);
        return result;
    }

    result.result = value;
    result.error = ERROR_NONE;
    snprintf(result.message, sizeof(result.message), "✅ ตัวเลขถูกต้อง: %.2f", value);
    ESP_LOGI(TAG, "%s", result.message);

    return result;
}

calculation_result_t calculate_interest(double principal, double rate, int years) {
    calculation_result_t result = {0};

    ESP_LOGI(TAG, "\n🏦 คำนวณดอกเบี้ย");
    ESP_LOGI(TAG, "💰 เงินต้น: %.2f บาท", principal);
    ESP_LOGI(TAG, "📈 อัตราดอกเบี้ย: %.2f%% ต่อปี", rate);
    ESP_LOGI(TAG, "⏰ ระยะเวลา: %d ปี", years);

    if (principal <= 0) {
        result.error = ERROR_NEGATIVE_VALUE;
        snprintf(result.message, sizeof(result.message), "❌ เงินต้นต้องมากกว่าศูนย์!");
        ESP_LOGE(TAG, "%s", result.message);
        return result;
    }

    if (rate < -100 || rate > 100) {
        result.error = ERROR_OUT_OF_RANGE;
        snprintf(result.message, sizeof(result.message), "❌ อัตราดอกเบี้ยไม่เหมาะสม!");
        ESP_LOGE(TAG, "%s", result.message);
        ESP_LOGI(TAG, "💡 ใช้ -100%% ถึง 100%% เท่านั้น");
        return result;
    }

    if (years < 0 || years > 100) {
        result.error = ERROR_OUT_OF_RANGE;
        snprintf(result.message, sizeof(result.message), "❌ ระยะเวลาไม่เหมาะสม!");
        ESP_LOGE(TAG, "%s", result.message);
        return result;
    }

    double interest = principal * (rate / 100.0) * years;
    double total = principal + interest;

    if (total > DBL_MAX / 2) {
        result.error = ERROR_OVERFLOW;
        snprintf(result.message, sizeof(result.message), "⚠️ ผลลัพธ์ใหญ่เกินไป!");
        ESP_LOGW(TAG, "%s", result.message);
        return result;
    }

    result.result = total;
    result.error = ERROR_NONE;
    snprintf(result.message, sizeof(result.message), "✅ ดอกเบี้ย: %.2f, รวม: %.2f", interest, total);
    ESP_LOGI(TAG, "%s", result.message);

    return result;
}

void pizza_shop_scenario(void) {
    ESP_LOGI(TAG, "\n🍕 === ร้านพิซซ่า ===");
    safe_divide(12, 4, "แบ่งพิซซ่าให้ลูกค้า 4 คน");
    vTaskDelay(pdMS_TO_TICKS(2000));

    safe_divide(12, 0, "แบ่งพิซซ่าให้ลูกค้า 0 คน");
    vTaskDelay(pdMS_TO_TICKS(2000));

    ESP_LOGI(TAG, "\n🌞 ฝนหยุดแล้ว! ลูกค้ามา 3 คน");
    safe_divide(12, 4, "แบ่งพิซซ่าให้ลูกค้า 3 คน");
}

void shop_scenario(void) {
    ESP_LOGI(TAG, "\n🛒 === ร้านขายของ ===");
    validate_number("ABC", "ราคาสินค้า");
    vTaskDelay(pdMS_TO_TICKS(2000));

    validate_number("12.50", "ราคาสินค้า");
    vTaskDelay(pdMS_TO_TICKS(1000));

    validate_money(-50.0, "เงินทอน");
    vTaskDelay(pdMS_TO_TICKS(2000));

    validate_money(25.75, "เงินทอน");
}

void bank_scenario(void) {
    ESP_LOGI(TAG, "\n🏦 === ธนาคาร ===");
    calculate_interest(100000, 2.5, 5);
    vTaskDelay(pdMS_TO_TICKS(2000));

    calculate_interest(100000, -5.0, 5);
    vTaskDelay(pdMS_TO_TICKS(2000));

    validate_money(999999999999.0, "เงินฝาก");
    vTaskDelay(pdMS_TO_TICKS(2000));

    calculate_interest(100000, 3.0, 10);
}

void show_error_handling_summary(void) {
    ESP_LOGI(TAG, "\n📚 === สรุปข้อผิดพลาด ===");
    ESP_LOGI(TAG, "╔══════════════════════════════════════╗");
    ESP_LOGI(TAG, "║ 🚫 Division by Zero  - หารด้วยศูนย์ ║");
    ESP_LOGI(TAG, "║ 📝 Invalid Input      - ป้อนผิด     ║");
    ESP_LOGI(TAG, "║ 📊 Out of Range       - เกินขอบเขต  ║");
    ESP_LOGI(TAG, "║ ➖ Negative Value      - ค่าติดลบ     ║");
    ESP_LOGI(TAG, "║ ⬆️ Overflow            - ล้นค่าระบบ ║");
    ESP_LOGI(TAG, "╚══════════════════════════════════════╝");

    ESP_LOGI(TAG, "\n🛡️ หลักการจัดการข้อผิดพลาด:");
    ESP_LOGI(TAG, "✅ ตรวจสอบข้อมูลก่อนคำนวณ");
    ESP_LOGI(TAG, "✅ แจ้งเตือนแบบเข้าใจง่าย");
    ESP_LOGI(TAG, "✅ ให้คำแนะนำแก้ปัญหา");
    ESP_LOGI(TAG, "✅ ป้องกัน crash หรือ hang");
    ESP_LOGI(TAG, "✅ ใช้ enum + struct คุมสถานะ");
}

void app_main(void) {
    ESP_LOGI(TAG, "🚀 เริ่มต้นระบบจัดการข้อผิดพลาด!");
    vTaskDelay(pdMS_TO_TICKS(1000));

    pizza_shop_scenario();
    vTaskDelay(pdMS_TO_TICKS(3000));

    shop_scenario();
    vTaskDelay(pdMS_TO_TICKS(3000));

    bank_scenario();
    vTaskDelay(pdMS_TO_TICKS(3000));

    show_error_handling_summary();

    ESP_LOGI(TAG, "\n✅ เสร็จสิ้น! พร้อมเขียนโปรแกรมปลอดภัยแล้ว!");
}
