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

#include <components/memory/memory.h>
#include <cstdio>
#include <cstdlib>

#include "utils/utils.h"

memory::memory(const char *_name, uint64_t size)
    : slave_device(_name)
{
    m_size = size;
    m_bytes = new unsigned char[m_size];
#ifdef PARANOID_INIT
    memset (m_bytes, 0, m_size);
#endif
    DPRINTF("memory: Memory area location: %p\n", m_bytes);
}


memory::~memory()
{
    if (m_bytes)
        delete[] m_bytes;
}

void memory::bus_cb_read(uint64_t addr, uint8_t *data, unsigned int len, bool &bErr)
{
    if(addr + len >= m_size) {
        printf("memory: error : reading outside bounds\n");
        exit(1);
    }

    memcpy(data, m_bytes + addr, len);

    wait(3, SC_NS);
}

void memory::bus_cb_write(uint64_t addr, uint8_t *data, unsigned int len, bool &bErr)
{
    if(addr + len >= m_size) {
        printf("memory: error : writing outside bounds\n");
        exit(1);
    }

    wait(1, SC_NS);

    memcpy(m_bytes + addr, data, len);
}

uint64_t memory::debug_read(uint64_t addr, uint8_t *buf, uint64_t size)
{
    unsigned int to_read = (addr + size > m_size) ? m_size - addr : size;

    memcpy(buf, m_bytes + addr, to_read);

    return to_read;
}

uint64_t memory::debug_write(uint64_t addr, const uint8_t *buf, uint64_t size)
{
    unsigned int to_write = (addr + size > m_size) ? m_size - addr : size;

    memcpy(m_bytes + addr, buf, to_write);

    return to_write;
}

