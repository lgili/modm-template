/*
 * Copyright (c) 2021, Jeff McBride
 * Copyright (c) 2023, Christopher Durand
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
// ----------------------------------------------------------------------------

#pragma once
#include <cstdint>
#include "timer_channel_base.hpp"

#include <modm/platform/clock/clockgen.hpp>

namespace modm::platform
{

/**
 * @brief 		Timer Channel 3
 *
 * Driver for TC1 Channel 0
 *
 * Each TC module provides three independent 16-bit timer channels, and each
 * channel can generate two waveform outputs (TIOA/TIOB). In the datasheet
 * and headers, TCx is sometimes used to refer to a module, and sometimes
 * to a specific channel (for example, TC3_IRQn is the IRQ for TC1 channel 0).
 *
 * This driver does not cover all the functionality of the timer. For example,
 * it does not (yet) support input capture or the block control that allows
 * synchronization of the three timers within a module.
 *
 * To define an interrupt handler for this timer:
 * \code
 * MODM_ISR(TC3)
 * {
 *     // Reading the interrupt flags clears them
 *     TimerChannel3::Interrupt_t flags = TimerChannel3::getInterruptFlags();
 * }
 * \endcode
 *
 * @author Jeff McBride
 * @ingroup modm_platform_timer
 */
class TimerChannel3 : public TimerChannelBase
{
public:
	/// Input clock selection values
	enum class ClockSource : uint32_t
	{
		Pck6 = 0,
		MckDiv8 = 1,
		MckDiv32 = 2,
		MckDiv128 = 3,
		Slck = 4,
		Xc0 = 5,
		Xc1 = 6,
		Xc2 = 7,
		Mck = 0xFFFF'FFFF
	};
	template< class... Pins >
	static void
	connect()
	{
		using TioaPin = GetPin_t<PeripheralPin::Tioa, Pins...>;
		using TiobPin = GetPin_t<PeripheralPin::Tiob, Pins...>;
		using TclkPin = GetPin_t<PeripheralPin::Tclk, Pins...>;
		using Tc = Peripherals::Tc<1>;

		if constexpr (!std::is_void<TioaPin>::value) {
			using TioaConnector = typename TioaPin::template Connector<Tc, Tc::Tioa<0>>;
			TioaConnector::connect();
		}
		if constexpr (!std::is_void<TiobPin>::value) {
			using TiobConnector = typename TiobPin::template Connector<Tc, Tc::Tiob<0>>;
			TiobConnector::connect();
		}
		if constexpr (!std::is_void<TclkPin>::value) {
			using TclkConnector = typename TclkPin::template Connector<Tc, Tc::Tclk<0>>;
			TclkConnector::connect();
		}
	}

	/** Enable the peripheral clock
	 *
	 * This method must be called before any timer channel configuration can
	 * be done.
	 */
	static void
	initialize()
	{
		ClockGen::enable<ClockPeripheral::Tc3>();
	}

	/** Select which clock source will be used for counting
	 */
	static inline void
	setClockSource(ClockSource src)
	{
		if (src == ClockSource::Mck) {
			TC1->TcChannel[0].TC_EMR |= TC_EMR_NODIVCLK;
			return;
		} else {
			uint32_t tmp = TC1->TcChannel[0].TC_CMR & ~(TC_CMR_TCCLKS_Msk);
			tmp |= (uint32_t)src << TC_CMR_TCCLKS_Pos;
			TC1->TcChannel[0].TC_CMR = tmp;

			TC1->TcChannel[0].TC_EMR &= ~TC_EMR_NODIVCLK;
		}
	}

	/** Returns the currently selected clock source
	 */
	static inline ClockSource
	getClockSource()
	{
	if (TC1->TcChannel[0].TC_EMR & TC_EMR_NODIVCLK) {
		return ClockSource::Mck;
	}
		const uint32_t cmr = TC1->TcChannel[0].TC_CMR;
		return (ClockSource)((cmr & TC_CMR_TCCLKS_Msk) >> TC_CMR_TCCLKS_Pos);
	}

	static inline void
	setWaveformSelection(WavSel ws)
	{
		uint32_t cmr = TC1->TcChannel[0].TC_CMR;
		cmr &= ~TC_CMR_WAVSEL_Msk;
		cmr |= (uint32_t)ws << TC_CMR_WAVSEL_Pos;
		TC1->TcChannel[0].TC_CMR = cmr;
	}

	static inline void
	enable()
	{
		TC1->TcChannel[0].TC_CCR = TC_CCR_CLKEN;
	}

	static inline void
	disable()
	{
		TC1->TcChannel[0].TC_CCR = TC_CCR_CLKDIS;
	}

	static inline void
	start()
	{
		softwareTrigger();
	}

	static inline uint16_t
	getValue()
	{
		return TC1->TcChannel[0].TC_CV;
	}

	static inline void
	setValue(uint16_t value)
	{
		TC1->TcChannel[0].TC_CV = value;
	}

	static inline uint16_t
	getRegA()
	{
		return TC1->TcChannel[0].TC_RA;
	}

	static inline void
	setRegA(uint16_t value)
	{
		TC1->TcChannel[0].TC_RA = value;
	}

	static inline uint16_t
	getRegB()
	{
		return TC1->TcChannel[0].TC_RB;
	}

	static inline void
	setRegB(uint16_t value)
	{
		TC1->TcChannel[0].TC_RB = value;
	}

	static inline uint16_t
	getRegC()
	{
		return TC1->TcChannel[0].TC_RC;
	}

	static inline void
	setRegC(uint16_t value)
	{
		TC1->TcChannel[0].TC_RC = value;
	}

	/** Return the frequency of the counter based on current configuration
	 *
	 * This method will return 0 if the counter is clocked from an external
	 * input.
	 */
	template<class SystemClock>
	static inline uint32_t
	getTickFrequency()
	{
		switch(getClockSource())
		{
		case ClockSource::Pck6:
			return SystemClock::Pck6;
		case ClockSource::MckDiv8:
			return SystemClock::Mck / 8;
		case ClockSource::MckDiv32:
			return SystemClock::Mck / 32;
		case ClockSource::MckDiv128:
			return SystemClock::Mck / 128;
		case ClockSource::Slck:
			return SystemClock::Slck;
		case ClockSource::Mck:
			return SystemClock::Mck;
		default:
			return 0; // Clocked externally, so we can't know the frequency
		}
	}

	/** Enable the NVIC IRQ for this timer channel
	 */
	static inline void enableInterruptVector(bool enable, uint32_t priority=5)
	{
		if(enable)
		{
			NVIC_SetPriority(TC3_IRQn, priority);
			NVIC_EnableIRQ(TC3_IRQn);
		} else {
			NVIC_DisableIRQ(TC3_IRQn);
		}
	}

	/** Enable interrupt in peripheral interrupt mask register
	 */
	static inline void enableInterrupt(Interrupt_t interrupts)
	{
		TC1->TcChannel[0].TC_IER = interrupts.value;
	}

	/** Disable interrupt in peripheral interrupt mask register
	 */
	static inline void disableInterrupt(Interrupt_t interrupts)
	{
		TC1->TcChannel[0].TC_IDR = interrupts.value;
	}

	/** Reads the currently pending interrupt flags
	 *
	 * Flags are automatically cleared in hardware when they are read
	 */
	static inline Interrupt_t getInterruptFlags()
	{
		return static_cast<Interrupt_t>(TC1->TcChannel[0].TC_SR & 0xf);
	}

	/** Generate a software trigger event */
	static inline void softwareTrigger()
	{
		TC1->TcChannel[0].TC_CCR = TC_CCR_SWTRG;
	}

	/** Enable or disable waveform mode
	 *
	 * When not in waveform mode, timer operates in capture mode.
	 */
	static inline void setWaveformMode(bool enabled)
	{
		if(enabled) {
			TC1->TcChannel[0].TC_CMR |= TC_CMR_WAVE;
		} else {
			TC1->TcChannel[0].TC_CMR &= ~TC_CMR_WAVE;
		}
	}

	/** Selects which input signal is used as an external event
	 *
	 * Note that by default, TIOB is selected, and this prevents TIOB from
	 * being used as a waveform output. To use it as an output, select one
	 * of the other input options
	 */
	static inline void setExtEventSource(ExtEventSource src)
	{
		uint32_t cmr = TC1->TcChannel[0].TC_CMR;
		cmr &= ~TC_CMR_EEVT_Msk;
		cmr |= (uint32_t)src << TC_CMR_EEVT_Pos;
		TC1->TcChannel[0].TC_CMR = cmr;
	}

	/** Set the effect of events on the TIOA output in waveform mode
	 */
	static inline void setTioaEffects(
		TioEffect raCompare,
		TioEffect rcCompare,
		TioEffect extEvent = TioEffect::None,
		TioEffect swTrig = TioEffect::None)
	{
		uint32_t tmp = TC1->TcChannel[0].TC_CMR;
		tmp &= ~(TC_CMR_ACPA_Msk | TC_CMR_ACPC_Msk | TC_CMR_AEEVT_Msk | TC_CMR_ASWTRG_Msk);
		tmp |= ((uint32_t)raCompare << TC_CMR_ACPA_Pos) |
			((uint32_t)rcCompare << TC_CMR_ACPC_Pos) |
			((uint32_t)extEvent << TC_CMR_AEEVT_Pos) |
			((uint32_t)swTrig << TC_CMR_ASWTRG_Pos);
		TC1->TcChannel[0].TC_CMR = tmp;
	}

	/** Set the effect of events on the TIOB output in waveform mode
	 *
	 * Note that by default TIOB is configured as an input for external events.
	 * To use it as a waveform output, you just select a different external
	 * event input with setExtEventSource.
	 */
	static inline void setTiobEffects(
		TioEffect rbCompare,
		TioEffect rcCompare,
		TioEffect extEvent = TioEffect::None,
		TioEffect swTrig = TioEffect::None)
	{
		uint32_t tmp = TC1->TcChannel[0].TC_CMR;
		tmp &= ~(TC_CMR_BCPB_Msk | TC_CMR_BCPC_Msk | TC_CMR_BEEVT_Msk | TC_CMR_BSWTRG_Msk);
		tmp |= ((uint32_t)rbCompare << TC_CMR_BCPB_Pos) |
			((uint32_t)rcCompare << TC_CMR_BCPC_Pos) |
			((uint32_t)extEvent << TC_CMR_BEEVT_Pos) |
			((uint32_t)swTrig << TC_CMR_BSWTRG_Pos);
		TC1->TcChannel[0].TC_CMR = tmp;
	}

};

}; // namespace modm::platform