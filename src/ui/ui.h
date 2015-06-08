#ifndef _UI_H
#define _UI_H

#include <string>

#include "rabbits-common.h"

#include "ui_fb.h"

class ui
{
private:
    static ui *singleton;

protected:
    ui_fb *m_active_fb;

public:
    virtual ~ui()
    {
    }

    static ui* get_ui();
    static void start_ui();

    virtual ui_fb* new_fb(std::string name, const ui_fb_info &info) = 0;
    virtual void show_fb(ui_fb *fb)
    {
        m_active_fb = fb;
    }

    virtual void update() = 0;
};

#endif
