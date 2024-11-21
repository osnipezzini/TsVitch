

#include <borealis/core/box.hpp>
#include <borealis/core/application.hpp>
#include <borealis/views/label.hpp>

#include "view/user_info.hpp"
#include "view/svg_image.hpp"
#include "utils/image_helper.hpp"

UserInfoView::UserInfoView() {
    this->inflateFromXMLRes("xml/views/user_info.xml");
    this->registerColorXMLAttribute("mainTextColor", [this](NVGcolor value) { this->setMainTextColor(value); });
}

UserInfoView::~UserInfoView() { ImageHelper::clear(this->avatarView); }

void UserInfoView::setUserInfo(const std::string& avatar, const std::string& username, const std::string& misc) {
    this->labeMisc->setText(misc);

    if (username.empty()) {
        this->labelUsername->setHeight(30);
    } else {
        this->labelUsername->setHeight(brls::View::AUTO);
        this->labelUsername->setText(username);
    }

    if (avatar.empty()) {
        this->avatarView->getParent()->setVisibility(brls::Visibility::GONE);
    } else {
        this->avatarView->getParent()->setVisibility(brls::Visibility::VISIBLE);
        ImageHelper::with(this->avatarView)->load(avatar);
    }
}

void UserInfoView::setMainTextColor(NVGcolor color) { this->labelUsername->setTextColor(color); }

brls::View* UserInfoView::create() { return new UserInfoView(); }

brls::Image* UserInfoView::getAvatar() { return this->avatarView; }

brls::Label* UserInfoView::getLabelName() { return this->labelUsername; }

brls::Label* UserInfoView::getLabelMisc() { return this->labeMisc; }

void UserInfoView::setHintType(InfoHintType type) {
    if (type == InfoHintType::NONE) {
        this->boxHint->setVisibility(brls::Visibility::GONE);
        return;
    }

    this->boxHint->setVisibility(brls::Visibility::VISIBLE);
}