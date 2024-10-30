#include "DSP28x_Project.h"  // Device header file
#include "grlib.h"           // Graphics library header
#include "button.h"          // Button header
#include "imageButton.h"     // Image button header
#include "radioButton.h"     // Radio button header
#include "checkbox.h"        // Checkbox header
#include "LcdDriver/kitronix320x240x16_ssd2119_spi.h" // LCD driver
#include "images/images.h"   // Image resources
#include "touch_P401R.h"     // Touch screen interface
#include "F2806x_Sysctrl.h"

// Touch screen context
touch_context g_sTouchContext;
Graphics_ImageButton primitiveButton;
Graphics_ImageButton imageButton;
Graphics_Button yesButton;
Graphics_Button noButton;

// Graphic library context
Graphics_Context g_sContext;

// Flag to know if a demo was run
bool g_ranDemo = false;


void Delay(uint16_t msec);
void boardInit(void);
void clockInit(void);
void initializeDemoButtons(void);
void drawMainMenu(void);
void runPrimitivesDemo(void);
void runImagesDemo(void);
void drawRestarDemo(void);

// Function prototypes for initialization





void main(void)
{
    // Initialize system
    watchdogInit();          // Disable watchdog
    clockInit();             // Initialize clocks
    boardInit();             // Initialize board
    initializeDemoButtons();  // Setup demo buttons

    // Globally enable interrupts
    __enable_interrupt();

    // LCD setup using Graphics Library API calls
    Kitronix320x240x16_SSD2119Init();  // Initialize LCD
    Graphics_initContext(&g_sContext, &g_sKitronix320x240x16_SSD2119); // Initialize graphics context
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK); // Set background color
    Graphics_setFont(&g_sContext, &g_sFontCmss20b); // Set font
    Graphics_clearDisplay(&g_sContext); // Clear display

    touch_initInterface(); // Initialize touch interface

    drawMainMenu(); // Draw the main menu

    // Main loop to detect touch
    while (1)
    {
        touch_updateCurrentTouch(&g_sTouchContext); // Update touch context

        if (g_sTouchContext.touch) // Check if the screen is touched
        {
            // Check if the primitive button is pressed
            if (Graphics_isImageButtonSelected(&primitiveButton, g_sTouchContext.x, g_sTouchContext.y))
            {
                Graphics_drawSelectedImageButton(&g_sContext, &primitiveButton);
                runPrimitivesDemo(); // Run demo for primitives
            }
            // Check if the image button is pressed
            else if (Graphics_isImageButtonSelected(&imageButton, g_sTouchContext.x, g_sTouchContext.y))
            {
                Graphics_drawSelectedImageButton(&g_sContext, &imageButton);
                runImagesDemo(); // Run demo for images
            }

            // If a demo was run, redraw the main menu
            if (g_ranDemo)
            {
                g_ranDemo = false; // Reset demo flag
                drawMainMenu(); // Redraw main menu
            }
        }
    }
}

// Function implementations for demo buttons and drawing menus...
/*
void initializeDemoButtons(void)
{
    // Initialize primitive button
    primitiveButton.xPosition = 20;
    primitiveButton.yPosition = 50;
    primitiveButton.borderWidth = 5;
    primitiveButton.selected = false;
    primitiveButton.imageWidth = Primitives_Button4BPP_UNCOMP.xSize;
    primitiveButton.imageHeight = Primitives_Button4BPP_UNCOMP.ySize;
    primitiveButton.borderColor = GRAPHICS_COLOR_WHITE;
    primitiveButton.selectedColor = GRAPHICS_COLOR_RED;
    primitiveButton.image = &Primitives_Button4BPP_UNCOMP;

    // Initialize image button
    imageButton.xPosition = 180;
    imageButton.yPosition = 50;
    imageButton.borderWidth = 5;
    imageButton.selected = false;
    imageButton.imageWidth = Images_Button4BPP_UNCOMP.xSize;
    imageButton.imageHeight = Images_Button4BPP_UNCOMP.ySize;
    imageButton.borderColor = GRAPHICS_COLOR_WHITE;
    imageButton.selectedColor = GRAPHICS_COLOR_RED;
    imageButton.image = &Images_Button4BPP_UNCOMP;

    // Initialize Yes button
    yesButton.xMin = 80;
    yesButton.xMax = 150;
    yesButton.yMin = 80;
    yesButton.yMax = 120;
    yesButton.borderWidth = 1;
    yesButton.selected = false;
    yesButton.fillColor = GRAPHICS_COLOR_RED;
    yesButton.borderColor = GRAPHICS_COLOR_RED;
    yesButton.selectedColor = GRAPHICS_COLOR_BLACK;
    yesButton.textColor = GRAPHICS_COLOR_BLACK;
    yesButton.selectedTextColor = GRAPHICS_COLOR_RED;
    yesButton.textXPos = 100;
    yesButton.textYPos = 90;
    yesButton.text = "YES";
    yesButton.font = &g_sFontCm18;

    // Initialize No button
    noButton.xMin = 180;
    noButton.xMax = 250;
    noButton.yMin = 80;
    noButton.yMax = 120;
    noButton.borderWidth = 1;
    noButton.selected = false;
    noButton.fillColor = GRAPHICS_COLOR_RED;
    noButton.borderColor = GRAPHICS_COLOR_RED;
    noButton.selectedColor = GRAPHICS_COLOR_BLACK;
    noButton.textColor = GRAPHICS_COLOR_BLACK;
    noButton.selectedTextColor = GRAPHICS_COLOR_RED;
    noButton.textXPos = 200;
    noButton.textYPos = 90;
    noButton.text = "NO";
    noButton.font = &g_sFontCm18;
}
*/
void drawMainMenu(void)
{
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_RED);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_clearDisplay(&g_sContext);
    Graphics_drawStringCentered(&g_sContext, "MSP Graphics Library Demo",
                                AUTO_STRING_LENGTH,
                                159,
                                15,
                                TRANSPARENT_TEXT);

    // Draw TI banner at the bottom of screen
    Graphics_drawImage(&g_sContext,
                       &TI_platform_bar_red4BPP_UNCOMP,
                       0,
                       Graphics_getDisplayHeight(&g_sContext) - TI_platform_bar_red4BPP_UNCOMP.ySize);

    // Draw buttons
    Graphics_drawImageButton(&g_sContext, &primitiveButton);
    Graphics_drawImageButton(&g_sContext, &imageButton);
}
