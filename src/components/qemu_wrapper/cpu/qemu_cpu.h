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

#include <map>
#include <systemc.h>

#include "../qemu_lib_wrapper.h"
#include "../dev/qemu_device.h"

class qemu_cpu : public qemu_device_interruptable {
protected:
    int m_cpuid;

public:
    SC_HAS_PROCESS(qemu_cpu);

    qemu_cpu(sc_module_name n, int cpuid, qemu_lib_wrapper *lib) 
        : qemu_device_interruptable(n, lib)
    {
        m_cpuid = cpuid;
        m_lib = lib;
        m_dev = m_lib->cpu_get_qdev(cpuid);
    }

    virtual sc_event_or_list & get_irq_events(void) {
        return m_irq_events;
    };

    virtual ~qemu_cpu() {}
};

