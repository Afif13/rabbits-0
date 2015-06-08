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

#include "rabbits-common.h"
#include "slave_device.h"

#define MODNAME "slave-device"
#include "utils/utils.h"

slave_device::slave_device(sc_module_name module_name)
	: sc_module(module_name)
{
	m_write_invalidate = false;
	m_bProcessing_rq = false;
	m_write = false;
	m_node_id = -1;
	m_subsys = NULL;

	socket.register_b_transport(this, &slave_device::b_transport);
	socket.register_transport_dbg(this, &slave_device::transport_dbg);
}

slave_device::~slave_device()
{
}

void slave_device::b_transport(tlm::tlm_generic_payload& trans, sc_time& delay)
{
	m_write = trans.get_command() == tlm::TLM_WRITE_COMMAND;

	if (m_bProcessing_rq) {
		fprintf(stdout,
				"Received a request while processing previous one: drop it\n");
		return;
	}
	m_bProcessing_rq = true;

	bool bErr = false;

	uint64_t addr = trans.get_address();
	uint8_t *buf = reinterpret_cast<uint8_t *>(trans.get_data_ptr());
	uint64_t size = trans.get_data_length();

	switch (trans.get_command()) {
	case tlm::TLM_WRITE_COMMAND:
		bus_cb_write(addr, buf, size, bErr);
		break;
	case tlm::TLM_READ_COMMAND:
		bus_cb_read(addr, buf, size, bErr);
		break;
	default:
		cerr << "Unknown command" << endl;
	}

	// returning synchronous response
	trans.set_response_status(
			bErr ? tlm::TLM_GENERIC_ERROR_RESPONSE : tlm::TLM_OK_RESPONSE);
	m_bProcessing_rq = false;
}

unsigned int slave_device::transport_dbg(tlm::tlm_generic_payload& trans)
{
	uint64_t addr = trans.get_address();
	uint8_t *buf = reinterpret_cast<uint8_t *>(trans.get_data_ptr());
	uint64_t size = trans.get_data_length();

	switch (trans.get_command()) {
	case tlm::TLM_READ_COMMAND:
		return debug_read(addr, buf, size);
	case tlm::TLM_WRITE_COMMAND:
		return debug_write(addr, buf, size);
	default:
		EPRINTF("Unsupported transport debug command type\n");
		exit(1);
	}
}
