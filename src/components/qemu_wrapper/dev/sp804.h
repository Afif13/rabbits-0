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

#ifndef _QEMU_WRAPPER_DEV_SP804_H
#define _QEMU_WRAPPER_DEV_SP804_H

#include "qemu_device.h"

class qemu_sp804 : public qemu_device
{
public:
    qemu_sp804(sc_module_name n, qemu_lib_wrapper *lib);
    virtual ~qemu_sp804() {}

    void map_mmio(uint32_t addr);
    void connect_irq(int idx);

};

#endif

