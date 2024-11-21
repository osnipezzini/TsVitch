

#include "utils/event_helper.hpp"
#include "view/mpv_core.hpp"

MPVEvent *EventHelper::getMpvEvent() { return MPVCore::instance().getEvent(); }

CustomEvent *EventHelper::getCustomEvent() { return &customEvent; }

CustomEvent *EventHelper::getSearchEvent() { return &searchEvent; }