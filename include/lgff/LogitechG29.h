#ifndef LogitechG29_H
#define LogitechG29_H

#include <libhid/LibHid.h>

#include "lgff/LogitechForceFeedback.h"


namespace logitech {

struct LogitechG29State {
    uint16_t wheel;
    uint16_t accelerator;
    uint16_t brake;
    uint16_t clutch;

    uint8_t dpad;
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
    int8_t redDial;
};


class LogitechG29: public LogitechForceFeedbackWheel {
protected:
    std::shared_ptr<libhid::HidDevice> mDevice;

public:
    std::string name() const { return "G29 Driving Force Racing Wheel"; };
    uint16_t vendorId() const  { return 0x046du; };
    uint16_t productId() const { return 0xc260u; };
    uint16_t minRange() const { return 40u; };
    uint16_t maxRange() const { return 900u; };

    LogitechG29(int32_t index = 0);
    void setRange(uint16_t range);
    LogitechG29State getState();
};


}

#endif