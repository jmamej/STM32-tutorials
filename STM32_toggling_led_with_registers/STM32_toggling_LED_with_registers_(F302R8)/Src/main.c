/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <stdint.h>

void delay(uint32_t millis)
{
	for(uint32_t i = 0; i<(millis*450); i++)
	{

	}
}

#define RCC_BASEADDRESS		0x40021000U

#define RCC_AHBENR			(RCC_BASEADDRESS + 0x14)

#define AHB_BASEADDRESS		0x48000000U

#define GPIOA_BASEADDRESS	(AHB_BASEADDRESS + 0x0000U)
#define GPIOB_BASEADDRESS	(AHB_BASEADDRESS + 0x0400U)
#define GPIOC_BASEADDRESS	(AHB_BASEADDRESS + 0x0800U)
#define GPIOD_BASEADDRESS	(AHB_BASEADDRESS + 0x0C00U)
#define GPIOF_BASEADDRESS	(AHB_BASEADDRESS + 0x1400U)

#define LED_PORT		B
#define LED_PIN			13
#define BUTTON_PORT		C
#define BUTTON_PIN		13

uint32_t* pClkCtrlReg = (uint32_t*) RCC_AHBENR;	//RCC

uint32_t* pPBModReg = (uint32_t*) GPIOB_BASEADDRESS;	//MODER FOR PORT B
uint32_t* pPCModReg = (uint32_t*) GPIOC_BASEADDRESS;	//MODER FOR PORT C

uint32_t* pPBPuPdReg = (uint32_t*) (GPIOB_BASEADDRESS + 0x0C);

uint32_t* pPBODRReg = (uint32_t*) (GPIOB_BASEADDRESS + 0x14);

uint32_t* pPCIDRReg = (uint32_t*) (GPIOC_BASEADDRESS + 0x10);

int main(void)
{
	/*
	 * RCC_AHBENR
	 */
	*pClkCtrlReg |= (1<<18);	//Enable port B
	*pClkCtrlReg |= (1<<19);	//Enable port C

	*pPBModReg &= ~(0x3 << LED_PIN*2);			//MODER LED
	*pPBModReg |= (0x1 << LED_PIN*2);	//MODER LED

	*pPCModReg &= ~(0x3 << BUTTON_PIN*2);		//MODER BUTTON

	*pPBPuPdReg &= ~(0x3 << LED_PIN*2);	//PUPDR	LED	01: Pull-up
	*pPBPuPdReg |= (0x1 << LED_PIN*2);	//PUPDR	LED	01: Pull-up

    while(1)
    {
		#define BUTTON_PRESS
		//#define LED_TOGGLE

		#ifdef BUTTON_PRESS
    		((*pPCIDRReg >> BUTTON_PIN) & 1) ? (*pPBODRReg &= ~(0x1 << LED_PIN)) : (*pPBODRReg |= (0x1 << LED_PIN));
		#endif

		#ifdef LED_TOGGLE
    		*pPBODRReg ^= (0x1 << LED_PIN);
    		delay(1000);
		#endif
    }
}
