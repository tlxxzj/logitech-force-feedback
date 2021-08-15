#ifndef LogitechG29_H
#define LogitechG29_H

#include <libhid/LibHid.h>

#include "lgff/LogitechForceFeedback.h"


namespace lgff {

struct LogitechG29State {
    /*
    a value between -1.0 and +1.0
    -1.0 corresponds to the left-most wheel position
    +1.0 corresponds to the right-most wheel position
    */
    float wheel;

    /*
    a value between 0.0 and 1.0
    0.0 fully released
    1.0 fully pressed
    */
    float throttle;
    float brake;
    float clutch;

    /*
    a value between 0 and 8
    0: neutral
    1: up
    2: up and right
    3: right
    4: right and down
    5: down
    6: down and left
    7: left
    8: left and up
    */
    uint8_t dpad;
    
    /*
    a value either 0 or 1
    0 released
    1 pressed
    */
    uint8_t cross;
    uint8_t square;
    uint8_t triangle;
    uint8_t circle;
    
    uint8_t l1;
    uint8_t l2;
    uint8_t l3;
    uint8_t r1;
    uint8_t r2;
    uint8_t r3;
    
    uint8_t plus;
    uint8_t minus;
    
    uint8_t optoins;
    uint8_t share;
    uint8_t ps;
    
    uint8_t redDialEnter;
    
    /*
    a value in (0, -1, 1)
    0 neutral
    -1 left
    1 right
    */
    int8_t redDial;
};


class LogitechG29: public LogitechForceFeedbackWheel {
protected:
    std::shared_ptr<libhid::HidDevice> mDevice;
    

public:
    std::string name() const override { return "G29 Driving Force Racing Wheel"; };
    uint16_t vendorId() const override { return 0x046du; };
    uint16_t productId() const override { return 0xc260u; };
    uint16_t minWheelRange() const override { return 40u; };
    uint16_t maxWheelRange() const override { return 900u; };

    void sendCommand(const ForceFeedbackCommand command) override;

public:

    LogitechG29(int32_t index = 0);
    LogitechG29State getState();
    void setAutocenter();
    void setWheelRange(uint16_t range);
    void setRpmLeds(uint8_t leds);

    void setDeadBand(DeadBandParameter param);
};


}

#endif