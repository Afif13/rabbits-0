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

/* 
 * This class is a specialised qemu_wrapper<qemu_cpu_arm> that setup the a15
 * private peripherals
 */

#ifndef _QEMU_WRAPPER_CORTEX_A15_H
#define _QEMU_WRAPPER_CORTEX_A15_H

#include "qemu_wrapper.h"
#include "cpu/arm.h"
#include "dev/cortex_a15_priv.h"

class qemu_cortex_a15 : public qemu_wrapper<qemu_cpu_arm>
{
protected:
    /* Cortex-A15 private devices (GIC, generic timers) */
    qemu_cortex_a15_priv priv;

public:
    qemu_cortex_a15(sc_module_name name, int num_cpu, int num_int)
        : qemu_wrapper<qemu_cpu_arm>(name, num_cpu, "cortex-a15")
        , priv("priv", &m_lib, num_int)
    {
        
    }

    qemu_cortex_a15_priv & get_priv() { return priv; }

    virtual ~qemu_cortex_a15() {}

    template<class t_dev> t_dev* create_qdev(sc_module_name n)
    {
        t_dev *ret = qemu_wrapper<qemu_cpu_arm>::create_qdev<t_dev>(n);
        ret->set_int_ctrl(&priv);
        return ret;
    }
};

#endif
