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
#include <cmath>
#include <numbers>

using namespace Board;

/*
 * DMA linked list transfer example
 *
 * Output two alternating signals on DAC output 0
 */

constexpr auto computeSinTable(float frequency = 1.f)
{
	std::array<uint16_t, 50> data{};
	constexpr auto HalfOutput = ((1 << 12) - 1) / 2; // 12 bit dac
	for (size_t i = 0; i < data.size(); ++i) {
		constexpr auto pi = std::numbers::pi_v<float>;
		data[i] = HalfOutput * (1 + sin(i * (2 * pi * frequency / data.size())));
	}
	return data;
}

constexpr std::array<uint16_t, 50> signal0 = computeSinTable(1.0f);
constexpr std::array<uint16_t, 50> signal1 = computeSinTable(2.0f);

// Manually configure DAC. There is no modm driver yet.
void initializeDac()
{
	// Enable DAC bus clock
	ClockGen::enable<ClockPeripheral::Dacc>();

	// Set up DAC in max speed mode
	// Max DAC clock: 12 MHz, output data rate is DAC clock / 12
	// Best available DAC clock with 150 MHz peripheral clock:
	// 150 MHz / 13 = 11.54 MHz
	// Resulting data rate = peripheral clock / (PRESCALER + 2) / 12 = 961.5 kHz
	DACC->DACC_MR = DACC_MR_PRESCALER(11) | DACC_MR_MAXS0_Msk;
	DACC->DACC_TRIGR = 0;

	// DAC analog bias setting, 3 for 1 Mbps max speed
	DACC->DACC_ACR = DACC_ACR_IBCTLCH0(3) | DACC_ACR_IBCTLCH1(3);

	// enable channel 0
	DACC->DACC_CHER = DACC_CHER_CH0;
}

using ListTransfer = LinkedListTransfer<Dma::View2, Dma::View0Src>;

ListTransfer prepareTransfer()
{
	ListTransfer transfer;

	// Transfer configuration, set by first descriptor.
	// It is not overwritten by the second View0 descriptor.
	Dma::ChannelConfig_t config;
	Dma::TransferType_t::set(config, Dma::TransferType::Peripheral);
	Dma::PeripheralDirection_t::set(config, Dma::PeripheralDirection::MemoryToPeripheral);
	// 16 bit data size
	Dma::DataWidth_t::set(config, Dma::DataWidth::HalfWord);
	// const data in flash, flash is connected to DMA AHB interface 1
	Dma::SourceBusInterface_t::set(config, Dma::BusInterface::Bus1);
	// peripherals are connected to DMA AHB interface 1
	Dma::DestinationBusInterface_t::set(config, Dma::BusInterface::Bus1);
	// Auto-increment source address after each sample
	Dma::SourceAddressingMode_t::set(config, Dma::AddressingMode::Incrementing);
	// Transfer is triggered by DAC channel 0 request
	Dma::DmaRequest_t::set(config, DmaRequests::Dacc::Tx);

	auto [d0, d1] = transfer.descriptors();

	// Configure first descriptor (type 2)
	// Set: configuration, source, destination, size
	d0.setConfiguration(config);
	d0.setSourceAddress(signal0.data());
	// destination: DAC channel 0 data register
	d0.setDestinationAddress(&DACC->DACC_CDR[0]);
	d0.setDataLength(signal0.size());

	// Configure first descriptor (type 0)
	// Update source and size, other parameters remain unchanged
	d1.setSourceAddress(signal1.data());
	d1.setDataLength(signal1.size());

	// Circular mode
	// After the second transfer has finished, the sequence automatically starts
	// again with the first descriptor.
	transfer.setCircularMode(true);

	return transfer;
}

DmaChannel channel = Dma::channel(0);
// Transfer object must remain valid while transfer is active
auto transfer = prepareTransfer();

int main()
{
	Board::initialize();
	initializeDac();

	Dma::initialize();

	channel.setTransfer(transfer);
	channel.startTransfer();

	while (true)
	{
		Led0::toggle();
		// Led1::toggle();
		modm::delay(500ms);

		MODM_LOG_INFO << "ping" << modm::endl;
	}

	return 0;
}
