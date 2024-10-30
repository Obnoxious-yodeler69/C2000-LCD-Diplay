#ifndef F2806X_LCD_HAL_H_
#define F2806X_LCD_HAL_H_

#include <stdint.h>
#include "F2806x_Device.h"        // Device Header for F2806x
#include "F2806x_Examples.h"      // Example configurations

// GPIO pin definitions for LCD control on F2806x
#define LCD_RESET_PIN   21    // GPIO21 for LCD Reset
#define LCD_SDC_PIN     20    // GPIO20 for Data/Command selection
#define LCD_SCS_PIN     19    // GPIO19 for Chip Select
#define LCD_SDI_PIN     16    // GPIO16 for Data Input (SPI)
#define LCD_SCL_PIN     18    // GPIO18 for Clock (SPI)
#define LCD_PWM_PIN     22    // GPIO22 for Backlight control (PWM)

// SPI Base for F2806x SPI-A peripheral
#define LCD_SPI_BASE    SpiaRegs

// Function Prototypes
void HAL_LCD_initLCD(void);         // Initialize LCD and set control pins
void HAL_LCD_writeCommand(uint16_t command); // Send command to LCD
void HAL_LCD_writeData(uint16_t data);       // Send data to LCD
void HAL_LCD_selectLCD(void);       // Activate LCD chip select
void HAL_LCD_deselectLCD(void);     // Deactivate LCD chip select
void HAL_LCD_delay(uint32_t msec);  // Delay in milliseconds

// Inline GPIO functions for control pins
inline void HAL_LCD_setResetPinHigh(void) { GpioDataRegs.GPASET.bit.GPIO21 = 1; }
inline void HAL_LCD_setResetPinLow(void) { GpioDataRegs.GPACLEAR.bit.GPIO21 = 1; }

inline void HAL_LCD_setSDCPinHigh(void) { GpioDataRegs.GPASET.bit.GPIO20 = 1; }
inline void HAL_LCD_setSDCPinLow(void) { GpioDataRegs.GPACLEAR.bit.GPIO20 = 1; }

inline void HAL_LCD_setSCSPinHigh(void) { GpioDataRegs.GPASET.bit.GPIO19 = 1; }
inline void HAL_LCD_setSCSPinLow(void) { GpioDataRegs.GPACLEAR.bit.GPIO19 = 1; }

inline void HAL_LCD_setPWMPinHigh(void) { GpioDataRegs.GPASET.bit.GPIO22 = 1; }
inline void HAL_LCD_setPWMPinLow(void) { GpioDataRegs.GPACLEAR.bit.GPIO22 = 1; }

#endif /* F2806X_LCD_HAL_H_ */
