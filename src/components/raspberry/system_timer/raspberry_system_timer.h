/*
 *  Copyright (c) 2015 Clement Deschamps and Luc Michel
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

#ifndef _RASPBERRY_SYSTEM_TIMER_H_
#define _RASPBERRY_SYSTEM_TIMER_H_

#include "components/rabbits/slave.h"

#define TIMER_CS        0x0
#define TIMER_CLO       0x4
#define TIMER_CHI       0x8
#define TIMER_CMP0      0xC
#define TIMER_CMP1      0x10
#define TIMER_CMP2      0x14
#define TIMER_CMP3      0x18

class raspberry_system_timer: public Slave
{
public:
    SC_HAS_PROCESS (raspberry_system_timer);
    raspberry_system_timer(sc_module_name module_name);
    virtual ~raspberry_system_timer();

private:
    void bus_cb_read_32(uint64_t addr, uint32_t *data, bool &bErr);
    void bus_cb_write_32(uint64_t addr, uint32_t *data, bool &bErr);

    void timer_thread();

public:
    //ports
    sc_out<bool> irq;

private:
    double ns_period;
    sc_event ev_wake;
    uint32_t cmp0;
    uint32_t cmp1;
    uint32_t cmp2;
    uint32_t cmp3;
    uint32_t clo;
    uint32_t chi;
    uint32_t cs;

};

#endif

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
