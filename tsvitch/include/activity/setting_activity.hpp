

#pragma once

#include <borealis/core/activity.hpp>
#include <borealis/core/bind.hpp>

namespace brls {
class RadioCell;
class BooleanCell;
class InputCell;
class Label;
}  // namespace brls

class TextBox;
class BiliSelectorCell;

class SettingActivity : public brls::Activity {
public:
    CONTENT_FROM_XML_RES("activity/setting_activity.xml");

    SettingActivity();

    void onContentAvailable() override;

    ~SettingActivity() override;

private:
    BRLS_BIND(brls::RadioCell, btnTutorialOpenApp, "tools/tutorial_open");
    BRLS_BIND(brls::RadioCell, btnTutorialError, "tools/tutorial_error");
    BRLS_BIND(brls::RadioCell, btnTutorialFont, "tools/tutorial_font");
    BRLS_BIND(brls::RadioCell, btnNetworkChecker, "tools/network_checker");
    BRLS_BIND(brls::RadioCell, btnReleaseChecker, "tools/release_checker");
    BRLS_BIND(brls::RadioCell, btnQuit, "tools/quit");
    BRLS_BIND(brls::RadioCell, btnOpenConfig, "tools/config_dir");
    BRLS_BIND(brls::RadioCell, btnVibrationTest, "tools/vibration_test");
    BRLS_BIND(brls::BooleanCell, btnTls, "setting/network/tls");
    BRLS_BIND(brls::BooleanCell, btnProxy, "setting/network/proxy");
    BRLS_BIND(brls::InputCell, btnM3U8Input, "setting/tools/m3u8/input");
    BRLS_BIND(BiliSelectorCell, selectorLang, "setting/language");
    BRLS_BIND(BiliSelectorCell, selectorTheme, "setting/ui/theme");
    BRLS_BIND(BiliSelectorCell, selectorCustomTheme, "setting/custom/theme");
    BRLS_BIND(BiliSelectorCell, selectorUIScale, "setting/ui/scale");
    BRLS_BIND(BiliSelectorCell, selectorTexture, "setting/image/texture");
    BRLS_BIND(BiliSelectorCell, selectorThreads, "setting/image/threads");
    BRLS_BIND(BiliSelectorCell, selectorKeymap, "setting/keymap");
    BRLS_BIND(brls::BooleanCell, btnKeymapSwap, "setting/keymap_swap");
    BRLS_BIND(brls::BooleanCell, btnOpencc, "setting/opencc");
    BRLS_BIND(brls::BooleanCell, btnQuality, "setting/video/quality");
    BRLS_BIND(brls::BooleanCell, btnHWDEC, "setting/video/hwdec");
    // BRLS_BIND(brls::BooleanCell, btnAutoPlay, "setting/video/auto_play");
    BRLS_BIND(BiliSelectorCell, selectorInmemory, "setting/video/inmemory");
    BRLS_BIND(BiliSelectorCell, selectorFormat, "setting/video/format");
    BRLS_BIND(BiliSelectorCell, selectorCodec, "setting/video/codec");
    BRLS_BIND(BiliSelectorCell, selectorQuality, "setting/audio/quality");
    BRLS_BIND(BiliSelectorCell, selectorFPS, "setting/fps");
    BRLS_BIND(TextBox, labelOpensource, "setting/label/opensource");
    BRLS_BIND(brls::BooleanCell, cellShowBar, "cell/showBottomBar");
    BRLS_BIND(brls::BooleanCell, cellShowFPS, "cell/showFPS");
    BRLS_BIND(brls::BooleanCell, cellTvSearch, "cell/tvSearch");
    BRLS_BIND(brls::BooleanCell, cellTvOSD, "cell/tvOSD");
    BRLS_BIND(brls::BooleanCell, cellFullscreen, "cell/fullscreen");
    BRLS_BIND(BiliSelectorCell, cellOnTopMode, "cell/onTopMode");
    BRLS_BIND(brls::BooleanCell, cellVibration, "cell/gamepadVibration");
    BRLS_BIND(brls::Label, labelAboutVersion, "setting/about/version");
};