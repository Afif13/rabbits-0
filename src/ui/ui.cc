#include "ui.h"

#ifdef CONFIG_SDL_UI
# include "sdl/ui.h"
#else
# include "dummy/ui.h"
#endif

#include "rabbits-common.h"

ui * ui::singleton = NULL;

ui * ui::get_ui()
{
    if (ui::singleton == NULL) {
#ifdef CONFIG_SDL_UI
        ui::singleton = new sdl_ui;
#else
        ui::singleton = new dummy_ui;
#endif
    }

    return ui::singleton;
}

void ui::start_ui()
{
    get_ui();
    /* TODO: Idle screen */
}
