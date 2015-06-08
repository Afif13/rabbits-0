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

#ifndef _DEBUG_INITIATOR_H
#define _DEBUG_INITIATOR_H

#include "rabbits-common.h"
#include <tlm_utils/simple_initiator_socket.h>

class DebugInitiator : public sc_module {

public:
    DebugInitiator(sc_module_name n);
    virtual ~DebugInitiator();

    uint64_t debug_read(uint64_t addr, void *buf, uint64_t size);
    uint64_t debug_write(uint64_t addr, void *buf, uint64_t size);

    tlm_utils::simple_initiator_socket<DebugInitiator> socket;
};

#endif
