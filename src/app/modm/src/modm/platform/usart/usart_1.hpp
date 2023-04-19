/*
 * Copyright (c) 2021, Jeff McBride
 * Copyright (c) 2022, Christopher Durand
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
// ----------------------------------------------------------------------------

#pragma once

#include "usart_base.hpp"
#include <modm/architecture/interface/uart.hpp>
#include <modm/math/algorithm/prescaler.hpp>
#include <modm/platform/gpio/connector.hpp>
#include <modm/platform/clock/clockgen.hpp>

namespace modm::platform
{

/**
 * Universal synchronous asynchronous receiver transmitter (USART1)
 *
 * @author		Jeff McBride
 * @author		Christopher Durand
 * @ingroup		modm_platform_usart modm_platform_usart_1
 */
class Usart1 : public UsartBase, public modm::Uart
{
private:
	// prevent name collision between ::Uart* from SAM header with modm::Uart
	static auto* Regs() { return USART1; }
	friend void ::USART1_IRQHandler();
public:
	static constexpr size_t RxBufferSize = 64;
	static constexpr size_t TxBufferSize = 64;

	template< class... Pins >
	static void
	connect()
	{
		using RxPin = GetPin_t<PeripheralPin::Rx, Pins...>;
		using TxPin = GetPin_t<PeripheralPin::Tx, Pins...>;
		static_assert(
			!std::is_same_v<typename RxPin::Base, typename TxPin::Base>,
			"Rx and Tx cannot use the same pin!");
		using Peripheral = Peripherals::Usart<1>;
		using RxConnector = typename RxPin::template Connector<Peripheral, Peripheral::Rxd<1>>;
		using TxConnector = typename TxPin::template Connector<Peripheral, Peripheral::Txd<1>>;
		RxConnector::connect();
		TxConnector::connect();
	}


	template< class SystemClock, baudrate_t baudrate, percent_t tolerance=pct(1) >
	static inline void
	initialize(
		Parity parity=Parity::Disabled,
		WordLength length=WordLength::Bit8,
		uint8_t irq_priority = 5)
	{
		ClockGen::enable<ClockPeripheral::Usart1>();

		constexpr auto result = Prescaler::from_function(
			SystemClock::Usart1,
			baudrate,
			1,
			65535,
			[](uint32_t x) { return x * 8; }
			);

		Regs()->US_BRGR = result.index;

		// Use 8x oversampling (this affects baud rate generation)
		Regs()->US_MR = US_MR_OVER;
		setParity(parity);
		setWordLength(length);
		Regs()->US_CR = US_CR_RXEN_Msk | US_CR_TXEN_Msk;
		// Enable rx interrupt
		Regs()->US_IER = US_IER_RXRDY_Msk;

		// Enable the IRQ
		NVIC_SetPriority(USART1_IRQn, irq_priority);
		NVIC_EnableIRQ(USART1_IRQn);
	}

	static bool read(uint8_t &dataOut);

	static std::size_t read(uint8_t *data, std::size_t length);

	static bool write(uint8_t data);

	static std::size_t write(const uint8_t *data, std::size_t length);

	static bool isWriteFinished();

	static void flushWriteBuffer();

	static void setParity(Parity parity);

	static void setWordLength(WordLength length);
	static inline bool isTransmitReady() { return Regs()->US_CSR & US_CSR_TXRDY_Msk; }

	static inline bool isReceiveReady() { return Regs()->US_CSR & US_CSR_RXRDY_Msk; }
};

} // namespace modm::platform