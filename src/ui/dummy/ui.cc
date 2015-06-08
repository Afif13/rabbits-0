#include <cassert>

#include "ui.h"

#define MODNAME "dummy_ui"

#include "rabbits-common.h"
#include "utils/utils.h"

dummy_ui::dummy_ui()
{
}

dummy_ui::~dummy_ui()
{
}

ui_fb* dummy_ui::new_fb(std::string name, const ui_fb_info &info)
{
    dummy_ui_fb *fb = new dummy_ui_fb(info);

    m_fbs.push_back(fb);

    return fb;
}

void dummy_ui::update()
{
}
