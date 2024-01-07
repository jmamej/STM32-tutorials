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

#define RCC_BASE_ADDRESS		0x40021000U
#define RCC_IOPENR				(RCC_BASE_ADDRESS + 0x34U)

#define IOPORT_BASE_ADDRESS		0x50000000U
#define GPIOA_BASE_ADDRESS		IOPORT_BASE_ADDRESS
#define GPIOA_MODER				IOPORT_BASE_ADDRESS
#define GPIOA_ODR				(IOPORT_BASE_ADDRESS + 0x14U)

#define GPIOC_BASE_ADDRESS		(IOPORT_BASE_ADDRESS + 0x0800U)
#define GPIOC_MODER				GPIOC_BASE_ADDRESS
#define GPIOC_IDR				(GPIOC_BASE_ADDRESS + 0x10U)


uint32_t* pRCC_IOPENReg = 	(uint32_t*) RCC_IOPENR;

uint32_t* pGPIOA_MODERReg = (uint32_t*) GPIOA_MODER;
uint32_t* pGPIOA_ODRReg = 	(uint32_t*) GPIOA_ODR;

uint32_t* pGPIOC_MODERReg = (uint32_t*) GPIOC_MODER;
uint32_t* pGPIOC_IDRReg = 	(uint32_t*) GPIOC_IDR;

void delay(uint16_t delay_time)
{
	for(int i = 0; i < delay_time * 700; i++);
}

int main(void)
{

	*pRCC_IOPENReg |= 1;			//enabling clock for GPIOA (on board led for G070RB)
	*pRCC_IOPENReg |= (1<<2);		//enabling clock for GPIOC (on board button for G070RB)

	*pGPIOA_MODERReg &= ~(1<<11);	//reset 11'th bit of MODER5
	*pGPIOA_MODERReg |= (1<<10);	//set 10'th bit of MODER5	Output mode: 01

	*pGPIOC_MODERReg &= ~(3<<26);	//reset 26'th and 27'th bit of MODER13 Input mode: 00

	for(;;)
	{

		((*pGPIOC_IDRReg >> 13 ) & 1) ? (*pGPIOA_ODRReg &= ~(1<<5)) : (*pGPIOA_ODRReg |= (1<<5));	//conditional operator: statement ? if true : if false;

	}
}