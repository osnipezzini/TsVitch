

#pragma once

#include "view/recycling_grid.hpp"

class SVGImage;
class TextBox;

class BaseVideoCard : public RecyclingGridItem {
public:
    void prepareForReuse() override;

    void cacheForReuse() override;

protected:
    BRLS_BIND(brls::Image, picture, "video/card/picture");
};

class RecyclingGridItemLiveVideoCard : public BaseVideoCard {
public:
    RecyclingGridItemLiveVideoCard();

    ~RecyclingGridItemLiveVideoCard() override;

    void setCard(std::string logo, std::string title, std::string groupTitle, std::string chno);

    static RecyclingGridItemLiveVideoCard* create();

private:
    BRLS_BIND(TextBox, labelTitle, "video/card/label/title");
    BRLS_BIND(brls::Label, labelUsername, "video/card/label/username");
    BRLS_BIND(brls::Label, labelCount, "video/card/label/count");
    BRLS_BIND(brls::Label, labelDuration, "video/card/label/duration");
    BRLS_BIND(brls::Box, boxPic, "video/card/pic_box");
    BRLS_BIND(brls::Box, boxHint, "video/card/hint");
    BRLS_BIND(SVGImage, svgUp, "video/svg/up");
};