/*
 * Copyright (c) 2018, Niklas Hauser
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

#include "pin.hpp"
#include <type_traits>

namespace modm::platform
{

/**
 * Create an up to 32-bit port from arbitrary pins.
 *
 * This class optimizes the data type for the `read()` and `write()` methods.
 * Supplying up to 8 Gpios will use `uint8_t`, up to 16 Gpios `uint16_t` and
 * up to 32 Gpios `uint32_t`.
 *
 * @note Since the bit order is explicitly given by the order of template arguments,
 *       this class only supports `DataOrder::Normal`.
 *       If you need reverse bit order, reverse the order of `Gpios`!
 *
 * @tparam Gpios	Up to 32 GpioIO classes, ordered MSB to LSB
 *
 * @author	Christopher Durand
 * @author	Niklas Hauser
 * @ingroup	modm_platform_gpio
 */
template<class... Gpios>
class SoftwareGpioPort : public ::modm::GpioPort, public GpioSet<Gpios...>
{
	using Set = GpioSet<Gpios...>;
public:
	static constexpr auto width = sizeof...(Gpios);
	static_assert(width <= 32, "Only a maximum of 32 pins are supported by this port!");
	using PortType = std::conditional_t< (width > 8),
					 std::conditional_t< (width > 16),
										 uint32_t,
										 uint16_t >,
										 uint8_t >;
	static constexpr DataOrder getDataOrder()
	{ return ::modm::GpioPort::DataOrder::Normal; }

protected:
	static constexpr int8_t shift_masks_A[] = {
		int8_t(Gpios::port == PortName::A ? Gpios::pin : -1)...
	};
	static_assert(std::size(shift_masks_A) == width);
	static constexpr int8_t shift_mask_A(uint8_t pos) { return shift_masks_A[width - 1 - pos]; };
	static constexpr int8_t shift_masks_B[] = {
		int8_t(Gpios::port == PortName::B ? Gpios::pin : -1)...
	};
	static_assert(std::size(shift_masks_B) == width);
	static constexpr int8_t shift_mask_B(uint8_t pos) { return shift_masks_B[width - 1 - pos]; };
	static constexpr int8_t shift_masks_D[] = {
		int8_t(Gpios::port == PortName::D ? Gpios::pin : -1)...
	};
	static_assert(std::size(shift_masks_D) == width);
	static constexpr int8_t shift_mask_D(uint8_t pos) { return shift_masks_D[width - 1 - pos]; };
	using Set::mask;
	using Set::invertedMask;

public:
	static PortType isSet()
	{
		PortType r{0};
		if constexpr (mask(PortName::A)) {
			const uint32_t p = Set::template readPortReg<PortName::A>(PIO_ODSR_OFFSET) ^ invertedMask(PortName::A);
			if constexpr (0 < width) if constexpr (constexpr auto pos = shift_mask_A(0); pos >= 0) r |= ((p >> pos) & 1) << 0;
			if constexpr (1 < width) if constexpr (constexpr auto pos = shift_mask_A(1); pos >= 0) r |= ((p >> pos) & 1) << 1;
			if constexpr (2 < width) if constexpr (constexpr auto pos = shift_mask_A(2); pos >= 0) r |= ((p >> pos) & 1) << 2;
			if constexpr (3 < width) if constexpr (constexpr auto pos = shift_mask_A(3); pos >= 0) r |= ((p >> pos) & 1) << 3;
			if constexpr (4 < width) if constexpr (constexpr auto pos = shift_mask_A(4); pos >= 0) r |= ((p >> pos) & 1) << 4;
			if constexpr (5 < width) if constexpr (constexpr auto pos = shift_mask_A(5); pos >= 0) r |= ((p >> pos) & 1) << 5;
			if constexpr (6 < width) if constexpr (constexpr auto pos = shift_mask_A(6); pos >= 0) r |= ((p >> pos) & 1) << 6;
			if constexpr (7 < width) if constexpr (constexpr auto pos = shift_mask_A(7); pos >= 0) r |= ((p >> pos) & 1) << 7;
			if constexpr (8 < width) if constexpr (constexpr auto pos = shift_mask_A(8); pos >= 0) r |= ((p >> pos) & 1) << 8;
			if constexpr (9 < width) if constexpr (constexpr auto pos = shift_mask_A(9); pos >= 0) r |= ((p >> pos) & 1) << 9;
			if constexpr (10 < width) if constexpr (constexpr auto pos = shift_mask_A(10); pos >= 0) r |= ((p >> pos) & 1) << 10;
			if constexpr (11 < width) if constexpr (constexpr auto pos = shift_mask_A(11); pos >= 0) r |= ((p >> pos) & 1) << 11;
			if constexpr (12 < width) if constexpr (constexpr auto pos = shift_mask_A(12); pos >= 0) r |= ((p >> pos) & 1) << 12;
			if constexpr (13 < width) if constexpr (constexpr auto pos = shift_mask_A(13); pos >= 0) r |= ((p >> pos) & 1) << 13;
			if constexpr (14 < width) if constexpr (constexpr auto pos = shift_mask_A(14); pos >= 0) r |= ((p >> pos) & 1) << 14;
			if constexpr (15 < width) if constexpr (constexpr auto pos = shift_mask_A(15); pos >= 0) r |= ((p >> pos) & 1) << 15;
			if constexpr (16 < width) if constexpr (constexpr auto pos = shift_mask_A(16); pos >= 0) r |= ((p >> pos) & 1) << 16;
			if constexpr (17 < width) if constexpr (constexpr auto pos = shift_mask_A(17); pos >= 0) r |= ((p >> pos) & 1) << 17;
			if constexpr (18 < width) if constexpr (constexpr auto pos = shift_mask_A(18); pos >= 0) r |= ((p >> pos) & 1) << 18;
			if constexpr (19 < width) if constexpr (constexpr auto pos = shift_mask_A(19); pos >= 0) r |= ((p >> pos) & 1) << 19;
			if constexpr (20 < width) if constexpr (constexpr auto pos = shift_mask_A(20); pos >= 0) r |= ((p >> pos) & 1) << 20;
			if constexpr (21 < width) if constexpr (constexpr auto pos = shift_mask_A(21); pos >= 0) r |= ((p >> pos) & 1) << 21;
			if constexpr (22 < width) if constexpr (constexpr auto pos = shift_mask_A(22); pos >= 0) r |= ((p >> pos) & 1) << 22;
			if constexpr (23 < width) if constexpr (constexpr auto pos = shift_mask_A(23); pos >= 0) r |= ((p >> pos) & 1) << 23;
			if constexpr (24 < width) if constexpr (constexpr auto pos = shift_mask_A(24); pos >= 0) r |= ((p >> pos) & 1) << 24;
			if constexpr (25 < width) if constexpr (constexpr auto pos = shift_mask_A(25); pos >= 0) r |= ((p >> pos) & 1) << 25;
			if constexpr (26 < width) if constexpr (constexpr auto pos = shift_mask_A(26); pos >= 0) r |= ((p >> pos) & 1) << 26;
			if constexpr (27 < width) if constexpr (constexpr auto pos = shift_mask_A(27); pos >= 0) r |= ((p >> pos) & 1) << 27;
			if constexpr (28 < width) if constexpr (constexpr auto pos = shift_mask_A(28); pos >= 0) r |= ((p >> pos) & 1) << 28;
			if constexpr (29 < width) if constexpr (constexpr auto pos = shift_mask_A(29); pos >= 0) r |= ((p >> pos) & 1) << 29;
			if constexpr (30 < width) if constexpr (constexpr auto pos = shift_mask_A(30); pos >= 0) r |= ((p >> pos) & 1) << 30;
			if constexpr (31 < width) if constexpr (constexpr auto pos = shift_mask_A(31); pos >= 0) r |= ((p >> pos) & 1) << 31;
		}
		if constexpr (mask(PortName::B)) {
			const uint32_t p = Set::template readPortReg<PortName::B>(PIO_ODSR_OFFSET) ^ invertedMask(PortName::B);
			if constexpr (0 < width) if constexpr (constexpr auto pos = shift_mask_B(0); pos >= 0) r |= ((p >> pos) & 1) << 0;
			if constexpr (1 < width) if constexpr (constexpr auto pos = shift_mask_B(1); pos >= 0) r |= ((p >> pos) & 1) << 1;
			if constexpr (2 < width) if constexpr (constexpr auto pos = shift_mask_B(2); pos >= 0) r |= ((p >> pos) & 1) << 2;
			if constexpr (3 < width) if constexpr (constexpr auto pos = shift_mask_B(3); pos >= 0) r |= ((p >> pos) & 1) << 3;
			if constexpr (4 < width) if constexpr (constexpr auto pos = shift_mask_B(4); pos >= 0) r |= ((p >> pos) & 1) << 4;
			if constexpr (5 < width) if constexpr (constexpr auto pos = shift_mask_B(5); pos >= 0) r |= ((p >> pos) & 1) << 5;
			if constexpr (6 < width) if constexpr (constexpr auto pos = shift_mask_B(6); pos >= 0) r |= ((p >> pos) & 1) << 6;
			if constexpr (7 < width) if constexpr (constexpr auto pos = shift_mask_B(7); pos >= 0) r |= ((p >> pos) & 1) << 7;
			if constexpr (8 < width) if constexpr (constexpr auto pos = shift_mask_B(8); pos >= 0) r |= ((p >> pos) & 1) << 8;
			if constexpr (9 < width) if constexpr (constexpr auto pos = shift_mask_B(9); pos >= 0) r |= ((p >> pos) & 1) << 9;
			if constexpr (10 < width) if constexpr (constexpr auto pos = shift_mask_B(10); pos >= 0) r |= ((p >> pos) & 1) << 10;
			if constexpr (11 < width) if constexpr (constexpr auto pos = shift_mask_B(11); pos >= 0) r |= ((p >> pos) & 1) << 11;
			if constexpr (12 < width) if constexpr (constexpr auto pos = shift_mask_B(12); pos >= 0) r |= ((p >> pos) & 1) << 12;
			if constexpr (13 < width) if constexpr (constexpr auto pos = shift_mask_B(13); pos >= 0) r |= ((p >> pos) & 1) << 13;
			if constexpr (14 < width) if constexpr (constexpr auto pos = shift_mask_B(14); pos >= 0) r |= ((p >> pos) & 1) << 14;
			if constexpr (15 < width) if constexpr (constexpr auto pos = shift_mask_B(15); pos >= 0) r |= ((p >> pos) & 1) << 15;
			if constexpr (16 < width) if constexpr (constexpr auto pos = shift_mask_B(16); pos >= 0) r |= ((p >> pos) & 1) << 16;
			if constexpr (17 < width) if constexpr (constexpr auto pos = shift_mask_B(17); pos >= 0) r |= ((p >> pos) & 1) << 17;
			if constexpr (18 < width) if constexpr (constexpr auto pos = shift_mask_B(18); pos >= 0) r |= ((p >> pos) & 1) << 18;
			if constexpr (19 < width) if constexpr (constexpr auto pos = shift_mask_B(19); pos >= 0) r |= ((p >> pos) & 1) << 19;
			if constexpr (20 < width) if constexpr (constexpr auto pos = shift_mask_B(20); pos >= 0) r |= ((p >> pos) & 1) << 20;
			if constexpr (21 < width) if constexpr (constexpr auto pos = shift_mask_B(21); pos >= 0) r |= ((p >> pos) & 1) << 21;
			if constexpr (22 < width) if constexpr (constexpr auto pos = shift_mask_B(22); pos >= 0) r |= ((p >> pos) & 1) << 22;
			if constexpr (23 < width) if constexpr (constexpr auto pos = shift_mask_B(23); pos >= 0) r |= ((p >> pos) & 1) << 23;
			if constexpr (24 < width) if constexpr (constexpr auto pos = shift_mask_B(24); pos >= 0) r |= ((p >> pos) & 1) << 24;
			if constexpr (25 < width) if constexpr (constexpr auto pos = shift_mask_B(25); pos >= 0) r |= ((p >> pos) & 1) << 25;
			if constexpr (26 < width) if constexpr (constexpr auto pos = shift_mask_B(26); pos >= 0) r |= ((p >> pos) & 1) << 26;
			if constexpr (27 < width) if constexpr (constexpr auto pos = shift_mask_B(27); pos >= 0) r |= ((p >> pos) & 1) << 27;
			if constexpr (28 < width) if constexpr (constexpr auto pos = shift_mask_B(28); pos >= 0) r |= ((p >> pos) & 1) << 28;
			if constexpr (29 < width) if constexpr (constexpr auto pos = shift_mask_B(29); pos >= 0) r |= ((p >> pos) & 1) << 29;
			if constexpr (30 < width) if constexpr (constexpr auto pos = shift_mask_B(30); pos >= 0) r |= ((p >> pos) & 1) << 30;
			if constexpr (31 < width) if constexpr (constexpr auto pos = shift_mask_B(31); pos >= 0) r |= ((p >> pos) & 1) << 31;
		}
		if constexpr (mask(PortName::D)) {
			const uint32_t p = Set::template readPortReg<PortName::D>(PIO_ODSR_OFFSET) ^ invertedMask(PortName::D);
			if constexpr (0 < width) if constexpr (constexpr auto pos = shift_mask_D(0); pos >= 0) r |= ((p >> pos) & 1) << 0;
			if constexpr (1 < width) if constexpr (constexpr auto pos = shift_mask_D(1); pos >= 0) r |= ((p >> pos) & 1) << 1;
			if constexpr (2 < width) if constexpr (constexpr auto pos = shift_mask_D(2); pos >= 0) r |= ((p >> pos) & 1) << 2;
			if constexpr (3 < width) if constexpr (constexpr auto pos = shift_mask_D(3); pos >= 0) r |= ((p >> pos) & 1) << 3;
			if constexpr (4 < width) if constexpr (constexpr auto pos = shift_mask_D(4); pos >= 0) r |= ((p >> pos) & 1) << 4;
			if constexpr (5 < width) if constexpr (constexpr auto pos = shift_mask_D(5); pos >= 0) r |= ((p >> pos) & 1) << 5;
			if constexpr (6 < width) if constexpr (constexpr auto pos = shift_mask_D(6); pos >= 0) r |= ((p >> pos) & 1) << 6;
			if constexpr (7 < width) if constexpr (constexpr auto pos = shift_mask_D(7); pos >= 0) r |= ((p >> pos) & 1) << 7;
			if constexpr (8 < width) if constexpr (constexpr auto pos = shift_mask_D(8); pos >= 0) r |= ((p >> pos) & 1) << 8;
			if constexpr (9 < width) if constexpr (constexpr auto pos = shift_mask_D(9); pos >= 0) r |= ((p >> pos) & 1) << 9;
			if constexpr (10 < width) if constexpr (constexpr auto pos = shift_mask_D(10); pos >= 0) r |= ((p >> pos) & 1) << 10;
			if constexpr (11 < width) if constexpr (constexpr auto pos = shift_mask_D(11); pos >= 0) r |= ((p >> pos) & 1) << 11;
			if constexpr (12 < width) if constexpr (constexpr auto pos = shift_mask_D(12); pos >= 0) r |= ((p >> pos) & 1) << 12;
			if constexpr (13 < width) if constexpr (constexpr auto pos = shift_mask_D(13); pos >= 0) r |= ((p >> pos) & 1) << 13;
			if constexpr (14 < width) if constexpr (constexpr auto pos = shift_mask_D(14); pos >= 0) r |= ((p >> pos) & 1) << 14;
			if constexpr (15 < width) if constexpr (constexpr auto pos = shift_mask_D(15); pos >= 0) r |= ((p >> pos) & 1) << 15;
			if constexpr (16 < width) if constexpr (constexpr auto pos = shift_mask_D(16); pos >= 0) r |= ((p >> pos) & 1) << 16;
			if constexpr (17 < width) if constexpr (constexpr auto pos = shift_mask_D(17); pos >= 0) r |= ((p >> pos) & 1) << 17;
			if constexpr (18 < width) if constexpr (constexpr auto pos = shift_mask_D(18); pos >= 0) r |= ((p >> pos) & 1) << 18;
			if constexpr (19 < width) if constexpr (constexpr auto pos = shift_mask_D(19); pos >= 0) r |= ((p >> pos) & 1) << 19;
			if constexpr (20 < width) if constexpr (constexpr auto pos = shift_mask_D(20); pos >= 0) r |= ((p >> pos) & 1) << 20;
			if constexpr (21 < width) if constexpr (constexpr auto pos = shift_mask_D(21); pos >= 0) r |= ((p >> pos) & 1) << 21;
			if constexpr (22 < width) if constexpr (constexpr auto pos = shift_mask_D(22); pos >= 0) r |= ((p >> pos) & 1) << 22;
			if constexpr (23 < width) if constexpr (constexpr auto pos = shift_mask_D(23); pos >= 0) r |= ((p >> pos) & 1) << 23;
			if constexpr (24 < width) if constexpr (constexpr auto pos = shift_mask_D(24); pos >= 0) r |= ((p >> pos) & 1) << 24;
			if constexpr (25 < width) if constexpr (constexpr auto pos = shift_mask_D(25); pos >= 0) r |= ((p >> pos) & 1) << 25;
			if constexpr (26 < width) if constexpr (constexpr auto pos = shift_mask_D(26); pos >= 0) r |= ((p >> pos) & 1) << 26;
			if constexpr (27 < width) if constexpr (constexpr auto pos = shift_mask_D(27); pos >= 0) r |= ((p >> pos) & 1) << 27;
			if constexpr (28 < width) if constexpr (constexpr auto pos = shift_mask_D(28); pos >= 0) r |= ((p >> pos) & 1) << 28;
			if constexpr (29 < width) if constexpr (constexpr auto pos = shift_mask_D(29); pos >= 0) r |= ((p >> pos) & 1) << 29;
			if constexpr (30 < width) if constexpr (constexpr auto pos = shift_mask_D(30); pos >= 0) r |= ((p >> pos) & 1) << 30;
			if constexpr (31 < width) if constexpr (constexpr auto pos = shift_mask_D(31); pos >= 0) r |= ((p >> pos) & 1) << 31;
		}
		return r;
	}

	static void write(PortType data)
	{
		if constexpr (mask(PortName::A)) {
			uint32_t set{0};
			uint32_t reset{0};
			if constexpr (0 < width) {
				if constexpr (constexpr auto shift = shift_mask_A(0); shift >= 0) {
					if (bool(data & (1ul << 0)) != bool(invertedMask(PortName::A) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (1 < width) {
				if constexpr (constexpr auto shift = shift_mask_A(1); shift >= 0) {
					if (bool(data & (1ul << 1)) != bool(invertedMask(PortName::A) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (2 < width) {
				if constexpr (constexpr auto shift = shift_mask_A(2); shift >= 0) {
					if (bool(data & (1ul << 2)) != bool(invertedMask(PortName::A) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (3 < width) {
				if constexpr (constexpr auto shift = shift_mask_A(3); shift >= 0) {
					if (bool(data & (1ul << 3)) != bool(invertedMask(PortName::A) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (4 < width) {
				if constexpr (constexpr auto shift = shift_mask_A(4); shift >= 0) {
					if (bool(data & (1ul << 4)) != bool(invertedMask(PortName::A) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (5 < width) {
				if constexpr (constexpr auto shift = shift_mask_A(5); shift >= 0) {
					if (bool(data & (1ul << 5)) != bool(invertedMask(PortName::A) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (6 < width) {
				if constexpr (constexpr auto shift = shift_mask_A(6); shift >= 0) {
					if (bool(data & (1ul << 6)) != bool(invertedMask(PortName::A) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (7 < width) {
				if constexpr (constexpr auto shift = shift_mask_A(7); shift >= 0) {
					if (bool(data & (1ul << 7)) != bool(invertedMask(PortName::A) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (8 < width) {
				if constexpr (constexpr auto shift = shift_mask_A(8); shift >= 0) {
					if (bool(data & (1ul << 8)) != bool(invertedMask(PortName::A) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (9 < width) {
				if constexpr (constexpr auto shift = shift_mask_A(9); shift >= 0) {
					if (bool(data & (1ul << 9)) != bool(invertedMask(PortName::A) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (10 < width) {
				if constexpr (constexpr auto shift = shift_mask_A(10); shift >= 0) {
					if (bool(data & (1ul << 10)) != bool(invertedMask(PortName::A) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (11 < width) {
				if constexpr (constexpr auto shift = shift_mask_A(11); shift >= 0) {
					if (bool(data & (1ul << 11)) != bool(invertedMask(PortName::A) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (12 < width) {
				if constexpr (constexpr auto shift = shift_mask_A(12); shift >= 0) {
					if (bool(data & (1ul << 12)) != bool(invertedMask(PortName::A) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (13 < width) {
				if constexpr (constexpr auto shift = shift_mask_A(13); shift >= 0) {
					if (bool(data & (1ul << 13)) != bool(invertedMask(PortName::A) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (14 < width) {
				if constexpr (constexpr auto shift = shift_mask_A(14); shift >= 0) {
					if (bool(data & (1ul << 14)) != bool(invertedMask(PortName::A) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (15 < width) {
				if constexpr (constexpr auto shift = shift_mask_A(15); shift >= 0) {
					if (bool(data & (1ul << 15)) != bool(invertedMask(PortName::A) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (16 < width) {
				if constexpr (constexpr auto shift = shift_mask_A(16); shift >= 0) {
					if (bool(data & (1ul << 16)) != bool(invertedMask(PortName::A) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (17 < width) {
				if constexpr (constexpr auto shift = shift_mask_A(17); shift >= 0) {
					if (bool(data & (1ul << 17)) != bool(invertedMask(PortName::A) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (18 < width) {
				if constexpr (constexpr auto shift = shift_mask_A(18); shift >= 0) {
					if (bool(data & (1ul << 18)) != bool(invertedMask(PortName::A) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (19 < width) {
				if constexpr (constexpr auto shift = shift_mask_A(19); shift >= 0) {
					if (bool(data & (1ul << 19)) != bool(invertedMask(PortName::A) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (20 < width) {
				if constexpr (constexpr auto shift = shift_mask_A(20); shift >= 0) {
					if (bool(data & (1ul << 20)) != bool(invertedMask(PortName::A) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (21 < width) {
				if constexpr (constexpr auto shift = shift_mask_A(21); shift >= 0) {
					if (bool(data & (1ul << 21)) != bool(invertedMask(PortName::A) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (22 < width) {
				if constexpr (constexpr auto shift = shift_mask_A(22); shift >= 0) {
					if (bool(data & (1ul << 22)) != bool(invertedMask(PortName::A) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (23 < width) {
				if constexpr (constexpr auto shift = shift_mask_A(23); shift >= 0) {
					if (bool(data & (1ul << 23)) != bool(invertedMask(PortName::A) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (24 < width) {
				if constexpr (constexpr auto shift = shift_mask_A(24); shift >= 0) {
					if (bool(data & (1ul << 24)) != bool(invertedMask(PortName::A) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (25 < width) {
				if constexpr (constexpr auto shift = shift_mask_A(25); shift >= 0) {
					if (bool(data & (1ul << 25)) != bool(invertedMask(PortName::A) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (26 < width) {
				if constexpr (constexpr auto shift = shift_mask_A(26); shift >= 0) {
					if (bool(data & (1ul << 26)) != bool(invertedMask(PortName::A) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (27 < width) {
				if constexpr (constexpr auto shift = shift_mask_A(27); shift >= 0) {
					if (bool(data & (1ul << 27)) != bool(invertedMask(PortName::A) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (28 < width) {
				if constexpr (constexpr auto shift = shift_mask_A(28); shift >= 0) {
					if (bool(data & (1ul << 28)) != bool(invertedMask(PortName::A) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (29 < width) {
				if constexpr (constexpr auto shift = shift_mask_A(29); shift >= 0) {
					if (bool(data & (1ul << 29)) != bool(invertedMask(PortName::A) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (30 < width) {
				if constexpr (constexpr auto shift = shift_mask_A(30); shift >= 0) {
					if (bool(data & (1ul << 30)) != bool(invertedMask(PortName::A) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (31 < width) {
				if constexpr (constexpr auto shift = shift_mask_A(31); shift >= 0) {
					if (bool(data & (1ul << 31)) != bool(invertedMask(PortName::A) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			*(Set::template getPortReg<PortName::A>(PIO_SODR_OFFSET)) = set;
			*(Set::template getPortReg<PortName::A>(PIO_CODR_OFFSET)) = reset;
		}
		if constexpr (mask(PortName::B)) {
			uint32_t set{0};
			uint32_t reset{0};
			if constexpr (0 < width) {
				if constexpr (constexpr auto shift = shift_mask_B(0); shift >= 0) {
					if (bool(data & (1ul << 0)) != bool(invertedMask(PortName::B) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (1 < width) {
				if constexpr (constexpr auto shift = shift_mask_B(1); shift >= 0) {
					if (bool(data & (1ul << 1)) != bool(invertedMask(PortName::B) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (2 < width) {
				if constexpr (constexpr auto shift = shift_mask_B(2); shift >= 0) {
					if (bool(data & (1ul << 2)) != bool(invertedMask(PortName::B) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (3 < width) {
				if constexpr (constexpr auto shift = shift_mask_B(3); shift >= 0) {
					if (bool(data & (1ul << 3)) != bool(invertedMask(PortName::B) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (4 < width) {
				if constexpr (constexpr auto shift = shift_mask_B(4); shift >= 0) {
					if (bool(data & (1ul << 4)) != bool(invertedMask(PortName::B) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (5 < width) {
				if constexpr (constexpr auto shift = shift_mask_B(5); shift >= 0) {
					if (bool(data & (1ul << 5)) != bool(invertedMask(PortName::B) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (6 < width) {
				if constexpr (constexpr auto shift = shift_mask_B(6); shift >= 0) {
					if (bool(data & (1ul << 6)) != bool(invertedMask(PortName::B) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (7 < width) {
				if constexpr (constexpr auto shift = shift_mask_B(7); shift >= 0) {
					if (bool(data & (1ul << 7)) != bool(invertedMask(PortName::B) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (8 < width) {
				if constexpr (constexpr auto shift = shift_mask_B(8); shift >= 0) {
					if (bool(data & (1ul << 8)) != bool(invertedMask(PortName::B) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (9 < width) {
				if constexpr (constexpr auto shift = shift_mask_B(9); shift >= 0) {
					if (bool(data & (1ul << 9)) != bool(invertedMask(PortName::B) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (10 < width) {
				if constexpr (constexpr auto shift = shift_mask_B(10); shift >= 0) {
					if (bool(data & (1ul << 10)) != bool(invertedMask(PortName::B) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (11 < width) {
				if constexpr (constexpr auto shift = shift_mask_B(11); shift >= 0) {
					if (bool(data & (1ul << 11)) != bool(invertedMask(PortName::B) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (12 < width) {
				if constexpr (constexpr auto shift = shift_mask_B(12); shift >= 0) {
					if (bool(data & (1ul << 12)) != bool(invertedMask(PortName::B) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (13 < width) {
				if constexpr (constexpr auto shift = shift_mask_B(13); shift >= 0) {
					if (bool(data & (1ul << 13)) != bool(invertedMask(PortName::B) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (14 < width) {
				if constexpr (constexpr auto shift = shift_mask_B(14); shift >= 0) {
					if (bool(data & (1ul << 14)) != bool(invertedMask(PortName::B) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (15 < width) {
				if constexpr (constexpr auto shift = shift_mask_B(15); shift >= 0) {
					if (bool(data & (1ul << 15)) != bool(invertedMask(PortName::B) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (16 < width) {
				if constexpr (constexpr auto shift = shift_mask_B(16); shift >= 0) {
					if (bool(data & (1ul << 16)) != bool(invertedMask(PortName::B) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (17 < width) {
				if constexpr (constexpr auto shift = shift_mask_B(17); shift >= 0) {
					if (bool(data & (1ul << 17)) != bool(invertedMask(PortName::B) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (18 < width) {
				if constexpr (constexpr auto shift = shift_mask_B(18); shift >= 0) {
					if (bool(data & (1ul << 18)) != bool(invertedMask(PortName::B) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (19 < width) {
				if constexpr (constexpr auto shift = shift_mask_B(19); shift >= 0) {
					if (bool(data & (1ul << 19)) != bool(invertedMask(PortName::B) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (20 < width) {
				if constexpr (constexpr auto shift = shift_mask_B(20); shift >= 0) {
					if (bool(data & (1ul << 20)) != bool(invertedMask(PortName::B) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (21 < width) {
				if constexpr (constexpr auto shift = shift_mask_B(21); shift >= 0) {
					if (bool(data & (1ul << 21)) != bool(invertedMask(PortName::B) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (22 < width) {
				if constexpr (constexpr auto shift = shift_mask_B(22); shift >= 0) {
					if (bool(data & (1ul << 22)) != bool(invertedMask(PortName::B) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (23 < width) {
				if constexpr (constexpr auto shift = shift_mask_B(23); shift >= 0) {
					if (bool(data & (1ul << 23)) != bool(invertedMask(PortName::B) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (24 < width) {
				if constexpr (constexpr auto shift = shift_mask_B(24); shift >= 0) {
					if (bool(data & (1ul << 24)) != bool(invertedMask(PortName::B) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (25 < width) {
				if constexpr (constexpr auto shift = shift_mask_B(25); shift >= 0) {
					if (bool(data & (1ul << 25)) != bool(invertedMask(PortName::B) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (26 < width) {
				if constexpr (constexpr auto shift = shift_mask_B(26); shift >= 0) {
					if (bool(data & (1ul << 26)) != bool(invertedMask(PortName::B) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (27 < width) {
				if constexpr (constexpr auto shift = shift_mask_B(27); shift >= 0) {
					if (bool(data & (1ul << 27)) != bool(invertedMask(PortName::B) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (28 < width) {
				if constexpr (constexpr auto shift = shift_mask_B(28); shift >= 0) {
					if (bool(data & (1ul << 28)) != bool(invertedMask(PortName::B) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (29 < width) {
				if constexpr (constexpr auto shift = shift_mask_B(29); shift >= 0) {
					if (bool(data & (1ul << 29)) != bool(invertedMask(PortName::B) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (30 < width) {
				if constexpr (constexpr auto shift = shift_mask_B(30); shift >= 0) {
					if (bool(data & (1ul << 30)) != bool(invertedMask(PortName::B) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (31 < width) {
				if constexpr (constexpr auto shift = shift_mask_B(31); shift >= 0) {
					if (bool(data & (1ul << 31)) != bool(invertedMask(PortName::B) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			*(Set::template getPortReg<PortName::B>(PIO_SODR_OFFSET)) = set;
			*(Set::template getPortReg<PortName::B>(PIO_CODR_OFFSET)) = reset;
		}
		if constexpr (mask(PortName::D)) {
			uint32_t set{0};
			uint32_t reset{0};
			if constexpr (0 < width) {
				if constexpr (constexpr auto shift = shift_mask_D(0); shift >= 0) {
					if (bool(data & (1ul << 0)) != bool(invertedMask(PortName::D) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (1 < width) {
				if constexpr (constexpr auto shift = shift_mask_D(1); shift >= 0) {
					if (bool(data & (1ul << 1)) != bool(invertedMask(PortName::D) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (2 < width) {
				if constexpr (constexpr auto shift = shift_mask_D(2); shift >= 0) {
					if (bool(data & (1ul << 2)) != bool(invertedMask(PortName::D) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (3 < width) {
				if constexpr (constexpr auto shift = shift_mask_D(3); shift >= 0) {
					if (bool(data & (1ul << 3)) != bool(invertedMask(PortName::D) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (4 < width) {
				if constexpr (constexpr auto shift = shift_mask_D(4); shift >= 0) {
					if (bool(data & (1ul << 4)) != bool(invertedMask(PortName::D) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (5 < width) {
				if constexpr (constexpr auto shift = shift_mask_D(5); shift >= 0) {
					if (bool(data & (1ul << 5)) != bool(invertedMask(PortName::D) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (6 < width) {
				if constexpr (constexpr auto shift = shift_mask_D(6); shift >= 0) {
					if (bool(data & (1ul << 6)) != bool(invertedMask(PortName::D) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (7 < width) {
				if constexpr (constexpr auto shift = shift_mask_D(7); shift >= 0) {
					if (bool(data & (1ul << 7)) != bool(invertedMask(PortName::D) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (8 < width) {
				if constexpr (constexpr auto shift = shift_mask_D(8); shift >= 0) {
					if (bool(data & (1ul << 8)) != bool(invertedMask(PortName::D) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (9 < width) {
				if constexpr (constexpr auto shift = shift_mask_D(9); shift >= 0) {
					if (bool(data & (1ul << 9)) != bool(invertedMask(PortName::D) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (10 < width) {
				if constexpr (constexpr auto shift = shift_mask_D(10); shift >= 0) {
					if (bool(data & (1ul << 10)) != bool(invertedMask(PortName::D) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (11 < width) {
				if constexpr (constexpr auto shift = shift_mask_D(11); shift >= 0) {
					if (bool(data & (1ul << 11)) != bool(invertedMask(PortName::D) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (12 < width) {
				if constexpr (constexpr auto shift = shift_mask_D(12); shift >= 0) {
					if (bool(data & (1ul << 12)) != bool(invertedMask(PortName::D) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (13 < width) {
				if constexpr (constexpr auto shift = shift_mask_D(13); shift >= 0) {
					if (bool(data & (1ul << 13)) != bool(invertedMask(PortName::D) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (14 < width) {
				if constexpr (constexpr auto shift = shift_mask_D(14); shift >= 0) {
					if (bool(data & (1ul << 14)) != bool(invertedMask(PortName::D) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (15 < width) {
				if constexpr (constexpr auto shift = shift_mask_D(15); shift >= 0) {
					if (bool(data & (1ul << 15)) != bool(invertedMask(PortName::D) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (16 < width) {
				if constexpr (constexpr auto shift = shift_mask_D(16); shift >= 0) {
					if (bool(data & (1ul << 16)) != bool(invertedMask(PortName::D) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (17 < width) {
				if constexpr (constexpr auto shift = shift_mask_D(17); shift >= 0) {
					if (bool(data & (1ul << 17)) != bool(invertedMask(PortName::D) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (18 < width) {
				if constexpr (constexpr auto shift = shift_mask_D(18); shift >= 0) {
					if (bool(data & (1ul << 18)) != bool(invertedMask(PortName::D) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (19 < width) {
				if constexpr (constexpr auto shift = shift_mask_D(19); shift >= 0) {
					if (bool(data & (1ul << 19)) != bool(invertedMask(PortName::D) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (20 < width) {
				if constexpr (constexpr auto shift = shift_mask_D(20); shift >= 0) {
					if (bool(data & (1ul << 20)) != bool(invertedMask(PortName::D) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (21 < width) {
				if constexpr (constexpr auto shift = shift_mask_D(21); shift >= 0) {
					if (bool(data & (1ul << 21)) != bool(invertedMask(PortName::D) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (22 < width) {
				if constexpr (constexpr auto shift = shift_mask_D(22); shift >= 0) {
					if (bool(data & (1ul << 22)) != bool(invertedMask(PortName::D) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (23 < width) {
				if constexpr (constexpr auto shift = shift_mask_D(23); shift >= 0) {
					if (bool(data & (1ul << 23)) != bool(invertedMask(PortName::D) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (24 < width) {
				if constexpr (constexpr auto shift = shift_mask_D(24); shift >= 0) {
					if (bool(data & (1ul << 24)) != bool(invertedMask(PortName::D) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (25 < width) {
				if constexpr (constexpr auto shift = shift_mask_D(25); shift >= 0) {
					if (bool(data & (1ul << 25)) != bool(invertedMask(PortName::D) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (26 < width) {
				if constexpr (constexpr auto shift = shift_mask_D(26); shift >= 0) {
					if (bool(data & (1ul << 26)) != bool(invertedMask(PortName::D) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (27 < width) {
				if constexpr (constexpr auto shift = shift_mask_D(27); shift >= 0) {
					if (bool(data & (1ul << 27)) != bool(invertedMask(PortName::D) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (28 < width) {
				if constexpr (constexpr auto shift = shift_mask_D(28); shift >= 0) {
					if (bool(data & (1ul << 28)) != bool(invertedMask(PortName::D) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (29 < width) {
				if constexpr (constexpr auto shift = shift_mask_D(29); shift >= 0) {
					if (bool(data & (1ul << 29)) != bool(invertedMask(PortName::D) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (30 < width) {
				if constexpr (constexpr auto shift = shift_mask_D(30); shift >= 0) {
					if (bool(data & (1ul << 30)) != bool(invertedMask(PortName::D) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			if constexpr (31 < width) {
				if constexpr (constexpr auto shift = shift_mask_D(31); shift >= 0) {
					if (bool(data & (1ul << 31)) != bool(invertedMask(PortName::D) & (1 << shift)))
						set |= (1ul << shift);
					else
						reset |= (1ul << shift);
				}
			}
			*(Set::template getPortReg<PortName::D>(PIO_SODR_OFFSET)) = set;
			*(Set::template getPortReg<PortName::D>(PIO_CODR_OFFSET)) = reset;
		}
	}

	static PortType read()
	{
		PortType r{0};
		if constexpr (mask(PortName::A)) {
			const uint32_t p = (Set::template readPortReg<PortName::A>(PIO_PDSR_OFFSET) & mask(PortName::A)) ^ invertedMask(PortName::A);
			if constexpr (0 < width) if constexpr (constexpr auto pos = shift_mask_A(0); pos >= 0) r |= ((p >> pos) & 1) << 0;
			if constexpr (1 < width) if constexpr (constexpr auto pos = shift_mask_A(1); pos >= 0) r |= ((p >> pos) & 1) << 1;
			if constexpr (2 < width) if constexpr (constexpr auto pos = shift_mask_A(2); pos >= 0) r |= ((p >> pos) & 1) << 2;
			if constexpr (3 < width) if constexpr (constexpr auto pos = shift_mask_A(3); pos >= 0) r |= ((p >> pos) & 1) << 3;
			if constexpr (4 < width) if constexpr (constexpr auto pos = shift_mask_A(4); pos >= 0) r |= ((p >> pos) & 1) << 4;
			if constexpr (5 < width) if constexpr (constexpr auto pos = shift_mask_A(5); pos >= 0) r |= ((p >> pos) & 1) << 5;
			if constexpr (6 < width) if constexpr (constexpr auto pos = shift_mask_A(6); pos >= 0) r |= ((p >> pos) & 1) << 6;
			if constexpr (7 < width) if constexpr (constexpr auto pos = shift_mask_A(7); pos >= 0) r |= ((p >> pos) & 1) << 7;
			if constexpr (8 < width) if constexpr (constexpr auto pos = shift_mask_A(8); pos >= 0) r |= ((p >> pos) & 1) << 8;
			if constexpr (9 < width) if constexpr (constexpr auto pos = shift_mask_A(9); pos >= 0) r |= ((p >> pos) & 1) << 9;
			if constexpr (10 < width) if constexpr (constexpr auto pos = shift_mask_A(10); pos >= 0) r |= ((p >> pos) & 1) << 10;
			if constexpr (11 < width) if constexpr (constexpr auto pos = shift_mask_A(11); pos >= 0) r |= ((p >> pos) & 1) << 11;
			if constexpr (12 < width) if constexpr (constexpr auto pos = shift_mask_A(12); pos >= 0) r |= ((p >> pos) & 1) << 12;
			if constexpr (13 < width) if constexpr (constexpr auto pos = shift_mask_A(13); pos >= 0) r |= ((p >> pos) & 1) << 13;
			if constexpr (14 < width) if constexpr (constexpr auto pos = shift_mask_A(14); pos >= 0) r |= ((p >> pos) & 1) << 14;
			if constexpr (15 < width) if constexpr (constexpr auto pos = shift_mask_A(15); pos >= 0) r |= ((p >> pos) & 1) << 15;
			if constexpr (16 < width) if constexpr (constexpr auto pos = shift_mask_A(16); pos >= 0) r |= ((p >> pos) & 1) << 16;
			if constexpr (17 < width) if constexpr (constexpr auto pos = shift_mask_A(17); pos >= 0) r |= ((p >> pos) & 1) << 17;
			if constexpr (18 < width) if constexpr (constexpr auto pos = shift_mask_A(18); pos >= 0) r |= ((p >> pos) & 1) << 18;
			if constexpr (19 < width) if constexpr (constexpr auto pos = shift_mask_A(19); pos >= 0) r |= ((p >> pos) & 1) << 19;
			if constexpr (20 < width) if constexpr (constexpr auto pos = shift_mask_A(20); pos >= 0) r |= ((p >> pos) & 1) << 20;
			if constexpr (21 < width) if constexpr (constexpr auto pos = shift_mask_A(21); pos >= 0) r |= ((p >> pos) & 1) << 21;
			if constexpr (22 < width) if constexpr (constexpr auto pos = shift_mask_A(22); pos >= 0) r |= ((p >> pos) & 1) << 22;
			if constexpr (23 < width) if constexpr (constexpr auto pos = shift_mask_A(23); pos >= 0) r |= ((p >> pos) & 1) << 23;
			if constexpr (24 < width) if constexpr (constexpr auto pos = shift_mask_A(24); pos >= 0) r |= ((p >> pos) & 1) << 24;
			if constexpr (25 < width) if constexpr (constexpr auto pos = shift_mask_A(25); pos >= 0) r |= ((p >> pos) & 1) << 25;
			if constexpr (26 < width) if constexpr (constexpr auto pos = shift_mask_A(26); pos >= 0) r |= ((p >> pos) & 1) << 26;
			if constexpr (27 < width) if constexpr (constexpr auto pos = shift_mask_A(27); pos >= 0) r |= ((p >> pos) & 1) << 27;
			if constexpr (28 < width) if constexpr (constexpr auto pos = shift_mask_A(28); pos >= 0) r |= ((p >> pos) & 1) << 28;
			if constexpr (29 < width) if constexpr (constexpr auto pos = shift_mask_A(29); pos >= 0) r |= ((p >> pos) & 1) << 29;
			if constexpr (30 < width) if constexpr (constexpr auto pos = shift_mask_A(30); pos >= 0) r |= ((p >> pos) & 1) << 30;
			if constexpr (31 < width) if constexpr (constexpr auto pos = shift_mask_A(31); pos >= 0) r |= ((p >> pos) & 1) << 31;
		}
		if constexpr (mask(PortName::B)) {
			const uint32_t p = (Set::template readPortReg<PortName::B>(PIO_PDSR_OFFSET) & mask(PortName::B)) ^ invertedMask(PortName::B);
			if constexpr (0 < width) if constexpr (constexpr auto pos = shift_mask_B(0); pos >= 0) r |= ((p >> pos) & 1) << 0;
			if constexpr (1 < width) if constexpr (constexpr auto pos = shift_mask_B(1); pos >= 0) r |= ((p >> pos) & 1) << 1;
			if constexpr (2 < width) if constexpr (constexpr auto pos = shift_mask_B(2); pos >= 0) r |= ((p >> pos) & 1) << 2;
			if constexpr (3 < width) if constexpr (constexpr auto pos = shift_mask_B(3); pos >= 0) r |= ((p >> pos) & 1) << 3;
			if constexpr (4 < width) if constexpr (constexpr auto pos = shift_mask_B(4); pos >= 0) r |= ((p >> pos) & 1) << 4;
			if constexpr (5 < width) if constexpr (constexpr auto pos = shift_mask_B(5); pos >= 0) r |= ((p >> pos) & 1) << 5;
			if constexpr (6 < width) if constexpr (constexpr auto pos = shift_mask_B(6); pos >= 0) r |= ((p >> pos) & 1) << 6;
			if constexpr (7 < width) if constexpr (constexpr auto pos = shift_mask_B(7); pos >= 0) r |= ((p >> pos) & 1) << 7;
			if constexpr (8 < width) if constexpr (constexpr auto pos = shift_mask_B(8); pos >= 0) r |= ((p >> pos) & 1) << 8;
			if constexpr (9 < width) if constexpr (constexpr auto pos = shift_mask_B(9); pos >= 0) r |= ((p >> pos) & 1) << 9;
			if constexpr (10 < width) if constexpr (constexpr auto pos = shift_mask_B(10); pos >= 0) r |= ((p >> pos) & 1) << 10;
			if constexpr (11 < width) if constexpr (constexpr auto pos = shift_mask_B(11); pos >= 0) r |= ((p >> pos) & 1) << 11;
			if constexpr (12 < width) if constexpr (constexpr auto pos = shift_mask_B(12); pos >= 0) r |= ((p >> pos) & 1) << 12;
			if constexpr (13 < width) if constexpr (constexpr auto pos = shift_mask_B(13); pos >= 0) r |= ((p >> pos) & 1) << 13;
			if constexpr (14 < width) if constexpr (constexpr auto pos = shift_mask_B(14); pos >= 0) r |= ((p >> pos) & 1) << 14;
			if constexpr (15 < width) if constexpr (constexpr auto pos = shift_mask_B(15); pos >= 0) r |= ((p >> pos) & 1) << 15;
			if constexpr (16 < width) if constexpr (constexpr auto pos = shift_mask_B(16); pos >= 0) r |= ((p >> pos) & 1) << 16;
			if constexpr (17 < width) if constexpr (constexpr auto pos = shift_mask_B(17); pos >= 0) r |= ((p >> pos) & 1) << 17;
			if constexpr (18 < width) if constexpr (constexpr auto pos = shift_mask_B(18); pos >= 0) r |= ((p >> pos) & 1) << 18;
			if constexpr (19 < width) if constexpr (constexpr auto pos = shift_mask_B(19); pos >= 0) r |= ((p >> pos) & 1) << 19;
			if constexpr (20 < width) if constexpr (constexpr auto pos = shift_mask_B(20); pos >= 0) r |= ((p >> pos) & 1) << 20;
			if constexpr (21 < width) if constexpr (constexpr auto pos = shift_mask_B(21); pos >= 0) r |= ((p >> pos) & 1) << 21;
			if constexpr (22 < width) if constexpr (constexpr auto pos = shift_mask_B(22); pos >= 0) r |= ((p >> pos) & 1) << 22;
			if constexpr (23 < width) if constexpr (constexpr auto pos = shift_mask_B(23); pos >= 0) r |= ((p >> pos) & 1) << 23;
			if constexpr (24 < width) if constexpr (constexpr auto pos = shift_mask_B(24); pos >= 0) r |= ((p >> pos) & 1) << 24;
			if constexpr (25 < width) if constexpr (constexpr auto pos = shift_mask_B(25); pos >= 0) r |= ((p >> pos) & 1) << 25;
			if constexpr (26 < width) if constexpr (constexpr auto pos = shift_mask_B(26); pos >= 0) r |= ((p >> pos) & 1) << 26;
			if constexpr (27 < width) if constexpr (constexpr auto pos = shift_mask_B(27); pos >= 0) r |= ((p >> pos) & 1) << 27;
			if constexpr (28 < width) if constexpr (constexpr auto pos = shift_mask_B(28); pos >= 0) r |= ((p >> pos) & 1) << 28;
			if constexpr (29 < width) if constexpr (constexpr auto pos = shift_mask_B(29); pos >= 0) r |= ((p >> pos) & 1) << 29;
			if constexpr (30 < width) if constexpr (constexpr auto pos = shift_mask_B(30); pos >= 0) r |= ((p >> pos) & 1) << 30;
			if constexpr (31 < width) if constexpr (constexpr auto pos = shift_mask_B(31); pos >= 0) r |= ((p >> pos) & 1) << 31;
		}
		if constexpr (mask(PortName::D)) {
			const uint32_t p = (Set::template readPortReg<PortName::D>(PIO_PDSR_OFFSET) & mask(PortName::D)) ^ invertedMask(PortName::D);
			if constexpr (0 < width) if constexpr (constexpr auto pos = shift_mask_D(0); pos >= 0) r |= ((p >> pos) & 1) << 0;
			if constexpr (1 < width) if constexpr (constexpr auto pos = shift_mask_D(1); pos >= 0) r |= ((p >> pos) & 1) << 1;
			if constexpr (2 < width) if constexpr (constexpr auto pos = shift_mask_D(2); pos >= 0) r |= ((p >> pos) & 1) << 2;
			if constexpr (3 < width) if constexpr (constexpr auto pos = shift_mask_D(3); pos >= 0) r |= ((p >> pos) & 1) << 3;
			if constexpr (4 < width) if constexpr (constexpr auto pos = shift_mask_D(4); pos >= 0) r |= ((p >> pos) & 1) << 4;
			if constexpr (5 < width) if constexpr (constexpr auto pos = shift_mask_D(5); pos >= 0) r |= ((p >> pos) & 1) << 5;
			if constexpr (6 < width) if constexpr (constexpr auto pos = shift_mask_D(6); pos >= 0) r |= ((p >> pos) & 1) << 6;
			if constexpr (7 < width) if constexpr (constexpr auto pos = shift_mask_D(7); pos >= 0) r |= ((p >> pos) & 1) << 7;
			if constexpr (8 < width) if constexpr (constexpr auto pos = shift_mask_D(8); pos >= 0) r |= ((p >> pos) & 1) << 8;
			if constexpr (9 < width) if constexpr (constexpr auto pos = shift_mask_D(9); pos >= 0) r |= ((p >> pos) & 1) << 9;
			if constexpr (10 < width) if constexpr (constexpr auto pos = shift_mask_D(10); pos >= 0) r |= ((p >> pos) & 1) << 10;
			if constexpr (11 < width) if constexpr (constexpr auto pos = shift_mask_D(11); pos >= 0) r |= ((p >> pos) & 1) << 11;
			if constexpr (12 < width) if constexpr (constexpr auto pos = shift_mask_D(12); pos >= 0) r |= ((p >> pos) & 1) << 12;
			if constexpr (13 < width) if constexpr (constexpr auto pos = shift_mask_D(13); pos >= 0) r |= ((p >> pos) & 1) << 13;
			if constexpr (14 < width) if constexpr (constexpr auto pos = shift_mask_D(14); pos >= 0) r |= ((p >> pos) & 1) << 14;
			if constexpr (15 < width) if constexpr (constexpr auto pos = shift_mask_D(15); pos >= 0) r |= ((p >> pos) & 1) << 15;
			if constexpr (16 < width) if constexpr (constexpr auto pos = shift_mask_D(16); pos >= 0) r |= ((p >> pos) & 1) << 16;
			if constexpr (17 < width) if constexpr (constexpr auto pos = shift_mask_D(17); pos >= 0) r |= ((p >> pos) & 1) << 17;
			if constexpr (18 < width) if constexpr (constexpr auto pos = shift_mask_D(18); pos >= 0) r |= ((p >> pos) & 1) << 18;
			if constexpr (19 < width) if constexpr (constexpr auto pos = shift_mask_D(19); pos >= 0) r |= ((p >> pos) & 1) << 19;
			if constexpr (20 < width) if constexpr (constexpr auto pos = shift_mask_D(20); pos >= 0) r |= ((p >> pos) & 1) << 20;
			if constexpr (21 < width) if constexpr (constexpr auto pos = shift_mask_D(21); pos >= 0) r |= ((p >> pos) & 1) << 21;
			if constexpr (22 < width) if constexpr (constexpr auto pos = shift_mask_D(22); pos >= 0) r |= ((p >> pos) & 1) << 22;
			if constexpr (23 < width) if constexpr (constexpr auto pos = shift_mask_D(23); pos >= 0) r |= ((p >> pos) & 1) << 23;
			if constexpr (24 < width) if constexpr (constexpr auto pos = shift_mask_D(24); pos >= 0) r |= ((p >> pos) & 1) << 24;
			if constexpr (25 < width) if constexpr (constexpr auto pos = shift_mask_D(25); pos >= 0) r |= ((p >> pos) & 1) << 25;
			if constexpr (26 < width) if constexpr (constexpr auto pos = shift_mask_D(26); pos >= 0) r |= ((p >> pos) & 1) << 26;
			if constexpr (27 < width) if constexpr (constexpr auto pos = shift_mask_D(27); pos >= 0) r |= ((p >> pos) & 1) << 27;
			if constexpr (28 < width) if constexpr (constexpr auto pos = shift_mask_D(28); pos >= 0) r |= ((p >> pos) & 1) << 28;
			if constexpr (29 < width) if constexpr (constexpr auto pos = shift_mask_D(29); pos >= 0) r |= ((p >> pos) & 1) << 29;
			if constexpr (30 < width) if constexpr (constexpr auto pos = shift_mask_D(30); pos >= 0) r |= ((p >> pos) & 1) << 30;
			if constexpr (31 < width) if constexpr (constexpr auto pos = shift_mask_D(31); pos >= 0) r |= ((p >> pos) & 1) << 31;
		}
		return r;
	}
};

} // namespace modm::platform