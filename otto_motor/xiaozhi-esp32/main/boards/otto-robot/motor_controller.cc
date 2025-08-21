#include <esp_log.h>

#include <cstring>

#include "application.h"
#include "board.h"
#include "config.h"
#include "iot/thing.h"
#include "motor_drive.h"
#include "sdkconfig.h"

#define TAG "MotorController"

namespace iot {

class MotorController : public Thing {
private:
    int MotorLeftSpeed;
    int MotorRightSpeed;
    MotorDrive motor_;


public:
    MotorController() : Thing("MotorController","电机的控制器，有左右两个电机。") {
        MotorLeftSpeed = 0;
        MotorRightSpeed = 0;

        motor_.AttachMotor();

        methods_.AddMethod("SetLeftMotorSpeed","设置左边电机速度",ParameterList({
            Parameter("MotorLeftSpeed", "-100到100之间的整数,负数为电机反向转动", kValueTypeNumber, true)
        }), [this](const ParameterList& parameters) {
            MotorLeftSpeed = static_cast<int>(parameters["MotorLeftSpeed"].number());
            motor_.SetLeftMotorSpeed(MotorLeftSpeed);
        });

        methods_.AddMethod("SetRightMotorSpeed","设置右边电机速度",ParameterList({
            Parameter("MotorRightSpeed", "-100到100之间的整数,负数为电机反向转动", kValueTypeNumber, true)
        }), [this](const ParameterList& parameters) {
            MotorRightSpeed = static_cast<int>(parameters["MotorRightSpeed"].number());
            motor_.SetRightMotorSpeed(MotorRightSpeed);
        });
    }
};

}

DECLARE_THING(MotorController);