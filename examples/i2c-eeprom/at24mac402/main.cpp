/*
 * Copyright (c) 2023, Christopher Durand
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
// ----------------------------------------------------------------------------

#include <mcal/board.hpp>
#include <mcal/driver/storage/at24mac402.hpp>
#include <array>

using namespace Board;
using namespace modm::literals;

using I2c = I2cMaster0;
using Sda = GpioA3;
using Scl = GpioA4;

// On board AT24MAC402 EEPROM driver example
int main()
{
	Board::initialize();

	MODM_LOG_INFO << "AT24MAC402 Test" << modm::endl;

	I2c::connect<Sda::Twd, Scl::Twck>();
	I2c::initialize<SystemClock, 400_kHz>();

	modm::At24Mac402<I2c> eeprom{0x37};

	MODM_LOG_INFO << "EEPROM detected: " << RF_CALL_BLOCKING(eeprom.ping()) << "\n\n";

	std::array<uint8_t, 6> buffer{};

	// Read pre-programmed MAC address
	bool readSuccess = RF_CALL_BLOCKING(eeprom.readMac(buffer));
	if (readSuccess)
	{
		MODM_LOG_INFO.printf("MAC: %02x:%02x:%02x:%02x:%02x:%02x\n\n",
							 buffer[0], buffer[1], buffer[2],
							 buffer[3], buffer[4], buffer[5]);

	}
	else
	{
		MODM_LOG_INFO << "Reading MAC address from EEPROM failed!\n";
	}

	// Write 4 data bytes to address 0x80
	/*constexpr std::array<uint8_t, 4> data = {0xAA, 0xBB, 0xCC, 0xDD};
	const bool writeSuccess = RF_CALL_BLOCKING(eeprom.write(0x80, data.data(), 4));
	MODM_LOG_INFO << "write successful: " << writeSuccess << "\n\n";*/

	// Read 4 data bytes from address 0x80
	// retry read until device responds after finishing previous write
	readSuccess = false;
	while (!readSuccess)
	{
		readSuccess = RF_CALL_BLOCKING(eeprom.read(0x80, buffer.data(), buffer.size()));
	}
	MODM_LOG_INFO.printf("data: 0x%02x 0x%02x 0x%02x 0x%02x\n\n",
						 buffer[0], buffer[1], buffer[2], buffer[3]);

	while (true)
	{
		Led0::toggle();
		modm::delay(500ms);
	}

	return 0;
}
