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

#ifndef _SLAVE_DEVICE_H_
#define _SLAVE_DEVICE_H_

class slave_device;

#include "components/generic_subsystem/generic_subsystem.h"

#include <tlm_utils/simple_target_socket.h>

class slave_device: public sc_module
{
public:
    SC_HAS_PROCESS (slave_device);
    slave_device(sc_module_name module_name);
    virtual ~slave_device();

public:
    virtual void bus_cb_read(uint64_t addr, uint8_t *data, unsigned int len, bool &bErr) {
        switch (len) {
        case 1:
            bus_cb_read_8(addr, (uint8_t *)data, bErr);
            break;
        case 2:
            bus_cb_read_16(addr, (uint16_t *)data, bErr);
            break;
        case 4:
            bus_cb_read_32(addr, (uint32_t *)data, bErr);
            break;
        }
    }

    virtual void bus_cb_read_8(uint64_t addr, uint8_t *value, bool &bErr) {
    	bErr = true;
    }

    virtual void bus_cb_read_16(uint64_t addr, uint16_t *value, bool &bErr) {
    	bErr = true;
    }

    virtual void bus_cb_read_32(uint64_t addr, uint32_t *value, bool &bErr) {
    	bErr = true;
    }

    virtual void bus_cb_write(uint64_t addr, uint8_t *data, unsigned int len, bool &bErr) {
        switch (len) {
        case 1:
            bus_cb_write_8(addr, (uint8_t *)data, bErr);
            break;
        case 2:
            bus_cb_write_16(addr, (uint16_t *)data, bErr);
            break;
        case 4:
            bus_cb_write_32(addr, (uint32_t *)data, bErr);
            break;
        }
    }

    virtual void bus_cb_write_8(uint64_t addr, uint8_t *value, bool &bErr) {
    	bErr = true;
    }

    virtual void bus_cb_write_16(uint64_t addr, uint16_t *value, bool &bErr) {
    	bErr = true;
    }

    virtual void bus_cb_write_32(uint64_t addr, uint32_t *value, bool &bErr) {
    	bErr = true;
    }

    virtual uint64_t debug_read(uint64_t addr, uint8_t* buf, uint64_t size) {
        return 0;
    }

    virtual uint64_t debug_write(uint64_t addr, const uint8_t* buf, uint64_t size) {
        return 0;
    }

    virtual unsigned char *get_mem() {
        return NULL;
    }

    virtual unsigned long get_size() {
        return 0;
    }

    tlm_utils::simple_target_socket<slave_device> socket;

private:
    void b_transport(tlm::tlm_generic_payload& trans, sc_time& delay);
    unsigned int transport_dbg(tlm::tlm_generic_payload& trans);

public:
    bool m_write;
    bool m_bProcessing_rq;
    bool m_write_invalidate;

    // invalidation facilities. valid only if m_write_invalidate = true
    generic_subsystem *m_subsys;

private:
    uint32_t m_node_id;
};

#endif
