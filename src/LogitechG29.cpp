#include <iostream>

#include "lgff/LogitechG29.h"


namespace lgff {

struct LogitechG29InputReport {
    /* 01 */ uint8_t id; /* report id 0x01 */
    /* 02 */ uint8_t x; /* 0x80 */
    /* 03 */ uint8_t y; /* 0x80 */
    /* 04 */ uint8_t z; /* 0x80 */
    /* 05 */ uint8_t rz; /* 0x80 */
    /* 06 */ uint8_t hatSwitch; /* dpad cross square triangle circle */
    /* 07 */ uint8_t buttons; /* l1 l2 l3 r1 r2 r3 share options */
    /* 08 */ uint8_t buttons2; /* ps */
    /* 09 */ uint8_t rx;
    /* 10 */ uint8_t ry;
    /* 11 */ uint8_t unknown[33];
    /* 44 */ uint8_t wheel[2];
    /* 46 */ uint8_t throttle[2];
    /* 48 */ uint8_t brake[2];
    /* 50 */ uint8_t clutch[2];
    /* 52 */ uint8_t unknown2[3];
    /* 55 */ uint8_t buttons3; /* red rotary dial plus minus */
    /* 56 */ uint8_t unknown3[8];

    static inline constexpr uint8_t kDpadMask = 0x0fu;
    static inline constexpr uint8_t kSquareMask = 0x10u; 
    static inline constexpr uint8_t kCrossMask = 0x20u;
    static inline constexpr uint8_t kCircleMask = 0x40u;
    static inline constexpr uint8_t kTriangleMask = 0x80u;

    static inline constexpr uint8_t kL1Mask = 0x01u;
    static inline constexpr uint8_t kR1Mask = 0x02u;
    static inline constexpr uint8_t kL2Mask = 0x04u;
    static inline constexpr uint8_t kR2Mask = 0x08u;

    static inline constexpr uint8_t kShareMask = 0x10u;
    static inline constexpr uint8_t kOptionsMask = 0x20u;
    static inline constexpr uint8_t kL3Mask = 0x40u;
    static inline constexpr uint8_t kR3Mask = 0x80u;

    static inline constexpr uint8_t kPsMask = 0x01u;

    static inline constexpr uint8_t kRedDialEnterMask = 0x01u;
    static inline constexpr uint8_t kRedDialLeftMask = 0x02u;
    static inline constexpr uint8_t kRedDialRightMask = 0x04u;
    static inline constexpr uint8_t kMinusMask = 0x08u;
    static inline constexpr uint8_t kPlusMask = 0x10u;

    /*
    returns a value between -1.0 and +1.0
    -1.0 corresponds to the left-most wheel position
    +1.0 corresponds to the right-most wheel position
    */
    inline float wheelValue() {
        int32_t intVal = * reinterpret_cast<uint16_t *>(&wheel);
        float fVal = ((intVal * 2 - 0xffff) * 1.0)/ 0xffff;
        return fVal;
    }

    /*
    returns a value between 0.0 and 1.0
    0.0 fully released
    1.0 fully pressed
    */
    inline float throttleValue() {
        int32_t intVal = * reinterpret_cast<uint16_t *>(&throttle);
        float fVal = ((0xffff - intVal) * 1.0) / 0xffff;
        return fVal;
    }

    inline float brakeValue() {
        int32_t intVal = * reinterpret_cast<uint16_t *>(&brake);
        float fVal = ((0xffff - intVal) * 1.0) / 0xffff;
        return fVal;
    }

    inline float clutchValue() {
        int32_t intVal = * reinterpret_cast<uint16_t *>(&clutch);
        float fVal = ((0xffff - intVal) * 1.0) / 0xffff;
        return fVal;
    }

    inline uint8_t dpadValue() {
        uint8_t val = hatSwitch & kDpadMask;
        if(val == 8)
            return 0;
        return val + 1;
    }

    inline uint8_t crossValue() {
        return (hatSwitch & kCrossMask) ? 1 : 0;
    }

    inline uint8_t squareValue() {
        return (hatSwitch & kSquareMask) ? 1 : 0;
    }

    inline uint8_t triangleValue() {
        return (hatSwitch & kTriangleMask) ? 1 : 0;
    }

    inline uint8_t circleValue() {
        return (hatSwitch & kCircleMask) ? 1 : 0;
    }

    inline uint8_t l1Value() {
        return (buttons & kL1Mask) ? 1 : 0;
    }

    inline uint8_t l2Value() {
        return (buttons & kL2Mask) ? 1 : 0;
    }

    inline uint8_t l3Value() {
        return (buttons & kL3Mask) ? 1 : 0;
    }

    inline uint8_t r1Value() {
        return (buttons & kR1Mask) ? 1 : 0;
    }

    inline uint8_t r2Value() {
        return (buttons & kR2Mask) ? 1 : 0;
    }

    inline uint8_t r3Value() {
        return (buttons & kR3Mask) ? 1 : 0;
    }

    inline uint8_t optionsValue() {
        return (buttons & kOptionsMask) ? 1 : 0;
    }

    inline uint8_t shareValue() {
        return (buttons & kShareMask) ? 1 : 0;
    }

    inline uint8_t psValue() {
        return (buttons2 & kPsMask) ? 1 : 0;
    }

    inline uint8_t redDialEnterValue() {
        return (buttons3 & kRedDialEnterMask) ? 1 : 0;
    }

    inline int8_t redDialValue() {
        if(buttons3 & kRedDialLeftMask)
            return -1;
        else if(buttons3 & kRedDialRightMask)
            return 1;
        return 0;
    }

    inline uint8_t plusValue() {
        return (buttons3 & kPlusMask) ? 1 : 0;
    }

    inline uint8_t minusValue() {
        return (buttons3 & kMinusMask) ? 1 : 0;
    }

    LogitechG29State toState() {
        LogitechG29State state = {
            .wheel = wheelValue(),
            .throttle = throttleValue(),
            .brake = brakeValue(),
            .clutch = clutchValue(),
            
            .dpad = dpadValue(),
            .cross = crossValue(),
            .square = squareValue(),
            .triangle = triangleValue(),
            .circle = circleValue(),

            .l1 = l1Value(),
            .l2 = l2Value(),
            .l3 = l3Value(),
            .r1 = r1Value(),
            .r2 = r2Value(),
            .r3 = r3Value(),
            
            .plus = plusValue(),
            .minus = minusValue(),

            .optoins = optionsValue(),
            .share = shareValue(),
            .ps = psValue(),
            .redDialEnter = redDialEnterValue(),
            .redDial = redDialValue()
        };
        return state;
    }
};


LogitechG29::LogitechG29(int32_t index) {
    libhid::HidDeviceFilterArray filters = {
        {
            { libhid::kHidDeviceFilterVendorId, vendorId() },
            { libhid::kHidDeviceFilterProductId, productId() }
        }
    };
    return;
    auto devices = libhid::HidManager::getDevices(filters);
    mDevice = devices[index];

    //sendCommand(kDontRevertIdentityCmd);
    //sendCommand(kSwitchToG29WithUsbDetachCmd);
}

void LogitechG29::sendCommand(const ForceFeedbackCommand cmd) {
    libhid::HidReport report(cmd, cmd + kForceFeedbackCommandSize);
    mDevice->sendOutputReport(report);
}

LogitechG29State LogitechG29::getState() {
    libhid::HidReport report = mDevice->getInputReport();
    LogitechG29InputReport * g29Report = reinterpret_cast<LogitechG29InputReport *>(report.data());
    return g29Report->toState();
}

void LogitechG29::setWheelRange(uint16_t range) {
    range = std::clamp(range, minWheelRange(), maxWheelRange());
    
    ForceFeedbackCommand cmd = {
        kExtendedCmd,
        kSetWheelRangeCmd,
        static_cast<uint8_t>(range & 0x00ffu),
        static_cast<uint8_t>((range & 0xff00u) >> 8),
        0x00,
        0x00,
        0x00
    };
    sendCommand(cmd);
}


void LogitechG29::setRpmLeds(uint8_t leds) {
    ForceFeedbackCommand cmd = {
        kExtendedCmd,
        kSetRpmLedsCmd,
        leds,
        0x00,
        0x00,
        0x00,
        0x00
    };
    sendCommand(cmd);
}

void LogitechG29::setAutocenter() {
    ForceFeedbackCommand cmd = {
        kSetDefaultSpringCmd,
        kHighResolutionAutoCenteringSpringForce,

    };
    sendCommand(cmd);
}

void LogitechG29::setDeadBand(DeadBandParameter param) {
    ForceFeedbackCommand cmd = { kSetDeadBandCmd, param, 0x00, 0x00, 0x00, 0x00, 0x00 };
    sendCommand(cmd);

    bool x= (UINT16_MAX == 0xffff);
}





}