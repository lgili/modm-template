/*
 * Copyright (c) 2021, Jeff McBride
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
// ---------------------------------------------------------------------------

#include "../device.hpp"
#include <modm/platform/core/hardware_init.hpp>

void
modm_gpio_enable(void)
{

    PMC->PMC_PCER0 =
        (1<<ID_PIOA) |
        (1<<ID_PIOB) |
        (1<<ID_PIOD);
    // Enable usage of the ODSR register for all pins
    PIOA->PIO_OWER = 0xFFFFFFFF;
    PIOB->PIO_OWER = 0xFFFFFFFF;
    PIOD->PIO_OWER = 0xFFFFFFFF;
}

MODM_HARDWARE_INIT_ORDER(modm_gpio_enable, 80);