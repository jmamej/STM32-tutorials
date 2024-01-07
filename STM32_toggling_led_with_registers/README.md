
# STM32 blinking LED with Registers

Documents required:
- Datasheet
- Reference Manual

Inside Datasheet localize Block diagram:

![image](https://github.com/jmamej/STM32-blinking-LED-with-Registers/assets/57408600/cce72730-8b87-41bd-aeab-fb90d64486f5)

Check which bus connects GPIOs to CPU. In case of G070RB it's IOPORT.

Inside Reference Manual localize Memory map:

![image](https://github.com/jmamej/STM32-blinking-LED-with-Registers/assets/57408600/171fa0f7-8985-432e-8d86-aa28a5ba9bb2)

![image](https://github.com/jmamej/STM32-blinking-LED-with-Registers/assets/57408600/d49569a7-1ed8-4d90-b4b0-ba7ef1a840e9)

If you scroll down you will find tables with Registers addresses. Localize RCC.

![image](https://github.com/jmamej/STM32-blinking-LED-with-Registers/assets/57408600/ac5a99a3-a802-4abd-a473-1052450009c7)

Make sure table refers to your microcontroler, one .pdf may refer to more than one microcontroler.

### 1. Create Empty project

![image](https://github.com/jmamej/STM32-blinking-LED-with-Registers/assets/57408600/69df6501-ffd7-4d26-a2a4-1324e40c5d53)


main.c should look like this:
```
#include <stdint.h>



int main(void)
{


	for(;;);
}
```

### 2. Define register addresses

RCC - Reset and Clock Control - this register enables GPIO ports. It's starting address is 0x4002 1000

![image](https://github.com/jmamej/STM32-blinking-LED-with-Registers/assets/57408600/e8544f11-54d6-492f-997f-af3bfc85b331)

Click the hyperlink in Peripheral register map column, you will be transfered to RCC register map.

![image](https://github.com/jmamej/STM32-blinking-LED-with-Registers/assets/57408600/1b47de86-c9eb-46ea-aa74-630757e60991)

If your GPIOs are connected to CPU via APB or AHB buss, look for RCC_APBENR of RCC_AHBENR

In my case it's RCC_IOPENR

![image](https://github.com/jmamej/STM32-blinking-LED-with-Registers/assets/57408600/f52ff86c-1962-4cea-9164-4889e86008e0)

To get address of this register simply add RCC base address and add offset (1st column). In my case it's 0x34

My built in led is connected to port A, pin 5. In order to enable clock for this port simply write 1 into 0'th bit of RCC_IOPENR.

Localize GPIOs, and get base oddress for desired port.

![image](https://github.com/jmamej/STM32-blinking-LED-with-Registers/assets/57408600/af17192a-3263-4726-a194-8585f2a146ab)

Go to the registers of GPIOs via hyperlink in Peripheral register map column

![image](https://github.com/jmamej/STM32-blinking-LED-with-Registers/assets/57408600/9e8dde62-9d63-4279-8654-51de156373fd)

To toggle led we need GPIOx_MODER and GPIOx_ODR

MODER:

![image](https://github.com/jmamej/STM32-blinking-LED-with-Registers/assets/57408600/62d11eef-31df-4370-9dac-e8084ca8006c)

ODR:

![image](https://github.com/jmamej/STM32-blinking-LED-with-Registers/assets/57408600/d7d2a587-ce1b-4b27-8d8c-029df4938cbb)


This is how I defined register addresses:

```
#define RCC_BASE_ADDRESS		  0x40021000U
#define RCC_IOPENR				    (RCC_BASE_ADDRESS + 0x34U)

#define IOPORT_BASE_ADDRESS		0x50000000U
#define GPIOA_BASE_ADDRESS		IOPORT_BASE_ADDRESS
#define GPIOA_MODER				    IOPORT_BASE_ADDRESS
#define GPIOA_ODR			      	(IOPORT_BASE_ADDRESS + 0x14U)
```

### 3. Assigning addresses to pointers

We need to create pointers so we can put 0's and 1's into microcontroller memory.

STM32 is 32 bit so we have to create 32 bit pointers:

```
uint32_t* pRCC_IOPENReg = 	(uint32_t*) RCC_IOPENR;

uint32_t* pGPIOA_MODERReg = (uint32_t*) GPIOA_MODER;
uint32_t* pGPIOA_ODRReg = 	(uint32_t*) GPIOA_ODR;
```

### 4. Set RCC and MODER

![image](https://github.com/jmamej/STM32-blinking-LED-with-Registers/assets/57408600/515b5e80-9aae-4c5e-bb6e-7cfb518782ee)

Set bit with logic operators AND (&), OR (|) and XOR (^).

Example:

Our point is to set 0'th bit of this register. We need to create mask

Some register: 00000000 00000000 00000000 00000000

register mask: 00000000 00000000 00000000 00000001

AND result:    00000000 00000000 00000000 00000000

OR result:     00000000 00000000 00000000 00000001

XOR result:    00000000 00000000 00000000 00000001


XOR is for bit toggling, OR is for bit seting, AND (with NOT) is for bit clearing.

In order to set 0'th bit of RCC_IOPENR we do:

```
*pRCC_IOPENReg = *pRCC_IOPENReg | 1;  //1 is our mask (0x01 or 0b00000001)
```

or:

*pRCC_IOPENReg |= 1;

In case of MODER (output mode: 01) we need to make sure bits are first cleared then set.

Our led is at pin 5, which means we need to clear 11'th bit and set 10'th bit.

```
*pGPIOA_MODERReg &= ~(1<<11);
*pGPIOA_MODERReg |= (1<<10);
```

And lastly write 1 to 5 bit of ODR.

```
*pGPIOA_ODRReg |= (1<<5);
```

All code:

```
#include <stdint.h>

#define RCC_BASE_ADDRESS		  0x40021000U
#define RCC_IOPENR				    (RCC_BASE_ADDRESS + 0x34U)

#define IOPORT_BASE_ADDRESS		0x50000000U
#define GPIOA_BASE_ADDRESS		IOPORT_BASE_ADDRESS
#define GPIOA_MODER				    IOPORT_BASE_ADDRESS
#define GPIOA_ODR				      (IOPORT_BASE_ADDRESS + 0x14U)

uint32_t* pRCC_IOPENReg = 	  (uint32_t*) RCC_IOPENR;

uint32_t* pGPIOA_MODERReg =   (uint32_t*) GPIOA_MODER;
uint32_t* pGPIOA_ODRReg = 	  (uint32_t*) GPIOA_ODR;

int main(void)
{

	*pRCC_IOPENReg |= 1;			      //enabling clock for GPIOA (on board led for G070RB)

	*pGPIOA_MODERReg &= ~(1<<11);	  //reset 11'th bit of MODER5
	*pGPIOA_MODERReg |= (1<<10);	  //set 10'th bit of MODER5	Output mode: 01

	*pGPIOA_ODRReg |= (1<<5);		    //Set 5'th bit of ODR - led will turn on.

	for(;;);
}
```

If you chose correct board during project creation and set up register addresses properly your led should turn on.

### Possible errors

Build and debug

![image](https://github.com/jmamej/STM32-blinking-LED-with-Registers/assets/57408600/9dda9aad-04e3-4a17-ad10-4f115d00b00e)

In debug configuretion make sure your .elf does match your project name:

![image](https://github.com/jmamej/STM32-blinking-LED-with-Registers/assets/57408600/ec4bedef-6e0a-441d-9090-d8bbba38eb67)

While in debug mode find SFR's window, if it's not showing go to Window >> Show View >> SFRs

![image](https://github.com/jmamej/STM32-blinking-LED-with-Registers/assets/57408600/f537b07d-43d8-48a3-a28a-210ade4c29a6)

First we set RCC_IOPENR. In SFR locate RCC, extend, IOPENR, click GPIOAEN - this bit will light up.

![image](https://github.com/jmamej/STM32-blinking-LED-with-Registers/assets/57408600/955a7e42-0521-4c30-b92c-0e65614e448c)

Now if you step over this bit should change from 0 to 1. You can observe rest of registers in SFRs

![image](https://github.com/jmamej/STM32-blinking-LED-with-Registers/assets/57408600/a3f27d3d-3bc5-4b1b-89b9-d41fcd910607)

![image](https://github.com/jmamej/STM32-blinking-LED-with-Registers/assets/57408600/06c171dd-222f-4b95-ba6e-10ac3ff58140)

if desired bit did not change either adresses are incorrect or selected board does not match with the one that is being used.

Make sure defined addresses does not contain space : #define RCC_BASE_ADDRESS		  0x4002 1000U

And make sure they have 'U' at the end of an address

Do not forget to put '*' when dealing with pointers

### 5. Toggling with delay

You can finally add your beloved arduino function - delay:

```
void delay(uint16_t delay_time)
{
	for(int i = 0; i < delay_time * 700; i++);
}
```

delay_time * 700 with my current clock settings gives me about 1 s delay, might work differently on different microcontrolers.

```
#include <stdint.h>

#define RCC_BASE_ADDRESS		  0x40021000U
#define RCC_IOPENR				    (RCC_BASE_ADDRESS + 0x34U)

#define IOPORT_BASE_ADDRESS		0x50000000U
#define GPIOA_BASE_ADDRESS		IOPORT_BASE_ADDRESS
#define GPIOA_MODER			    	IOPORT_BASE_ADDRESS
#define GPIOA_ODR			    	(IOPORT_BASE_ADDRESS + 0x14U)

uint32_t* pRCC_IOPENReg = 	(uint32_t*) RCC_IOPENR;

uint32_t* pGPIOA_MODERReg = (uint32_t*) GPIOA_MODER;
uint32_t* pGPIOA_ODRReg = 	(uint32_t*) GPIOA_ODR;

void delay(uint16_t delay_time)
{
	for(int i = 0; i < delay_time * 700; i++);
}


int main(void)
{

	*pRCC_IOPENReg |= 1;			        //enabling clock for GPIOA (on board led for G070RB)

	*pGPIOA_MODERReg &= ~(1<<11);	    //reset 11'th bit of MODER5
	*pGPIOA_MODERReg |= (1<<10);	    //set 10'th bit of MODER5	Output mode: 01

	*pGPIOA_ODRReg |= (1<<5);		      //Set 5'th bit of ODR - led will turn on.

	for(;;)
	{
		delay(1000);
		*pGPIOA_ODRReg ^= (1<<5);  //XOR
	}
}
```

Led should toggle every second.

### 5. Led turns on while button is pressed

To add button i will have to enable port C in RCC and set it to input.

```
#include <stdint.h>

#define RCC_BASE_ADDRESS  0x40021000U
#define RCC_IOPENR    (RCC_BASE_ADDRESS + 0x34U)

#define IOPORT_BASE_ADDRESS  0x50000000U
#define GPIOA_BASE_ADDRESS  IOPORT_BASE_ADDRESS
#define GPIOA_MODER      IOPORT_BASE_ADDRESS
#define GPIOA_ODR      (IOPORT_BASE_ADDRESS + 0x14U)

#define GPIOC_BASE_ADDRESS  (IOPORT_BASE_ADDRESS + 0x0800U)
#define GPIOC_MODER      GPIOC_BASE_ADDRESS
#define GPIOC_IDR      (GPIOC_BASE_ADDRESS + 0x10U)


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

	*pRCC_IOPENReg |= 1;      //enabling clock for GPIOA (on board led for G070RB)
	*pRCC_IOPENReg |= (1<<2);  //enabling clock for GPIOC (on board button for G070RB)

	*pGPIOA_MODERReg &= ~(1<<11);  //reset 11'th bit of MODER5
	*pGPIOA_MODERReg |= (1<<10);  //set 10'th bit of MODER5	Output mode: 01

	*pGPIOC_MODERReg &= ~(3<<26);  //reset 26'th and 27'th bit of MODER13 Input mode: 00


	for(;;)
	{

		((*pGPIOC_IDRReg >> 13 ) & 1) ? (*pGPIOA_ODRReg &= ~(1<<5)) : (*pGPIOA_ODRReg |= (1<<5));  //conditional operator: statement ? if true : if false;

	}
}
```
