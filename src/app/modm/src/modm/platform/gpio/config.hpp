/*
 * Copyright (c) 2020, Erik Henriksson
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
// ----------------------------------------------------------------------------

#pragma once

#include <stdint.h>
#include <tuple>

namespace modm::platform
{
/// @ingroup modm_platform_gpio
/// @{

typedef uint32_t Instance;

enum class PinFunction
{
	A,
	B,
	C,
	D,
	X1,
};

struct Peripherals
{
	template<int instance>
	struct Afec
	{
		struct Adtrg {};
		struct Ad {};
		struct Wkup {};
		struct Piodcen {};
		struct Rtcout {};
  	};

	struct Dacc
	{
		struct Datrg {};
		template<int index>
		struct Dac;
  	};

	struct Gmac
	{
		struct Gtsucomp {};
		struct Gtxck {};
		struct Gtxen {};
		template<int index>
		struct Gtx;
		struct Grxdv {};
		template<int index>
		struct Grx;
		struct Grxer {};
		struct Gmdc {};
		struct Gmdio {};
		struct Gcrs {};
		struct Gcol {};
		struct Grxck {};
		struct Gtxer {};
  	};

	struct Hsmci
	{
		struct Mcck {};
		template<int index>
		struct Mcda;
		struct Mccda {};
  	};

	struct Isi
	{
		template<int index>
		struct D;
		struct Pck {};
		struct Hsync {};
		struct Vsync {};
  	};

	template<int instance>
	struct Mcan
	{
		template<int index>
		struct Cantx;
		template<int index>
		struct Canrx;
  	};

	struct Pmc
	{
		template<int index>
		struct Pck;
  	};

	template<int instance>
	struct Pwm
	{
		template<int index>
		struct Pwmh;
		template<int index>
		struct Pwml;
		template<int index>
		struct Pwmfi;
		template<int index>
		struct Pwmextrg;
  	};

	struct Qspi
	{
		struct Qcs {};
		template<int index>
		struct Qio;
		struct Qsck {};
  	};

	template<int instance>
	struct Spi
	{
		template<int index>
		struct Npcs;
		struct Miso {};
		struct Mosi {};
		struct Spck {};
  	};

	struct Ssc
	{
		struct Rd {};
		struct Rk {};
		struct Tf {};
		struct Tk {};
		struct Td {};
		struct Rf {};
  	};

	template<int instance>
	struct Tc
	{
		template<int index>
		struct Tioa;
		template<int index>
		struct Tiob;
		template<int index>
		struct Tclk;
  	};

	template<int instance>
	struct Twihs
	{
		template<int index>
		struct Twd;
		template<int index>
		struct Twck;
  	};

	template<int instance>
	struct Uart
	{
		template<int index>
		struct Utxd;
		template<int index>
		struct Urxd;
  	};

	template<int instance>
	struct Usart
	{
		template<int index>
		struct Loncol;
		template<int index>
		struct Rxd;
		template<int index>
		struct Sck;
		template<int index>
		struct Rts;
		template<int index>
		struct Cts;
		template<int index>
		struct Dcd;
		template<int index>
		struct Dtr;
		template<int index>
		struct Dsr;
		template<int index>
		struct Txd;
		template<int index>
		struct Ri;
  	};

};

enum class PortName
{
	A,
	B,
	D,
};
/// @}

/// @cond
template<>
struct Peripherals::Afec<0>::Adtrg {};
template<>
struct Peripherals::Afec<0>::Ad {};
template<>
struct Peripherals::Afec<0>::Wkup {};
template<>
struct Peripherals::Afec<0>::Piodcen {};
template<>
struct Peripherals::Afec<0>::Rtcout {};
template<>
struct Peripherals::Afec<1>::Adtrg {};
template<>
struct Peripherals::Afec<1>::Ad {};
template<>
struct Peripherals::Afec<1>::Wkup {};
template<>
struct Peripherals::Afec<1>::Piodcen {};
template<>
struct Peripherals::Afec<1>::Rtcout {};
template<>
struct Peripherals::Dacc::Dac<0> {};
template<>
struct Peripherals::Dacc::Dac<1> {};
template<>
struct Peripherals::Gmac::Gtx<0> {};
template<>
struct Peripherals::Gmac::Gtx<1> {};
template<>
struct Peripherals::Gmac::Gtx<2> {};
template<>
struct Peripherals::Gmac::Gtx<3> {};
template<>
struct Peripherals::Gmac::Grx<0> {};
template<>
struct Peripherals::Gmac::Grx<1> {};
template<>
struct Peripherals::Gmac::Grx<2> {};
template<>
struct Peripherals::Gmac::Grx<3> {};
template<>
struct Peripherals::Hsmci::Mcda<0> {};
template<>
struct Peripherals::Hsmci::Mcda<1> {};
template<>
struct Peripherals::Hsmci::Mcda<2> {};
template<>
struct Peripherals::Hsmci::Mcda<3> {};
template<>
struct Peripherals::Isi::D<0> {};
template<>
struct Peripherals::Isi::D<1> {};
template<>
struct Peripherals::Isi::D<2> {};
template<>
struct Peripherals::Isi::D<3> {};
template<>
struct Peripherals::Isi::D<4> {};
template<>
struct Peripherals::Isi::D<5> {};
template<>
struct Peripherals::Isi::D<6> {};
template<>
struct Peripherals::Isi::D<7> {};
template<>
struct Peripherals::Isi::D<8> {};
template<>
struct Peripherals::Isi::D<9> {};
template<>
struct Peripherals::Isi::D<10> {};
template<>
struct Peripherals::Isi::D<11> {};
template<> template<>
struct Peripherals::Mcan<0>::Cantx<0> {};
template<> template<>
struct Peripherals::Mcan<0>::Cantx<1> {};
template<> template<>
struct Peripherals::Mcan<0>::Canrx<0> {};
template<> template<>
struct Peripherals::Mcan<0>::Canrx<1> {};
template<> template<>
struct Peripherals::Mcan<1>::Cantx<0> {};
template<> template<>
struct Peripherals::Mcan<1>::Cantx<1> {};
template<> template<>
struct Peripherals::Mcan<1>::Canrx<0> {};
template<> template<>
struct Peripherals::Mcan<1>::Canrx<1> {};
template<>
struct Peripherals::Pmc::Pck<0> {};
template<>
struct Peripherals::Pmc::Pck<1> {};
template<>
struct Peripherals::Pmc::Pck<2> {};
template<> template<>
struct Peripherals::Pwm<0>::Pwmh<0> {};
template<> template<>
struct Peripherals::Pwm<0>::Pwmh<1> {};
template<> template<>
struct Peripherals::Pwm<0>::Pwmh<2> {};
template<> template<>
struct Peripherals::Pwm<0>::Pwmh<3> {};
template<> template<>
struct Peripherals::Pwm<0>::Pwml<0> {};
template<> template<>
struct Peripherals::Pwm<0>::Pwml<1> {};
template<> template<>
struct Peripherals::Pwm<0>::Pwml<2> {};
template<> template<>
struct Peripherals::Pwm<0>::Pwml<3> {};
template<> template<>
struct Peripherals::Pwm<0>::Pwmfi<0> {};
template<> template<>
struct Peripherals::Pwm<0>::Pwmfi<1> {};
template<> template<>
struct Peripherals::Pwm<0>::Pwmfi<2> {};
template<> template<>
struct Peripherals::Pwm<0>::Pwmextrg<0> {};
template<> template<>
struct Peripherals::Pwm<0>::Pwmextrg<1> {};
template<> template<>
struct Peripherals::Pwm<1>::Pwmh<0> {};
template<> template<>
struct Peripherals::Pwm<1>::Pwmh<1> {};
template<> template<>
struct Peripherals::Pwm<1>::Pwmh<2> {};
template<> template<>
struct Peripherals::Pwm<1>::Pwmh<3> {};
template<> template<>
struct Peripherals::Pwm<1>::Pwml<0> {};
template<> template<>
struct Peripherals::Pwm<1>::Pwml<1> {};
template<> template<>
struct Peripherals::Pwm<1>::Pwml<2> {};
template<> template<>
struct Peripherals::Pwm<1>::Pwml<3> {};
template<> template<>
struct Peripherals::Pwm<1>::Pwmfi<0> {};
template<> template<>
struct Peripherals::Pwm<1>::Pwmfi<1> {};
template<> template<>
struct Peripherals::Pwm<1>::Pwmfi<2> {};
template<> template<>
struct Peripherals::Pwm<1>::Pwmextrg<0> {};
template<> template<>
struct Peripherals::Pwm<1>::Pwmextrg<1> {};
template<>
struct Peripherals::Qspi::Qio<0> {};
template<>
struct Peripherals::Qspi::Qio<1> {};
template<>
struct Peripherals::Qspi::Qio<2> {};
template<>
struct Peripherals::Qspi::Qio<3> {};
template<> template<>
struct Peripherals::Spi<0>::Npcs<0> {};
template<> template<>
struct Peripherals::Spi<0>::Npcs<1> {};
template<> template<>
struct Peripherals::Spi<0>::Npcs<2> {};
template<> template<>
struct Peripherals::Spi<0>::Npcs<3> {};
template<>
struct Peripherals::Spi<0>::Miso {};
template<>
struct Peripherals::Spi<0>::Mosi {};
template<>
struct Peripherals::Spi<0>::Spck {};
template<> template<>
struct Peripherals::Tc<0>::Tioa<0> {};
template<> template<>
struct Peripherals::Tc<0>::Tioa<1> {};
template<> template<>
struct Peripherals::Tc<0>::Tioa<2> {};
template<> template<>
struct Peripherals::Tc<0>::Tioa<11> {};
template<> template<>
struct Peripherals::Tc<0>::Tiob<0> {};
template<> template<>
struct Peripherals::Tc<0>::Tiob<1> {};
template<> template<>
struct Peripherals::Tc<0>::Tiob<2> {};
template<> template<>
struct Peripherals::Tc<0>::Tiob<11> {};
template<> template<>
struct Peripherals::Tc<0>::Tclk<0> {};
template<> template<>
struct Peripherals::Tc<0>::Tclk<1> {};
template<> template<>
struct Peripherals::Tc<0>::Tclk<11> {};
template<> template<>
struct Peripherals::Tc<3>::Tioa<0> {};
template<> template<>
struct Peripherals::Tc<3>::Tioa<1> {};
template<> template<>
struct Peripherals::Tc<3>::Tioa<2> {};
template<> template<>
struct Peripherals::Tc<3>::Tioa<11> {};
template<> template<>
struct Peripherals::Tc<3>::Tiob<0> {};
template<> template<>
struct Peripherals::Tc<3>::Tiob<1> {};
template<> template<>
struct Peripherals::Tc<3>::Tiob<2> {};
template<> template<>
struct Peripherals::Tc<3>::Tiob<11> {};
template<> template<>
struct Peripherals::Tc<3>::Tclk<0> {};
template<> template<>
struct Peripherals::Tc<3>::Tclk<1> {};
template<> template<>
struct Peripherals::Tc<3>::Tclk<11> {};
template<> template<>
struct Peripherals::Twihs<0>::Twd<0> {};
template<> template<>
struct Peripherals::Twihs<0>::Twd<1> {};
template<> template<>
struct Peripherals::Twihs<0>::Twd<2> {};
template<> template<>
struct Peripherals::Twihs<0>::Twck<0> {};
template<> template<>
struct Peripherals::Twihs<0>::Twck<1> {};
template<> template<>
struct Peripherals::Twihs<0>::Twck<2> {};
template<> template<>
struct Peripherals::Twihs<1>::Twd<0> {};
template<> template<>
struct Peripherals::Twihs<1>::Twd<1> {};
template<> template<>
struct Peripherals::Twihs<1>::Twd<2> {};
template<> template<>
struct Peripherals::Twihs<1>::Twck<0> {};
template<> template<>
struct Peripherals::Twihs<1>::Twck<1> {};
template<> template<>
struct Peripherals::Twihs<1>::Twck<2> {};
template<> template<>
struct Peripherals::Twihs<2>::Twd<0> {};
template<> template<>
struct Peripherals::Twihs<2>::Twd<1> {};
template<> template<>
struct Peripherals::Twihs<2>::Twd<2> {};
template<> template<>
struct Peripherals::Twihs<2>::Twck<0> {};
template<> template<>
struct Peripherals::Twihs<2>::Twck<1> {};
template<> template<>
struct Peripherals::Twihs<2>::Twck<2> {};
template<> template<>
struct Peripherals::Uart<0>::Utxd<0> {};
template<> template<>
struct Peripherals::Uart<0>::Utxd<1> {};
template<> template<>
struct Peripherals::Uart<0>::Utxd<2> {};
template<> template<>
struct Peripherals::Uart<0>::Utxd<3> {};
template<> template<>
struct Peripherals::Uart<0>::Utxd<4> {};
template<> template<>
struct Peripherals::Uart<0>::Urxd<0> {};
template<> template<>
struct Peripherals::Uart<0>::Urxd<1> {};
template<> template<>
struct Peripherals::Uart<0>::Urxd<2> {};
template<> template<>
struct Peripherals::Uart<0>::Urxd<3> {};
template<> template<>
struct Peripherals::Uart<0>::Urxd<4> {};
template<> template<>
struct Peripherals::Uart<1>::Utxd<0> {};
template<> template<>
struct Peripherals::Uart<1>::Utxd<1> {};
template<> template<>
struct Peripherals::Uart<1>::Utxd<2> {};
template<> template<>
struct Peripherals::Uart<1>::Utxd<3> {};
template<> template<>
struct Peripherals::Uart<1>::Utxd<4> {};
template<> template<>
struct Peripherals::Uart<1>::Urxd<0> {};
template<> template<>
struct Peripherals::Uart<1>::Urxd<1> {};
template<> template<>
struct Peripherals::Uart<1>::Urxd<2> {};
template<> template<>
struct Peripherals::Uart<1>::Urxd<3> {};
template<> template<>
struct Peripherals::Uart<1>::Urxd<4> {};
template<> template<>
struct Peripherals::Uart<2>::Utxd<0> {};
template<> template<>
struct Peripherals::Uart<2>::Utxd<1> {};
template<> template<>
struct Peripherals::Uart<2>::Utxd<2> {};
template<> template<>
struct Peripherals::Uart<2>::Utxd<3> {};
template<> template<>
struct Peripherals::Uart<2>::Utxd<4> {};
template<> template<>
struct Peripherals::Uart<2>::Urxd<0> {};
template<> template<>
struct Peripherals::Uart<2>::Urxd<1> {};
template<> template<>
struct Peripherals::Uart<2>::Urxd<2> {};
template<> template<>
struct Peripherals::Uart<2>::Urxd<3> {};
template<> template<>
struct Peripherals::Uart<2>::Urxd<4> {};
template<> template<>
struct Peripherals::Uart<3>::Utxd<0> {};
template<> template<>
struct Peripherals::Uart<3>::Utxd<1> {};
template<> template<>
struct Peripherals::Uart<3>::Utxd<2> {};
template<> template<>
struct Peripherals::Uart<3>::Utxd<3> {};
template<> template<>
struct Peripherals::Uart<3>::Utxd<4> {};
template<> template<>
struct Peripherals::Uart<3>::Urxd<0> {};
template<> template<>
struct Peripherals::Uart<3>::Urxd<1> {};
template<> template<>
struct Peripherals::Uart<3>::Urxd<2> {};
template<> template<>
struct Peripherals::Uart<3>::Urxd<3> {};
template<> template<>
struct Peripherals::Uart<3>::Urxd<4> {};
template<> template<>
struct Peripherals::Uart<4>::Utxd<0> {};
template<> template<>
struct Peripherals::Uart<4>::Utxd<1> {};
template<> template<>
struct Peripherals::Uart<4>::Utxd<2> {};
template<> template<>
struct Peripherals::Uart<4>::Utxd<3> {};
template<> template<>
struct Peripherals::Uart<4>::Utxd<4> {};
template<> template<>
struct Peripherals::Uart<4>::Urxd<0> {};
template<> template<>
struct Peripherals::Uart<4>::Urxd<1> {};
template<> template<>
struct Peripherals::Uart<4>::Urxd<2> {};
template<> template<>
struct Peripherals::Uart<4>::Urxd<3> {};
template<> template<>
struct Peripherals::Uart<4>::Urxd<4> {};
template<> template<>
struct Peripherals::Usart<0>::Loncol<1> {};
template<> template<>
struct Peripherals::Usart<0>::Rxd<0> {};
template<> template<>
struct Peripherals::Usart<0>::Rxd<1> {};
template<> template<>
struct Peripherals::Usart<0>::Rxd<2> {};
template<> template<>
struct Peripherals::Usart<0>::Sck<0> {};
template<> template<>
struct Peripherals::Usart<0>::Sck<1> {};
template<> template<>
struct Peripherals::Usart<0>::Sck<2> {};
template<> template<>
struct Peripherals::Usart<0>::Rts<0> {};
template<> template<>
struct Peripherals::Usart<0>::Rts<1> {};
template<> template<>
struct Peripherals::Usart<0>::Rts<2> {};
template<> template<>
struct Peripherals::Usart<0>::Cts<0> {};
template<> template<>
struct Peripherals::Usart<0>::Cts<1> {};
template<> template<>
struct Peripherals::Usart<0>::Cts<2> {};
template<> template<>
struct Peripherals::Usart<0>::Dcd<0> {};
template<> template<>
struct Peripherals::Usart<0>::Dcd<1> {};
template<> template<>
struct Peripherals::Usart<0>::Dcd<2> {};
template<> template<>
struct Peripherals::Usart<0>::Dtr<0> {};
template<> template<>
struct Peripherals::Usart<0>::Dtr<1> {};
template<> template<>
struct Peripherals::Usart<0>::Dtr<2> {};
template<> template<>
struct Peripherals::Usart<0>::Dsr<0> {};
template<> template<>
struct Peripherals::Usart<0>::Dsr<1> {};
template<> template<>
struct Peripherals::Usart<0>::Dsr<2> {};
template<> template<>
struct Peripherals::Usart<0>::Txd<0> {};
template<> template<>
struct Peripherals::Usart<0>::Txd<1> {};
template<> template<>
struct Peripherals::Usart<0>::Txd<2> {};
template<> template<>
struct Peripherals::Usart<0>::Ri<0> {};
template<> template<>
struct Peripherals::Usart<0>::Ri<2> {};
template<> template<>
struct Peripherals::Usart<1>::Loncol<1> {};
template<> template<>
struct Peripherals::Usart<1>::Rxd<0> {};
template<> template<>
struct Peripherals::Usart<1>::Rxd<1> {};
template<> template<>
struct Peripherals::Usart<1>::Rxd<2> {};
template<> template<>
struct Peripherals::Usart<1>::Sck<0> {};
template<> template<>
struct Peripherals::Usart<1>::Sck<1> {};
template<> template<>
struct Peripherals::Usart<1>::Sck<2> {};
template<> template<>
struct Peripherals::Usart<1>::Rts<0> {};
template<> template<>
struct Peripherals::Usart<1>::Rts<1> {};
template<> template<>
struct Peripherals::Usart<1>::Rts<2> {};
template<> template<>
struct Peripherals::Usart<1>::Cts<0> {};
template<> template<>
struct Peripherals::Usart<1>::Cts<1> {};
template<> template<>
struct Peripherals::Usart<1>::Cts<2> {};
template<> template<>
struct Peripherals::Usart<1>::Dcd<0> {};
template<> template<>
struct Peripherals::Usart<1>::Dcd<1> {};
template<> template<>
struct Peripherals::Usart<1>::Dcd<2> {};
template<> template<>
struct Peripherals::Usart<1>::Dtr<0> {};
template<> template<>
struct Peripherals::Usart<1>::Dtr<1> {};
template<> template<>
struct Peripherals::Usart<1>::Dtr<2> {};
template<> template<>
struct Peripherals::Usart<1>::Dsr<0> {};
template<> template<>
struct Peripherals::Usart<1>::Dsr<1> {};
template<> template<>
struct Peripherals::Usart<1>::Dsr<2> {};
template<> template<>
struct Peripherals::Usart<1>::Txd<0> {};
template<> template<>
struct Peripherals::Usart<1>::Txd<1> {};
template<> template<>
struct Peripherals::Usart<1>::Txd<2> {};
template<> template<>
struct Peripherals::Usart<1>::Ri<0> {};
template<> template<>
struct Peripherals::Usart<1>::Ri<2> {};
template<> template<>
struct Peripherals::Usart<2>::Loncol<1> {};
template<> template<>
struct Peripherals::Usart<2>::Rxd<0> {};
template<> template<>
struct Peripherals::Usart<2>::Rxd<1> {};
template<> template<>
struct Peripherals::Usart<2>::Rxd<2> {};
template<> template<>
struct Peripherals::Usart<2>::Sck<0> {};
template<> template<>
struct Peripherals::Usart<2>::Sck<1> {};
template<> template<>
struct Peripherals::Usart<2>::Sck<2> {};
template<> template<>
struct Peripherals::Usart<2>::Rts<0> {};
template<> template<>
struct Peripherals::Usart<2>::Rts<1> {};
template<> template<>
struct Peripherals::Usart<2>::Rts<2> {};
template<> template<>
struct Peripherals::Usart<2>::Cts<0> {};
template<> template<>
struct Peripherals::Usart<2>::Cts<1> {};
template<> template<>
struct Peripherals::Usart<2>::Cts<2> {};
template<> template<>
struct Peripherals::Usart<2>::Dcd<0> {};
template<> template<>
struct Peripherals::Usart<2>::Dcd<1> {};
template<> template<>
struct Peripherals::Usart<2>::Dcd<2> {};
template<> template<>
struct Peripherals::Usart<2>::Dtr<0> {};
template<> template<>
struct Peripherals::Usart<2>::Dtr<1> {};
template<> template<>
struct Peripherals::Usart<2>::Dtr<2> {};
template<> template<>
struct Peripherals::Usart<2>::Dsr<0> {};
template<> template<>
struct Peripherals::Usart<2>::Dsr<1> {};
template<> template<>
struct Peripherals::Usart<2>::Dsr<2> {};
template<> template<>
struct Peripherals::Usart<2>::Txd<0> {};
template<> template<>
struct Peripherals::Usart<2>::Txd<1> {};
template<> template<>
struct Peripherals::Usart<2>::Txd<2> {};
template<> template<>
struct Peripherals::Usart<2>::Ri<0> {};
template<> template<>
struct Peripherals::Usart<2>::Ri<2> {};
template<class _>
class Gpio;

namespace gpio
{
struct A0
{
	static constexpr PortName port = PortName::A;
	static constexpr uint32_t pin = 0;

	struct Tc0Tioa0
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Tc<0>;
		using signal = peripheral::Tioa<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Pwm0Pwmh0
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Pwm<0>;
		using signal = peripheral::Pwmh<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Tc0Tioa0,
			Pwm0Pwmh0>;
};
struct A1
{
	static constexpr PortName port = PortName::A;
	static constexpr uint32_t pin = 1;

	struct Pwm0Pwml0
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Pwm<0>;
		using signal = peripheral::Pwml<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Tc0Tiob0
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Tc<0>;
		using signal = peripheral::Tiob<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Pwm0Pwml0,
			Tc0Tiob0>;
};
struct A2
{
	static constexpr PortName port = PortName::A;
	static constexpr uint32_t pin = 2;

	struct Pwm0Pwmh1
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Pwm<0>;
		using signal = peripheral::Pwmh<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct DaccDatrg
	{
		static constexpr PinFunction function{PinFunction::C};
		using peripheral = Peripherals::Dacc;
		using signal = peripheral::Datrg;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Pwm0Pwmh1,
			DaccDatrg>;
};
struct A3
{
	static constexpr PortName port = PortName::A;
	static constexpr uint32_t pin = 3;

	struct PmcPck2
	{
		static constexpr PinFunction function{PinFunction::C};
		using peripheral = Peripherals::Pmc;
		using signal = peripheral::Pck<2>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Usart1Loncol1
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Usart<1>;
		using signal = peripheral::Loncol<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Twihs0Twd0
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Twihs<0>;
		using signal = peripheral::Twd<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			PmcPck2,
			Usart1Loncol1,
			Twihs0Twd0>;
};
struct A4
{
	static constexpr PortName port = PortName::A;
	static constexpr uint32_t pin = 4;

	struct Twihs0Twck0
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Twihs<0>;
		using signal = peripheral::Twck<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Tc0Tclk0
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Tc<0>;
		using signal = peripheral::Tclk<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Uart1Utxd1
	{
		static constexpr PinFunction function{PinFunction::C};
		using peripheral = Peripherals::Uart<1>;
		using signal = peripheral::Utxd<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Twihs0Twck0,
			Tc0Tclk0,
			Uart1Utxd1>;
};
struct A5
{
	static constexpr PortName port = PortName::A;
	static constexpr uint32_t pin = 5;

	struct Uart1Urxd1
	{
		static constexpr PinFunction function{PinFunction::C};
		using peripheral = Peripherals::Uart<1>;
		using signal = peripheral::Urxd<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Pwm1Pwml3
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Pwm<1>;
		using signal = peripheral::Pwml<3>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct IsiD4
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Isi;
		using signal = peripheral::D<4>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Uart1Urxd1,
			Pwm1Pwml3,
			IsiD4>;
};
struct A7
{
	static constexpr PortName port = PortName::A;
	static constexpr uint32_t pin = 7;

	struct Pwm0Pwmh3
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Pwm<0>;
		using signal = peripheral::Pwmh<3>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Pwm0Pwmh3>;
};
struct A8
{
	static constexpr PortName port = PortName::A;
	static constexpr uint32_t pin = 8;

	struct Pwm1Pwmh3
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Pwm<1>;
		using signal = peripheral::Pwmh<3>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Afec0Adtrg
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Afec<0>;
		using signal = peripheral::Adtrg;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Pwm1Pwmh3,
			Afec0Adtrg>;
};
struct A9
{
	static constexpr PortName port = PortName::A;
	static constexpr uint32_t pin = 9;

	struct Pwm0Pwmfi0
	{
		static constexpr PinFunction function{PinFunction::C};
		using peripheral = Peripherals::Pwm<0>;
		using signal = peripheral::Pwmfi<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct IsiD3
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Isi;
		using signal = peripheral::D<3>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Uart0Urxd0
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Uart<0>;
		using signal = peripheral::Urxd<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Pwm0Pwmfi0,
			IsiD3,
			Uart0Urxd0>;
};
struct A10
{
	static constexpr PortName port = PortName::A;
	static constexpr uint32_t pin = 10;

	struct Uart0Utxd0
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Uart<0>;
		using signal = peripheral::Utxd<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct SscRd
	{
		static constexpr PinFunction function{PinFunction::C};
		using peripheral = Peripherals::Ssc;
		using signal = peripheral::Rd;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Pwm0Pwmextrg0
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Pwm<0>;
		using signal = peripheral::Pwmextrg<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Uart0Utxd0,
			SscRd,
			Pwm0Pwmextrg0>;
};
struct A11
{
	static constexpr PortName port = PortName::A;
	static constexpr uint32_t pin = 11;

	struct QspiQcs
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Qspi;
		using signal = peripheral::Qcs;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Pwm1Pwml0
	{
		static constexpr PinFunction function{PinFunction::C};
		using peripheral = Peripherals::Pwm<1>;
		using signal = peripheral::Pwml<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Pwm0Pwmh0
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Pwm<0>;
		using signal = peripheral::Pwmh<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			QspiQcs,
			Pwm1Pwml0,
			Pwm0Pwmh0>;
};
struct A12
{
	static constexpr PortName port = PortName::A;
	static constexpr uint32_t pin = 12;

	struct Pwm0Pwmh1
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Pwm<0>;
		using signal = peripheral::Pwmh<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Pwm1Pwmh0
	{
		static constexpr PinFunction function{PinFunction::C};
		using peripheral = Peripherals::Pwm<1>;
		using signal = peripheral::Pwmh<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct QspiQio1
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Qspi;
		using signal = peripheral::Qio<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Pwm0Pwmh1,
			Pwm1Pwmh0,
			QspiQio1>;
};
struct A13
{
	static constexpr PortName port = PortName::A;
	static constexpr uint32_t pin = 13;

	struct QspiQio0
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Qspi;
		using signal = peripheral::Qio<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Pwm0Pwmh2
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Pwm<0>;
		using signal = peripheral::Pwmh<2>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Pwm1Pwml1
	{
		static constexpr PinFunction function{PinFunction::C};
		using peripheral = Peripherals::Pwm<1>;
		using signal = peripheral::Pwml<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			QspiQio0,
			Pwm0Pwmh2,
			Pwm1Pwml1>;
};
struct A14
{
	static constexpr PortName port = PortName::A;
	static constexpr uint32_t pin = 14;

	struct Pwm1Pwmh1
	{
		static constexpr PinFunction function{PinFunction::C};
		using peripheral = Peripherals::Pwm<1>;
		using signal = peripheral::Pwmh<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Pwm0Pwmh3
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Pwm<0>;
		using signal = peripheral::Pwmh<3>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct QspiQsck
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Qspi;
		using signal = peripheral::Qsck;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Pwm1Pwmh1,
			Pwm0Pwmh3,
			QspiQsck>;
};
struct A15
{
	static constexpr PortName port = PortName::A;
	static constexpr uint32_t pin = 15;

	struct Pwm0Pwml3
	{
		static constexpr PinFunction function{PinFunction::C};
		using peripheral = Peripherals::Pwm<0>;
		using signal = peripheral::Pwml<3>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Tc0Tioa1
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Tc<0>;
		using signal = peripheral::Tioa<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Pwm0Pwml3,
			Tc0Tioa1>;
};
struct A16
{
	static constexpr PortName port = PortName::A;
	static constexpr uint32_t pin = 16;

	struct Pwm0Pwml2
	{
		static constexpr PinFunction function{PinFunction::C};
		using peripheral = Peripherals::Pwm<0>;
		using signal = peripheral::Pwml<2>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Tc0Tiob1
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Tc<0>;
		using signal = peripheral::Tiob<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Pwm0Pwml2,
			Tc0Tiob1>;
};
struct A17
{
	static constexpr PortName port = PortName::A;
	static constexpr uint32_t pin = 17;

	struct Afec0Ad6
	{
		static constexpr PinFunction function{PinFunction::X1};
		using peripheral = Peripherals::Afec<0>;
		using signal = peripheral::Ad;
		static constexpr int32_t AdcChannel = 6;
	};
	struct PmcPck1
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Pmc;
		using signal = peripheral::Pck<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Pwm0Pwmh3
	{
		static constexpr PinFunction function{PinFunction::C};
		using peripheral = Peripherals::Pwm<0>;
		using signal = peripheral::Pwmh<3>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct QspiQio2
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Qspi;
		using signal = peripheral::Qio<2>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Afec0Ad6,
			PmcPck1,
			Pwm0Pwmh3,
			QspiQio2>;
};
struct A18
{
	static constexpr PortName port = PortName::A;
	static constexpr uint32_t pin = 18;

	struct Afec0Ad7
	{
		static constexpr PinFunction function{PinFunction::X1};
		using peripheral = Peripherals::Afec<0>;
		using signal = peripheral::Ad;
		static constexpr int32_t AdcChannel = 7;
	};
	struct Pwm1Pwmextrg1
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Pwm<1>;
		using signal = peripheral::Pwmextrg<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct PmcPck2
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Pmc;
		using signal = peripheral::Pck<2>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Afec0Ad7,
			Pwm1Pwmextrg1,
			PmcPck2>;
};
struct A19
{
	static constexpr PortName port = PortName::A;
	static constexpr uint32_t pin = 19;

	struct Pwm0Pwml0
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Pwm<0>;
		using signal = peripheral::Pwml<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Afec0Wkup9
	{
		static constexpr PinFunction function{PinFunction::X1};
		using peripheral = Peripherals::Afec<0>;
		using signal = peripheral::Wkup;
		static constexpr int32_t AdcChannel = 9;
	};
	struct Afec0Ad8
	{
		static constexpr PinFunction function{PinFunction::X1};
		using peripheral = Peripherals::Afec<0>;
		using signal = peripheral::Ad;
		static constexpr int32_t AdcChannel = 8;
	};
	using Signals =
		std::tuple<
			Pwm0Pwml0,
			Afec0Wkup9,
			Afec0Ad8>;
};
struct A20
{
	static constexpr PortName port = PortName::A;
	static constexpr uint32_t pin = 20;

	struct Pwm0Pwml1
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Pwm<0>;
		using signal = peripheral::Pwml<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Afec0Ad9
	{
		static constexpr PinFunction function{PinFunction::X1};
		using peripheral = Peripherals::Afec<0>;
		using signal = peripheral::Ad;
		static constexpr int32_t AdcChannel = 9;
	};
	struct Afec0Wkup10
	{
		static constexpr PinFunction function{PinFunction::X1};
		using peripheral = Peripherals::Afec<0>;
		using signal = peripheral::Wkup;
		static constexpr int32_t AdcChannel = 10;
	};
	using Signals =
		std::tuple<
			Pwm0Pwml1,
			Afec0Ad9,
			Afec0Wkup10>;
};
struct A21
{
	static constexpr PortName port = PortName::A;
	static constexpr uint32_t pin = 21;

	struct Afec0Ad1
	{
		static constexpr PinFunction function{PinFunction::X1};
		using peripheral = Peripherals::Afec<0>;
		using signal = peripheral::Ad;
		static constexpr int32_t AdcChannel = 1;
	};
	struct Pwm1Pwmfi0
	{
		static constexpr PinFunction function{PinFunction::C};
		using peripheral = Peripherals::Pwm<1>;
		using signal = peripheral::Pwmfi<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Afec0Piodcen2
	{
		static constexpr PinFunction function{PinFunction::X1};
		using peripheral = Peripherals::Afec<0>;
		using signal = peripheral::Piodcen;
		static constexpr int32_t AdcChannel = 2;
	};
	struct Usart1Rxd1
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Usart<1>;
		using signal = peripheral::Rxd<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct PmcPck1
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Pmc;
		using signal = peripheral::Pck<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Afec0Ad1,
			Pwm1Pwmfi0,
			Afec0Piodcen2,
			Usart1Rxd1,
			PmcPck1>;
};
struct A22
{
	static constexpr PortName port = PortName::A;
	static constexpr uint32_t pin = 22;

	struct Pwm0Pwmextrg1
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Pwm<0>;
		using signal = peripheral::Pwmextrg<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct SscRk
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Ssc;
		using signal = peripheral::Rk;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Pwm0Pwmextrg1,
			SscRk>;
};
struct A23
{
	static constexpr PortName port = PortName::A;
	static constexpr uint32_t pin = 23;

	struct Pwm1Pwml2
	{
		static constexpr PinFunction function{PinFunction::D};
		using peripheral = Peripherals::Pwm<1>;
		using signal = peripheral::Pwml<2>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Usart1Sck1
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Usart<1>;
		using signal = peripheral::Sck<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Pwm0Pwmh0
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Pwm<0>;
		using signal = peripheral::Pwmh<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Pwm1Pwml2,
			Usart1Sck1,
			Pwm0Pwmh0>;
};
struct A24
{
	static constexpr PortName port = PortName::A;
	static constexpr uint32_t pin = 24;

	struct Usart1Rts1
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Usart<1>;
		using signal = peripheral::Rts<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Pwm0Pwmh1
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Pwm<0>;
		using signal = peripheral::Pwmh<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct IsiPck
	{
		static constexpr PinFunction function{PinFunction::D};
		using peripheral = Peripherals::Isi;
		using signal = peripheral::Pck;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Usart1Rts1,
			Pwm0Pwmh1,
			IsiPck>;
};
struct A25
{
	static constexpr PortName port = PortName::A;
	static constexpr uint32_t pin = 25;

	struct Pwm0Pwmh2
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Pwm<0>;
		using signal = peripheral::Pwmh<2>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct HsmciMcck
	{
		static constexpr PinFunction function{PinFunction::D};
		using peripheral = Peripherals::Hsmci;
		using signal = peripheral::Mcck;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Usart1Cts1
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Usart<1>;
		using signal = peripheral::Cts<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Pwm0Pwmh2,
			HsmciMcck,
			Usart1Cts1>;
};
struct A26
{
	static constexpr PortName port = PortName::A;
	static constexpr uint32_t pin = 26;

	struct Pwm1Pwmfi1
	{
		static constexpr PinFunction function{PinFunction::D};
		using peripheral = Peripherals::Pwm<1>;
		using signal = peripheral::Pwmfi<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Tc0Tioa2
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Tc<0>;
		using signal = peripheral::Tioa<2>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct HsmciMcda2
	{
		static constexpr PinFunction function{PinFunction::C};
		using peripheral = Peripherals::Hsmci;
		using signal = peripheral::Mcda<2>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Usart1Dcd1
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Usart<1>;
		using signal = peripheral::Dcd<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Pwm1Pwmfi1,
			Tc0Tioa2,
			HsmciMcda2,
			Usart1Dcd1>;
};
struct A27
{
	static constexpr PortName port = PortName::A;
	static constexpr uint32_t pin = 27;

	struct IsiD7
	{
		static constexpr PinFunction function{PinFunction::D};
		using peripheral = Peripherals::Isi;
		using signal = peripheral::D<7>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Usart1Dtr1
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Usart<1>;
		using signal = peripheral::Dtr<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Tc0Tiob2
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Tc<0>;
		using signal = peripheral::Tiob<2>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct HsmciMcda3
	{
		static constexpr PinFunction function{PinFunction::C};
		using peripheral = Peripherals::Hsmci;
		using signal = peripheral::Mcda<3>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			IsiD7,
			Usart1Dtr1,
			Tc0Tiob2,
			HsmciMcda3>;
};
struct A28
{
	static constexpr PortName port = PortName::A;
	static constexpr uint32_t pin = 28;

	struct Usart1Dsr1
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Usart<1>;
		using signal = peripheral::Dsr<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Pwm1Pwmfi2
	{
		static constexpr PinFunction function{PinFunction::D};
		using peripheral = Peripherals::Pwm<1>;
		using signal = peripheral::Pwmfi<2>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Tc0Tclk1
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Tc<0>;
		using signal = peripheral::Tclk<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct HsmciMccda
	{
		static constexpr PinFunction function{PinFunction::C};
		using peripheral = Peripherals::Hsmci;
		using signal = peripheral::Mccda;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Usart1Dsr1,
			Pwm1Pwmfi2,
			Tc0Tclk1,
			HsmciMccda>;
};
struct A30
{
	static constexpr PortName port = PortName::A;
	static constexpr uint32_t pin = 30;

	struct Pwm1Pwmextrg0
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Pwm<1>;
		using signal = peripheral::Pwmextrg<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Pwm0Pwml2
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Pwm<0>;
		using signal = peripheral::Pwml<2>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct HsmciMcda0
	{
		static constexpr PinFunction function{PinFunction::C};
		using peripheral = Peripherals::Hsmci;
		using signal = peripheral::Mcda<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Pwm1Pwmextrg0,
			Pwm0Pwml2,
			HsmciMcda0>;
};
struct A31
{
	static constexpr PortName port = PortName::A;
	static constexpr uint32_t pin = 31;

	struct HsmciMcda1
	{
		static constexpr PinFunction function{PinFunction::C};
		using peripheral = Peripherals::Hsmci;
		using signal = peripheral::Mcda<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct PmcPck2
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Pmc;
		using signal = peripheral::Pck<2>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Pwm1Pwmh2
	{
		static constexpr PinFunction function{PinFunction::D};
		using peripheral = Peripherals::Pwm<1>;
		using signal = peripheral::Pwmh<2>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Spi0Npcs1
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Spi<0>;
		using signal = peripheral::Npcs<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			HsmciMcda1,
			PmcPck2,
			Pwm1Pwmh2,
			Spi0Npcs1>;
};
struct B0
{
	static constexpr PortName port = PortName::B;
	static constexpr uint32_t pin = 0;

	struct Afec0Ad10
	{
		static constexpr PinFunction function{PinFunction::X1};
		using peripheral = Peripherals::Afec<0>;
		using signal = peripheral::Ad;
		static constexpr int32_t AdcChannel = 10;
	};
	struct Usart0Rxd0
	{
		static constexpr PinFunction function{PinFunction::C};
		using peripheral = Peripherals::Usart<0>;
		using signal = peripheral::Rxd<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Afec0Rtcout0
	{
		static constexpr PinFunction function{PinFunction::X1};
		using peripheral = Peripherals::Afec<0>;
		using signal = peripheral::Rtcout;
		static constexpr int32_t AdcChannel = 0;
	};
	struct Pwm0Pwmh0
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Pwm<0>;
		using signal = peripheral::Pwmh<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct SscTf
	{
		static constexpr PinFunction function{PinFunction::D};
		using peripheral = Peripherals::Ssc;
		using signal = peripheral::Tf;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Afec0Ad10,
			Usart0Rxd0,
			Afec0Rtcout0,
			Pwm0Pwmh0,
			SscTf>;
};
struct B1
{
	static constexpr PortName port = PortName::B;
	static constexpr uint32_t pin = 1;

	struct Usart0Txd0
	{
		static constexpr PinFunction function{PinFunction::C};
		using peripheral = Peripherals::Usart<0>;
		using signal = peripheral::Txd<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Afec1Ad0
	{
		static constexpr PinFunction function{PinFunction::X1};
		using peripheral = Peripherals::Afec<1>;
		using signal = peripheral::Ad;
		static constexpr int32_t AdcChannel = 0;
	};
	struct SscTk
	{
		static constexpr PinFunction function{PinFunction::D};
		using peripheral = Peripherals::Ssc;
		using signal = peripheral::Tk;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Afec1Rtcout1
	{
		static constexpr PinFunction function{PinFunction::X1};
		using peripheral = Peripherals::Afec<1>;
		using signal = peripheral::Rtcout;
		static constexpr int32_t AdcChannel = 1;
	};
	struct GmacGtsucomp
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Gmac;
		using signal = peripheral::Gtsucomp;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Pwm0Pwmh1
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Pwm<0>;
		using signal = peripheral::Pwmh<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Usart0Txd0,
			Afec1Ad0,
			SscTk,
			Afec1Rtcout1,
			GmacGtsucomp,
			Pwm0Pwmh1>;
};
struct B2
{
	static constexpr PortName port = PortName::B;
	static constexpr uint32_t pin = 2;

	struct Afec0Ad5
	{
		static constexpr PinFunction function{PinFunction::X1};
		using peripheral = Peripherals::Afec<0>;
		using signal = peripheral::Ad;
		static constexpr int32_t AdcChannel = 5;
	};
	struct Mcan0Cantx0
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Mcan<0>;
		using signal = peripheral::Cantx<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Usart0Cts0
	{
		static constexpr PinFunction function{PinFunction::C};
		using peripheral = Peripherals::Usart<0>;
		using signal = peripheral::Cts<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Spi0Npcs0
	{
		static constexpr PinFunction function{PinFunction::D};
		using peripheral = Peripherals::Spi<0>;
		using signal = peripheral::Npcs<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Afec0Ad5,
			Mcan0Cantx0,
			Usart0Cts0,
			Spi0Npcs0>;
};
struct B3
{
	static constexpr PortName port = PortName::B;
	static constexpr uint32_t pin = 3;

	struct IsiD2
	{
		static constexpr PinFunction function{PinFunction::D};
		using peripheral = Peripherals::Isi;
		using signal = peripheral::D<2>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Usart0Rts0
	{
		static constexpr PinFunction function{PinFunction::C};
		using peripheral = Peripherals::Usart<0>;
		using signal = peripheral::Rts<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Afec0Ad2
	{
		static constexpr PinFunction function{PinFunction::X1};
		using peripheral = Peripherals::Afec<0>;
		using signal = peripheral::Ad;
		static constexpr int32_t AdcChannel = 2;
	};
	struct Afec0Wkup12
	{
		static constexpr PinFunction function{PinFunction::X1};
		using peripheral = Peripherals::Afec<0>;
		using signal = peripheral::Wkup;
		static constexpr int32_t AdcChannel = 12;
	};
	struct Mcan0Canrx0
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Mcan<0>;
		using signal = peripheral::Canrx<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct PmcPck2
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Pmc;
		using signal = peripheral::Pck<2>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			IsiD2,
			Usart0Rts0,
			Afec0Ad2,
			Afec0Wkup12,
			Mcan0Canrx0,
			PmcPck2>;
};
struct B4
{
	static constexpr PortName port = PortName::B;
	static constexpr uint32_t pin = 4;

	struct Usart1Txd1
	{
		static constexpr PinFunction function{PinFunction::D};
		using peripheral = Peripherals::Usart<1>;
		using signal = peripheral::Txd<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Pwm0Pwmh2
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Pwm<0>;
		using signal = peripheral::Pwmh<2>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Twihs1Twd1
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Twihs<1>;
		using signal = peripheral::Twd<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Usart1Txd1,
			Pwm0Pwmh2,
			Twihs1Twd1>;
};
struct B5
{
	static constexpr PortName port = PortName::B;
	static constexpr uint32_t pin = 5;

	struct Pwm0Pwml0
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Pwm<0>;
		using signal = peripheral::Pwml<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Twihs1Twck1
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Twihs<1>;
		using signal = peripheral::Twck<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct SscTd
	{
		static constexpr PinFunction function{PinFunction::D};
		using peripheral = Peripherals::Ssc;
		using signal = peripheral::Td;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Pwm0Pwml0,
			Twihs1Twck1,
			SscTd>;
};
struct B6
{
	static constexpr PortName port = PortName::B;
	static constexpr uint32_t pin = 6;

};
struct B7
{
	static constexpr PortName port = PortName::B;
	static constexpr uint32_t pin = 7;

};
struct B8
{
	static constexpr PortName port = PortName::B;
	static constexpr uint32_t pin = 8;

};
struct B9
{
	static constexpr PortName port = PortName::B;
	static constexpr uint32_t pin = 9;

};
struct B12
{
	static constexpr PortName port = PortName::B;
	static constexpr uint32_t pin = 12;

	struct PmcPck0
	{
		static constexpr PinFunction function{PinFunction::D};
		using peripheral = Peripherals::Pmc;
		using signal = peripheral::Pck<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Pwm0Pwml1
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Pwm<0>;
		using signal = peripheral::Pwml<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct GmacGtsucomp
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Gmac;
		using signal = peripheral::Gtsucomp;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			PmcPck0,
			Pwm0Pwml1,
			GmacGtsucomp>;
};
struct B13
{
	static constexpr PortName port = PortName::B;
	static constexpr uint32_t pin = 13;

	struct DaccDac0
	{
		static constexpr PinFunction function{PinFunction::X1};
		using peripheral = Peripherals::Dacc;
		using signal = peripheral::Dac<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Pwm0Pwml2
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Pwm<0>;
		using signal = peripheral::Pwml<2>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Usart0Sck0
	{
		static constexpr PinFunction function{PinFunction::C};
		using peripheral = Peripherals::Usart<0>;
		using signal = peripheral::Sck<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct PmcPck0
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Pmc;
		using signal = peripheral::Pck<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			DaccDac0,
			Pwm0Pwml2,
			Usart0Sck0,
			PmcPck0>;
};
struct D0
{
	static constexpr PortName port = PortName::D;
	static constexpr uint32_t pin = 0;

	struct Pwm1Pwml0
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Pwm<1>;
		using signal = peripheral::Pwml<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct DaccDac1
	{
		static constexpr PinFunction function{PinFunction::X1};
		using peripheral = Peripherals::Dacc;
		using signal = peripheral::Dac<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct GmacGtxck
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Gmac;
		using signal = peripheral::Gtxck;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Usart0Dcd0
	{
		static constexpr PinFunction function{PinFunction::D};
		using peripheral = Peripherals::Usart<0>;
		using signal = peripheral::Dcd<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Pwm1Pwml0,
			DaccDac1,
			GmacGtxck,
			Usart0Dcd0>;
};
struct D1
{
	static constexpr PortName port = PortName::D;
	static constexpr uint32_t pin = 1;

	struct Pwm1Pwmh0
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Pwm<1>;
		using signal = peripheral::Pwmh<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Usart0Dtr0
	{
		static constexpr PinFunction function{PinFunction::D};
		using peripheral = Peripherals::Usart<0>;
		using signal = peripheral::Dtr<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct GmacGtxen
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Gmac;
		using signal = peripheral::Gtxen;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Pwm1Pwmh0,
			Usart0Dtr0,
			GmacGtxen>;
};
struct D2
{
	static constexpr PortName port = PortName::D;
	static constexpr uint32_t pin = 2;

	struct Pwm1Pwml1
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Pwm<1>;
		using signal = peripheral::Pwml<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Usart0Dsr0
	{
		static constexpr PinFunction function{PinFunction::D};
		using peripheral = Peripherals::Usart<0>;
		using signal = peripheral::Dsr<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct GmacGtx0
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Gmac;
		using signal = peripheral::Gtx<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Pwm1Pwml1,
			Usart0Dsr0,
			GmacGtx0>;
};
struct D3
{
	static constexpr PortName port = PortName::D;
	static constexpr uint32_t pin = 3;

	struct Uart4Utxd4
	{
		static constexpr PinFunction function{PinFunction::C};
		using peripheral = Peripherals::Uart<4>;
		using signal = peripheral::Utxd<4>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Pwm1Pwmh1
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Pwm<1>;
		using signal = peripheral::Pwmh<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct GmacGtx1
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Gmac;
		using signal = peripheral::Gtx<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Usart0Ri0
	{
		static constexpr PinFunction function{PinFunction::D};
		using peripheral = Peripherals::Usart<0>;
		using signal = peripheral::Ri<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Uart4Utxd4,
			Pwm1Pwmh1,
			GmacGtx1,
			Usart0Ri0>;
};
struct D4
{
	static constexpr PortName port = PortName::D;
	static constexpr uint32_t pin = 4;

	struct Usart2Dcd2
	{
		static constexpr PinFunction function{PinFunction::D};
		using peripheral = Peripherals::Usart<2>;
		using signal = peripheral::Dcd<2>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct GmacGrxdv
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Gmac;
		using signal = peripheral::Grxdv;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Pwm1Pwml2
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Pwm<1>;
		using signal = peripheral::Pwml<2>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Usart2Dcd2,
			GmacGrxdv,
			Pwm1Pwml2>;
};
struct D5
{
	static constexpr PortName port = PortName::D;
	static constexpr uint32_t pin = 5;

	struct Pwm1Pwmh2
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Pwm<1>;
		using signal = peripheral::Pwmh<2>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Usart2Dtr2
	{
		static constexpr PinFunction function{PinFunction::D};
		using peripheral = Peripherals::Usart<2>;
		using signal = peripheral::Dtr<2>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct GmacGrx0
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Gmac;
		using signal = peripheral::Grx<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Pwm1Pwmh2,
			Usart2Dtr2,
			GmacGrx0>;
};
struct D6
{
	static constexpr PortName port = PortName::D;
	static constexpr uint32_t pin = 6;

	struct Usart2Dsr2
	{
		static constexpr PinFunction function{PinFunction::D};
		using peripheral = Peripherals::Usart<2>;
		using signal = peripheral::Dsr<2>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Pwm1Pwml3
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Pwm<1>;
		using signal = peripheral::Pwml<3>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct GmacGrx1
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Gmac;
		using signal = peripheral::Grx<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Usart2Dsr2,
			Pwm1Pwml3,
			GmacGrx1>;
};
struct D7
{
	static constexpr PortName port = PortName::D;
	static constexpr uint32_t pin = 7;

	struct Pwm1Pwmh3
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Pwm<1>;
		using signal = peripheral::Pwmh<3>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Usart2Ri2
	{
		static constexpr PinFunction function{PinFunction::D};
		using peripheral = Peripherals::Usart<2>;
		using signal = peripheral::Ri<2>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct GmacGrxer
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Gmac;
		using signal = peripheral::Grxer;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Pwm1Pwmh3,
			Usart2Ri2,
			GmacGrxer>;
};
struct D8
{
	static constexpr PortName port = PortName::D;
	static constexpr uint32_t pin = 8;

	struct GmacGmdc
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Gmac;
		using signal = peripheral::Gmdc;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Pwm0Pwmfi1
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Pwm<0>;
		using signal = peripheral::Pwmfi<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			GmacGmdc,
			Pwm0Pwmfi1>;
};
struct D9
{
	static constexpr PortName port = PortName::D;
	static constexpr uint32_t pin = 9;

	struct Pwm0Pwmfi2
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Pwm<0>;
		using signal = peripheral::Pwmfi<2>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct GmacGmdio
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Gmac;
		using signal = peripheral::Gmdio;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Afec1Adtrg
	{
		static constexpr PinFunction function{PinFunction::C};
		using peripheral = Peripherals::Afec<1>;
		using signal = peripheral::Adtrg;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Pwm0Pwmfi2,
			GmacGmdio,
			Afec1Adtrg>;
};
struct D10
{
	static constexpr PortName port = PortName::D;
	static constexpr uint32_t pin = 10;

	struct SscTd
	{
		static constexpr PinFunction function{PinFunction::C};
		using peripheral = Peripherals::Ssc;
		using signal = peripheral::Td;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Pwm0Pwml0
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Pwm<0>;
		using signal = peripheral::Pwml<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct GmacGcrs
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Gmac;
		using signal = peripheral::Gcrs;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			SscTd,
			Pwm0Pwml0,
			GmacGcrs>;
};
struct D11
{
	static constexpr PortName port = PortName::D;
	static constexpr uint32_t pin = 11;

	struct GmacGrx2
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Gmac;
		using signal = peripheral::Grx<2>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Pwm0Pwmh0
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Pwm<0>;
		using signal = peripheral::Pwmh<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct IsiD5
	{
		static constexpr PinFunction function{PinFunction::D};
		using peripheral = Peripherals::Isi;
		using signal = peripheral::D<5>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct GmacGtsucomp
	{
		static constexpr PinFunction function{PinFunction::C};
		using peripheral = Peripherals::Gmac;
		using signal = peripheral::Gtsucomp;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			GmacGrx2,
			Pwm0Pwmh0,
			IsiD5,
			GmacGtsucomp>;
};
struct D12
{
	static constexpr PortName port = PortName::D;
	static constexpr uint32_t pin = 12;

	struct Mcan1Cantx1
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Mcan<1>;
		using signal = peripheral::Cantx<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Spi0Npcs2
	{
		static constexpr PinFunction function{PinFunction::C};
		using peripheral = Peripherals::Spi<0>;
		using signal = peripheral::Npcs<2>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct IsiD6
	{
		static constexpr PinFunction function{PinFunction::D};
		using peripheral = Peripherals::Isi;
		using signal = peripheral::D<6>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct GmacGrx3
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Gmac;
		using signal = peripheral::Grx<3>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Mcan1Cantx1,
			Spi0Npcs2,
			IsiD6,
			GmacGrx3>;
};
struct D13
{
	static constexpr PortName port = PortName::D;
	static constexpr uint32_t pin = 13;

	struct GmacGcol
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Gmac;
		using signal = peripheral::Gcol;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			GmacGcol>;
};
struct D14
{
	static constexpr PortName port = PortName::D;
	static constexpr uint32_t pin = 14;

	struct GmacGrxck
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Gmac;
		using signal = peripheral::Grxck;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			GmacGrxck>;
};
struct D15
{
	static constexpr PortName port = PortName::D;
	static constexpr uint32_t pin = 15;

	struct GmacGtx2
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Gmac;
		using signal = peripheral::Gtx<2>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Usart2Rxd2
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Usart<2>;
		using signal = peripheral::Rxd<2>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			GmacGtx2,
			Usart2Rxd2>;
};
struct D16
{
	static constexpr PortName port = PortName::D;
	static constexpr uint32_t pin = 16;

	struct GmacGtx3
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Gmac;
		using signal = peripheral::Gtx<3>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Usart2Txd2
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Usart<2>;
		using signal = peripheral::Txd<2>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			GmacGtx3,
			Usart2Txd2>;
};
struct D17
{
	static constexpr PortName port = PortName::D;
	static constexpr uint32_t pin = 17;

	struct GmacGtxer
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Gmac;
		using signal = peripheral::Gtxer;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Usart2Sck2
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Usart<2>;
		using signal = peripheral::Sck<2>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			GmacGtxer,
			Usart2Sck2>;
};
struct D18
{
	static constexpr PortName port = PortName::D;
	static constexpr uint32_t pin = 18;

	struct Uart4Urxd4
	{
		static constexpr PinFunction function{PinFunction::C};
		using peripheral = Peripherals::Uart<4>;
		using signal = peripheral::Urxd<4>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Usart2Rts2
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Usart<2>;
		using signal = peripheral::Rts<2>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Uart4Urxd4,
			Usart2Rts2>;
};
struct D19
{
	static constexpr PortName port = PortName::D;
	static constexpr uint32_t pin = 19;

	struct Uart4Utxd4
	{
		static constexpr PinFunction function{PinFunction::C};
		using peripheral = Peripherals::Uart<4>;
		using signal = peripheral::Utxd<4>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Usart2Cts2
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Usart<2>;
		using signal = peripheral::Cts<2>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Uart4Utxd4,
			Usart2Cts2>;
};
struct D20
{
	static constexpr PortName port = PortName::D;
	static constexpr uint32_t pin = 20;

	struct Spi0Miso
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Spi<0>;
		using signal = peripheral::Miso;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Pwm0Pwmh0
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Pwm<0>;
		using signal = peripheral::Pwmh<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct GmacGtsucomp
	{
		static constexpr PinFunction function{PinFunction::C};
		using peripheral = Peripherals::Gmac;
		using signal = peripheral::Gtsucomp;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Spi0Miso,
			Pwm0Pwmh0,
			GmacGtsucomp>;
};
struct D21
{
	static constexpr PortName port = PortName::D;
	static constexpr uint32_t pin = 21;

	struct Spi0Mosi
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Spi<0>;
		using signal = peripheral::Mosi;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Pwm0Pwmh1
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Pwm<0>;
		using signal = peripheral::Pwmh<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Tc3Tioa11
	{
		static constexpr PinFunction function{PinFunction::C};
		using peripheral = Peripherals::Tc<3>;
		using signal = peripheral::Tioa<11>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct IsiD1
	{
		static constexpr PinFunction function{PinFunction::D};
		using peripheral = Peripherals::Isi;
		using signal = peripheral::D<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Spi0Mosi,
			Pwm0Pwmh1,
			Tc3Tioa11,
			IsiD1>;
};
struct D22
{
	static constexpr PortName port = PortName::D;
	static constexpr uint32_t pin = 22;

	struct Tc3Tiob11
	{
		static constexpr PinFunction function{PinFunction::C};
		using peripheral = Peripherals::Tc<3>;
		using signal = peripheral::Tiob<11>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Spi0Spck
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Spi<0>;
		using signal = peripheral::Spck;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Pwm0Pwmh2
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Pwm<0>;
		using signal = peripheral::Pwmh<2>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct IsiD0
	{
		static constexpr PinFunction function{PinFunction::D};
		using peripheral = Peripherals::Isi;
		using signal = peripheral::D<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Tc3Tiob11,
			Spi0Spck,
			Pwm0Pwmh2,
			IsiD0>;
};
struct D24
{
	static constexpr PortName port = PortName::D;
	static constexpr uint32_t pin = 24;

	struct Pwm0Pwml0
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Pwm<0>;
		using signal = peripheral::Pwml<0>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct SscRf
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Ssc;
		using signal = peripheral::Rf;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Tc3Tclk11
	{
		static constexpr PinFunction function{PinFunction::C};
		using peripheral = Peripherals::Tc<3>;
		using signal = peripheral::Tclk<11>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct IsiHsync
	{
		static constexpr PinFunction function{PinFunction::D};
		using peripheral = Peripherals::Isi;
		using signal = peripheral::Hsync;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Pwm0Pwml0,
			SscRf,
			Tc3Tclk11,
			IsiHsync>;
};
struct D25
{
	static constexpr PortName port = PortName::D;
	static constexpr uint32_t pin = 25;

	struct Spi0Npcs1
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Spi<0>;
		using signal = peripheral::Npcs<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Uart2Urxd2
	{
		static constexpr PinFunction function{PinFunction::C};
		using peripheral = Peripherals::Uart<2>;
		using signal = peripheral::Urxd<2>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct IsiVsync
	{
		static constexpr PinFunction function{PinFunction::D};
		using peripheral = Peripherals::Isi;
		using signal = peripheral::Vsync;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Pwm0Pwml1
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Pwm<0>;
		using signal = peripheral::Pwml<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Spi0Npcs1,
			Uart2Urxd2,
			IsiVsync,
			Pwm0Pwml1>;
};
struct D26
{
	static constexpr PortName port = PortName::D;
	static constexpr uint32_t pin = 26;

	struct Uart1Utxd1
	{
		static constexpr PinFunction function{PinFunction::D};
		using peripheral = Peripherals::Uart<1>;
		using signal = peripheral::Utxd<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Uart2Utxd2
	{
		static constexpr PinFunction function{PinFunction::C};
		using peripheral = Peripherals::Uart<2>;
		using signal = peripheral::Utxd<2>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Pwm0Pwml2
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Pwm<0>;
		using signal = peripheral::Pwml<2>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct SscTd
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Ssc;
		using signal = peripheral::Td;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Uart1Utxd1,
			Uart2Utxd2,
			Pwm0Pwml2,
			SscTd>;
};
struct D27
{
	static constexpr PortName port = PortName::D;
	static constexpr uint32_t pin = 27;

	struct Spi0Npcs3
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Spi<0>;
		using signal = peripheral::Npcs<3>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Twihs2Twd2
	{
		static constexpr PinFunction function{PinFunction::C};
		using peripheral = Peripherals::Twihs<2>;
		using signal = peripheral::Twd<2>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Pwm0Pwml3
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Pwm<0>;
		using signal = peripheral::Pwml<3>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct IsiD8
	{
		static constexpr PinFunction function{PinFunction::D};
		using peripheral = Peripherals::Isi;
		using signal = peripheral::D<8>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Spi0Npcs3,
			Twihs2Twd2,
			Pwm0Pwml3,
			IsiD8>;
};
struct D28
{
	static constexpr PortName port = PortName::D;
	static constexpr uint32_t pin = 28;

	struct Mcan1Canrx1
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Mcan<1>;
		using signal = peripheral::Canrx<1>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Twihs2Twck2
	{
		static constexpr PinFunction function{PinFunction::C};
		using peripheral = Peripherals::Twihs<2>;
		using signal = peripheral::Twck<2>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Uart3Urxd3
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Uart<3>;
		using signal = peripheral::Urxd<3>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct IsiD9
	{
		static constexpr PinFunction function{PinFunction::D};
		using peripheral = Peripherals::Isi;
		using signal = peripheral::D<9>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Mcan1Canrx1,
			Twihs2Twck2,
			Uart3Urxd3,
			IsiD9>;
};
struct D30
{
	static constexpr PortName port = PortName::D;
	static constexpr uint32_t pin = 30;

	struct IsiD10
	{
		static constexpr PinFunction function{PinFunction::D};
		using peripheral = Peripherals::Isi;
		using signal = peripheral::D<10>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Uart3Utxd3
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Uart<3>;
		using signal = peripheral::Utxd<3>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct Afec0Ad0
	{
		static constexpr PinFunction function{PinFunction::X1};
		using peripheral = Peripherals::Afec<0>;
		using signal = peripheral::Ad;
		static constexpr int32_t AdcChannel = 0;
	};
	using Signals =
		std::tuple<
			IsiD10,
			Uart3Utxd3,
			Afec0Ad0>;
};
struct D31
{
	static constexpr PortName port = PortName::D;
	static constexpr uint32_t pin = 31;

	struct Uart3Utxd3
	{
		static constexpr PinFunction function{PinFunction::B};
		using peripheral = Peripherals::Uart<3>;
		using signal = peripheral::Utxd<3>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct PmcPck2
	{
		static constexpr PinFunction function{PinFunction::C};
		using peripheral = Peripherals::Pmc;
		using signal = peripheral::Pck<2>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct IsiD11
	{
		static constexpr PinFunction function{PinFunction::D};
		using peripheral = Peripherals::Isi;
		using signal = peripheral::D<11>;
		static constexpr int32_t AdcChannel = -1;
	};
	struct QspiQio3
	{
		static constexpr PinFunction function{PinFunction::A};
		using peripheral = Peripherals::Qspi;
		using signal = peripheral::Qio<3>;
		static constexpr int32_t AdcChannel = -1;
	};
	using Signals =
		std::tuple<
			Uart3Utxd3,
			PmcPck2,
			IsiD11,
			QspiQio3>;
};
}  // namespace gpio
/// @endcond

/// @ingroup modm_platform_gpio
/// @{
using GpioA0 = Gpio<gpio::A0>;
using GpioA1 = Gpio<gpio::A1>;
using GpioA2 = Gpio<gpio::A2>;
using GpioA3 = Gpio<gpio::A3>;
using GpioA4 = Gpio<gpio::A4>;
using GpioA5 = Gpio<gpio::A5>;
using GpioA7 = Gpio<gpio::A7>;
using GpioA8 = Gpio<gpio::A8>;
using GpioA9 = Gpio<gpio::A9>;
using GpioA10 = Gpio<gpio::A10>;
using GpioA11 = Gpio<gpio::A11>;
using GpioA12 = Gpio<gpio::A12>;
using GpioA13 = Gpio<gpio::A13>;
using GpioA14 = Gpio<gpio::A14>;
using GpioA15 = Gpio<gpio::A15>;
using GpioA16 = Gpio<gpio::A16>;
using GpioA17 = Gpio<gpio::A17>;
using GpioA18 = Gpio<gpio::A18>;
using GpioA19 = Gpio<gpio::A19>;
using GpioA20 = Gpio<gpio::A20>;
using GpioA21 = Gpio<gpio::A21>;
using GpioA22 = Gpio<gpio::A22>;
using GpioA23 = Gpio<gpio::A23>;
using GpioA24 = Gpio<gpio::A24>;
using GpioA25 = Gpio<gpio::A25>;
using GpioA26 = Gpio<gpio::A26>;
using GpioA27 = Gpio<gpio::A27>;
using GpioA28 = Gpio<gpio::A28>;
using GpioA30 = Gpio<gpio::A30>;
using GpioA31 = Gpio<gpio::A31>;
using GpioB0 = Gpio<gpio::B0>;
using GpioB1 = Gpio<gpio::B1>;
using GpioB2 = Gpio<gpio::B2>;
using GpioB3 = Gpio<gpio::B3>;
using GpioB4 = Gpio<gpio::B4>;
using GpioB5 = Gpio<gpio::B5>;
using GpioB6 = Gpio<gpio::B6>;
using GpioB7 = Gpio<gpio::B7>;
using GpioB8 = Gpio<gpio::B8>;
using GpioB9 = Gpio<gpio::B9>;
using GpioB12 = Gpio<gpio::B12>;
using GpioB13 = Gpio<gpio::B13>;
using GpioD0 = Gpio<gpio::D0>;
using GpioD1 = Gpio<gpio::D1>;
using GpioD2 = Gpio<gpio::D2>;
using GpioD3 = Gpio<gpio::D3>;
using GpioD4 = Gpio<gpio::D4>;
using GpioD5 = Gpio<gpio::D5>;
using GpioD6 = Gpio<gpio::D6>;
using GpioD7 = Gpio<gpio::D7>;
using GpioD8 = Gpio<gpio::D8>;
using GpioD9 = Gpio<gpio::D9>;
using GpioD10 = Gpio<gpio::D10>;
using GpioD11 = Gpio<gpio::D11>;
using GpioD12 = Gpio<gpio::D12>;
using GpioD13 = Gpio<gpio::D13>;
using GpioD14 = Gpio<gpio::D14>;
using GpioD15 = Gpio<gpio::D15>;
using GpioD16 = Gpio<gpio::D16>;
using GpioD17 = Gpio<gpio::D17>;
using GpioD18 = Gpio<gpio::D18>;
using GpioD19 = Gpio<gpio::D19>;
using GpioD20 = Gpio<gpio::D20>;
using GpioD21 = Gpio<gpio::D21>;
using GpioD22 = Gpio<gpio::D22>;
using GpioD24 = Gpio<gpio::D24>;
using GpioD25 = Gpio<gpio::D25>;
using GpioD26 = Gpio<gpio::D26>;
using GpioD27 = Gpio<gpio::D27>;
using GpioD28 = Gpio<gpio::D28>;
using GpioD30 = Gpio<gpio::D30>;
using GpioD31 = Gpio<gpio::D31>;
/// @}

} // namespace modm::platform