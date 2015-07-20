#include "vcore.h"

#define MODNAME "rpi-vcore"
#include "utils/utils.h"

rpi_vcore::rpi_vcore(sc_module_name mod_name)
	: Master(mod_name)
	, m_mbox("vcore_mailbox")
	, m_fb("vcore_framebuffer")
{
    m_mbox.set_vcore(this);
    m_fb.set_vcore(this);
}

uint32_t rpi_vcore::vcore_to_arm_addr(uint32_t addr)
{
    /* TODO: Vcore MMU translation */
    return addr & ~0xc0000000;
}

uint32_t rpi_vcore::arm_to_vcore_addr(uint32_t addr)
{
    /* TODO: Vcore MMU translation */
    return addr | 0x40000000;
}

void rpi_vcore::bus_read(uint64_t addr, uint8_t *data, unsigned int len)
{
    Master::bus_read(vcore_to_arm_addr(addr), data, len);
}

void rpi_vcore::bus_write(uint64_t addr, uint8_t *data, unsigned int len)
{
    Master::bus_write(vcore_to_arm_addr(addr), data, len);
}

