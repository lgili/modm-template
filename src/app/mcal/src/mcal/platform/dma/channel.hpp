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

#ifndef MODM_SAMX7X_DMA_CHANNEL_HPP
#define MODM_SAMX7X_DMA_CHANNEL_HPP

#include <cstdint>
#include <mcal/platform/dma/transfer.hpp>

namespace modm::platform
{

class DmaChannel : public DmaBase
{
public:
	DmaChannel(uint8_t index);

	using Handler = void(*)(Interrupt_t);

	void setTransfer(const BlockTransfer& transfer);

	template<typename... Descriptors>
	void setTransfer(LinkedListTransfer<Descriptors...>& transfer);

	void startTransfer();
	void stopTransfer();

	void enableInterrupts();
	void disableInterrupts();

	void enableInterruptFlag(Interrupt_t interrupt);
	void disableInterruptFlag(Interrupt_t interrupt);
	Interrupt_t interruptMask() const;
	Interrupt_t readAndClearFlags();

	void setInterruptHandler(Handler handler);

private:
	uint8_t index_{};
};

} // namespace modm::platform

#include "channel_impl.hpp"

#endif // MODM_SAMX7X_DMA_CHANNEL_HPP
