#ifndef LogitechForceFeedback_H
#define LogitechForceFeedback_H

#include <string>

namespace logitech {

class LogitechForceFeedback {
public:
    virtual std::string name() const = 0;
    virtual uint16_t vendorId() const = 0;
    virtual uint16_t productId() const = 0;
};

class LogitechForceFeedbackWheel: public LogitechForceFeedback {
public:
    virtual uint16_t minRange() const = 0;
    virtual uint16_t maxRange() const = 0;
};



}

#endif