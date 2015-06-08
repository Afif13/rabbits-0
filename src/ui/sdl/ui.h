#ifndef _UI_SDL_UI
#define _UI_SDL_UI

#include <SDL/SDL.h>
#include <vector>

#include "ui/ui.h"
#include "ui_fb.h"

class sdl_ui: public ui
{
private:
    static const int DEFAULT_W = 800;
    static const int DEFAULT_H = 600;

    static bool sdl_inited;

    SDL_Surface * m_screen;

    std::vector<sdl_ui_fb*> m_fbs;

protected:
    sdl_ui();

public:
    friend class ui;
    virtual ~sdl_ui();

    ui_fb* new_fb(std::string name, const ui_fb_info &info);

    void update();

    static void sdl_cleanup();
};

#endif
