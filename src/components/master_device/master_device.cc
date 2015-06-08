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

#include "master_device.h"

#define MODNAME "master-device"
#include "utils/utils.h"

master_device::master_device(sc_module_name module_name) :
        sc_module(module_name)
{
    m_node_id = -1;

}

master_device::~master_device(void)
{
}

void master_device::rw(tlm::tlm_command cmd, uint64_t addr, uint8_t *data,
        unsigned int len)
{
    DPRINTF("rw: addr=%p, data=%p, len=%d\n", (void *) addr, data,
            len);

    if (!data) {
        EPRINTF("rw: error, data is null\n");
        exit(1);
    }

    tlm::tlm_generic_payload trans;
    sc_time delay = sc_time(0, SC_NS);

    trans.set_command(cmd);
    trans.set_address(addr);
    trans.set_data_ptr(data);
    trans.set_data_length(len);
    trans.set_byte_enable_ptr(NULL);
    trans.set_byte_enable_length(0);
    trans.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
    trans.set_dmi_allowed(false);
    socket->b_transport(trans, delay);

    if (trans.is_response_error()) {
        SC_REPORT_ERROR("master_device", "response error from b_transport");
    }
}

void master_device::bus_read(uint64_t addr, uint8_t *data, unsigned int len)
{
    rw(tlm::TLM_READ_COMMAND, addr, data, len);
}

void master_device::bus_write(uint64_t addr, uint8_t *data, unsigned int len)
{
    rw(tlm::TLM_WRITE_COMMAND, addr, data, len);
}
