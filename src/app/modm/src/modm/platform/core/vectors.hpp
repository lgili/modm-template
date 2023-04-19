/*
 * Copyright (c) 2021, Niklas Hauser
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
#include <modm/architecture/utils.hpp>
#include <string_view>

extern "C"
{

void Reset_Handler(void);
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void SUPC_IRQHandler(void);
void RSTC_IRQHandler(void);
void RTC_IRQHandler(void);
void RTT_IRQHandler(void);
void WDT_IRQHandler(void);
void PMC_IRQHandler(void);
void EFC_IRQHandler(void);
void UART0_IRQHandler(void);
void UART1_IRQHandler(void);
void PIOA_IRQHandler(void);
void PIOB_IRQHandler(void);
void USART0_IRQHandler(void);
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void PIOD_IRQHandler(void);
void HSMCI_IRQHandler(void);
void TWIHS0_IRQHandler(void);
void TWIHS1_IRQHandler(void);
void SPI0_IRQHandler(void);
void SSC_IRQHandler(void);
void TC0_IRQHandler(void);
void TC1_IRQHandler(void);
void TC2_IRQHandler(void);
void TC3_IRQHandler(void);
void TC4_IRQHandler(void);
void TC5_IRQHandler(void);
void AFEC0_IRQHandler(void);
void DACC_IRQHandler(void);
void PWM0_IRQHandler(void);
void ICM_IRQHandler(void);
void ACC_IRQHandler(void);
void USBHS_IRQHandler(void);
void MCAN0_INT0_IRQHandler(void);
void MCAN0_INT1_IRQHandler(void);
void MCAN1_INT0_IRQHandler(void);
void MCAN1_INT1_IRQHandler(void);
void GMAC_IRQHandler(void);
void AFEC1_IRQHandler(void);
void TWIHS2_IRQHandler(void);
void QSPI_IRQHandler(void);
void UART2_IRQHandler(void);
void UART3_IRQHandler(void);
void UART4_IRQHandler(void);
void TC6_IRQHandler(void);
void TC7_IRQHandler(void);
void TC8_IRQHandler(void);
void TC9_IRQHandler(void);
void TC10_IRQHandler(void);
void TC11_IRQHandler(void);
void AES_IRQHandler(void);
void TRNG_IRQHandler(void);
void XDMAC_IRQHandler(void);
void ISI_IRQHandler(void);
void PWM1_IRQHandler(void);
void FPU_IRQHandler(void);
void RSWDT_IRQHandler(void);
void CCW_IRQHandler(void);
void CCF_IRQHandler(void);
void GMAC_Q1_IRQHandler(void);
void GMAC_Q2_IRQHandler(void);
void IXC_IRQHandler(void);
}

namespace modm::platform::detail
{

constexpr std::string_view vectorNames[] =
{
	"__main_stack_top",
	"Reset",
	"NMI",
	"HardFault",
	"MemManage",
	"BusFault",
	"UsageFault",
	"Undefined",
	"Undefined",
	"Undefined",
	"Undefined",
	"SVC",
	"DebugMon",
	"Undefined",
	"PendSV",
	"SysTick",
	"SUPC",
	"RSTC",
	"RTC",
	"RTT",
	"WDT",
	"PMC",
	"EFC",
	"UART0",
	"UART1",
	"Undefined",
	"PIOA",
	"PIOB",
	"Undefined",
	"USART0",
	"USART1",
	"USART2",
	"PIOD",
	"Undefined",
	"HSMCI",
	"TWIHS0",
	"TWIHS1",
	"SPI0",
	"SSC",
	"TC0",
	"TC1",
	"TC2",
	"TC3",
	"TC4",
	"TC5",
	"AFEC0",
	"DACC",
	"PWM0",
	"ICM",
	"ACC",
	"USBHS",
	"MCAN0_INT0",
	"MCAN0_INT1",
	"MCAN1_INT0",
	"MCAN1_INT1",
	"GMAC",
	"AFEC1",
	"TWIHS2",
	"Undefined",
	"QSPI",
	"UART2",
	"UART3",
	"UART4",
	"TC6",
	"TC7",
	"TC8",
	"TC9",
	"TC10",
	"TC11",
	"Undefined",
	"Undefined",
	"Undefined",
	"AES",
	"TRNG",
	"XDMAC",
	"ISI",
	"PWM1",
	"FPU",
	"Undefined",
	"RSWDT",
	"CCW",
	"CCF",
	"GMAC_Q1",
	"GMAC_Q2",
	"IXC",
};


#ifndef MODM_ISR_DISABLE_VALIDATION
#define MODM_ISR_VALIDATE(vector_str, vector) \
	static_assert(::modm::platform::detail::validateIrqName(vector_str), \
			"'" vector_str "' is not a valid IRQ name!\n" \
			"  Hint: You do not need to add '_IRQHandler' to the name.\n" \
			"  Hint: Here are all the IRQs on this device:\n" \
			"    - SUPC\n" \
			"    - RSTC\n" \
			"    - RTC\n" \
			"    - RTT\n" \
			"    - WDT\n" \
			"    - PMC\n" \
			"    - EFC\n" \
			"    - UART0\n" \
			"    - UART1\n" \
			"    - PIOA\n" \
			"    - PIOB\n" \
			"    - USART0\n" \
			"    - USART1\n" \
			"    - USART2\n" \
			"    - PIOD\n" \
			"    - HSMCI\n" \
			"    - TWIHS0\n" \
			"    - TWIHS1\n" \
			"    - SPI0\n" \
			"    - SSC\n" \
			"    - TC0\n" \
			"    - TC1\n" \
			"    - TC2\n" \
			"    - TC3\n" \
			"    - TC4\n" \
			"    - TC5\n" \
			"    - AFEC0\n" \
			"    - DACC\n" \
			"    - PWM0\n" \
			"    - ICM\n" \
			"    - ACC\n" \
			"    - USBHS\n" \
			"    - MCAN0_INT0\n" \
			"    - MCAN0_INT1\n" \
			"    - MCAN1_INT0\n" \
			"    - MCAN1_INT1\n" \
			"    - GMAC\n" \
			"    - AFEC1\n" \
			"    - TWIHS2\n" \
			"    - QSPI\n" \
			"    - UART2\n" \
			"    - UART3\n" \
			"    - UART4\n" \
			"    - TC6\n" \
			"    - TC7\n" \
			"    - TC8\n" \
			"    - TC9\n" \
			"    - TC10\n" \
			"    - TC11\n" \
			"    - AES\n" \
			"    - TRNG\n" \
			"    - XDMAC\n" \
			"    - ISI\n" \
			"    - PWM1\n" \
			"    - FPU\n" \
			"    - RSWDT\n" \
			"    - CCW\n" \
			"    - CCF\n" \
			"    - GMAC_Q1\n" \
			"    - GMAC_Q2\n" \
			"    - IXC\n" \
	)
#else
#define MODM_ISR_VALIDATE(...)
#endif

constexpr int getIrqPosition(std::string_view name)
{
	for (int pos = 0; pos < 85; pos++)
		if (vectorNames[pos] == name) return pos;
	return -1;
}

constexpr bool validateIrqName(std::string_view name)
{
	return getIrqPosition(name) != -1;
}

}	// namespace modm::platform::detail