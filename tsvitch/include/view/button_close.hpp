

#pragma once

#include <borealis/core/box.hpp>
#include <borealis/core/bind.hpp>

namespace brls {
class Label;
}

class ButtonClose : public brls::Box {
public:
    ButtonClose();

    void setTextColor(NVGcolor color);

    ~ButtonClose() override;

    static View* create();

private:
    BRLS_BIND(brls::Label, label, "close/button/text");
};