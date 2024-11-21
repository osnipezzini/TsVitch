

#include <borealis/core/thread.hpp>
#include <borealis/core/view.hpp>
#include <borealis/core/application.hpp>

#include "utils/gesture_helper.hpp"

#define MAX_DELTA_MOVEMENT 24

#define LONG_TIME_MS 250
#define LONG_TIME_US (LONG_TIME_MS * 1000)

OsdGestureRecognizer::OsdGestureRecognizer(const OsdGestureEvent::Callback& respond) {
    tapEvent.subscribe(respond);
    this->startTime = 0;
    this->endTime   = -1 - LONG_TIME_US;
}

static inline OsdGestureType updateGestureType(OsdGestureType osdGestureType) {
    if (osdGestureType == OsdGestureType::LONG_PRESS_START) {
        return OsdGestureType::LONG_PRESS_CANCEL;
    } else if (osdGestureType == OsdGestureType::LEFT_VERTICAL_PAN_START ||
               osdGestureType == OsdGestureType::LEFT_VERTICAL_PAN_UPDATE) {
        return OsdGestureType::LEFT_VERTICAL_PAN_CANCEL;
    } else if (osdGestureType == OsdGestureType::RIGHT_VERTICAL_PAN_START ||
               osdGestureType == OsdGestureType::RIGHT_VERTICAL_PAN_UPDATE) {
        return OsdGestureType::RIGHT_VERTICAL_PAN_CANCEL;
    } else if (osdGestureType == OsdGestureType::HORIZONTAL_PAN_START ||
               osdGestureType == OsdGestureType::HORIZONTAL_PAN_UPDATE) {
        return OsdGestureType::HORIZONTAL_PAN_CANCEL;
    }
    return osdGestureType;
}

brls::GestureState OsdGestureRecognizer::recognitionLoop(brls::TouchState touch, brls::MouseState mouse,
                                                         brls::View* view, brls::Sound* soundToPlay) {
    brls::TouchPhase phase = touch.phase;
    brls::Point position   = touch.position;

    if (phase == brls::TouchPhase::NONE) {
        position = mouse.position;
        phase    = mouse.leftButton;
    }

    if (!enabled || phase == brls::TouchPhase::NONE) return brls::GestureState::FAILED;

    if (phase != brls::TouchPhase::START) {
        if (this->state == brls::GestureState::INTERRUPTED || this->state == brls::GestureState::FAILED) {
            if (this->state != lastState) {
                this->osdGestureType = updateGestureType(this->osdGestureType);
                this->tapEvent.fire(getCurrentStatus());
            }

            lastState = this->state;
            return this->state;
        }
    }

    switch (phase) {
        case brls::TouchPhase::START:
            brls::Application::giveFocus(view);
            this->startTime = brls::getCPUTimeUsec();
            if (this->startTime - this->endTime < LONG_TIME_US) {
                brls::cancelDelay(iter);
                this->osdGestureType = OsdGestureType::DOUBLE_TAP_START;
            } else {
                this->osdGestureType = OsdGestureType::NONE;
            }

            this->state    = brls::GestureState::UNSURE;
            this->position = position;
            this->tapEvent.fire(getCurrentStatus());
            break;
        case brls::TouchPhase::STAY: {
            auto frame = view->getFrame();

            if (!frame.pointInside(position)) {
                this->state          = brls::GestureState::FAILED;
                this->osdGestureType = updateGestureType(this->osdGestureType);
            } else if (this->osdGestureType == OsdGestureType::NONE) {
                this->delta = position - this->position;
                if (fabs(this->delta.x) > MAX_DELTA_MOVEMENT) {
                    this->osdGestureType = OsdGestureType::HORIZONTAL_PAN_START;
                } else if (fabs(this->delta.y) > MAX_DELTA_MOVEMENT) {
                    if (position.x < frame.getMidX()) {
                        this->osdGestureType = OsdGestureType::LEFT_VERTICAL_PAN_START;
                    } else {
                        this->osdGestureType = OsdGestureType::RIGHT_VERTICAL_PAN_START;
                    }
                } else if (brls::getCPUTimeUsec() - this->startTime > LONG_TIME_US) {
                    this->osdGestureType = OsdGestureType::LONG_PRESS_START;
                } else {
                    break;
                }
            } else if (this->osdGestureType == OsdGestureType::HORIZONTAL_PAN_START ||
                       this->osdGestureType == OsdGestureType::HORIZONTAL_PAN_UPDATE) {
                this->delta          = position - this->position;
                this->deltaX         = delta.x / frame.size.width;
                this->osdGestureType = OsdGestureType::HORIZONTAL_PAN_UPDATE;
            } else if (this->osdGestureType == OsdGestureType::LEFT_VERTICAL_PAN_START ||
                       this->osdGestureType == OsdGestureType::LEFT_VERTICAL_PAN_UPDATE) {
                this->delta          = position - this->position;
                this->deltaY         = -delta.y / frame.size.height;
                this->osdGestureType = OsdGestureType::LEFT_VERTICAL_PAN_UPDATE;
            } else if (this->osdGestureType == OsdGestureType::RIGHT_VERTICAL_PAN_START ||
                       this->osdGestureType == OsdGestureType::RIGHT_VERTICAL_PAN_UPDATE) {
                this->delta          = position - this->position;
                this->deltaY         = -delta.y / frame.size.height;
                this->osdGestureType = OsdGestureType::RIGHT_VERTICAL_PAN_UPDATE;
            } else {
                break;
            }
            this->tapEvent.fire(getCurrentStatus());
            break;
        }

        case brls::TouchPhase::END: {
            this->endTime = brls::getCPUTimeUsec();
            this->state   = brls::GestureState::END;

            switch (this->osdGestureType) {
                case OsdGestureType::DOUBLE_TAP_START:
                    this->osdGestureType = OsdGestureType::DOUBLE_TAP_END;
                    this->tapEvent.fire(getCurrentStatus());
                    break;
                case OsdGestureType::LONG_PRESS_START:
                    this->osdGestureType = OsdGestureType::LONG_PRESS_END;
                    this->tapEvent.fire(getCurrentStatus());
                    break;
                case OsdGestureType::HORIZONTAL_PAN_START:
                case OsdGestureType::HORIZONTAL_PAN_UPDATE:

                    this->endTime        = 0;
                    this->osdGestureType = OsdGestureType::HORIZONTAL_PAN_END;
                    this->tapEvent.fire(getCurrentStatus());
                    break;
                case OsdGestureType::LEFT_VERTICAL_PAN_START:
                case OsdGestureType::LEFT_VERTICAL_PAN_UPDATE:
                    this->endTime        = 0;
                    this->osdGestureType = OsdGestureType::LEFT_VERTICAL_PAN_END;
                    this->tapEvent.fire(getCurrentStatus());
                    break;
                case OsdGestureType::RIGHT_VERTICAL_PAN_START:
                case OsdGestureType::RIGHT_VERTICAL_PAN_UPDATE:
                    this->endTime        = 0;
                    this->osdGestureType = OsdGestureType::RIGHT_VERTICAL_PAN_END;
                    this->tapEvent.fire(getCurrentStatus());
                    break;
                default:
                    this->osdGestureType = OsdGestureType::TAP;
                    brls::cancelDelay(iter);
                    iter = brls::delay(LONG_TIME_MS, [this]() { this->tapEvent.fire(getCurrentStatus()); });
                    break;
            }
            break;
        }
        case brls::TouchPhase::NONE:
            this->state = brls::GestureState::FAILED;
            break;
    }

    lastState = this->state;
    return this->state;
}

OsdGestureStatus OsdGestureRecognizer::getCurrentStatus() {
    return OsdGestureStatus{
        .osdGestureType = this->osdGestureType,
        .state          = this->state,
        .position       = this->position,
        .deltaX         = this->deltaX,
        .deltaY         = this->deltaY,
    };
}