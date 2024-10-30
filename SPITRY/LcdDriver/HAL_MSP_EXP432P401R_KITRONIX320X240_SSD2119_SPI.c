#include "F2806x_Device.h"     // F28069M register definitions
#include "f2806x_examples.h"    // F28069M system setup
#include <stdint.h>
#include "HAL_MSP_EXP432P401R_KITRONIX320X240_SSD2119_SPI.h"
// Function prototypes
void HAL_LCD_initLCD(void);
void HAL_LCD_writeCommand(uint16_t command);
void HAL_LCD_writeData(uint16_t data);
void HAL_LCD_selectLCD(void);
void HAL_LCD_deselectLCD(void);
void HAL_LCD_delay(uint32_t msec);

//*****************************************************************************
//
//! Initializes the display driver on F28069M.
//
//*****************************************************************************
void HAL_LCD_initLCD(void)
{
    // Configure GPIO pins for LCD control signals as output
    EALLOW;
    GpioCtrlRegs.GPAMUX1.all &= ~(0x0000FFFF);  // Set pins as GPIO
    GpioCtrlRegs.GPADIR.all |= (1 << LCD_RESET_PIN);  // Set as output
    GpioCtrlRegs.GPADIR.all |= (1 << LCD_SDC_PIN);    // Set as output
    GpioCtrlRegs.GPADIR.all |= (1 << LCD_SCS_PIN);    // Set as output
    GpioCtrlRegs.GPADIR.all |= (1 << LCD_PWM_PIN);    // Backlight control

    // Initialize GPIO pins for LCD control to low state
    GpioDataRegs.GPACLEAR.all = (1 << LCD_RESET_PIN) | (1 << LCD_SDC_PIN) | (1 << LCD_SCS_PIN);
    EDIS;

    // Configure SPI
    EALLOW;
    SpiaRegs.SPICCR.all = 0x0007;      // Reset SPI, 8-bit char size
    SpiaRegs.SPICTL.all = 0x0006;      // Enable master mode, enable talk, no loopback
    SpiaRegs.SPIBRR = 0x007F;          // Set SPI baud rate (use a suitable divider)
    SpiaRegs.SPICCR.all = 0x0087;      // Release SPI from reset
    SpiaRegs.SPIPRI.bit.FREE = 1;      // Free run, unaffected by debug halt
    EDIS;

    // Backlight Enable
    EALLOW;
    GpioDataRegs.GPASET.all = (1 << LCD_PWM_PIN);  // Set backlight pin high
    EDIS;

    // LCD reset sequence
    GpioDataRegs.GPASET.all = (1 << LCD_RESET_PIN);  // Set LCD_RESET_PIN high
    HAL_LCD_delay(1);  // Delay for LCD reset
}

//*****************************************************************************
//
// Writes a command to the LCD.
//
//*****************************************************************************
void HAL_LCD_writeCommand(uint16_t command)
{
    // Wait until SPI is not busy
    while (SpiaRegs.SPISTS.bit.BUFFULL_FLAG == 1);

    // Set SDC to low to indicate command
    EALLOW;
    GpioDataRegs.GPACLEAR.all = (1 << LCD_SDC_PIN);
    EDIS;

    // Send command
    SpiaRegs.SPITXBUF = command;

    // Wait for SPI transmission to complete
    while (SpiaRegs.SPISTS.bit.INT_FLAG == 0);

    // Set SDC high after sending command
    EALLOW;
    GpioDataRegs.GPASET.all = (1 << LCD_SDC_PIN);
    EDIS;
}

//*****************************************************************************
//
// Writes data to the LCD.
//
//*****************************************************************************
void HAL_LCD_writeData(uint16_t data)
{
    // Wait until SPI is not busy
    while (SpiaRegs.SPISTS.bit.BUFFULL_FLAG == 1);

    // Set SDC to high to indicate data
    EALLOW;
    GpioDataRegs.GPASET.all = (1 << LCD_SDC_PIN);
    EDIS;

    // Send high byte of data
    SpiaRegs.SPITXBUF = (data >> 8);

    // Wait for SPI transmission to complete
    while (SpiaRegs.SPISTS.bit.INT_FLAG == 0);

    // Send low byte of data
    SpiaRegs.SPITXBUF = (data & 0xFF);

    // Wait for SPI transmission to complete
    while (SpiaRegs.SPISTS.bit.INT_FLAG == 0);
}

//*****************************************************************************
//
// Selects the LCD by pulling the chip select (CS) low.
//
//*****************************************************************************
void HAL_LCD_selectLCD(void)
{
    // Wait until SPI is not busy
    while (SpiaRegs.SPISTS.bit.BUFFULL_FLAG == 1);

    // Set SCS low to select the LCD
    EALLOW;
    GpioDataRegs.GPACLEAR.all = (1 << LCD_SCS_PIN);
    EDIS;
}

//*****************************************************************************
//
// Deselects the LCD by pulling the chip select (CS) high.
//
//*****************************************************************************
void HAL_LCD_deselectLCD(void)
{
    // Wait until SPI is not busy
    while (SpiaRegs.SPISTS.bit.BUFFULL_FLAG == 1);

    // Set SCS high to deselect the LCD
    EALLOW;
    GpioDataRegs.GPASET.all = (1 << LCD_SCS_PIN);
    EDIS;
}

//*****************************************************************************
//
// Generates delay (approximately in milliseconds based on clock).
//
//*****************************************************************************
void HAL_LCD_delay(uint32_t msec)
{
    uint32_t i;
    uint32_t delay = msec * (SysCtrlRegs.LOSPCP.all ? 1500 : 750);

    for (i = 0; i < delay; i++) { asm(" NOP"); }
}
