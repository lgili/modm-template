// Copyright (c) 2023 lgili
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.


#include <mcal/board.hpp>
#include "schedule.hpp"
using namespace Board;



int main()
{
	Board::initialize();

	

	// Use the logging streams to print some messages.
	// Change MODM_LOG_LEVEL above to enable or disable these messages
	MODM_LOG_DEBUG << "debug" << modm::endl;
	MODM_LOG_INFO << "info" << modm::endl;
	MODM_LOG_WARNING << "warning" << modm::endl;
	MODM_LOG_ERROR << "error" << modm::endl;

	uint32_t counter(0);

	os::start_os();

	// should no get here
	MODM_LOG_ERROR << "error, program exit" << modm::endl;

	return 0;
}