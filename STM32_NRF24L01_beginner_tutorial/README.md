### NRF24L01+

Driver (created by – mokhwasomssi):
https://github.com/mokhwasomssi/stm32_hal_nrf24l01p

![image](https://github.com/jmamej/STM32-tutorials/assets/57408600/933faea1-92ab-442e-96eb-2949945d438e)


### SPI configuration

Keep baud rate below 10 Mbits/s

![image](https://github.com/jmamej/STM32-tutorials/assets/57408600/0b5c9465-378f-4e81-b76d-0ca5c099a57d)


### PINs configuration

![image](https://github.com/jmamej/STM32-tutorials/assets/57408600/91ea4334-55ca-463e-926f-c654ca7b16eb)

![image](https://github.com/jmamej/STM32-tutorials/assets/57408600/cc68a49b-3d27-4b06-8da7-2000ee1e99f9)


### IRQ configuration

IRQ active low, setip falling edge trigger detection

![image](https://github.com/jmamej/STM32-tutorials/assets/57408600/a3e7e3ee-7503-4164-b066-6d7f41168cdb)

![image](https://github.com/jmamej/STM32-tutorials/assets/57408600/7e5bd918-40bf-44ba-a221-ae4363ad4725)

![image](https://github.com/jmamej/STM32-tutorials/assets/57408600/49457023-bb9c-4d6d-88cd-059970fd8a99)


### NRF24L01+ Setup

TX and RX frequencies must match exactly for a connection to occur. 1Hz difference will prevent devices from connecting.

The Air-data-rate must match for a connection to occur. Any difference will prevent devices from connecting.

You have the flexibility to utilize varying levels of output power.

Max retransmit number is 15 (reset value is 3).

![image](https://github.com/jmamej/STM32-tutorials/assets/57408600/e7cc88ea-73f6-4502-967b-32e9df4e550f)


### Interupts

Masking interrupts will prevent them from being signaled on the IRQ pin.

![image](https://github.com/jmamej/STM32-tutorials/assets/57408600/86ec6b71-c579-4d84-9a0a-04c9bf957521)


RX_DR – Receiver Data Received

TX_DS – Transmitter Data Sent

MAX_RT – Max retransmissions



API for masking IRQ:

```
uint8_t nrf24l01p_irq_mask_en(uint8_t rx_dr, uint8_t tx_ds, uint8_t max_rt)
{
	uint8_t temp_reg;
	temp_reg = read_register(NRF24L01P_REG_CONFIG);

	if(rx_dr == 1)	temp_reg |= (1<<6);
	else		temp_reg &= ~(1<<6);
	if(tx_ds == 1)	temp_reg |= (1<<5);
	else		temp_reg &= ~(1<<5);
	if(max_rt == 1)	temp_reg |= (1<<4);
	else		temp_reg &= ~(1<<4);

	write_register(NRF24L01P_REG_CONFIG, temp_reg);
	return temp_reg;
}
```

main.c:

```
nrf24l01p_irq_mask_en(1, 0, 0); //for transmitter
nrf24l01p_irq_mask_en(0, 1, 1); //for receiver
```

Handling interupts logic:


TX


main.c:


nrf24l01p_tx_transmit(data);	// keep in main


Interrupt callback:

-	flush FIFO
	
-	reset interrupt flags



RX


Interrupt callback:


- nrf24l01p_rx_receive(data);
 
-	flush FIFO
	
-	reset interrupt flags



Handling interrupts example:

```
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == NRF_IRQ_Pin)
	{
// nrf24l01p_get_status(); //uncomment to see which interrupt fired
#ifdef TX
	nrf24l01p_flush_tx_fifo();//flush FIFO to avoid immediate interrupt
	nrf24l01p_tx_irq();		//clear IRQ flags to avoid immediate interrupt
	HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);//Visual indication of transmitted data
#else
	nrf24l01p_rx_receive(data);	//reading data from FIFO
	nrf24l01p_flush_rx_fifo();//flush FIFO to avoid immediate interrupt
	nrf24l01p_clear_rx_dr();	//clear IRQ flags to avoid immediate interrupt
	HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin); //Visual indication of received data
#endif
	}
}
```

### How NRF communicates

TX_DS – IRQ goes low if payload was sent and ACK was received back.
TX sends data > RX sends back ACK packet > TX_DS = 1 > IRQ = 0. 

MAX_RT – IRQ goes low if payload was sent (pushed to FIFO) and not received by any RX (no ACK was received by TX). Packets are being transmitted regardless. 

RX_DR – Data received by RX device.

![image](https://github.com/jmamej/STM32-tutorials/assets/57408600/52be71c5-8cb1-404b-8a14-1918cf437ec2)

When debugging transmitter only, if you get MAX_RT interrupt and device is configured correctly, packets are possibly being transmitted. Without RX device TX will not receive ACK.

