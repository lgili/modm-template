/*
 * Copyright (c) 2019 Niklas Hauser
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
// ----------------------------------------------------------------------------

#ifndef MODM_DEVICE_HPP
#define MODM_DEVICE_HPP

#define DONT_USE_CMSIS_INIT 1
#define __SAME70N20__ 1
#include <stdint.h>
#include <modm/architecture/utils.hpp>

// Include external device headers:
#include <same70n20.h>
#endif  // MODM_DEVICE_HPP