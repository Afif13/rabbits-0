#ifndef _UI_FB_H
#define _UI_FB_H

enum ui_fb_mode_e
{
    FB_MODE_RGB888 = 0,
    FB_MODE_RGB565,
};

struct ui_fb_info
{
    int physical_w, physical_h;
    int virtual_w, virtual_h;
    int pitch;
    int x_offset, y_offset;
    ui_fb_mode_e mode;
    void * buf;
};

class ui_fb
{
protected:
    ui_fb_info m_info;

public:
    virtual ~ui_fb()
    {
    }

    ui_fb(const ui_fb_info & info)
    {
    }

    virtual void set_info(const ui_fb_info & info) = 0;
};

#endif
