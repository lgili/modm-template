/*
 * Copyright (c) 2023, Luiz Carlos Gili
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

using Ad2_afe0_ch2 = GpioB3::Ad;
using Ad3_afe0_ch8 = GpioA19::Ad;
using Ad1_afe0_ch10 = GpioB0::Ad;

using Buffer = GpioA5;
using Led0 = GpioA0;
// using Led1 = GpioA5

std::array<uint32_t, 3> afec0ResultRaw;
/*
 * DMA linked list transfer
 *
 * Input from AFEC0 channel 2, 8 and 10
 */

using ListTransfer = LinkedListTransfer<Dma::View3>;

ListTransfer prepareTransfer()
{
	ListTransfer transfer;

	// Transfer configuration, set by first descriptor.
	Dma::ChannelConfig_t config;
	Dma::TransferType_t::set(config, Dma::TransferType::Peripheral);
	Dma::PeripheralDirection_t::set(config, Dma::PeripheralDirection::PeripheralToMemory);
	// 32 bit data size
	Dma::DataWidth_t::set(config, Dma::DataWidth::Word);
	// peripherals are connected to DMA AHB interface 1
	Dma::SourceBusInterface_t::set(config, Dma::BusInterface::Bus1);
	// peripherals are connected to DMA AHB interface 1// data is connected to DMA AHB interface 0
	Dma::DestinationBusInterface_t::set(config, Dma::BusInterface::Bus0);
	// No-increment source address after each sample
	Dma::SourceAddressingMode_t::set(config, Dma::AddressingMode::Fixed);
	// Auto-increment destination address after each sample
	Dma::DestinationAddressingMode_t::set(config, Dma::AddressingMode::Incrementing);
	// Transfer is triggered by AFEC1 request
	Dma::DmaRequest_t::set(config, DmaRequests::Afec<0>::Rx);

	auto [d0] = transfer.descriptors();

	// Configure first descriptor (type 3)
	// Set: configuration, source, destination, size
	d0.setConfiguration(config);
	d0.setSourceAddress(&AFEC0->AFEC_LCDR);
	// destination: DAC channel 0 data register
	d0.setDestinationAddress(&afec0ResultRaw[0]);
	d0.setDataLength(afec0ResultRaw.size());

	// Circular mode
	// After the transfer has finished, the sequence automatically starts
	// again with the first descriptor.
	transfer.setCircularMode(true);

	return transfer;
}

DmaChannel channel = Dma::channel(0);
// Transfer object must remain valid while transfer is active
auto transfer = prepareTransfer();
double iGrid_real, vGrid_real, vBus_real;

MODM_ISR(TC0)
{
	// clear interrupt flags by reading
	(void)TimerChannel0::getInterruptFlags();
	Led0::toggle();
}
int main()
{
	Board::initialize();

	// initialize and set trigger to afec0
	Afec0::initialize<Board::SystemClock>();
	Afec0::setTrigger(Afec0::Trigger::TIOACH0_AFEC0);

	// enable channels
	Afec0::enableChannel(2);
	Afec0::enableChannel(8);
	Afec0::enableChannel(10);

	// configure timer 3 trigger AFEC0 readings
	TimerChannel0::initialize();
	TimerChannel0::setClockSource(TimerChannel0::ClockSource::MckDiv32);
	TimerChannel0::setWaveformMode(true);
	// Up-counter, reset on register C compare match
	TimerChannel0::setWaveformSelection(TimerChannel0::WavSel::Up_Rc);

	// Clear output on register A match, set on register C match
	TimerChannel0::setTioaEffects(TimerChannel0::TioEffect::Clear, TimerChannel0::TioEffect::Set);

	// set frequency of timer 3 with random period
	uint32_t freq = 10e3;
	uint32_t period = (uint32_t)(75e6 / 32) / freq;
	TimerChannel0::setRegA(uint32_t(period * 0.1667));
	TimerChannel0::setRegC(uint32_t(period));

	TimerChannel0::enableInterrupt(TimerChannel0::Interrupt::RcCompare);
	TimerChannel0::enableInterruptVector(true, 1);
	TimerChannel0::enable();

	// start timer
	TimerChannel0::start();

	// config dma
	Dma::initialize();

	channel.setTransfer(transfer);
	channel.startTransfer();

	while (true)
	{

		modm::delay(500ms);
		Led0::toggle();
		// ad10_voltage++;
		iGrid_real = (double)(afec0ResultRaw[0] * 3.3 / 4095);
		vGrid_real = (double)(afec0ResultRaw[1] * 3.3 / 4095);
		vBus_real = (double)(afec0ResultRaw[2] * 3.3 / 4095);
	}

	return 0;
}
