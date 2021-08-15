#ifndef LogitechForceFeedback_H
#define LogitechForceFeedback_H

#include <string>

#include "lgff/LogitechForceFeedbackCommand.h"

namespace lgff {


class LogitechForceFeedback {
public:
    virtual std::string name() const = 0;
    virtual uint16_t vendorId() const = 0;
    virtual uint16_t productId() const = 0;
    
    virtual void sendCommand(const ForceFeedbackCommand command) = 0;

    static inline void copyCommand(const ForceFeedbackCommand src, ForceFeedbackCommand dest) {
        std::copy(src, src + kForceFeedbackCommandSize, dest);
    }
};



class LogitechForceFeedbackWheel: public LogitechForceFeedback {
public:
    virtual uint16_t minWheelRange() const = 0;
    virtual uint16_t maxWheelRange() const = 0;

};



}

#endif