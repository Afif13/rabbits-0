/*
 *  Copyright (c) 2010 TIMA Laboratory
 *
 *  This file is part of Rabbits.
 *
 *  Rabbits is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Rabbits is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Rabbits.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <cstdio>
#include <cstdlib>
#include "raspberry_system_timer.h"

#define MODNAME "rpi-sys-timer"
#include "utils/utils.h"

#define TIMER_CLOCK_FV 1000000000

raspberry_system_timer::raspberry_system_timer(sc_module_name module_name) :
        Slave(module_name)
{
    ns_period = 100;

    clo = chi = cmp0 = cmp1 = cmp2 = cmp3 = 0;

    SC_THREAD(timer_thread);
}

raspberry_system_timer::~raspberry_system_timer()
{
}

void raspberry_system_timer::bus_cb_write_32(uint64_t ofs, uint32_t *data, bool &bErr)
{
    uint32_t val1 = *data;

    DPRINTF("write to ofs: 0x%x val: 0x%x\n", ofs, val1);

    if (irq) {
        DPRINTF("irq\n");
    }
    switch (ofs) {
    case TIMER_CS:
        if (irq) {
            if (((val1 & 0x1)) && (cs & 0x1)) {
                cs &= 0xFE;
                DPRINTF("event notify\n");
                ev_wake.notify();
            }
            if (((val1 & 0x2) >> 1) && ((cs & 0x2) >> 1)) {
                cs &= 0xFD;
                DPRINTF("event notify\n");
                ev_wake.notify();
            }
            if (((val1 & 0x4) >> 2) && ((cs & 0x4) >> 2)) {
                cs &= 0xFB;
                DPRINTF("event notify\n");
                ev_wake.notify();
            }
            if (((val1 & 0x8) >> 3) && ((cs & 0x8) >> 3)) {
                cs &= 0xF7;
                DPRINTF("event notify\n");
                ev_wake.notify();
            }
            break;
        }
        cs = val1 & 0xF;
        break;

    case TIMER_CLO:
        clo = val1;
        break;

    case TIMER_CHI:
        chi = val1;
        break;

    case TIMER_CMP0:
        cmp0 = val1;
        break;

    case TIMER_CMP1:
        cmp1 = val1;
        break;

    case TIMER_CMP2:
        cmp2 = val1;
        break;

    case TIMER_CMP3:
        cmp3 = val1;
        break;

    default:
        printf("Bad %s::%s ofs=0x%X, data=0x%X-%X!\n", name(),
                __FUNCTION__, (unsigned int) ofs,
                (unsigned int) *((uint32_t *) data + 0),
                (unsigned int) *((uint32_t *) data + 1));
        exit(1);
        break;
    }
    bErr = false;
}

void raspberry_system_timer::bus_cb_read_32(uint64_t ofs, uint32_t *data, bool &bErr)
{
    switch (ofs) {
    case TIMER_CS:
        *data = cs;
        break;

    case TIMER_CLO:
        *data = clo;
        break;

    case TIMER_CHI:
        *data = chi;
        break;

    case TIMER_CMP0:
        *data = cmp0;
        break;

    case TIMER_CMP1:
        *data = cmp1;
        break;

    case TIMER_CMP2:
        *data = cmp2;
        break;

    case TIMER_CMP3:
        *data = cmp3;
        break;
    default:
        printf("Bad %s::%s ofs=0x%X!\n", name(), __FUNCTION__,
                (unsigned int) ofs);
        exit(1);
    }
    bErr = false;
}

void raspberry_system_timer::timer_thread()
{
    while (1) {
        wait(ns_period, SC_NS);

        if (clo == 0xFFFFFFFF) {
            clo = 0;
            chi++;
        } else {
            clo++;
        }

        if (clo != 0) {
            if (clo == cmp0) {
                cs |= 1;
                irq.write(true);
            }
            if (clo == cmp1) {
                cs |= 2;
                irq.write(true);
            }
            if (clo == cmp2) {
                cs |= 4;
                irq.write(true);
            }
            if (clo == cmp3) {
                cs |= 8;
                irq.write(true);
            }
        }
        if (irq) {
            DPRINTF("irq cnt=0x%x\n", clo);
            wait(ev_wake);
            DPRINTF("Wake up after interrupt\n");
            irq.write(false);
        }
    }
}

/*
 * Vim standard variables
 * vim:set ts=4 expandtab tw=80 cindent syntax=c:
 *
 * Emacs standard variables
 * Local Variables:
 * mode: c
 * tab-width: 4
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */
