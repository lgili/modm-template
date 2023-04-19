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

#include "usart_1.hpp"

#include <modm/architecture/driver/atomic/queue.hpp>

namespace
{
	static modm::atomic::Queue<uint8_t, 64> rxBuffer;
	static modm::atomic::Queue<uint8_t, 64> txBuffer;
}

MODM_ISR(USART1)
{
	using namespace modm::platform;
	if(Usart1::isReceiveReady()) {
		uint8_t data = (uint8_t)Usart1::Regs()->US_RHR;
		Usart1::read(data);
		rxBuffer.push(data);
	}

	if(Usart1::isTransmitReady()) {
		if(txBuffer.isEmpty()) {
			Usart1::Regs()->US_IDR = US_IDR_TXRDY_Msk;
		} else {
			Usart1::Regs()->US_THR = txBuffer.get();
			txBuffer.pop();
		}
	}
}

namespace modm::platform
{

bool
Usart1::read(uint8_t &dataOut) {
	if(rxBuffer.isEmpty()) {
		return false;
	} else {
		dataOut = rxBuffer.get();
		rxBuffer.pop();
		return true;
	}
}

std::size_t
Usart1::read(uint8_t *data, std::size_t length) {
	uint32_t i = 0;
	for(; i < length; i++) {
		if(rxBuffer.isEmpty()) {
			return i;
		} else {
			data[i] = rxBuffer.get();
			rxBuffer.pop();
		}
	}
	return i;
}

bool
Usart1::write(uint8_t data)
{
	if(txBuffer.isEmpty() && isTransmitReady()) {
		Regs()->US_THR = data;
	} else {
		if(!txBuffer.push(data)) {
			return false;
		}
		// Enable tx interrupt
		Regs()->US_IER = US_IER_TXRDY_Msk;
	}
	return true;
}

std::size_t
Usart1::write(const uint8_t *data, std::size_t length)
{
	uint32_t i = 0;
	for(; i < length; i++) {
		if(!write(data[i])) {
			return i;
		}
	}
	return i;
}

bool
Usart1::isWriteFinished()
{
	return txBuffer.isEmpty() && isTransmitReady();
}

void
Usart1::flushWriteBuffer()
{
	while(!isWriteFinished());
}

void
Usart1::setParity(Parity parity)
{
	Regs()->US_MR = (Regs()->US_MR & ~US_MR_PAR_Msk) | (uint32_t)parity;
}

void
Usart1::setWordLength(WordLength length)
{
	if(length == WordLength::Bit9) {
		Regs()->US_MR |= US_MR_MODE9_Msk;
	} else {
		Regs()->US_MR &= ~US_MR_MODE9_Msk;
		Regs()->US_MR =
			(Regs()->US_MR & ~US_MR_CHRL_Msk)
				| US_MR_CHRL((uint32_t)length);
	}
}
} // namespace modm::platform