/*
 * Copyright (c) 2021, Jeff McBride
 * Copyright (c) 2022, Christopher Durand
 * Copyright (c) 2023, Luiz Carlos Gili
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once

#include <modm/architecture/interface/adc.hpp>
#include <modm/math/algorithm/prescaler.hpp>
#include <modm/platform/clock/clockgen.hpp>
#include <modm/platform/gpio/connector.hpp>

namespace modm::platform
{

/// @ingroup modm_platform_adc
class Afec0 : modm::Adc
{
	static const modm::frequency_t MaxAdcFrequency = modm::MHz(40);

	// Work around a name collision between 'struct modm::Adc' and 'struct Adc'
	// defined in the CMSIS headers
	static inline auto*
	Regs()
	{
		return (::Afec*)AFEC0;
	};

public:
	enum class Channel : uint8_t
	{
		Ch0 = 0,
		Ch1 = 1,
		Ch2 = 2,
		Ch3 = 3,
		Ch4 = 4,
		Ch5 = 5,
		Ch6 = 6,
		Ch7 = 7,
		Ch8 = 8,
		Ch9 = 9,
		Ch10 = 10,
		Ch11 = 11
	};

public:

	/** Trigger to start conversion
	  *
	  * Set the peripheral to start the ADC conversion.
	  */
	 enum class Trigger : uint8_t
	 {
		SOFTWARE = AFEC_MR_TRGEN_DIS,
		ADTRG_AFECx   = AFEC_MR_TRGSEL_AFEC_TRIG0 | AFEC_MR_TRGEN,    /**< (AFEC_MR) AFE0_ADTRG for AFEC0 / AFE1_ADTRG for AFEC1 Position */
		TIOACH0_AFEC0 = AFEC_MR_TRGSEL_AFEC_TRIG1 | AFEC_MR_TRGEN,    /**< (AFEC_MR) TIOA Output of the Timer Counter Channel 0 for AFEC0 */
		TIOACH1_AFEC0 = AFEC_MR_TRGSEL_AFEC_TRIG2 | AFEC_MR_TRGEN,    /**< (AFEC_MR) TIOA Output of the Timer Counter Channel 1 for AFEC0 */
		TIOACH2_AFEC0 = AFEC_MR_TRGSEL_AFEC_TRIG3 | AFEC_MR_TRGEN,    /**< (AFEC_MR) TIOA Output of the Timer Counter Channel 2 for AFEC0 */
		TIOACH3_AFEC1 = AFEC_MR_TRGSEL_AFEC_TRIG1 | AFEC_MR_TRGEN,    /**< (AFEC_MR) TIOA Output of the Timer Counter Channel 3 for AFEC1 */
		TIOACH4_AFEC1 = AFEC_MR_TRGSEL_AFEC_TRIG2 | AFEC_MR_TRGEN,    /**< (AFEC_MR) TIOA Output of the Timer Counter Channel 4 for AFEC1 */
		TIOACH5_AFEC1 = AFEC_MR_TRGSEL_AFEC_TRIG3 | AFEC_MR_TRGEN,    /**< (AFEC_MR) TIOA Output of the Timer Counter Channel 5 for AFEC1 */
		PWM0LINE0_AFEC0	  = AFEC_MR_TRGSEL_AFEC_TRIG4 | AFEC_MR_TRGEN,    /**< (AFEC_MR) PWM0 event line 0 for AFEC0 */
		PWM1LINE0_AFEC1	  = AFEC_MR_TRGSEL_AFEC_TRIG4 | AFEC_MR_TRGEN,    /**< (AFEC_MR) PWM1 event line 0 for AFEC1 */
		PWM0LINE1_AFEC0	  = AFEC_MR_TRGSEL_AFEC_TRIG5 | AFEC_MR_TRGEN,    /**< (AFEC_MR) PWM0 event line 1 for AFEC0 */
		PWM1LINE1_AFEC1	  = AFEC_MR_TRGSEL_AFEC_TRIG5 | AFEC_MR_TRGEN,    /**< (AFEC_MR) PWM1 event line 1 for AFEC1 */
		FREERUN = 0xFF,
	 };

	enum class InterruptMask : uint32_t
	{
		Eoc0 = (1U << 0U),
		Eoc1 = (1U << 1U),
		Eoc2 = (1U << 2U),
		Eoc3 = (1U << 3U),
		Eoc4 = (1U << 4U),
		Eoc5 = (1U << 5U),
		Eoc6 = (1U << 6U),
		Eoc7 = (1U << 7U),
		Eoc8 = (1U << 8U),
		Eoc9 = (1U << 9U),
		Eoc10 = (1U << 10U),
		Eoc11 = (1U << 11U),
		Compe = (1U << 26U)
	};

	// start inherited documentation
	template<class Pin, class... Pins>
	static inline void
	connect()
	{
		// Pins are automatically connected to the ADC when they are enabled,
		// so all this does is set the pin mode to input.
		using Connector = typename Pin::template Connector<Peripherals::Afec<0>, Peripherals::Afec<0>::Ad>;
		static_assert(Connector::PinSignal::AdcChannel >= 0, "Pin cannot be used as ADC input");
		Pin::setInput();

		// Call recursively for all Pins
		if constexpr (sizeof...(Pins)) { connect<Pins...>(); }
	}

	template<class SystemClock, frequency_t frequency = MHz(40), percent_t tolerance = pct(10)>
	static inline void
	initialize()
	{
		constexpr auto result = modm::Prescaler::from_function(
			SystemClock::Frequency,                 // input frequency
			frequency,                              // desired adc frequency
			0,                                      // lowest prescaler value
			255,                                    // highest prescaler value
			[](uint32_t x) { return (x + 1); }      // transform function
		);
		static_assert(result.frequency <= MaxAdcFrequency,
					  "Generated ADC frequency is above maximum frequency!");
		assertBaudrateInTolerance<result.frequency, frequency, tolerance>();

		ClockGen::enable<ClockPeripheral::Afec0>();

		/* Reset and configure the AFEC module */
		Regs()->AFEC_CR = AFEC_CR_SWRST;

		Regs()->AFEC_MR =
			AFEC_MR_PRESCAL(result.index) |
			// 2: recommended value according to datasheet
			AFEC_MR_TRANSFER(2) |
			// The datasheet states TRACKTIM should be set to 15 AFE clock cycles.
			// According to app note 44046 this is achieved with a value of 14.
			// If the datasheets guidance is followed to not change this value the
			// ADC reads wrong values half of the time.
			// Also, none of the 3 vendor HALs use the reset value of 0.
			AFEC_MR_TRACKTIM(15) |
			AFEC_MR_ONE; // reserved, must always be set
		// Enable PGAs and set up biasing
		Regs()->AFEC_ACR = AFEC_ACR_PGA1EN | AFEC_ACR_PGA0EN |
			AFEC_ACR_IBCTL((result.frequency >= MHz(20) ? 0b11 : 0b10));

		// set 10-bit offset DACs to zero offset (value 512, mid scale)
		for (int channel = 0; channel < 12; ++channel) {
			Regs()->AFEC_CSELR = channel; // select channel of COCR register
			Regs()->AFEC_COCR = 512;
		}
	}

	static inline void
	startConversion()
	{
		Regs()->AFEC_CR = AFEC_CR_START;
	}

	static inline bool
	isConversionFinished()
	{
		return Regs()->AFEC_ISR & AFEC_ISR_DRDY;
	}

	static inline uint16_t
	getValue()
	{
		return (uint16_t)(Regs()->AFEC_LCDR & 0xffff);
	}

	static inline uint16_t
	getChannelResult(uint8_t channel)
	{
		Regs()->AFEC_CSELR = (uint8_t)channel;
		return (uint16_t)(Regs()->AFEC_CDR);
	}

	static inline uint16_t
	readChannel(uint8_t channel)
	{
		if (!setChannel(channel)) return 0;

		startConversion();
		while (!isConversionFinished()) {}

		return getValue();
	}

	static inline bool
	setChannel(Channel channel)
	{
		return setChannel((uint8_t)channel);
	}

	static inline bool
	setChannel(uint8_t channel)
	{
		if (channel >= 12) return false;
		Regs()->AFEC_CHDR = (1u << 12) - 1u;
		Regs()->AFEC_CHER = (1 << channel);
		return true;
	}

	static inline bool
	enableChannel(uint8_t channel)
	{
		if (channel >= 12) return false;
		Regs()->AFEC_CHER = (1 << channel);
		return true;
	}

	static inline void
	enableFreeRunningMode()
	{
		Regs()->AFEC_MR |= AFEC_MR_FREERUN;
	}

	static inline void
	disableFreeRunningMode()
	{
		Regs()->AFEC_MR &= ~AFEC_MR_FREERUN;
	}

	/* Configure the user defined conversion sequence */
	static inline void
	enableUserSequence(uint32_t *channelList, uint8_t numChannel)
	{
		uint8_t channelIndex;
		Regs()->AFEC_SEQ1R = 0U;
		Regs()->AFEC_SEQ2R = 0U;
		Regs()->AFEC_MR |= AFEC_MR_USEQ_Msk;
		constexpr uint8_t AFEC_SEQ1_CHANNEL_NUM  = (8U);

		for (channelIndex = 0U; channelIndex < AFEC_SEQ1_CHANNEL_NUM; channelIndex++)
		{
			if (channelIndex >= numChannel)
			{
				break;
			}
			Regs()->AFEC_SEQ1R |= (uint32_t)channelList[channelIndex] << (channelIndex * 4U);
		}
		if (numChannel > AFEC_SEQ1_CHANNEL_NUM)
		{
			for (channelIndex = 0U; channelIndex < (numChannel - AFEC_SEQ1_CHANNEL_NUM); channelIndex++)
			{
				Regs()->AFEC_SEQ2R |= (uint32_t)channelList[channelIndex + AFEC_SEQ1_CHANNEL_NUM] << (channelIndex * 4U);
			}
		}
	}

	/**
	 * \brief Configure conversion trigger and free run mode.
	 */
	static inline void
	setTrigger(Trigger trigger)
	{
		uint32_t reg;
		reg = Regs()->AFEC_MR;

		if (trigger == Trigger::FREERUN) {
			reg |= AFEC_MR_FREERUN_ON;
		} else {
			reg &= ~(AFEC_MR_TRGSEL_Msk | AFEC_MR_TRGEN | AFEC_MR_FREERUN_ON);
			reg |= (uint32_t)trigger;
		}

		Regs()->AFEC_MR |= reg;
	}

	/* Enable channel end of conversion interrupt */
	static inline void
	enableInterrupt(InterruptMask interruptMask)
	{
		Regs()->AFEC_IER |= (uint32_t)interruptMask;
	}

	/** Enable the NVIC IRQ for this timer channel
	 */
	static inline void
	enableInterruptVector(bool enable, uint32_t priority=1)
	{
		if(enable)
		{
			NVIC_SetPriority(AFEC0_IRQn, priority);
			NVIC_EnableIRQ(AFEC0_IRQn);
		} else {
			NVIC_DisableIRQ(AFEC0_IRQn);
		}
	}

	/** Reads the currently pending interrupt flags
	 *
	 * Flags are automatically cleared in hardware when they are read
	 */
	static inline uint32_t getInterruptFlags()
	{
		return Regs()->AFEC_ISR;
	}

	// end inherited documentation

	template<class Pin>
	static inline constexpr uint8_t
	getPinChannel()
	{
		using Connector = typename Pin::Ad::template Connector<Peripherals::Afec<0>, Peripherals::Afec<0>::Ad>;

		static_assert(Connector::PinSignal::AdcChannel >= 0, "Pin cannot be used as ADC input");
		return Connector::PinSignal::AdcChannel;
	}
};

}  // namespace modm::platform