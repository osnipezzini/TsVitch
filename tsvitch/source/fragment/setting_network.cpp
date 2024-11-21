

#include <borealis/core/i18n.hpp>
#include <borealis/core/application.hpp>
#include <borealis/core/thread.hpp>
#include <borealis/views/header.hpp>

#include "fragment/setting_network.hpp"
#include "tsvitch.h"

#include "tsvitch/result/setting.h"
#include "utils/number_helper.hpp"
#include "utils/config_helper.hpp"

using namespace brls::literals;

SettingNetwork::SettingNetwork() {
    this->inflateFromXMLRes("xml/fragment/setting_network.xml");
    brls::Logger::debug("Fragment SettingNetwork: create");
    this->networkTest();

    if (brls::Application::getPlatform()->hasWirelessConnection()) {
        labelWIFI->setTextColor(nvgRGB(72, 154, 83));
        labelWIFI->setText("hints/on"_i18n);
    } else {
        labelWIFI->setTextColor(nvgRGB(199, 84, 80));
        labelWIFI->setText("hints/off"_i18n);
    }
    labelIP->setText(brls::Application::getPlatform()->getIpAddress());
#ifdef PS4

    labelDNS->setText(primaryDNSStr + "\n" + secondaryDNSStr);
#else
    labelDNS->setText(brls::Application::getPlatform()->getDnsServer());
#endif

    headerTest->setSubtitle(APPVersion::instance().git_tag);
}

void SettingNetwork::networkTest() {
    CLIENT::get_file_m3u8(
        [this](const auto& result) {
            this->labelTest1->setTextColor(nvgRGB(72, 154, 83));
            this->labelTest1->setText("hints/success"_i18n);
        },
        [this](CLIENT_ERR) {
            this->labelTest1->setTextColor(nvgRGB(199, 84, 80));
            this->labelTest1->setText("hints/failed"_i18n);
        });
}

SettingNetwork::~SettingNetwork() { brls::Logger::debug("Fragment SettingNetwork: delete"); }

brls::View* SettingNetwork::create() { return new SettingNetwork(); }