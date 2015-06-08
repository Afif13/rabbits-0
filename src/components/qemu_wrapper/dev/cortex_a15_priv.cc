/*
 *  Copyright (c) 2015 TIMA Laboratory
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

#include <sc_qemu.h>

#include "cortex_a15_priv.h"

qemu_cortex_a15_priv::qemu_cortex_a15_priv(sc_module_name n, qemu_lib_wrapper *lib, int num_irq)
    : qemu_device_interruptable(n, lib)
{
    m_num_irq = num_irq;
    m_dev = lib->qdev_create_cortex_a15_priv(num_irq);
}

qemu_cortex_a15_priv::~qemu_cortex_a15_priv() 
{
    m_lib->qdev_destroy(m_dev);
}

void qemu_cortex_a15_priv::map_gic(uint32_t base_addr) 
{
    m_lib->qdev_mmio_map(m_dev, SC_QDEV_A15PRIV_MMIO_GIC, base_addr);
}

bool qemu_cortex_a15_priv::check_irq_idx(int idx)
{
    return idx < m_num_irq;
}
