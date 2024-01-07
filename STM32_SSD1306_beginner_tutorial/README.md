# STM32-SSD1306-for-beginners
Easy step-by-step tutorial on how to make OLED screen work with your STM32 project.

### 1. Create STM32 project and choose appropriate board.
![image](https://github.com/jmamej/STM32-SSD1306-for-beginners/assets/57408600/9ba0e80d-dc11-43ac-b338-f46a98745fc6)

### 2. Generate .c/.h files
In MX go to Project Manager tab >> check Generate peripheral initialization as a pair of '.c/.h' files per peripheral for code readability.

![image](https://github.com/jmamej/STM32-SSD1306-for-beginners/assets/57408600/665b014a-28f2-423e-95bc-f283fcecda75)

Clock configuration:

![image](https://github.com/jmamej/STM32-SSD1306-for-beginners/assets/57408600/a394716c-ff9b-47b5-b4f1-8e43ecf9e074)

### 3. Enable I2C in Pinout & Configuration tab

Change speed mode to Fast, leave primary slave address as 7-bit.

![image](https://github.com/jmamej/STM32-SSD1306-for-beginners/assets/57408600/25a6b524-1baa-4154-9c61-4b99d81ce52f)

### 4. Generate code

![image](https://github.com/jmamej/STM32-SSD1306-for-beginners/assets/57408600/9e272742-16dc-42cc-a0b0-e240576911b1)

### 5. Create new folder and import SSD1306 library

In Project Explorer right click your project and add new folder.

![image](https://github.com/jmamej/STM32-SSD1306-for-beginners/assets/57408600/d0d949ad-027a-4620-b0d7-2e08434f3223)

Download SSD1306 library:
https://github.com/taburyak/STM32_OLED_SSD1306_HAL_DMA

I did not code this driver, all credit goes to taburyak.

Now you can simply copy/ paste files into SSD1306 folder.
You can split .c and .h files into Inc and Src folders (not required).

![image](https://github.com/jmamej/STM32-SSD1306-for-beginners/assets/57408600/986b0533-09ac-467a-a0f8-10d27da78ecd)

IDE does not recognise this files, even if they are in the same workspace/ project. 

![image](https://github.com/jmamej/STM32-SSD1306-for-beginners/assets/57408600/7fd5d697-5826-4200-bae7-559530e9d18c)

Right click your project and go to Properties, extend C/C++ General >> Paths and symbols.

In the Include tab click ADD

![image](https://github.com/jmamej/STM32-SSD1306-for-beginners/assets/57408600/e25c4eca-5a52-4f0a-8b33-9979f9b4c783)

Workspace

![image](https://github.com/jmamej/STM32-SSD1306-for-beginners/assets/57408600/ebe77468-ffa8-465a-8f64-73289607566c)

In Project Explorer find your project, extend, click on the SSD folder and OK

![image](https://github.com/jmamej/STM32-SSD1306-for-beginners/assets/57408600/ae2b7975-6322-4a8a-be10-21fd628bba1d)

In Source Location click Add folder

![image](https://github.com/jmamej/STM32-SSD1306-for-beginners/assets/57408600/339d0c72-b4ef-47ad-a865-c7f6ef16a1f3)

![image](https://github.com/jmamej/STM32-SSD1306-for-beginners/assets/57408600/45bc7be0-b552-4cd6-98c5-9e7f7c2d88fb)

Click OK, Apply, Apply and close

Now the driver icons should look like this:

![image](https://github.com/jmamej/STM32-SSD1306-for-beginners/assets/57408600/e4198b9a-f628-4af9-bc13-b8b0b59172f4)

If the font on driver icons is hollow, driver files were not propperly included:

![image](https://github.com/jmamej/STM32-SSD1306-for-beginners/assets/57408600/eca97284-d6ea-43c3-ac38-189ea50dc5ed)

### 6. Include library header file

![image](https://github.com/jmamej/STM32-SSD1306-for-beginners/assets/57408600/e002a5bb-a496-4b36-b418-851370ff3f76)

### 7. Build

Building should return no errors

![image](https://github.com/jmamej/STM32-SSD1306-for-beginners/assets/57408600/d05ba74b-1a21-48d5-8150-0f2383fc86cb)

Inside ssd1306_defines.h you can chose between 128x64 and 128x32 oled.

Make sure that #define SSD1306_I2C_PORT hi2c1 is correct. If you are not sure which I2C was enabled, go to:

![image](https://github.com/jmamej/STM32-SSD1306-for-beginners/assets/57408600/938eff0c-0d42-4231-8adb-36d64e2e2cc5)

![image](https://github.com/jmamej/STM32-SSD1306-for-beginners/assets/57408600/c409ac11-1035-4dde-a507-da831a0370e1)

### 8. Run configurations

![image](https://github.com/jmamej/STM32-SSD1306-for-beginners/assets/57408600/1f670c55-bdac-425a-be1e-af8f0b8de7b1)

![image](https://github.com/jmamej/STM32-SSD1306-for-beginners/assets/57408600/d9682c3c-4539-4c62-a229-5837cbcc8367)

Double click STM32 C/C++ Aplication

Make sure Debug/STM32_OLED.elf is .elf of your current project

Apply then Close.

### 9. Add Code

Just before while loop add Init, Fill and UpdateScreen.

![image](https://github.com/jmamej/STM32-SSD1306-for-beginners/assets/57408600/407d06f0-2555-4b62-a1b9-71b3fa9449a5)

### 10. Connect SSD1306 to your board

Download User Manual for your board:

G070RB: https://www.st.com/resource/en/user_manual/um2324-stm32-nucleo64-boards-mb1360-stmicroelectronics.pdf

![image](https://github.com/jmamej/STM32-SSD1306-for-beginners/assets/57408600/05688597-ab2a-4253-a42d-c7fa9d1eec14)

### 11. Build and run

![image](https://github.com/jmamej/STM32-SSD1306-for-beginners/assets/57408600/70942281-c17a-4b4d-9f5d-c7d4d00d6aaa)

### Possible errors

1. If your screen does not "Fill" do not worry, there might be and error (or something that i do not comprehend) in the driver. Go to ssd1306.c and Init function and find:

```
  // Set default values for screen object
  SSD1306.CurrentX = 0;
  SSD1306.CurrentY = 0;
  SSD1306.Color = Black;  //White
```

  Now change color to White, build and run again.

2. If you put Init in: USER CODE BEGIN Init, OLED might not initialize.

3. If your screen does not work, double check phisical connections, then use onboard led for debugging:

Make sure your onboard led is initialized in MX:

![image](https://github.com/jmamej/STM32-SSD1306-for-beginners/assets/57408600/27eaef41-3c10-4b5b-a66a-070da67c74f5)

Use conditional operator (or good old if else):

![image](https://github.com/jmamej/STM32-SSD1306-for-beginners/assets/57408600/b757716c-de68-462e-91e7-2d65704e73f2)

![image](https://github.com/jmamej/STM32-SSD1306-for-beginners/assets/57408600/986dd2bf-6ad5-4489-a638-1c25f76cae78)

Correctly initialized SSD1306 Init function will return 1, the led will turn on, if it returns 0 led will stay off.

### 12. Printing text and variables

You write string by simply using: ssd1306_WriteString(str, font);

You can find fonts in fonts.h.

eg:

```
  ssd1306_Init();
  ssd1306_WriteString("IT works :)", Font_11x18);
  ssd1306_UpdateScreen();
```
  
![image](https://github.com/jmamej/STM32-SSD1306-for-beginners/assets/57408600/ecfc7247-9954-4d37-9728-3261c48871d0)

If the text is upside down from your perspective use:

```
ssd1306_FlipScreenVertically();
```

**Printing variables**

Add stdio.h to your private includes to make sprintf work

![image](https://github.com/jmamej/STM32-SSD1306-for-beginners/assets/57408600/ed3b8ffe-6b92-4b08-acbd-c4e7fe2aa021)

```
  char string_buffer[32];
  int secret_number = 2137;
  ssd1306_Init() ? HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, 1) : HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, 0);
  ssd1306_FlipScreenVertically();
  sprintf(string_buffer, "Num: %d", secret_number);	//%d is format specifier for printing int
  ssd1306_SetCursor(0, 16);
  ssd1306_WriteString(string_buffer, Font_11x18);
  ssd1306_UpdateScreen();
```

![image](https://github.com/jmamej/STM32-SSD1306-for-beginners/assets/57408600/949c9b8a-cc5b-47eb-b861-695b6654a56a)

**Printing float**

Float formating is not supported by default, revisit properties:

Properties >> C/C++ build >> Settings >> MCU Settigs >> check use float with printf

![image](https://github.com/jmamej/STM32-SSD1306-for-beginners/assets/57408600/a96d282d-44e9-42d1-835f-dc8daf03548b)

```
  char string_buffer[32];
  float secret_number = 21.37;
  ssd1306_Init() ? HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, 1) : HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, 0);
  ssd1306_FlipScreenVertically();
  sprintf(string_buffer, "Num: %f", secret_number); //%f is format specifier for printing float
  ssd1306_SetCursor(0, 16);
  ssd1306_WriteString(string_buffer, Font_11x18);
  ssd1306_UpdateScreen();
```

![image](https://github.com/jmamej/STM32-SSD1306-for-beginners/assets/57408600/90627bc1-23e6-47b5-9a28-49c689556f75)

```
sprintf(string_buffer, "Num: %.2f", secret_number); //%.2f will display float with 2 decimal places
```

![image](https://github.com/jmamej/STM32-SSD1306-for-beginners/assets/57408600/5a9f37f3-3fb5-475b-b164-5b3f9cfdf67b)
