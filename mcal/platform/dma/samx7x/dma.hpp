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

#ifndef MODM_SAMX7X_DMA_XDMAC_HPP
#define MODM_SAMX7X_DMA_XDMAC_HPP

#include <cstddef>
#include <cstdint>

#include <mcal/platform/dma/channel.hpp>

namespace modm::platform
{

class Dma : public DmaBase
{
public:
	static void
	initialize();

	static DmaChannel
	channel(uint_fast8_t index);

	static void
	enableInterruptVector(uint32_t priority);

	static void
	disableInterruptVector();
};

} // namespace modm::platform

#endif // MODM_SAMX7X_DMA_XDMAC_HPP
