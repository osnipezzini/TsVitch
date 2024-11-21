

#pragma once

#include <borealis/core/activity.hpp>
#include <borealis/core/bind.hpp>

class GalleryView;

class HintActivity : public brls::Activity {
public:
    CONTENT_FROM_XML_RES("activity/hint_activity.xml");

    HintActivity();

    void onContentAvailable() override;

    ~HintActivity();

private:
    BRLS_BIND(GalleryView, gallery, "hint/gallery");
};