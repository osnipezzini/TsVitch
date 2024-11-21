

#include <iostream>
#include <borealis/core/application.hpp>

#include "activity/live_player_activity.hpp"

#include "activity/setting_activity.hpp"

#include "activity/main_activity.hpp"
#include "activity/hint_activity.hpp"

#include "utils/activity_helper.hpp"
#include "utils/config_helper.hpp"

void Intent::openLive(const std::string& url, const std::string& title, const std::string& groupTitle) {
    auto activity = new LiveActivity(url, title, groupTitle);
    brls::Application::pushActivity(activity, brls::TransitionAnimation::NONE);
    registerFullscreen(activity);
}

void Intent::openSetting() {
    auto activity = new SettingActivity();
    brls::Application::pushActivity(activity);
    registerFullscreen(activity);
}

void Intent::openHint() { brls::Application::pushActivity(new HintActivity()); }

void Intent::openMain() {
    auto activity = new MainActivity();
    brls::Application::pushActivity(activity);
    registerFullscreen(activity);
}

void Intent::_registerFullscreen(brls::Activity* activity) { (void)activity; }
