#include "ui_fb.h"

#define MODNAME "dummy_ui_fb"
#include "rabbits-common.h"
#include "utils/utils.h"

dummy_ui_fb::dummy_ui_fb(const ui_fb_info & info) :
        ui_fb(info)
{
    set_info(info);
}

void dummy_ui_fb::set_info(const ui_fb_info & info)
{
}

