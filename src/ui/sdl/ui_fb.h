#ifndef _UI_SDL_FB_H
#define _UI_SDL_FB_H

#include <SDL/SDL.h>

#include "ui/ui_fb.h"

class sdl_ui_fb: public ui_fb
{
private:
    void fb_mode_to_sdl_masks(ui_fb_mode_e mode, Uint32 &rmask, Uint32 &gmask,
            Uint32 &bmask, Uint32 &amask, int &byte_per_pix);

protected:
    SDL_Surface * m_fb_surface;

public:
    sdl_ui_fb(const ui_fb_info & info);

    void set_info(const ui_fb_info & info);

    SDL_Surface* get_surface()
    {
        return m_fb_surface;
    }
};

#endif
