// Copyright (c) 2023 lgili
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include <modm/architecture/interface/clock.hpp>
#include <modm/platform.hpp>
#include <modm/debug/logger.hpp>

#define MODM_BOARD_HAS_LOGGER

namespace Board
{
	/// @ingroup mcal_board_a
	/// @{
	using namespace modm::literals;
	using namespace modm::platform;

	struct SystemClock
	{
		// 300 MHz system clock generated by PLLA from external 12 MHz crystal
		static constexpr uint32_t PllAMult = 25;
		static constexpr uint32_t Frequency = 300_MHz;
		static constexpr uint32_t Mck = Frequency / 2; // 150 MHz max.
		static constexpr uint32_t Usart1 = Mck;
		static constexpr uint32_t Spi0 = Mck;
		//	static constexpr uint32_t Usb = 48_MHz;

		static bool inline enable()
		{
			ClockGen::setFlashLatency<Mck>();

			ClockGen::enableMainExternalCrystal<12_MHz>(std::chrono::microseconds{1000});
			ClockGen::selectMainClockSource(MainClockSource::External);

			ClockGen::enablePllA<PllAMult>();
			ClockGen::selectMasterClk<MasterClkSource::PLLA_CLK, MasterClkPrescaler::CLK_1, MasterClkDivider::Div2>();
			ClockGen::updateCoreFrequency<Frequency>();

			return true;
		}
	};

	using Led0 = GpioC8;
	using ButtonSW0 = GpioInverted<GpioA11>;

	using Leds = SoftwareGpioPort<Led0>;

	struct Debug
	{
		using Uart = Usart1;
		using UartTx = GpioB4;
		using UartRx = GpioA21;
	};

	using LoggerDevice = modm::IODeviceWrapper<Debug::Uart, modm::IOBuffer::BlockIfFull>;

	inline void
	initialize()
	{
		// Turn off the watchdog
		WDT->WDT_MR = WDT_MR_WDDIS_Msk;

		SystemClock::enable();
		SysTickTimer::initialize<SystemClock>();

		// Disable JTAG TDI function on debug UART TX pin
		MATRIX->CCFG_SYSIO |= CCFG_SYSIO_SYSIO4;

		Debug::Uart::initialize<SystemClock, 115200>();
		Debug::Uart::connect<Debug::UartTx::Tx, Debug::UartRx::Rx>();

		Leds::setOutput();
		ButtonSW0::setInput(InputType::PullUp);
	}

	/*
	// TODO: usb
	inline void initializeUsbFs()
	{
		//SystemClock::enableUsb();
		//modm::platform::Usb::initialize<Board::SystemClock>();
	}
	*/
	/// @}

} // namespace Board
