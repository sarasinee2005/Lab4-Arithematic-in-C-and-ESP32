#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "COOKIES_MATH";

void app_main(void)
{
    ESP_LOGI(TAG, "🍪 เริ่มต้นโปรแกรมแบ่งคุกกี้ 🍪");
    ESP_LOGI(TAG, "================================");
    
    // ประกาศตัวแปรเก็บจำนวนคุกกี้
    int total_cookies = 24;        // คุกกี้ทั้งหมด
    int number_of_friends = 6;     // จำนวนเพื่อน
    int cookies_per_person;        // คุกกี้ต่อคน
    int remaining_cookies;         // คุกกี้ที่เหลือ
    cookies_per_person = total_cookies / number_of_friends;
    remaining_cookies = total_cookies % number_of_friends;
    // แสดงข้อมูลเริ่มต้น
    ESP_LOGI(TAG, "📖 โจทย์:");
    ESP_LOGI(TAG, "   มีคุกกี้: %d ชิ้น", total_cookies);
    ESP_LOGI(TAG, "   จะแบ่งให้เพื่อน: %d คน", number_of_friends);
    ESP_LOGI(TAG, "   ❓ แต่ละคนได้คุกกี้กี่ชิ้น?");
    ESP_LOGI(TAG, "");
    
    vTaskDelay(3000 / portTICK_PERIOD_MS);
    
    // ตรวจสอบการหารด้วยศูนย์
    if (number_of_friends == 0) {
        ESP_LOGE(TAG, "❌ ข้อผิดพลาด: ไม่สามารถหารด้วยศูนย์ได้!");
        ESP_LOGI(TAG, "   ในชีวิตจริง: ไม่มีเพื่อนมาแบ่งคุกกี้");
        ESP_LOGI(TAG, "   คุกกี้ทั้งหมด %d ชิ้น จะเหลือไว้ทั้งหมด", total_cookies);
        ESP_LOGI(TAG, "");
        ESP_LOGI(TAG, "🎉 จบโปรแกรม!");
        return;
    }
    
    // คำนวณผลลัพธ์ (การหาร)
    cookies_per_person = total_cookies / number_of_friends;    // ผลหาร
    remaining_cookies = total_cookies % number_of_friends;     // เศษที่เหลือ
    
    // แสดงขั้นตอนการคิด
    ESP_LOGI(TAG, "🧮 ขั้นตอนการคิด:");
    ESP_LOGI(TAG, "   คุกกี้ทั้งหมด ÷ จำนวนเพื่อน");
    ESP_LOGI(TAG, "   = %d ÷ %d", total_cookies, number_of_friends);
    ESP_LOGI(TAG, "   = %d ชิ้นต่อคน", cookies_per_person);
    if (remaining_cookies > 0) {
        ESP_LOGI(TAG, "   เศษที่เหลือ = %d ชิ้น", remaining_cookies);
    }
    ESP_LOGI(TAG, "");
    
    // แสดงคำตอบ
    ESP_LOGI(TAG, "✅ คำตอบ:");
    ESP_LOGI(TAG, "   แต่ละคนได้คุกกี้ %d ชิ้น", cookies_per_person);
    if (remaining_cookies > 0) {
        ESP_LOGI(TAG, "   มีคุกกี้เหลือ %d ชิ้น (ไม่สามารถแบ่งได้เท่าๆ กัน)", remaining_cookies);
    } else {
        ESP_LOGI(TAG, "   แบ่งได้พอดี ไม่มีเหลือ");
    }
    if (remaining_cookies == 0) {
    ESP_LOGI(TAG, "✅ หารลงตัว! ทุกคนได้เท่ากัน");
    } else {
    ESP_LOGI(TAG, "⚠️ หารไม่ลงตัว! เหลือ %d ชิ้น", remaining_cookies);
    }
    ESP_LOGI(TAG, "");
    
    // แสดงภาพประกอบ
    ESP_LOGI(TAG, "🎨 ภาพประกอบการแบ่ง:");
    ESP_LOGI(TAG, "   คุกกี้ทั้งหมด: 🍪🍪🍪🍪🍪🍪🍪🍪🍪🍪🍪🍪 (%d ชิ้น)", total_cookies);
    ESP_LOGI(TAG, "");
    
    // แสดงการแบ่งให้แต่ละคน
    for (int person = 1; person <= number_of_friends; person++) {
        ESP_LOGI(TAG, "   เพื่อนคนที่ %d: ", person);
        for (int cookie = 0; cookie < cookies_per_person; cookie++) {
            // แสดงคุกกี้ที่ได้รับ (อย่างง่าย)
        }
        ESP_LOGI(TAG, "🍪🍪🍪 (%d ชิ้น)", cookies_per_person);
    }
    
    if (remaining_cookies > 0) {
        ESP_LOGI(TAG, "   เหลือ: ");
        for (int i = 0; i < remaining_cookies; i++) {
            // แสดงคุกกี้ที่เหลือ
        }
        ESP_LOGI(TAG, "🍪 (%d ชิ้น)", remaining_cookies);
    }
    if (remaining_cookies == 0) {
    ESP_LOGI(TAG, "✅ หารลงตัว! ทุกคนได้เท่ากัน");
    } else {
    ESP_LOGI(TAG, "⚠️ หารไม่ลงตัว! เหลือ %d ชิ้น", remaining_cookies);
    }
    ESP_LOGI(TAG, "");
    
    int cookies = 30;
    ESP_LOGI(TAG, "🔍 คุกกี้ %d ชิ้น หารลงตัวกับ:", cookies);

    for (int people = 1; people <= 10; people++) {
    if (cookies % people == 0) {
        ESP_LOGI(TAG, "   ✅ %d คน → คนละ %d ชิ้น", 
                 people, cookies / people);
    }
    }

    // ตัวอย่างเพิ่มเติม
    ESP_LOGI(TAG, "💡 ตัวอย่างเพิ่มเติม:");
    
    // ตัวอย่างที่ 1: หารลงตัว
    int ex1_cookies = 15;
    int ex1_friends = 3;
    int ex1_per_person = ex1_cookies / ex1_friends;
    int ex1_remainder = ex1_cookies % ex1_friends;
    ESP_LOGI(TAG, "   คุกกี้ %d ชิ้น แบ่งให้ %d คน", ex1_cookies, ex1_friends);
    ESP_LOGI(TAG, "   = %d ÷ %d = %d ชิ้นต่อคน, เหลือ %d ชิ้น", 
             ex1_cookies, ex1_friends, ex1_per_person, ex1_remainder);
    ESP_LOGI(TAG, "");
    
    // ตัวอย่างที่ 2: หารไม่ลงตัว
    int ex2_cookies = 13;
    int ex2_friends = 4;
    int ex2_per_person = ex2_cookies / ex2_friends;
    int ex2_remainder = ex2_cookies % ex2_friends;
    ESP_LOGI(TAG, "   คุกกี้ %d ชิ้น แบ่งให้ %d คน", ex2_cookies, ex2_friends);
    ESP_LOGI(TAG, "   = %d ÷ %d = %d ชิ้นต่อคน, เหลือ %d ชิ้น", 
             ex2_cookies, ex2_friends, ex2_per_person, ex2_remainder);
    ESP_LOGI(TAG, "   (หารไม่ลงตัว)");
    ESP_LOGI(TAG, "");
    
    // ตัวอย่างที่ 3: กรณีพิเศษ
    ESP_LOGI(TAG, "⚠️  กรณีพิเศษ - หารด้วยศูนย์:");
    ESP_LOGI(TAG, "   ถ้าไม่มีเพื่อนมาแบ่ง (หารด้วย 0)");
    ESP_LOGI(TAG, "   ไม่สามารถคำนวณได้ในทางคณิตศาสตร์");
    ESP_LOGI(TAG, "   ในชีวิตจริง: คุกกี้จะเหลือทั้งหมด");
    ESP_LOGI(TAG, "");
    
    // ความสัมพันธ์กับการคูณ
    ESP_LOGI(TAG, "🔄 ความสัมพันธ์กับการคูณ:");
    ESP_LOGI(TAG, "   การหาร: %d ÷ %d = %d", total_cookies, number_of_friends, cookies_per_person);
    ESP_LOGI(TAG, "   การคูณ: %d × %d = %d", cookies_per_person, number_of_friends, cookies_per_person * number_of_friends);
    if (remaining_cookies > 0) {
        ESP_LOGI(TAG, "   บวกเศษ: %d + %d = %d", cookies_per_person * number_of_friends, remaining_cookies, total_cookies);
    }
    ESP_LOGI(TAG, "   การหารและการคูณเป็นการดำเนินการตรงข้ามกัน");
    ESP_LOGI(TAG, "");
    
    // เปรียบเทียบการดำเนินการทั้งหมด
    ESP_LOGI(TAG, "📊 สรุปการดำเนินการทั้งหมด:");
    ESP_LOGI(TAG, "   การบวก (+): เพิ่มจำนวน");
    ESP_LOGI(TAG, "   การลบ (-): ลดจำนวน");
    ESP_LOGI(TAG, "   การคูณ (×): บวกซ้ำๆ หลายชุด");
    ESP_LOGI(TAG, "   การหาร (÷): แบ่งออกเป็นกลุ่มเท่าๆ กัน");
    ESP_LOGI(TAG, "");
    
    // แนวคิดขั้นสูง
    ESP_LOGI(TAG, "🎓 แนวคิดขั้นสูง:");
    ESP_LOGI(TAG, "   1. การหารจะได้ผลหาร (quotient) และเศษ (remainder)");
    ESP_LOGI(TAG, "   2. ในภาษา C:");
    ESP_LOGI(TAG, "      ผลหาร = a / b");
    ESP_LOGI(TAG, "      เศษ = a %% b");
    ESP_LOGI(TAG, "   3. การตรวจสอบการหารด้วยศูนย์เป็นสิ่งสำคัญ");
    ESP_LOGI(TAG, "   4. การหารด้วย 1 จะได้ตัวเลขเดิม");
    ESP_LOGI(TAG, "   5. การหารตัวเลขด้วยตัวมันเองจะได้ 1");
    ESP_LOGI(TAG, "");
    
    // สรุปการเรียนรู้
    ESP_LOGI(TAG, "📚 สิ่งที่เรียนรู้:");
    ESP_LOGI(TAG, "   1. การหารเลข (Division): a ÷ b = c");
    ESP_LOGI(TAG, "   2. การใช้ Modulo operator (%%) หาเศษ");
    ESP_LOGI(TAG, "   3. การตรวจสอบการหารด้วยศูนย์");
    ESP_LOGI(TAG, "   4. ความแตกต่างระหว่างหารลงตัวและไม่ลงตัว");
    ESP_LOGI(TAG, "   5. ความสัมพันธ์ระหว่างการหารและการคูณ");
    ESP_LOGI(TAG, "   6. การจัดการกรณีพิเศษ (Error Handling)");
    ESP_LOGI(TAG, "");
    
    ESP_LOGI(TAG, "🎉 จบโปรแกรมแบ่งคุกกี้!");
    ESP_LOGI(TAG, "📖 อ่านต่อในโปรเจคถัดไป: 05_mixed_shopping");
    
    vTaskDelay(2000 / portTICK_PERIOD_MS);
}
