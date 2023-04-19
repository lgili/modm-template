/*
 * Copyright (c) 2018, Niklas Hauser
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
// ----------------------------------------------------------------------------

#include <stdint.h>
#include <modm/architecture/utils.hpp>

// ----------------------------------------------------------------------------
void Undefined_Handler(void);
/* Provide weak aliases for each Exception handler to Undefined_Handler.
 * As they are weak aliases, any function with the same name will override
 * this definition. */
void Reset_Handler(void);
void NMI_Handler(void)							__attribute__((weak, alias("Undefined_Handler")));
void HardFault_Handler(void)					__attribute__((weak, alias("Undefined_Handler")));
void MemManage_Handler(void)					__attribute__((weak, alias("Undefined_Handler")));
void BusFault_Handler(void)						__attribute__((weak, alias("Undefined_Handler")));
void UsageFault_Handler(void)					__attribute__((weak, alias("Undefined_Handler")));
void SVC_Handler(void)							__attribute__((weak, alias("Undefined_Handler")));
void DebugMon_Handler(void)						__attribute__((weak, alias("Undefined_Handler")));
void PendSV_Handler(void)						__attribute__((weak, alias("Undefined_Handler")));
void SysTick_Handler(void)						__attribute__((weak, alias("Undefined_Handler")));
void SUPC_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void RSTC_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void RTC_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void RTT_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void WDT_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void PMC_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void EFC_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void UART0_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void UART1_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void PIOA_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void PIOB_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void USART0_IRQHandler(void)					__attribute__((weak, alias("Undefined_Handler")));
void USART1_IRQHandler(void)					__attribute__((weak, alias("Undefined_Handler")));
void USART2_IRQHandler(void)					__attribute__((weak, alias("Undefined_Handler")));
void PIOD_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void HSMCI_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void TWIHS0_IRQHandler(void)					__attribute__((weak, alias("Undefined_Handler")));
void TWIHS1_IRQHandler(void)					__attribute__((weak, alias("Undefined_Handler")));
void SPI0_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void SSC_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void TC0_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void TC1_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void TC2_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void TC3_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void TC4_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void TC5_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void AFEC0_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void DACC_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void PWM0_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void ICM_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void ACC_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void USBHS_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void MCAN0_INT0_IRQHandler(void)				__attribute__((weak, alias("Undefined_Handler")));
void MCAN0_INT1_IRQHandler(void)				__attribute__((weak, alias("Undefined_Handler")));
void MCAN1_INT0_IRQHandler(void)				__attribute__((weak, alias("Undefined_Handler")));
void MCAN1_INT1_IRQHandler(void)				__attribute__((weak, alias("Undefined_Handler")));
void GMAC_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void AFEC1_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void TWIHS2_IRQHandler(void)					__attribute__((weak, alias("Undefined_Handler")));
void QSPI_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void UART2_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void UART3_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void UART4_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void TC6_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void TC7_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void TC8_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void TC9_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void TC10_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void TC11_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void AES_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void TRNG_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void XDMAC_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void ISI_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void PWM1_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void FPU_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void RSWDT_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void CCW_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void CCF_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
void GMAC_Q1_IRQHandler(void)					__attribute__((weak, alias("Undefined_Handler")));
void GMAC_Q2_IRQHandler(void)					__attribute__((weak, alias("Undefined_Handler")));
void IXC_IRQHandler(void)						__attribute__((weak, alias("Undefined_Handler")));
// ----------------------------------------------------------------------------
typedef void (* const FunctionPointer)(void);

// defined in the linkerscript
extern uint32_t __main_stack_top[];

// Define the vector table
modm_section(".vector_rom")
FunctionPointer vectorsRom[] =
{
	(FunctionPointer)__main_stack_top,		// -16: stack pointer
	Reset_Handler,							// -15: code entry point
	NMI_Handler,							// -14: Non Maskable Interrupt handler
	HardFault_Handler,						// -13: hard fault handler
	MemManage_Handler,						// -12
	BusFault_Handler,						// -11
	UsageFault_Handler,						// -10
	Undefined_Handler,						//  -9
	Undefined_Handler,						//  -8
	Undefined_Handler,						//  -7
	Undefined_Handler,						//  -6
	SVC_Handler,							//  -5
	DebugMon_Handler,						//  -4
	Undefined_Handler,						//  -3
	PendSV_Handler,							//  -2
	SysTick_Handler,						//  -1
	SUPC_IRQHandler,						//   0
	RSTC_IRQHandler,						//   1
	RTC_IRQHandler,							//   2
	RTT_IRQHandler,							//   3
	WDT_IRQHandler,							//   4
	PMC_IRQHandler,							//   5
	EFC_IRQHandler,							//   6
	UART0_IRQHandler,						//   7
	UART1_IRQHandler,						//   8
	Undefined_Handler,						//   9
	PIOA_IRQHandler,						//  10
	PIOB_IRQHandler,						//  11
	Undefined_Handler,						//  12
	USART0_IRQHandler,						//  13
	USART1_IRQHandler,						//  14
	USART2_IRQHandler,						//  15
	PIOD_IRQHandler,						//  16
	Undefined_Handler,						//  17
	HSMCI_IRQHandler,						//  18
	TWIHS0_IRQHandler,						//  19
	TWIHS1_IRQHandler,						//  20
	SPI0_IRQHandler,						//  21
	SSC_IRQHandler,							//  22
	TC0_IRQHandler,							//  23
	TC1_IRQHandler,							//  24
	TC2_IRQHandler,							//  25
	TC3_IRQHandler,							//  26
	TC4_IRQHandler,							//  27
	TC5_IRQHandler,							//  28
	AFEC0_IRQHandler,						//  29
	DACC_IRQHandler,						//  30
	PWM0_IRQHandler,						//  31
	ICM_IRQHandler,							//  32
	ACC_IRQHandler,							//  33
	USBHS_IRQHandler,						//  34
	MCAN0_INT0_IRQHandler,					//  35
	MCAN0_INT1_IRQHandler,					//  36
	MCAN1_INT0_IRQHandler,					//  37
	MCAN1_INT1_IRQHandler,					//  38
	GMAC_IRQHandler,						//  39
	AFEC1_IRQHandler,						//  40
	TWIHS2_IRQHandler,						//  41
	Undefined_Handler,						//  42
	QSPI_IRQHandler,						//  43
	UART2_IRQHandler,						//  44
	UART3_IRQHandler,						//  45
	UART4_IRQHandler,						//  46
	TC6_IRQHandler,							//  47
	TC7_IRQHandler,							//  48
	TC8_IRQHandler,							//  49
	TC9_IRQHandler,							//  50
	TC10_IRQHandler,						//  51
	TC11_IRQHandler,						//  52
	Undefined_Handler,						//  53
	Undefined_Handler,						//  54
	Undefined_Handler,						//  55
	AES_IRQHandler,							//  56
	TRNG_IRQHandler,						//  57
	XDMAC_IRQHandler,						//  58
	ISI_IRQHandler,							//  59
	PWM1_IRQHandler,						//  60
	FPU_IRQHandler,							//  61
	Undefined_Handler,						//  62
	RSWDT_IRQHandler,						//  63
	CCW_IRQHandler,							//  64
	CCF_IRQHandler,							//  65
	GMAC_Q1_IRQHandler,						//  66
	GMAC_Q2_IRQHandler,						//  67
	IXC_IRQHandler,							//  68
};
// ----------------------------------------------------------------------------
// Ignore redeclaration of interrupt handlers in vendor headers
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wredundant-decls"
// Explicitly include this BELOW the vector table to *not deal* with potential
// re-#defines of interrupt vector names! Bad vendors!! BAD!!!
#include <modm/platform/device.hpp>
#include <modm/architecture/interface/assert.h>
void Undefined_Handler(void)
{
	const int32_t irqn = ((int32_t)__get_IPSR()) - 16;
	// Set the currently executing interrupt to the lowest priority to allow
	// reporting of the assertion failure and disable it from firing again.
	NVIC_SetPriority((IRQn_Type)irqn, (1ul << __NVIC_PRIO_BITS) - 1ul);
	NVIC_DisableIRQ((IRQn_Type)irqn);
	modm_assert_continue_fail(0, "nvic.undef",
			"An undefined NVIC interrupt was raised!", irqn);
}

#pragma GCC diagnostic pop