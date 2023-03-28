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

using Ad1_afe1_ch6 = GpioC31::Ad;
using Ad2_afe0_ch0 = GpioD30::Ad;
using Ad3_afe0_ch8 = GpioA19::Ad;
using Ad4_afe1_ch1 = GpioC13::Ad;
using Ad5_afe1_ch5 = GpioC30::Ad;
using Ad6_afe0_ch6 = GpioA17::Ad;
using Ad7_afe1_ch3 = GpioC12::Ad;

std::array<uint32_t, 2> afec1ResultRaw;
/*
 * DMA linked list transfer example
 *
 * Input from AFEC1 channel 1 and 6
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
	Dma::DmaRequest_t::set(config, DmaRequests::Afec<1>::Rx);

	auto [d0] = transfer.descriptors();

	// Configure first descriptor (type 3)
	// Set: configuration, source, destination, size
	d0.setConfiguration(config);
	d0.setSourceAddress(&AFEC1->AFEC_LCDR);
	// destination: DAC channel 0 data register
	d0.setDestinationAddress(&afec1ResultRaw[0]);
	d0.setDataLength(afec1ResultRaw.size());

	// Circular mode
	// After the transfer has finished, the sequence automatically starts
	// again with the first descriptor.
	transfer.setCircularMode(true);

	return transfer;
}

DmaChannel channel = Dma::channel(0);
// Transfer object must remain valid while transfer is active
auto transfer = prepareTransfer();
double ad1_voltage, ad4_voltage;

MODM_ISR(TC3)
{
	// clear interrupt flags by reading
	(void)TimerChannel3::getInterruptFlags();
	Led0::toggle();
}
int main()
{
	Board::initialize();

	// initialize and set trigger to afec1
	Afec1::initialize<Board::SystemClock>();
	Afec1::setTrigger(Afec1::Trigger::TIOACH0_AFEC0);

	// enable channels
	Afec1::enableChannel(6);
	Afec1::enableChannel(1);

	// configure timer 3 trigger AFEC1 readings
	TimerChannel3::initialize();
	TimerChannel3::setClockSource(TimerChannel3::ClockSource::MckDiv32);
	TimerChannel3::setWaveformMode(true);
	// Up-counter, reset on register C compare match
	TimerChannel3::setWaveformSelection(TimerChannel3::WavSel::Up_Rc);

	// Clear output on register A match, set on register C match
	TimerChannel3::setTioaEffects(TimerChannel3::TioEffect::Clear, TimerChannel3::TioEffect::Set);

	// set frequency of timer 3 with random period 
	uint32_t freq = 10e3;
	uint32_t period = (uint32_t)(75e6 / 32) / freq;
	TimerChannel3::setRegA(uint32_t(period * 0.1667));
	TimerChannel3::setRegC(uint32_t(period));

	TimerChannel3::enableInterrupt(TimerChannel3::Interrupt::RcCompare);
	TimerChannel3::enableInterruptVector(true, 1);
	TimerChannel3::enable();

	// start timer
	TimerChannel3::start();

	// config dma
	Dma::initialize();

	channel.setTransfer(transfer);
	channel.startTransfer();

	MODM_LOG_INFO.printf("\n\r--------------------------------------------");
	MODM_LOG_INFO.printf("\n\r        AFEC DMA Demo                 ");
	MODM_LOG_INFO.printf("\n\r--------------------------------------------\n\r");
	MODM_LOG_INFO.printf("Ad1 Raw  Ad1 Voltage  Ad4 Raw  Ad4 Voltage \n\r");

	while (true)
	{

		modm::delay(500ms);

		ad1_voltage = (double)(afec1ResultRaw[1] * 3.3 / 4095);
		ad4_voltage = (double)(afec1ResultRaw[0] * 3.3 / 4095);
		MODM_LOG_INFO.printf("%lu      %0.2f V       %lu      %0.2f V  \t\r",
							 afec1ResultRaw[1], ad1_voltage, afec1ResultRaw[0], ad4_voltage);
	}

	return 0;
}
