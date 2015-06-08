#include <cassert>

#include "ui.h"

#define MODNAME "sdl_ui"

#include "rabbits-common.h"
#include "utils/utils.h"

bool sdl_ui::sdl_inited = false;

void sdl_ui::sdl_cleanup()
{
    SDL_Quit();
    sdl_inited = false;
}

sdl_ui::sdl_ui()
{
    assert(!sdl_ui::sdl_inited);

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE) == -1) {
        EPRINTF("SDL_Init failed\n");
        goto sdl_init_err;
    }

    m_screen = SDL_SetVideoMode(DEFAULT_W, DEFAULT_H, 0, 0);

    if (m_screen == NULL) {
        EPRINTF("SDL_SetVideoMode failed\n");
        goto sdl_screen_err;
    }

    atexit(sdl_cleanup);
    sdl_inited = true;

    m_active_fb = NULL;

    sdl_screen_err: sdl_init_err: return;
}

sdl_ui::~sdl_ui()
{
}

ui_fb* sdl_ui::new_fb(std::string name, const ui_fb_info &info)
{
    sdl_ui_fb *fb = new sdl_ui_fb(info);

    m_fbs.push_back(fb);

    if (m_active_fb == NULL) {
        show_fb(fb);
    }

    return fb;
}

void sdl_ui::update()
{
    sdl_ui_fb *active_fb = static_cast<sdl_ui_fb*>(m_active_fb);
    if (active_fb) {
        if (SDL_BlitSurface(active_fb->get_surface(), NULL, m_screen, NULL)
                == -1) {
            EPRINTF("blit failed: %s\n", SDL_GetError());
        }
        SDL_Flip(m_screen);
    }
}
