#include "generic_subsystem.h"

#define MODNAME "generic-subsystem"
#include "utils/utils.h"

generic_subsystem::generic_subsystem(sc_module_name name) :
        sc_module(name)
{
    m_onoc = new interconnect("interconnect");
}

generic_subsystem::~generic_subsystem()
{
    DPRINTF("Generic subsystem destructor called\n");
    if (m_onoc)
        delete m_onoc;
}

void generic_subsystem::connect_target(slave_device *target, uint64_t addr, uint64_t len) {
    m_targets.push_back(target);
    m_onoc->connect_target<slave_device>(&target->socket, addr, len);
}

void generic_subsystem::connect_initiator(master_device *initiator) {
    m_initiators.push_back(initiator);
    m_onoc->connect_initiator<master_device>(&initiator->socket);
}
