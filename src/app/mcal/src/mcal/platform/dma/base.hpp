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

#ifndef MODM_SAMX7X_DMA_BASE_HPP
#define MODM_SAMX7X_DMA_BASE_HPP

#include <array>
#include <cstdint>
#include <modm/architecture/interface/register.hpp>
#include <modm/platform/device.hpp>

namespace modm::platform
{

enum class DmaRequest : uint32_t
{};

struct DmaBase
{
	static constexpr std::size_t ChannelCount{24};

	enum class Interrupt : uint32_t
	{
		EndOfBlock = Bit0,
		EndOfLinkedList = Bit1,
		EndOfDisable = Bit2,
		EndOfFlush = Bit3,
		ReadBusError = Bit4,
		WriteBusError = Bit5,
		RequestOverflowError = Bit6
	};

	MODM_FLAGS32(Interrupt);

	enum class TransferType : uint32_t
	{
		MemoryToMemory = 0,
		Peripheral = XDMAC_CC_TYPE
	};

	enum class PeripheralDirection : uint32_t
	{
		PeripheralToMemory = 0,
		MemoryToPeripheral = XDMAC_CC_DSYNC
	};

	enum class RequestSource : uint32_t
	{
		Hardware = 0,
		Software = XDMAC_CC_SWREQ
	};

	enum class DataWidth : uint32_t
	{
		Byte = 0,
		HalfWord = XDMAC_CC_DWIDTH_HALFWORD,
		Word = XDMAC_CC_DWIDTH_WORD
	};

	enum class BusInterface : uint32_t
	{
		Bus0 = 0,
		Bus1 = 1
	};

	enum class AddressingMode : uint32_t
	{
		Fixed = 0,
		Incrementing = 1,
		Strided = 3
	};

	enum class ChannelConfig : uint32_t
	{};
	MODM_FLAGS32(ChannelConfig);

	using TransferType_t = Configuration<ChannelConfig_t, TransferType, XDMAC_CC_TYPE_Msk>;
	using PeripheralDirection_t = Configuration<ChannelConfig_t, PeripheralDirection, XDMAC_CC_DSYNC_Msk>;
	using RequestSource_t = Configuration<ChannelConfig_t, RequestSource, XDMAC_CC_SWREQ_Msk>;
	using DataWidth_t = Configuration<ChannelConfig_t, DataWidth, XDMAC_CC_DWIDTH_Msk>;
	using SourceBusInterface_t = Configuration<ChannelConfig_t, BusInterface, 0b1, XDMAC_CC_SIF_Pos>;
	using DestinationBusInterface_t = Configuration<ChannelConfig_t, BusInterface, 0b1, XDMAC_CC_DIF_Pos>;
	using SourceAddressingMode_t = Configuration<ChannelConfig_t, AddressingMode, 0b11, XDMAC_CC_SAM_Pos>;
	using DestinationAddressingMode_t = Configuration<ChannelConfig_t, AddressingMode, 0b11, XDMAC_CC_DAM_Pos>;
	using DmaRequest_t = Configuration<ChannelConfig_t, DmaRequest, 0x7f, XDMAC_CC_PERID_Pos>;

	enum class ViewType : uint8_t
	{
		View0 = XDMAC_CNDC_NDVIEW_NDV0,
		View1 = XDMAC_CNDC_NDVIEW_NDV1,
		View2 = XDMAC_CNDC_NDVIEW_NDV2,
		View3 = XDMAC_CNDC_NDVIEW_NDV3
	};

	class ViewBase
	{
	public:
		constexpr ViewBase(uint32_t* data) : data_{data} {}

		constexpr void
		setDataLength(std::size_t length);

		constexpr std::size_t
		dataLength() const;

	protected:
		uint32_t* data_{};
	};

	class View0Dst : public ViewBase
	{
	public:
		using ViewBase::ViewBase;

		using Data = std::array<uint32_t, 3>;
		static constexpr auto Type = ViewType::View0;

		constexpr void
		setDestinationAddress(uintptr_t address);

		constexpr void
		setDestinationAddress(volatile void* data);

		constexpr uintptr_t
		destinationAddress() const;
	};

	class View0Src : public ViewBase
	{
	public:
		using ViewBase::ViewBase;

		using Data = std::array<uint32_t, 3>;
		static constexpr auto Type = ViewType::View0;

		constexpr void
		setSourceAddress(uintptr_t address);

		constexpr void
		setSourceAddress(const volatile void* data);

		constexpr uintptr_t
		sourceAddress() const;
	};

	class View1 : public View0Src
	{
	public:
		using View0Src::View0Src;

		using Data = std::array<uint32_t, 4>;
		static constexpr auto Type = ViewType::View1;

		constexpr void
		setDestinationAddress(uintptr_t address);

		constexpr void
		setDestinationAddress(volatile void* data);

		constexpr uintptr_t
		destinationAddress() const;
	};

	class View2 : public View1
	{
	public:
		using View1::View1;

		using Data = std::array<uint32_t, 5>;
		static constexpr auto Type = ViewType::View2;

		constexpr void
		setConfiguration(ChannelConfig_t configuration);

		constexpr ChannelConfig_t
		configuration() const;

	};

	class View3 : public View2
	{
	public:
		using View2::View2;

		using Data = std::array<uint32_t, 9>;
		static constexpr auto Type = ViewType::View3;

		constexpr int16_t
		sourceDataStride() const;

		constexpr void
		setSourceDataStride(int16_t stride);

		constexpr int16_t
		destinationDataStride() const;

		constexpr void
		setDestinationDataStride(int16_t stride);
	};
};

namespace DmaRequests
{
	struct Hsmci
	{
		static constexpr auto Rx = DmaRequest(0);
		static constexpr auto Tx = DmaRequest(0);
	};

	template<std::size_t Instance>
	struct Spi;

	template<>
	struct Spi<0>
	{
		static constexpr auto Tx = DmaRequest(1);
		static constexpr auto Rx = DmaRequest(2);
	};

	struct Qspi
	{
		static constexpr auto Tx = DmaRequest(5);
		static constexpr auto Rx = DmaRequest(6);
	};

	template<std::size_t Instance>
	struct Usart;

	template<>
	struct Usart<0>
	{
		static constexpr auto Tx = DmaRequest(7);
		static constexpr auto Rx = DmaRequest(8);
	};

	template<>
	struct Usart<1>
	{
		static constexpr auto Tx = DmaRequest(9);
		static constexpr auto Rx = DmaRequest(10);
	};

	template<>
	struct Usart<2>
	{
		static constexpr auto Tx = DmaRequest(11);
		static constexpr auto Rx = DmaRequest(12);
	};

	template<std::size_t Instance>
	struct Pwm;

	template<>
	struct Pwm<0>
	{
		static constexpr auto Tx = DmaRequest(13);
	};

	template<>
	struct Pwm<1>
	{
		static constexpr auto Tx = DmaRequest(39);
	};

	template<std::size_t Instance>
	struct Twihs;

	template<>
	struct Twihs<0>
	{
		static constexpr auto Tx = DmaRequest(14);
		static constexpr auto Rx = DmaRequest(15);
	};

	template<>
	struct Twihs<1>
	{
		static constexpr auto Tx = DmaRequest(16);
		static constexpr auto Rx = DmaRequest(17);
	};

	template<>
	struct Twihs<2>
	{
		static constexpr auto Tx = DmaRequest(18);
		static constexpr auto Rx = DmaRequest(19);
	};

	template<std::size_t Instance>
	struct Uart;

	template<>
	struct Uart<0>
	{
		static constexpr auto Tx = DmaRequest(20);
		static constexpr auto Rx = DmaRequest(21);
	};

	template<>
	struct Uart<1>
	{
		static constexpr auto Tx = DmaRequest(22);
		static constexpr auto Rx = DmaRequest(23);
	};

	template<>
	struct Uart<2>
	{
		static constexpr auto Tx = DmaRequest(24);
		static constexpr auto Rx = DmaRequest(25);
	};

	template<>
	struct Uart<3>
	{
		static constexpr auto Tx = DmaRequest(26);
		static constexpr auto Rx = DmaRequest(27);
	};

	template<>
	struct Uart<4>
	{
		static constexpr auto Tx = DmaRequest(28);
		static constexpr auto Rx = DmaRequest(29);
	};

	struct Dacc
	{
		static constexpr auto Tx = DmaRequest(30);
	};

	struct Ssc
	{
		static constexpr auto Tx = DmaRequest(32);
		static constexpr auto Rx = DmaRequest(33);
	};

	struct Pioa
	{
		static constexpr auto Rx = DmaRequest(34);
	};

	template<std::size_t Instance>
	struct Afec;

	template<>
	struct Afec<0>
	{
		static constexpr auto Rx = DmaRequest(35);
	};

	template<>
	struct Afec<1>
	{
		static constexpr auto Rx = DmaRequest(36);
	};

	struct Aes
	{
		static constexpr auto Tx = DmaRequest(37);
		static constexpr auto Rx = DmaRequest(38);
	};

	template<std::size_t Instance>
	struct Tc;

	template<>
	struct Tc<0>
	{
		static constexpr auto Rx = DmaRequest(40);
	};

	template<>
	struct Tc<1>
	{
		static constexpr auto Rx = DmaRequest(41);
	};

	template<>
	struct Tc<2>
	{
		static constexpr auto Rx = DmaRequest(42);
	};

	template<>
	struct Tc<3>
	{
		static constexpr auto Rx = DmaRequest(43);
	};

}

} // namespace modm::platform

#include "base_impl.hpp"

#endif // MODM_SAMX7X_DMA_BASE_HPP