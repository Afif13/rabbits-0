#ifndef _UI_DUMMY_UI
#define _UI_DUMMY_UI

#include <vector>

#include "ui/ui.h"
#include "ui_fb.h"

class dummy_ui: public ui
{
private:
    std::vector<dummy_ui_fb*> m_fbs;

protected:
    dummy_ui();

public:
    friend class ui;
    virtual ~dummy_ui();

    ui_fb* new_fb(std::string name, const ui_fb_info &info);

    void update();
};

#endif
