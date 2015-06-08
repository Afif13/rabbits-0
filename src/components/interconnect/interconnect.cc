/*
 *  Copyright (c) 2010 TIMA Laboratory
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

#include "interconnect.h"

#define MODNAME "interconnect"
#include "utils/utils.h"

/**
 * Name: interconnect
 * Function: interconnect class constructor. Initialize all masters and slaves
 * Inputs: name: module name
 *         nmasters: master numbre
 *         nslaves : slaves number
 */
interconnect::interconnect(sc_module_name name) : sc_module(name)
{
}

/**
 * Name: ~interconnect
 * Function: interconnect class destructor. Delete all masters and slaves
 */
interconnect::~interconnect()
{
    unsigned int i;

    for (i = 0; i < m_initiators.size(); i++) {
        delete m_initiators[i];
    }

    for (i = 0; i < m_targets.size(); i++) {
        delete m_targets[i];
    }
}


tlm_utils::simple_initiator_socket<interconnect> * 
interconnect::decode_address(sc_dt::uint64 addr, sc_dt::uint64& target_address)
{
    unsigned int i;
    AddressRange *range;

    for (i = 0; i < m_ranges.size(); i++) {
        range = m_ranges[i];
        if (addr >= range->begin && addr < range->end)
            break;
    }
    if (i == m_ranges.size()) {
        return NULL;
    }

    target_address = addr - range->begin;

    return range->socket;
}

void interconnect::b_transport(tlm::tlm_generic_payload& trans,
        sc_time& delay)
{
    sc_dt::uint64 target_address;
    tlm_utils::simple_initiator_socket<interconnect> *target;

    wait(3, SC_NS);

    target = decode_address(trans.get_address(), target_address);
    if (!target) {
        EPRINTF("Cannot find slave at address %08llx\n", trans.get_address());
        exit(1);
    }

    trans.set_address(target_address);

    (*target)->b_transport(trans, delay);

    wait(1, SC_NS);
}

unsigned int interconnect::transport_dbg(tlm::tlm_generic_payload& trans)
{
    sc_dt::uint64 target_address;
    tlm_utils::simple_initiator_socket<interconnect> *target;

    target = decode_address(trans.get_address(), target_address);
    if(!target) {
        return 0;
    }

    trans.set_address(target_address);
    return (*target)->transport_dbg(trans);
}
