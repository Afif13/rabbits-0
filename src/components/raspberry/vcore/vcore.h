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

#ifndef _RASPBERRY_VCORE_H_
#define _RASPBERRY_VCORE_H_

#include "components/slave_device/slave_device.h"
#include "components/master_device/master_device.h"

#include "mailbox.h"
#include "fb.h"

class rpi_vcore: public master_device
{
private:
    vcore_mbox m_mbox;
    rpi_vcore_fb m_fb;

public:
    SC_HAS_PROCESS (rpi_vcore);
    rpi_vcore(sc_module_name mod_name);

    virtual ~rpi_vcore() {}

    vcore_mbox * get_mbox() { return &m_mbox; }
    rpi_vcore_fb * get_fb() { return &m_fb; }

    virtual void bus_read(uint64_t addr, uint8_t *data, unsigned int len);
    virtual void bus_write(uint64_t addr, uint8_t *data, unsigned int len);

    uint32_t vcore_to_arm_addr(uint32_t addr);
    uint32_t arm_to_vcore_addr(uint32_t addr);
};

#endif
