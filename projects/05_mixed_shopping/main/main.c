#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "SHOPPING_MATH";  // แท็กสำหรับการแสดง log

// 🔶 โครงสร้างข้อมูลสินค้า
typedef struct {
    char name[64];          // ชื่อสินค้า
    int quantity;           // จำนวน
    float price_per_unit;   // ราคาต่อหน่วย
    float total_price;      // ราคารวม
} product_t;

// 🧮 ฟังก์ชันคำนวณราคารวมของสินค้าแต่ละชิ้น
void calculate_product_total(product_t *product) {
    product->total_price = product->quantity * product->price_per_unit;
}

// 📋 ฟังก์ชันแสดงรายการสินค้า
void display_product(const product_t *product) {
    ESP_LOGI(TAG, "   %s: %d × %.0f = %.0f บาท", 
             product->name, product->quantity, product->price_per_unit, product->total_price);
}

// 🔢 ฟังก์ชันคำนวณยอดรวมทั้งหมดของสินค้าทั้งหมด
float calculate_total_bill(product_t products[], int count) {
    float total = 0.0;
    for (int i = 0; i < count; i++) {
        calculate_product_total(&products[i]);  // คำนวณราคาสินค้าแต่ละรายการ
        total += products[i].total_price;
    }
    return total;
}

// 💸 ฟังก์ชันใช้ส่วนลดแบบเปอร์เซ็นต์
float apply_percentage_discount(float total, float percent) {
    return total - (total * percent / 100.0);
}

// 🧾 ฟังก์ชันคำนวณภาษี VAT
float apply_vat(float total, float vat_percent) {
    return total + (total * vat_percent / 100.0);
}

// 👥 ฟังก์ชันแบ่งจ่ายเงินต่อคน
float split_payment(float amount, int people) {
    if (people <= 0) {
        ESP_LOGE(TAG, "Error: จำนวนคนต้องมากกว่า 0");
        return 0.0;
    }
    return amount / people;
}

void app_main(void)
{
    ESP_LOGI(TAG, "🛒 เริ่มต้นโปรแกรมซื้อของที่ตลาด (เวอร์ชันใหม่) 🛒");
    ESP_LOGI(TAG, "=====================================");

    // 📦 ข้อมูลการซื้อของ (เพิ่มสินค้าที่ชอบ: ช็อกโกแลต)
    product_t products[] = {
        {"แอปเปิ้ล", 6, 15.0, 0.0},
        {"กล้วย", 12, 8.0, 0.0},
        {"ส้ม", 8, 12.0, 0.0},
        {"ช็อกโกแลต", 3, 30.0, 0.0}
    };
    int product_count = sizeof(products) / sizeof(products[0]);

    float discount_percent = 10.0;  // ส่วนลด 10%
    float vat_percent = 7.0;        // ภาษี VAT 7%
    int people = 3;                 // จำนวนคนที่หารกันจ่าย

    // 🧮 คำนวณขั้นตอนต่าง ๆ
    float subtotal = calculate_total_bill(products, product_count);  // ยอดรวมก่อนส่วนลด
    float discount_amount = subtotal * (discount_percent / 100.0);   // คำนวณส่วนลด
    float discounted_total = apply_percentage_discount(subtotal, discount_percent);  // ยอดหลังหักส่วนลด
    float total_with_vat = apply_vat(discounted_total, vat_percent);  // ยอดหลังบวก VAT
    float per_person = split_payment(total_with_vat, people);  // หารเงินต่อคน

    vTaskDelay(2000 / portTICK_PERIOD_MS);  // หน่วงเวลาให้เห็นผลการคำนวณชัดขึ้น

    // 🧾 แสดงรายการสินค้า
    ESP_LOGI(TAG, "📖 รายการสินค้า:");
    for (int i = 0; i < product_count; i++) {
        display_product(&products[i]);
    }

    // 💰 สรุปค่าใช้จ่ายทั้งหมด
    ESP_LOGI(TAG, "");
    ESP_LOGI(TAG, "💰 สรุปค่าใช้จ่าย:");
    ESP_LOGI(TAG, "   ยอดรวมก่อนส่วนลด:           %.2f บาท", subtotal);
    ESP_LOGI(TAG, "   ส่วนลด %.0f%%:                -%.2f บาท", discount_percent, discount_amount);
    ESP_LOGI(TAG, "   ยอดหลังหักส่วนลด:            %.2f บาท", discounted_total);
    ESP_LOGI(TAG, "   ภาษีมูลค่าเพิ่ม (VAT %.0f%%): +%.2f บาท", vat_percent, total_with_vat - discounted_total);
    ESP_LOGI(TAG, "   ยอดสุทธิรวม VAT:             %.2f บาท", total_with_vat);
    ESP_LOGI(TAG, "   แบ่งจ่าย %d คน:               %.2f บาท/คน", people, per_person);
    ESP_LOGI(TAG, "");

    // 📌 แสดงข้อคิดและการประยุกต์ใช้
    ESP_LOGI(TAG, "🌟 การประยุกต์ใช้ในชีวิตจริง:");
    ESP_LOGI(TAG, "   - การซื้อของเป็นกลุ่ม");
    ESP_LOGI(TAG, "   - การแบ่งบิลในร้านอาหาร");
    ESP_LOGI(TAG, "   - การคำนวณงบประมาณแบบรวมภาษี");
    ESP_LOGI(TAG, "   - การทำระบบคิดเงินอัตโนมัติ");
    ESP_LOGI(TAG, "");

    ESP_LOGI(TAG, "🎉 จบโปรแกรมซื้อของที่ตลาดเวอร์ชันใหม่!");
}
