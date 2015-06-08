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

class master_device: public sc_module
{
public:
    SC_HAS_PROCESS (master_device);
    master_device(sc_module_name module_name);
    virtual ~master_device();

public:
    virtual void bus_read(uint64_t addr, uint8_t *data, unsigned int len);
    virtual void bus_write(uint64_t addr, uint8_t *data, unsigned int len);

public:
    tlm_utils::simple_initiator_socket<master_device> socket;

private:
    uint32_t m_node_id;

    void rw(tlm::tlm_command cmd, uint64_t addr, uint8_t *data,
            unsigned int len);

    void dispatch_response(uint8_t tid, uint8_t be, uint8_t *data);
};

#endif
