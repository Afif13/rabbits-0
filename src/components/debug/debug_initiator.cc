#include "rabbits-common.h"
#include "components/debug/debug_initiator.h"

DebugInitiator::DebugInitiator(sc_module_name n) : sc_module(n)
{
}

DebugInitiator::~DebugInitiator()
{
}


uint64_t DebugInitiator::debug_read(uint64_t addr, void *buf, uint64_t size)
{
    tlm::tlm_generic_payload pl;

    pl.set_address(addr);
    pl.set_read();
    pl.set_data_ptr(reinterpret_cast<unsigned char*>(buf));
    pl.set_data_length(size);

    return static_cast<uint64_t>(socket->transport_dbg(pl));
}

uint64_t DebugInitiator::debug_write(uint64_t addr, void *buf, uint64_t size)
{
    tlm::tlm_generic_payload pl;

    pl.set_address(addr);
    pl.set_write();
    pl.set_data_ptr(reinterpret_cast<unsigned char*>(buf));
    pl.set_data_length(size);

    return static_cast<uint64_t>(socket->transport_dbg(pl));
}
