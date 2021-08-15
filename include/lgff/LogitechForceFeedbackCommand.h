#ifndef LogitechForceFeedbackCommand_H
#define LogitechForceFeedbackCommand_H

#include <cstdint>
#include <cstddef>

namespace lgff {



/*
Classic Format
Commands are sent to the device via HID Output Reports.
The command and its parameters is seven bytes.
Byte | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0
0       F3       F2      F1      F0                 CMD
1     FORCE_TYPE or CMD_PARAM
2     Force/Command parameter 1 (or 0x00 if not used)
3     Force/Command parameter 2 (or 0x00 if not used)
4     Force/Command parameter 3 (or 0x00 if not used)
5     Force/Command parameter 4 (or 0x00 if not used)
6     Force/Command parameter 5 (or 0x00 if not used)
*/
inline constexpr size_t kForceFeedbackCommandSize = 7;
using ForceFeedbackCommand = uint8_t[kForceFeedbackCommandSize];


/*
0x00 Download Force
0x01 Download and Play Force
0x02 Play Force
0x03 Stop Force
0x04 Default Spring On
0x05 Default Spring Off
0x06 [reserved, do not use]
0x07 [reserved, do not use]
0x08 Turn on Normal Mode (see CMD 0x0b)
0x09 Set LED
0x0a Set Watchdog
0x0b Turn on Raw Mode (see CMD 0x08)
0x0c Refresh Force
0x0d Fixed Time Loop
0x0e Set Default Spring
0x0f Set Dead Band
0xf8 Extended Command
*/
enum ForceFeedbackCommandType: uint8_t {
    kDownloadForceCmd = 0x00,
    kDownlaodAndPlayForceCmd = 0x01,
    kPlayForceCmd = 0x02,
    kStopForceCmd = 0x03,
    kDefaultSpringOnCmd = 0x04,
    kDefaultSpringOffCmd = 0x05,
    /* 0x06 [reserved, do not use] */
    /* 0x07 [reserved, do not use] */
    kTurnOnNormalModeCmd = 0x08,
    kSetLedCmd = 0x09,
    kSetWatchdogCmd = 0x0a,
    kTurnOnRawModeCmd = 0x0b,
    kRefreshForceCmd = 0x0c,
    kFixedTimeLoopCmd = 0x0d,
    kSetDefaultSpringCmd = 0x0e,
    kSetDeadBandCmd = 0x0f,
    kExtendedCmd = 0xf8
};


/*
0x01 Change Mode to Driving Force Pro
0x02 Change Wheel Range to 200 Degrees
0x03 Change Wheel Range to 900 Degrees
0x09 Change Device Mode
0x0a Revert Identity
0x10 Switch to G25 Identity with USB Detach
0x11 Switch to G25 Identity without USB Detach
0x12 Set RPM LEDs
0x81 Wheel Range Change
*/
enum ForceFeedbackExtendedCommandType: uint8_t {
    kSwitchDeviceModeToDrivingForceProCmd = 0x01,
    kSetWheelRangeTo200DegreesCmd = 0x02,
    kSetWheelRangeTo900DegreesCmd = 0x03,
    kSwitchDeviceModeCmd = 0x09,
    kRevertIdentityCmd = 0x0a,
    kSwitchDeviceModeToG25WithUsbDetachCmd = 0x10,
    kSwitchDeviceModeToG25WithoutUsbDeatchCmd = 0x11,
    kSetRpmLedsCmd = 0x12,
    kSetWheelRangeCmd = 0x81
};

/*
0x00 = Do not revert identity.
0x01 = Revert identity (default)
*/
enum RevertIdentityParameter: uint8_t {
    kDontRevertIdentity = 0x00,
    kRevertIdentity = 0x01
};

/*
0x00 Constant
0x01 Spring
0x02 Damper
0x03 Auto-Centering Spring
0x04 Sawtooth Up
0x05 Sawtooth Down
0x06 Trapezoid
0x07 Rectangle
0x08 Variable
0x09 Ramp
0x0a Square Wave (not implemented on all devices)
0x0b High-Resolution Spring
0x0c High-Resolution Damper
0x0d High-Resolution Auto-Centering Spring
0x0e Friction (not implemented on all devices)
*/
enum ForceFeedbackType: uint8_t {
    kConstantForce = 0x00,
    kSpringForce = 0x01,
    kDamperForce = 0x02,
    kAutoCenteringSpringForce = 0x03,
    kSawtoothUpForce = 0x04,
    kSawtoothDownForce = 0x05,
    kTrapezoidForce = 0x06,
    kRectangleForce = 0x07,
    kVariableForce = 0x08,
    kRampForce = 0x09,
    kSquareWaveForce = 0x0a,
    kHighResolutionSpring = 0x0b,
    kHighResolutionDamper = 0x0c,
    kHighResolutionAutoCenteringSpringForce = 0x0d,
    kFrictionForce = 0x0e
};

/*
Table 26: Spring Force Parameters
Parameter | Value           |    Definition
D1         0...255               Lower limit of central dead band
D2         0...255               Upper limit of central dead band
K1         see Table 27/28       Low (left or push) side spring constant selector
K2         see Table 27/28       High (right or pull) side spring constant selector
S1         0/1                   Low side slope inversion (1 = inverted)
S2         0/1                   High side slope inversion (1 = inverted)
CLIP       0...255               Clip level (maximum force), on either side

Table 27: Spring Coefficients
K    |   Value Spring Coefficient
0x00     1/4 of offset
0x01     1/2 of offset
0x02     3/4 of offset
0x03     Force = offset
0x04     3/2 of offset
0x05     2 times offset
0x06     3 times offset
0x07     4 times offset
*/
struct SpringForceParameter {
    uint8_t d1;
    uint8_t d2;
    uint8_t k1;
    uint8_t k2;
    uint8_t s1;
    uint8_t s2;
    uint8_t clip;
};

/*
0x00 Dead band is off.
0x01 Dead band is on.
*/
enum DeadBandParameter: uint8_t {
    kDeadBandOff = 0x00,
    kDeadBandOn = 0x01
};


}

#endif