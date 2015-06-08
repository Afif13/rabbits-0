#include <sc_qemu.h>

#include "arm.h"

qemu_cpu_arm::qemu_cpu_arm(sc_module_name n, int cpuid, qemu_lib_wrapper *lib) 
    : qemu_cpu(n, cpuid, lib)
{
}

sc_in<bool> & qemu_cpu_arm::get_line_irq()
{
    /* Mapping with indexes in QEMU
     *
     * We have sc_in<bool> in SystemC world and indexes in QEMU world.
     * <sc_qemu.h> exposes theses indexes as constants so we know how to map
     * them to the corresponding sc_in here.
     *
     * This mapping is then used by the parent class qemu_device_interruptable
     * to update QEMU irq when a sc_in state changes 
     *
     * the get_irq protected method will create the sc_in port on the first call
     */
    return get_irq(SC_QEMU_ARM_IRQ_IRQ);
}

sc_in<bool> & qemu_cpu_arm::get_line_fiq()
{
    return get_irq(SC_QEMU_ARM_IRQ_FIQ);
}
