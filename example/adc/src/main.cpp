// Copyright (c) 2023 lgili
// 
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// Copyright (c) 2023 lgili
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.


#include <mcal/board.hpp>

using namespace Board;

using Ad2 = GpioD30::Ad; // channel 0, pin AD2 on board
using Ad3 = GpioA19::Ad; // channel 8, pin AD8 on board

int main()
{
	Board::initialize();

	Afec0::initialize<Board::SystemClock>();
	Afec0::connect<Ad2::Ad, Ad3::Ad>();

	while (true)
	{
		MODM_LOG_INFO << "ADC Readings: ";
		MODM_LOG_INFO.printf("%5d ", Afec0::readChannel(Afec0::getPinChannel<Ad2>()));
		MODM_LOG_INFO.printf("%5d ", Afec0::readChannel(Afec0::getPinChannel<Ad3>()));
		MODM_LOG_INFO << modm::endl;

		modm::delay(500ms);
	}
}