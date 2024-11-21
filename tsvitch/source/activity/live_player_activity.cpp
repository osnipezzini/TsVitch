

#include <borealis/core/thread.hpp>
#include <borealis/views/dialog.hpp>

#include "activity/live_player_activity.hpp"
#include "utils/number_helper.hpp"

#include <vector>
#include <chrono>

#include "utils/shader_helper.hpp"
#include "utils/config_helper.hpp"

#include "view/video_view.hpp"

#include "view/grid_dropdown.hpp"
#include "view/qr_image.hpp"
#include "view/mpv_core.hpp"

using namespace brls::literals;

LiveActivity::LiveActivity(const std::string& url, const std::string& title, const std::string& groupTitle) {
    brls::Logger::debug("LiveActivity: create: {}", title);
    this->liveData.url        = url;
    this->liveData.title      = title;
    this->liveData.groupTitle = groupTitle;
    MPVCore::instance().reset();
    ShaderHelper::instance().clearShader(false);
}

void LiveActivity::onContentAvailable() {
    brls::Logger::debug("LiveActivity: onContentAvailable");

    MPVCore::instance().setAspect(
        ProgramConfig::instance().getSettingItem(SettingItem::PLAYER_ASPECT, std::string{"-1"}));

    this->video->registerAction("", brls::BUTTON_B, [this](...) {
        if (this->video->isOSDLock()) {
            this->video->toggleOSD();
        } else {
            if (this->video->getTvControlMode() && this->video->isOSDShown()) {
                this->video->toggleOSD();
                return true;
            }
            brls::Logger::debug("exit live");
            brls::Application::popActivity();
        }
        return true;
    });

    this->video->setLiveMode();
    this->video->hideVideoProgressSlider();

    this->video->hideSubtitleSetting();
    this->video->hideVideoRelatedSetting();
    this->video->hideVideoSpeedButton();
    this->video->hideBottomLineSetting();
    this->video->hideHighlightLineSetting();

    this->video->disableCloseOnEndOfFile();
    this->video->setFullscreenIcon(true);
    this->video->setTitle(liveData.title);

    this->video->setStatusLabelLeft("");
    this->video->setCustomToggleAction([this]() {
        if (MPVCore::instance().isStopped()) {
            this->onLiveData(this->liveData.url);
        } else if (MPVCore::instance().isPaused()) {
            MPVCore::instance().resume();
        } else {
            this->video->showOSD(false);
            MPVCore::instance().pause();
        }
    });

    this->requestData(liveData.url);
}

void LiveActivity::onLiveData(std::string url) {
    brls::Logger::debug("Live stream url: {}", url);

    this->video->setUrl(url);
    return;
}

void LiveActivity::onError(const std::string& error) {
    brls::Logger::error("ERROR request live data: {}", error);
    this->video->showOSD(false);
    this->video->setOnlineCount(error);
    this->retryRequestData();
}

void LiveActivity::retryRequestData() {
    brls::cancelDelay(errorDelayIter);
    errorDelayIter = brls::delay(2000, [this]() {
        if (!MPVCore::instance().isPlaying()) this->requestData(liveData.url);
    });
}

LiveActivity::~LiveActivity() {
    brls::Logger::debug("LiveActivity: delete");

    this->video->stop();

    brls::cancelDelay(toggleDelayIter);
    brls::cancelDelay(errorDelayIter);
}
