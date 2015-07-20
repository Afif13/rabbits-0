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

#ifndef _MEM_DEVICE_H_
#define _MEM_DEVICE_H_

#include "components/rabbits/slave.h"

class memory: public Slave
{
protected:
    uint64_t m_size;
    uint8_t *m_bytes;

    void bus_cb_read(uint64_t addr, uint8_t *data, unsigned int len, bool &bErr);
    void bus_cb_write(uint64_t addr, uint8_t *data, unsigned int len, bool &bErr);

    virtual uint64_t debug_read(uint64_t addr, uint8_t *buf, uint64_t size);
    virtual uint64_t debug_write(uint64_t addr, const uint8_t *buf, uint64_t size);

    virtual bool get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmi_data);

public:
    const sc_time MEM_WRITE_LATENCY;
    const sc_time MEM_READ_LATENCY;

    memory(const char *name, uint64_t size);
    virtual ~memory();
};

#endif
