// OLED example from D1_mini_examples
#include <SPI.h>
#include <Wire.h>  // Include Wire if you're using I2C
#include <SFE_MicroOLED.h>  // Include the SFE_MicroOLED library
#include "oled.h"

#define PIN_RESET 255  // Connect RST to pin 9 (req. for SPI and I2C)
#define DC_JUMPER 1  // I2C Addres: 0 - 0x3C, 1 - 0x3D
#define PIN_DC    8  // Connect DC to pin 8 (required for SPI)
#define PIN_CS    10 // Connect CS to pin 10 (required for SPI)
// Also connect pin 13 to SCK and pin 11 to MOSI

//MicroOLED oled(PIN_RESET, PIN_DC, PIN_CS); // SPI declaration
MicroOLED oled(PIN_RESET, DC_JUMPER); // Example I2C declaration

// Center and print a small title
// This function is quick and dirty. Only works for titles one
// line long.
void printTitle(String title, int font)
{
  int middleX = oled.getLCDWidth() / 2;
  int middleY = oled.getLCDHeight() / 2;

  oled.clear(PAGE);
  oled.setFontType(font);
  // Try to set the cursor in the middle of the screen
  oled.setCursor(middleX - (oled.getFontWidth() * (title.length()/2)),
                 middleY - (oled.getFontWidth() / 2));
  // Print the title:
  oled.print(title);
  oled.display();
  //delay(1500);
  //oled.clear(PAGE);
}

// I2C is great, but will result in a much slower update rate. The
// slower framerate may be a worthwhile tradeoff, if you need more
// pins, though.
void setupOLED()
{
  // These three lines of code are all you need to initialize the
  // OLED and print the splash screen.

  // Before you can start using the OLED, call begin() to init
  // all of the pins and configure the OLED.
  oled.begin();
  // clear(ALL) will clear out the OLED's graphic memory.
  // clear(PAGE) will clear the Arduino's display buffer.
  oled.clear(ALL);  // Clear the display's memory (gets rid of artifacts)

  // To actually draw anything on the display, you must call the
  // display() function.
  oled.display();
return;
  //printTitle("Text!", 1);
  // Demonstrate font 0. 5x8 font
  oled.clear(PAGE);     // Clear the screen
  oled.setFontType(0);  // Set font to type 0
  oled.setCursor(0, 0); // Set cursor to top-left
  // There are 255 possible characters in the font 0 type.
  // Lets run through all of them and print them out!
  for (int i=0; i<=255; i++)
  {
    // You can write byte values and they'll be mapped to
    // their ASCII equivalent character.
//    oled.write(i);  // Write a byte out as a character
    Serial.printf("write(%d)\n", i);

    oled.display(); // Draw on the screen
    delay(10);      // Wait 10ms
    // We can only display 60 font 0 characters at a time.
    // Every 60 characters, pause for a moment. Then clear
    // the page and start over.
    if ((i%60 == 0) && (i != 0))
    {
      delay(500);           // Delay 500 ms
      oled.clear(PAGE);     // Clear the page
      oled.setCursor(0, 0); // Set cursor to top-left
    }
  }
  //delay(500);  // Wait 500ms before next example

}
