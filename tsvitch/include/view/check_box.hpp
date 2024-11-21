

#pragma once

#include <borealis/core/view.hpp>

class BiliCheckBox : public brls::View {
public:
    BiliCheckBox();
    virtual void draw(NVGcontext* vg, float x, float y, float width, float height, brls::Style style,
                      brls::FrameContext* ctx) override;

    void setChecked(bool value);

    bool getChecked();

    static View* create();

protected:
    bool checked = false;
};