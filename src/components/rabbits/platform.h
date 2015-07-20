#ifndef __GENERIC_SUBSYSTEM_H__
#define __GENERIC_SUBSYSTEM_H__

class Platform;

#include "components/rabbits/master.h"
#include "components/rabbits/slave.h"
#include "components/rabbits/interconnect.h"

#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>
#include <vector>

class Platform: public sc_module
{
protected:
    struct mapping_descr {
        uint64_t addr;
        uint64_t len;
    };

    std::vector<Slave *> m_targets;
    std::vector<Master *> m_initiators;
    std::vector<mapping_descr *> m_mappings;
    Interconnect<32> *m_interco;

    virtual void end_of_elaboration();

public:
    Platform(sc_module_name name);
    ~Platform();

    void connect_target(Slave *target, uint64_t addr, uint64_t len);
    
    template <unsigned int BUSWIDTH>
    void connect_target(tlm::tlm_target_socket<BUSWIDTH> *target, uint64_t addr, uint64_t len) {
        mapping_descr *descr = new mapping_descr;

        descr->addr = addr;
        descr->len = len;
        m_mappings.push_back(descr);

        m_interco->connect_target(target, addr, len);
    }

    void connect_initiator(Master *initiator);

    template <unsigned int BUSWIDTH>
    void connect_initiator(tlm::tlm_initiator_socket<BUSWIDTH> *initiator) {
        m_interco->connect_initiator(initiator);
    }

};

#endif /* __GENERIC_SUBSYSTEM_H__ */
