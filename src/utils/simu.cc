#include "simu.h"

#include "rabbits-common.h"
#include "ui/ui.h"

void simu_manager::start()
{
    while (sc_get_status() != SC_STOPPED) {
        ui::get_ui()->update();
        sc_start(1, SC_MS);
    }
}
