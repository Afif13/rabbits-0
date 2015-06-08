#ifndef _UI_DUMMY_FB_H
#define _UI_DUMMY_FB_H

#include "ui/ui_fb.h"

class dummy_ui_fb: public ui_fb
{
public:
    dummy_ui_fb(const ui_fb_info & info);

    void set_info(const ui_fb_info & info);
};

#endif
