/* --COPYRIGHT--, BSD
 * Copyright (c) 2016, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 *
 * * Neither the name of Texas Instruments Incorporated nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT-- */

#ifndef TOUCH_H_
#define TOUCH_H_

#include <stdint.h>
#include <stdbool.h>
#include <F2806x_Device.h> // Include F28069M device header

/*
 * Pin definitions for the touch interface.
 */

/* Switch 1 Pin Definitions */
#define TOUCH_SW1_PORT          GPIO_PORT_P1  // Port for SW1
#define TOUCH_SW1_PIN           GPIO_PIN1      // Pin for SW1 (GPIO1)

/* X+ Definitions: Connect to GPIO34 (P4.0) */
#define TOUCH_X_PLUS_PORT       GPIO_PORT_P4   // Port for X+
#define TOUCH_X_PLUS_PIN        GPIO_PIN0       // Pin for X+ (GPIO34)
#define TOUCH_X_PLUS_INPUT      ADC_INPUT_A13   // ADC Channel A13
#define TOUCH_X_PLUS_MEMORY     ADC_MEM1        // ADC Memory 1
#define TOUCH_X_PLUS_IFG        ADC_INT1        // ADC Interrupt Flag 1

/* Y+ Definitions: Connect to GPIO35 (P6.1) */
#define TOUCH_Y_PLUS_PORT       GPIO_PORT_P6   // Port for Y+
#define TOUCH_Y_PLUS_PIN        GPIO_PIN1       // Pin for Y+ (GPIO35)
#define TOUCH_Y_PLUS_INPUT      ADC_INPUT_A14   // ADC Channel A14
#define TOUCH_Y_PLUS_MEMORY     ADC_MEM0        // ADC Memory 0
#define TOUCH_Y_PLUS_IFG        ADC_INT0        // ADC Interrupt Flag 0

/* X- Definitions: Connect to GPIO37 (P3.7) */
#define TOUCH_X_MINUS_PORT      GPIO_PORT_P3   // Port for X-
#define TOUCH_X_MINUS_PIN       GPIO_PIN7       // Pin for X- (GPIO37)

/* Y- Definitions: Connect to GPIO36 (P3.6) */
#define TOUCH_Y_MINUS_PORT      GPIO_PORT_P3   // Port for Y-
#define TOUCH_Y_MINUS_PIN       GPIO_PIN6       // Pin for Y- (GPIO36)

/* Threshold for detecting if there is a touch. */
#define TOUCH_THRESHOLD          16000

/* Touch screen calibration values. */
#define TOUCH_X_MINIMUM         (750 << 2)
#define TOUCH_X_MAXIMUM         (3500 << 2)
#define TOUCH_Y_MINIMUM         (1130 << 2)
#define TOUCH_Y_MAXIMUM         (3400 << 2)

#define TOUCH_OVERSAMPLE        8
#define TOUCH_AVERAGE_DIVISOR   3

#define TOUCH_CALIBRATION_KEY    0xA5A5A5A5

/*
 * Radius of calibration circles.
 */
#define TOUCH_CALIBRATION_RADIUS 16

/*
 * Typedef for touch context structure.
 */
typedef struct {
    bool touch;            // Flag indicating if the screen is touched
    uint16_t x;           // X coordinate of the touch
    uint16_t y;           // Y coordinate of the touch
} touch_context;

/*
 * Typedef for touch calibration structure.
 */
typedef struct {
    uint16_t xMin;        // Minimum X calibration value
    uint16_t xMax;        // Maximum X calibration value
    uint16_t yMin;        // Minimum Y calibration value
    uint16_t yMax;        // Maximum Y calibration value
    uint32_t key;         // Key for calibration validation
} touch_calibration;

// Global variable for current touch context
extern touch_context touch_currentTouch;

/* Function prototypes. */
extern void touch_initInterface(void);
extern void touch_updateCurrentTouch(touch_context *data);
extern void touch_calibrate(void);

#endif /* TOUCH_H_ */
