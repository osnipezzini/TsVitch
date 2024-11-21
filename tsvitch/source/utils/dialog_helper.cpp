

#include <borealis/views/dialog.hpp>
#include "utils/dialog_helper.hpp"
#include "utils/config_helper.hpp"

using namespace brls::literals;

void DialogHelper::showCancelableDialog(const std::string& msg, std::function<void(void)> cb) {
    auto dialog = new brls::Dialog(msg);
    dialog->addButton("hints/cancel"_i18n, []() {});
    dialog->addButton("hints/ok"_i18n, [cb]() { cb(); });
    dialog->open();
}

void DialogHelper::quitApp(bool restart) {
    auto dialog = new brls::Dialog("tsvitch/setting/quit_hint"_i18n);
    dialog->addButton("hints/ok"_i18n, [restart]() {
#ifndef IOS
        brls::Box* container = new brls::Box();
        container->setJustifyContent(brls::JustifyContent::CENTER);
        container->setAlignItems(brls::AlignItems::CENTER);
        brls::Label* hint = new brls::Label();
        hint->setFocusable(true);
        hint->setHideHighlight(true);
        hint->setFontSize(32);
        hint->setText("tsvitch/dialog/quit_hint"_i18n);
        container->addView(hint);
        container->setBackgroundColor(brls::Application::getTheme().getColor("brls/background"));
        brls::Application::pushActivity(new brls::Activity(container), brls::TransitionAnimation::NONE);
        brls::Application::getPlatform()->exitToHomeMode(!restart);
        brls::Application::quit();
#endif
    });
    dialog->setCancelable(false);
    dialog->open();
}