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

#ifndef MODM_SAMX7X_DMA_TRANSFER_HPP
#define MODM_SAMX7X_DMA_TRANSFER_HPP

#include <cstddef>
#include <cstdint>
#include <tuple>

#include <mcal/platform/dma/base.hpp>

namespace modm::platform
{

class DmaChannel;

class BlockTransfer : public DmaBase
{
public:
	constexpr uintptr_t
	sourceAddress() const;

	constexpr void
	setSourceAddress(uintptr_t address);

	inline void
	setSourceAddress(const volatile void* address);

	constexpr uintptr_t
	destinationAddress() const;

	constexpr void
	setDestinationAddress(uintptr_t address);

	inline void
	setDestinationAddress(volatile void* address);

	constexpr void
	setDataLength(std::size_t length);

	constexpr std::size_t
	dataLength() const;

	constexpr ChannelConfig_t
	configuration() const;

	constexpr void
	setConfiguration(ChannelConfig_t config);

	constexpr int16_t
	sourceDataStride() const;

	constexpr void
	setSourceDataStride(int16_t stride);

	constexpr int16_t
	destinationDataStride() const;

	constexpr void
	setDestinationDataStride(int16_t stride);

	uintptr_t csa{};
	uintptr_t cda{};
	uint32_t cc{};
	uint32_t cubc{};
	uint32_t cds_msp{};
};

template<typename... Descriptors>
class LinkedListTransfer : public DmaBase
{
public:
	static_assert(sizeof...(Descriptors) > 0);

	using First = std::tuple_element_t<0, std::tuple<Descriptors...>>;
	static_assert(std::is_same_v<First, View2> || std::is_same_v<First, View3>,
		"The first descriptor must be of type 2 or 3");

	constexpr LinkedListTransfer();

	template<std::size_t index, typename... Ds>
	friend auto descriptor(LinkedListTransfer<Ds...>& transfer);

	std::tuple<Descriptors...> descriptors();

	void setCircularMode(bool circular);

private:
	friend DmaChannel;

	std::tuple<typename Descriptors::Data...> descriptors_{};
	static_assert((sizeof(typename Descriptors::Data) + ...) == sizeof(descriptors_));
};

template<std::size_t index, typename... Descriptors>
auto descriptor(LinkedListTransfer<Descriptors...>& transfer);


} // namespace modm::platform

#include "transfer_impl.hpp"

#endif // MODM_SAMX7X_DMA_TRANSFER_HPP
