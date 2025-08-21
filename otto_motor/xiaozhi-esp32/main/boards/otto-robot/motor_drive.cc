#include "motor_drive.h"

#include <driver/ledc.h>
#include <esp_timer.h>
#include "esp_err.h"
#include "esp_log.h"

#include <algorithm>
#include <cmath>

#define TAG "MotorDrive"

MotorDrive::MotorDrive() {
    is_attached_ = false;
}

MotorDrive::~MotorDrive() {
    DetachMotor();
}

void MotorDrive::AttachMotor() {
    // Prepare and then apply the LEDC PWM timer configuration
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_MODE,
        .duty_resolution  = LEDC_DUTY_RES,
        .timer_num        = LEDC_TIMER,
        .freq_hz          = LEDC_FREQUENCY,  // Set output frequency at 4 kHz
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    
    for (int i = 0; i < LEDC_CHANNEL_COUNT; i++) {
        ledc_channel_config_t ledc_channel = {
            .gpio_num       = ledc_channel_pins[i],
            .speed_mode     = LEDC_MODE,
            .channel        = motor_ledc_channel[i], // Assuming channel values increment for each new channel
            .intr_type      = LEDC_INTR_DISABLE,
            .timer_sel      = LEDC_TIMER,
            .duty           = 0, // Set duty to 0%
            .hpoint         = 0
        };
        ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
    }

    is_attached_ = true;
}

void MotorDrive::DetachMotor(){
    if (!is_attached_)
        return;

    for(int i = 0; i < LEDC_CHANNEL_COUNT; i++) {
        ESP_ERROR_CHECK(ledc_stop(LEDC_MODE,motor_ledc_channel[i],0));
    }

    is_attached_ = false;
}

void MotorDrive::SetLeftMotorSpeed(int speed) {
    if (speed >= 0) {
        uint32_t m1a_duty = (uint32_t)((speed * m1_coefficient * 8192) / 100);
        ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_M1_CHANNEL_A, m1a_duty));
        ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_M1_CHANNEL_A));
        ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_M1_CHANNEL_B, 0));
        ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_M1_CHANNEL_B));
    } else {
        uint32_t m1b_duty = (uint32_t)((-speed * m1_coefficient * 8192) / 100);
        ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_M1_CHANNEL_A, 0));
        ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_M1_CHANNEL_A));
        ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_M1_CHANNEL_B, m1b_duty));
        ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_M1_CHANNEL_B));
    }
    ESP_LOGE(TAG,"Set Left Motor OK!  speed:%d",speed);
}

void MotorDrive::SetRightMotorSpeed(int speed) {
    if (speed >= 0) {
        uint32_t m2a_duty = (uint32_t)((speed * m2_coefficient * 8192) / 100);
        ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_M2_CHANNEL_A, m2a_duty));
        ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_M2_CHANNEL_A));
        ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_M2_CHANNEL_B, 0));
        ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_M2_CHANNEL_B));
    } else {
        uint32_t m2b_duty = (uint32_t)((-speed * m2_coefficient * 8192) / 100);
        ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_M2_CHANNEL_A, 0));
        ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_M2_CHANNEL_A));
        ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_M2_CHANNEL_B, m2b_duty));
        ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_M2_CHANNEL_B));
    }
    ESP_LOGE(TAG,"Set Left Motor OK!  speed:%d",speed);
}