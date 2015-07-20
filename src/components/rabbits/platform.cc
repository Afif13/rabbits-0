#include "platform.h"

#define MODNAME "platform"
#include "utils/utils.h"

Platform::Platform(sc_module_name name) :
        sc_module(name)
{
    m_interco = new Interconnect<32>("interconnect");
}

Platform::~Platform()
{
    delete m_interco;
}

void Platform::connect_target(Slave *target, uint64_t addr, uint64_t len) {
    m_targets.push_back(target);
    connect_target(&target->socket, addr, len);
}

void Platform::connect_initiator(Master *initiator) {
    m_initiators.push_back(initiator);
    connect_initiator(&initiator->socket);
}

void Platform::end_of_elaboration() {
    std::vector<Master *>::iterator master;
    std::vector<mapping_descr *>::iterator descr;

    for (master = m_initiators.begin(); master != m_initiators.end(); master++) {
        for (descr = m_mappings.begin(); descr != m_mappings.end(); descr++) {
            (*master)->dmi_hint((*descr)->addr, (*descr)->len);
        }
    }
}
