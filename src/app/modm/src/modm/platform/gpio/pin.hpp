/*
 * Copyright (c) 2017-2018, Niklas Hauser
 * Copyright (c) 2020, Erik Henriksson
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

#include <type_traits>

#include "../device.hpp"
#include "config.hpp"
#include "modm/architecture/interface.hpp"

namespace modm::platform
{
/// @ingroup modm_platform_gpio
/// @{

enum class InputType
{
	Floating = 0x0,  ///< floating on input
	PullUp = 0x1,    ///< pull-up on input
	PullDown = 0x2,  ///< pull-down on input
};

enum class PeripheralPin
{
	BitBang,
	Rx,
	Tx,
	Rts,
	Cts,
	ExtInt,
	Dm,
	Dp,
	Wo,
	Sck,
	Miso,
	Mosi,
	Npcs,
	Spck,
	Ad,
	Adtrg,
	Wkup,
	Tioa,
	Tiob,
	Tclk,
	Twd,
	Twck,
	Pck,
	I2sck,
	I2sws,
	I2sdi,
	I2sdo,
	I2smck,
	PwmH0,
	PwmH1,
	PwmH2,
	PwmH3,
	PwmL0,
	PwmL1,
	PwmL2,
	PwmL3,
	PwmFi0,
	PwmFi1,
	PwmFi2,
	PwmExtrg0,
	PwmExtrg1
};

template<typename... Tuples>
using tuple_cat_t = decltype(std::tuple_cat(std::declval<Tuples>()...));

template<class Predicate, class Tuple>
struct tuple_filter;

template<class Predicate, class Tuple>
using tuple_filter_t = typename tuple_filter<Predicate, Tuple>::type;

// Recursive case
template<class Predicate, class X, class... Xs>
struct tuple_filter<Predicate, std::tuple<X, Xs...>>
{
	using type =
		std::conditional_t<Predicate::template value<X>,
						   tuple_cat_t<std::tuple<X>, tuple_filter_t<Predicate, std::tuple<Xs...>>>,
						   tuple_filter_t<Predicate, std::tuple<Xs...>>>;
};

// Base case
template<class Predicate>
struct tuple_filter<Predicate, std::tuple<>>
{
	using type = std::tuple<>;
};

template<class P>
struct EqualsPeripheral
{
	template<class Signal>
	static constexpr bool value = std::is_same_v<P, typename Signal::peripheral>;
};

template<class S>
struct EqualsSignal
{
	template<class Signal>
	static constexpr bool value = std::is_same_v<S, typename Signal::signal>;
};

template<class... Signals>
struct OneOfSignals
{
	template<class Signal>
	static constexpr bool value = ((std::is_same_v<typename Signal::signal, Signals>) | ...);
};

// Detect if a pin is inverted
// Used to support both pins config and gpio classes being passed to GpioSet.
// Pin config classes don't define isInverted and are treated as non-inverted.
template<typename T>
struct is_inverted
{
    static constexpr bool value = false;
};

template<typename T>
    requires (T::isInverted == true)
struct is_inverted<T>
{
    static constexpr bool value = true;
};

template<typename T>
constexpr bool is_inverted_v = is_inverted<T>::value;

template<class... PinConfigs>
struct PinMuxMixin
{
	inline static void set(uint8_t){};
};

template<class PinConfig, class... PinConfigs>
struct PinMuxMixin<PinConfig, PinConfigs...>
{
	inline static void
	set(uint8_t cfg)
	{
		uint8_t bit0 = cfg & 1;
		uint8_t bit1 = (cfg & 2) >> 1;
		if constexpr (PinConfig::port == PortName::A)
		{
			PIOA->PIO_ABCDSR[0] = (PIOA->PIO_ABCDSR[0] & ~(1<<PinConfig::pin)) | (bit0 << PinConfig::pin);
			PIOA->PIO_ABCDSR[1] = (PIOA->PIO_ABCDSR[1] & ~(1<<PinConfig::pin)) | (bit1 << PinConfig::pin);
		}
		if constexpr (PinConfig::port == PortName::B)
		{
			PIOB->PIO_ABCDSR[0] = (PIOB->PIO_ABCDSR[0] & ~(1<<PinConfig::pin)) | (bit0 << PinConfig::pin);
			PIOB->PIO_ABCDSR[1] = (PIOB->PIO_ABCDSR[1] & ~(1<<PinConfig::pin)) | (bit1 << PinConfig::pin);
		}
		if constexpr (PinConfig::port == PortName::D)
		{
			PIOD->PIO_ABCDSR[0] = (PIOD->PIO_ABCDSR[0] & ~(1<<PinConfig::pin)) | (bit0 << PinConfig::pin);
			PIOD->PIO_ABCDSR[1] = (PIOD->PIO_ABCDSR[1] & ~(1<<PinConfig::pin)) | (bit1 << PinConfig::pin);
		}
		PinMuxMixin<PinConfigs...>::set(cfg);
	}
};

template<class... PinConfigs>
class GpioSet : protected PinMuxMixin<PinConfigs...>
{
protected:
	using PinMux = PinMuxMixin<PinConfigs...>;

	static consteval uint32_t
	mask(PortName port)
	{
		return (((PinConfigs::port == port) ? 1u << PinConfigs::pin : 0u) | ...);
	}

	static consteval uint32_t
	invertedMask(PortName port)
	{
		return (((PinConfigs::port == port) ? (is_inverted_v<PinConfigs> ? 1u : 0u) << PinConfigs::pin : 0u) | ...);
	}

	static consteval uint32_t
	nonInvertedMask(PortName port)
	{
		return mask(port) & ~invertedMask(port);
	}

	template<PortName port>
	inline static constexpr volatile uint32_t*
	getPortReg(size_t offset)
	{
		if constexpr (port == PortName::A) {
			return (uint32_t*)((uint8_t*)PIOA + offset);
		}
		if constexpr (port == PortName::B) {
			return (uint32_t*)((uint8_t*)PIOB + offset);
		}
		if constexpr (port == PortName::D) {
			return (uint32_t*)((uint8_t*)PIOD + offset);
		}
	}

	inline static constexpr void
	setPortReg(size_t offset)
	{
		if constexpr (mask(PortName::A) != 0) { *getPortReg<PortName::A>(offset) = mask(PortName::A); }
		if constexpr (mask(PortName::B) != 0) { *getPortReg<PortName::B>(offset) = mask(PortName::B); }
		if constexpr (mask(PortName::D) != 0) { *getPortReg<PortName::D>(offset) = mask(PortName::D); }
	}

	template<PortName port>
	inline static constexpr uint32_t
	readPortReg(size_t offset)
	{
		if constexpr (port == PortName::A)
		{
			static_assert(mask(PortName::A) != 0,
				"Trying to read port which is not in the GpioSet!");
			return *getPortReg<PortName::A>(offset) & mask(PortName::A);
		}
		if constexpr (port == PortName::B)
		{
			static_assert(mask(PortName::B) != 0,
				"Trying to read port which is not in the GpioSet!");
			return *getPortReg<PortName::B>(offset) & mask(PortName::B);
		}
		if constexpr (port == PortName::D)
		{
			static_assert(mask(PortName::D) != 0,
				"Trying to read port which is not in the GpioSet!");
			return *getPortReg<PortName::D>(offset) & mask(PortName::D);
		}
	}

public:
	inline static void
	setOutput()
	{
		// Enable PIO control of the pin (disables peripheral control)
		setPortReg(PIO_PER_OFFSET);
		// Enable output driver
		setPortReg(PIO_OER_OFFSET);
	}

	inline static void
	setOutput(bool status)
	{
		set(status);
		setOutput();
	}

	static void
	setInput()
	{
		// Enable PIO control of the pin (disables peripheral control)
		setPortReg(PIO_PER_OFFSET);
		// Disable output driver
		setPortReg(PIO_ODR_OFFSET);
	}

	static void
	setInput(InputType type)
	{
		configure(type);
		setInput();
	}

	static void
	configure(InputType type)
	{
		if(type == InputType::Floating) {
			setPortReg(PIO_PPDDR_OFFSET); // disable pull down
			setPortReg(PIO_PUDR_OFFSET); // disable pull up
		} else if (type == InputType::PullDown) {
			setPortReg(PIO_PUDR_OFFSET); // disable pull up
			setPortReg(PIO_PPDER_OFFSET); // enable pull down
		} else {
			setPortReg(PIO_PPDDR_OFFSET); // Disable pull down
			setPortReg(PIO_PUER_OFFSET); // Enable pull up
		}
	}

	static void
	setAnalogInput()
	{}

	static void
	set()
	{
		if constexpr (nonInvertedMask(PortName::A)) {
			*getPortReg<PortName::A>(PIO_SODR_OFFSET) = nonInvertedMask(PortName::A);
		}
		if constexpr (invertedMask(PortName::A)) {
			*getPortReg<PortName::A>(PIO_CODR_OFFSET) = invertedMask(PortName::A);
		}
		if constexpr (nonInvertedMask(PortName::B)) {
			*getPortReg<PortName::B>(PIO_SODR_OFFSET) = nonInvertedMask(PortName::B);
		}
		if constexpr (invertedMask(PortName::B)) {
			*getPortReg<PortName::B>(PIO_CODR_OFFSET) = invertedMask(PortName::B);
		}
		if constexpr (nonInvertedMask(PortName::D)) {
			*getPortReg<PortName::D>(PIO_SODR_OFFSET) = nonInvertedMask(PortName::D);
		}
		if constexpr (invertedMask(PortName::D)) {
			*getPortReg<PortName::D>(PIO_CODR_OFFSET) = invertedMask(PortName::D);
		}
	}

	static void
	set(bool status)
	{
		if (status)
			set();
		else
			reset();
	}

	static void
	reset()
	{
		if constexpr (nonInvertedMask(PortName::A)) {
			*getPortReg<PortName::A>(PIO_CODR_OFFSET) = nonInvertedMask(PortName::A);
		}
		if constexpr (invertedMask(PortName::A)) {
			*getPortReg<PortName::A>(PIO_SODR_OFFSET) = invertedMask(PortName::A);
		}
		if constexpr (nonInvertedMask(PortName::B)) {
			*getPortReg<PortName::B>(PIO_CODR_OFFSET) = nonInvertedMask(PortName::B);
		}
		if constexpr (invertedMask(PortName::B)) {
			*getPortReg<PortName::B>(PIO_SODR_OFFSET) = invertedMask(PortName::B);
		}
		if constexpr (nonInvertedMask(PortName::D)) {
			*getPortReg<PortName::D>(PIO_CODR_OFFSET) = nonInvertedMask(PortName::D);
		}
		if constexpr (invertedMask(PortName::D)) {
			*getPortReg<PortName::D>(PIO_SODR_OFFSET) = invertedMask(PortName::D);
		}
	}

	static void
	toggle()
	{
		if constexpr (mask(PortName::A) != 0) {
			volatile uint32_t *reg = getPortReg<PortName::A>(PIO_ODSR_OFFSET);
			uint32_t tmp = *reg;
			tmp ^= mask(PortName::A);
			*reg = tmp;
		}
		if constexpr (mask(PortName::B) != 0) {
			volatile uint32_t *reg = getPortReg<PortName::B>(PIO_ODSR_OFFSET);
			uint32_t tmp = *reg;
			tmp ^= mask(PortName::B);
			*reg = tmp;
		}
		if constexpr (mask(PortName::D) != 0) {
			volatile uint32_t *reg = getPortReg<PortName::D>(PIO_ODSR_OFFSET);
			uint32_t tmp = *reg;
			tmp ^= mask(PortName::D);
			*reg = tmp;
		}
	}

	static void
	disconnect()
	{
		setInput(InputType::Floating);
	}
};

template<class PinConfig>
class Gpio : public GpioSet<PinConfig>, public ::modm::GpioIO
{
	using Base = GpioSet<PinConfig>;

public:
	// For backwards compability with bitbang API
	using InputType = ::modm::platform::InputType;

	// For compability with GpioInverted
	using Type = Gpio<PinConfig>;
	using IO = Type;
	using Input = Type;
	using Output = Type;
	using Data = PinConfig;
	static constexpr bool isInverted = false;

	static constexpr auto pin = PinConfig::pin;
	static constexpr auto port = PinConfig::port;

	template<PeripheralPin peripheral_pin_v>
	struct As;

	using Rx = As<PeripheralPin::Rx>;
	using Tx = As<PeripheralPin::Tx>;
	using Rts = As<PeripheralPin::Rts>;
	using Cts = As<PeripheralPin::Cts>;
	using ExtInt = As<PeripheralPin::ExtInt>;
	using Dm = As<PeripheralPin::Dm>;
	using Dp = As<PeripheralPin::Dp>;
	using Wo = As<PeripheralPin::Wo>;
	using Sck = As<PeripheralPin::Sck>;
	using Miso = As<PeripheralPin::Miso>;
	using Mosi = As<PeripheralPin::Mosi>;
	using Npcs = As<PeripheralPin::Npcs>;
	using Spck = As<PeripheralPin::Spck>;
	using Ad = As<PeripheralPin::Ad>;
	using Adtrg = As<PeripheralPin::Adtrg>;
	using Wkup = As<PeripheralPin::Wkup>;
	using Tioa = As<PeripheralPin::Tioa>;
	using Tiob = As<PeripheralPin::Tiob>;
	using Tclk = As<PeripheralPin::Tclk>;
	using Twd = As<PeripheralPin::Twd>;
	using Twck = As<PeripheralPin::Twck>;
	using Pck = As<PeripheralPin::Pck>;
	using I2sck = As<PeripheralPin::I2sck>;
	using I2sws = As<PeripheralPin::I2sws>;
	using I2sdi = As<PeripheralPin::I2sdi>;
	using I2sdo = As<PeripheralPin::I2sdo>;
	using I2smck = As<PeripheralPin::I2smck>;
	using PwmH0 = As<PeripheralPin::PwmH0>;
	using PwmH1 = As<PeripheralPin::PwmH1>;
	using PwmH2 = As<PeripheralPin::PwmH2>;
	using PwmH3 = As<PeripheralPin::PwmH3>;
	using PwmL0 = As<PeripheralPin::PwmL0>;
	using PwmL1 = As<PeripheralPin::PwmL1>;
	using PwmL2 = As<PeripheralPin::PwmL2>;
	using PwmL3 = As<PeripheralPin::PwmL3>;
	using PwmFi0 = As<PeripheralPin::PwmFi0>;
	using PwmFi1 = As<PeripheralPin::PwmFi1>;
	using PwmFi2 = As<PeripheralPin::PwmFi2>;
	using PwmExtrg0 = As<PeripheralPin::PwmExtrg0>;
	using PwmExtrg1 = As<PeripheralPin::PwmExtrg1>;

	inline static bool
	read()
	{
		return Base::template readPortReg<PinConfig::port>(PIO_PDSR_OFFSET);
	}

	inline static bool
	isSet()
	{
		return Base::template readPortReg<PinConfig::port>(PIO_ODSR_OFFSET);
	}

	inline static void
	write(bool status)
	{
		Base::set(status);
	}
};

template<class PinConfig>
template<PeripheralPin peripheral_pin_v>
struct Gpio<PinConfig>::As : public Gpio<PinConfig>
{
	static constexpr PeripheralPin peripheral_pin = peripheral_pin_v;
	using Base = Gpio<PinConfig>;

	template<class Signals, class P>
	struct ValidatePeripheral
	{
		using type = tuple_filter_t<EqualsPeripheral<P>, Signals>;
		static_assert(!std::is_same_v<type, std::tuple<>>,
					  "Gpio pin does not connect to this peripheral! (see above)");
	};

	template<class Signals, class... RequiredSignals>
	struct ValidateSignal
	{
		using type = tuple_filter_t<OneOfSignals<RequiredSignals...>, Signals>;
		static_assert(!std::is_same_v<type, std::tuple<>>,
					  "Gpio pin does not connect to any of the required signals! "
					  "(see above)");
	};

	template<class Signals>
	struct GetSingleSignal
	{
		using crash = typename Signals::errorPeripheralInstanceMatchedMoreThanOneSignal;
	};

	template<class Signal>
	struct GetSingleSignal<std::tuple<Signal>>
	{
		using type = Signal;
	};

	template<class peripheral, class... RequiredSignals>
	struct Connector
	{
		using ValidatedPeripheral =
			typename ValidatePeripheral<typename PinConfig::Signals, peripheral>::type;
		using ValidatedSignals =
			typename ValidateSignal<ValidatedPeripheral, RequiredSignals...>::type;
		using PinSignal = typename GetSingleSignal<ValidatedSignals>::type;
		using Signal = typename PinSignal::signal;

		inline static void
		connect()
		{

			// X1 denotes an "extra function", such as an ADC pin, which is not
			// enabled by the PIO ABCD register.
			static_assert(PinSignal::function != PinFunction::X1,
				"This is a system connection, and cannot be connected by Gpio connect()");
			Pio* PIOBase;
			if constexpr (PinConfig::port == PortName::A)
				PIOBase = PIOA;
			if constexpr (PinConfig::port == PortName::B)
				PIOBase = PIOB;
			if constexpr (PinConfig::port == PortName::D)
				PIOBase = PIOD;
			PIOBase->PIO_PDR = (1<<PinConfig::pin);
			Base::PinMux::set((uint32_t)PinSignal::function);
		}

	};
};

template<PeripheralPin peripheral, class... Pins>
struct GetPin;

template<PeripheralPin peripheral_pin, class... Pins>
using GetPin_t = typename GetPin<peripheral_pin, Pins...>::type;

template<PeripheralPin peripheral_pin, class Pin, class... Pins>
struct GetPin<peripheral_pin, Pin, Pins...>
{
	using type = typename std::conditional_t<peripheral_pin == Pin::peripheral_pin, Pin,
											 GetPin_t<peripheral_pin, Pins...>>;
};

template<PeripheralPin peripheral_pin>
struct GetPin<peripheral_pin>
{
	using type = void;
};
/// @}

}  // namespace modm::platform