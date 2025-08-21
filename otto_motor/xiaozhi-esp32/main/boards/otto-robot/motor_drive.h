#ifndef __MOTOR_DRIVE_H__
#define __MOTOR_DRIVE_H__

#include "driver/ledc.h"
#include "esp_log.h"
#include <stdio.h>
#include "math.h"
#include "esp_err.h"

#define LEDC_TIMER                  LEDC_TIMER_2
#define LEDC_MODE                   LEDC_LOW_SPEED_MODE
#define LEDC_DUTY_RES               LEDC_TIMER_13_BIT // Set duty resolution to 13 bits
#define LEDC_FREQUENCY              (4000) // Frequency in Hertz. Set frequency at 4 kHz

#define LEDC_CHANNEL_COUNT          (4)
#define LEDC_M1_CHANNEL_A           LEDC_CHANNEL_1
#define LEDC_M1_CHANNEL_B           LEDC_CHANNEL_2
#define LEDC_M2_CHANNEL_A           LEDC_CHANNEL_3
#define LEDC_M2_CHANNEL_B           LEDC_CHANNEL_4

#define LEDC_M1_CHANNEL_A_IO        (42)
#define LEDC_M1_CHANNEL_B_IO        (41)
#define LEDC_M2_CHANNEL_A_IO        (40)
#define LEDC_M2_CHANNEL_B_IO        (45)

class MotorDrive {
public:
    MotorDrive();
    ~MotorDrive();
    void AttachMotor();
    void DetachMotor();
    void SetLeftMotorSpeed(int speed);
    void SetRightMotorSpeed(int speed);

private:
    bool is_attached_;
    float m1_coefficient = 1.0;
    float m2_coefficient = 1.0;
    // Array of channel configurations for easy iteration
    const ledc_channel_t motor_ledc_channel[LEDC_CHANNEL_COUNT] = {LEDC_M1_CHANNEL_A, LEDC_M1_CHANNEL_B, LEDC_M2_CHANNEL_A, LEDC_M2_CHANNEL_B};
    const int32_t ledc_channel_pins[LEDC_CHANNEL_COUNT] = {LEDC_M1_CHANNEL_A_IO, LEDC_M1_CHANNEL_B_IO, LEDC_M2_CHANNEL_A_IO, LEDC_M2_CHANNEL_B_IO};
};

#endif
