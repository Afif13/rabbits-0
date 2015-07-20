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

#ifndef _MASTER_DEVICE_H_
#define _MASTER_DEVICE_H_

#include "rabbits-common.h"

#include <tlm_utils/simple_initiator_socket.h>

class Master: public sc_module
{
protected:
    uint32_t m_node_id;

    void bus_access(tlm::tlm_command cmd, uint64_t addr, uint8_t *data,
                    unsigned int len);

    /* To be overloaded by master devices that want to be informed of memory
     * mapping during end of elaboration */
    virtual void dmi_hint_cb(uint64_t start, uint64_t size, void *data,
                             sc_time read_latency, sc_time write_latency) {}

public:
    tlm_utils::simple_initiator_socket<Master> socket;

    SC_HAS_PROCESS (Master);
    Master(sc_module_name module_name);
    virtual ~Master();

    virtual void bus_read(uint64_t addr, uint8_t *data, unsigned int len);
    virtual void bus_write(uint64_t addr, uint8_t *data, unsigned int len);

    void dmi_hint(uint64_t start, uint64_t size);
};

#endif
