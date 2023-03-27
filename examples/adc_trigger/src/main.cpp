// Copyright (c) 2023 lgili
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.



#include <mcal/board.hpp>
#include <mcal/platform/timer/timer_channel_3.hpp>
#include <modm/platform/device.hpp>
using namespace Board;


using Ad1_afe1_ch6 = GpioC31::Ad; 	
using Ad2_afe0_ch0 = GpioD30::Ad; 
using Ad3_afe0_ch8 = GpioA19::Ad; 
using Ad4_afe1_ch1 = GpioC13::Ad; 
using Ad5_afe1_ch5 = GpioC30::Ad; 
using Ad6_afe0_ch6 = GpioA17::Ad; 
using Ad7_afe1_ch3 = GpioC12::Ad; 

uint16_t ad1_raw,ad4_raw,ad5_raw;
double ad1_voltage, ad4_voltage;
uint32_t adc_sequence[3] = {6,1,5};
uint8_t ready = 0;

// use timer channel 3 
MODM_ISR(TC3)
{
	// clear interrupt flags by reading
	(void) TimerChannel3::getInterruptFlags();
	// Led0::toggle();
}

MODM_ISR(AFEC1)
{
	// clear interrupt flags by reading
	(void) Afec1::getInterruptFlags();
	ad1_raw = Afec1::getChannelResult(6);
	ad4_raw = Afec1::getChannelResult(1);
	ad5_raw = Afec1::getChannelResult(5);
	ready = 1;
	Led0::toggle();
}

int main()
{
	Board::initialize();

	MODM_LOG_INFO << "Init \n";
	Afec1::initialize<Board::SystemClock>();
	Afec1::setTrigger(Afec1::Trigger::TIOACH0_AFEC0);
	Afec1::enableUserSequence(adc_sequence, 3);

	Afec1::enableInterrupt(Afec1::InterruptMask::Eoc5);

	Afec1::enableChannel(0);
	Afec1::enableChannel(1);
	Afec1::enableChannel(2);


	// setup timer channel 10 to run interrupt at ~1 Hz from ~32 kHz internal slow clock
	TimerChannel3::initialize();
	TimerChannel3::setClockSource(TimerChannel3::ClockSource::MckDiv32);
	TimerChannel3::setWaveformMode(true);
	// Up-counter, reset on register C compare match
	TimerChannel3::setWaveformSelection(TimerChannel3::WavSel::Up_Rc);

	// Clear output on register A match, set on register C match
	TimerChannel3::setTioaEffects(TimerChannel3::TioEffect::Clear, TimerChannel3::TioEffect::Set);
	
	uint32_t freq = 10e3;
	uint32_t period = (uint32_t) (75e6/32)/freq; 
	TimerChannel3::setRegA(uint32_t(period* 0.1667));
	TimerChannel3::setRegC(uint32_t(period));

	
	TimerChannel3::enableInterrupt(TimerChannel3::Interrupt::RcCompare);
	TimerChannel3::enableInterruptVector(true,1);
	TimerChannel3::enable();
	
	Afec1::enableInterruptVector(true,2);
	TimerChannel3::start();
	
	MODM_LOG_INFO.printf("\n\r--------------------------------------------");
    MODM_LOG_INFO.printf("\n\r        AFEC User Sequence Demo                 ");
    MODM_LOG_INFO.printf("\n\r--------------------------------------------\n\r");
    MODM_LOG_INFO.printf("Ad1 Raw  Ad1 Voltage  Ad4 Raw  Ad4 Voltage \n\r"); 
	
	

	while (true)
	{
		modm::delay(500ms);
		if(ready)
		{
			ad1_voltage = (double)(ad1_raw * 3.3/4095);
			ad4_voltage = (double)(ad4_raw * 3.3/4095);
			MODM_LOG_INFO.printf("%u      %0.2f V       %u      %0.2f V  \t\r", \
                    ad1_raw, ad1_voltage, ad4_raw, ad4_voltage);
			ready = 0;
		}
	}
}