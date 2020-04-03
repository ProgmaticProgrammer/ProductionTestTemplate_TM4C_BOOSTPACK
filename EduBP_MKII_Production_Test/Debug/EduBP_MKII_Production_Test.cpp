#include "Energia.h"

#line 1 "C:/Users/Owner/workspace_v9/EduBP_MKII_Production_Test/EduBP_MKII_Production_Test.ino"
#include "pitches.h"
#include <itoa.h>
#include <Wire.h>
#include <Adafruit_TMP006.h>
#include "OPT3001.h"


#define USING_TIVA_C_LAUNCHPAD


#if defined(WIRING) 
#include "Wiring.h"
#elif defined(MAPLE_IDE) 
#include "WProgram.h"
#elif defined(MPIDE) 
#include "WProgram.h"
#elif defined(DIGISPARK) 
#include "Arduino.h"
#elif defined(ENERGIA) 
#include "Energia.h"
#elif defined(CORE_TEENSY) 
#include "WProgram.h"
#elif defined(ARDUINO) && (ARDUINO >= 100) 
#include "Arduino.h"
#elif defined(ARDUINO) && (ARDUINO < 100) 
#include "WProgram.h"
#else 
#error Platform not defined
#endif


#include "SPI.h"


#define HX8353E 

#include "Screen_HX8353E.h"
void protocolSquare(uint16_t pixels);
void protocolText();
void setup();
char *ftoa(char *a, float f, int precision);
void loop();

#line 38
Screen_HX8353E myScreen;









void protocolSquare(uint16_t pixels)
{
    if ((pixels < myScreen.screenSizeX()) && (pixels < myScreen.screenSizeY())
            && (pixels > 48))
    {

        myScreen.setOrientation(0);
        myScreen.setPenSolid(false);

        uint16_t x100 = (myScreen.screenSizeX() - pixels) / 2;
        uint16_t y100 = (myScreen.screenSizeY() - pixels) / 2;

        myScreen.dRectangle(x100 - 1, y100 - 1, pixels + 2, pixels + 2,
                            whiteColour);
        myScreen.setPenSolid(true);
        uint32_t chrono = millis();
        myScreen.dRectangle(x100, y100, pixels, pixels, grayColour);
        chrono = millis() - chrono;

        myScreen.setFontSize(myScreen.fontMax());
        myScreen.gText(x100 + 2, y100 + 2, "(" + i32toa(pixels) + ")");
        myScreen.gText(x100 + 2, y100 + pixels - myScreen.fontSizeY() - 2,
                       i32toa(chrono) + " ms");

        Serial.print("Square(");
        Serial.print(pixels, DEC);
        Serial.print(")\t");
        Serial.println(chrono, DEC);
    }
}






void protocolCopyPaste(uint8_t orientation = 1)
{
    uint32_t chrono;
    myScreen.clear();
    myScreen.setOrientation(orientation);

    
    chrono = millis();
    for (uint8_t i = 0; i < 64; i++)
    {
        for (uint8_t j = 0; j < 64; j++)
        {
            myScreen.point(
                    i,
                    j,
                    myScreen.calculateColour(4 * i, 4 * j,
                                             254 - 2 * i - 2 * j));
        }
    }

    myScreen.setPenSolid(false);
    myScreen.rectangle(1, 1, 62, 62, blackColour);
    myScreen.line(0, 0, 63, 63, whiteColour);
    myScreen.line(32, 0, 63, 63, whiteColour);
    myScreen.line(0, 32, 63, 63, whiteColour);
    myScreen.dRectangle(0, 0, 64, 64, whiteColour);
    chrono = millis() - chrono;

    myScreen.setFontSize(0);
    myScreen.gText(0, 66, "0: Original");
    myScreen.setFontSize(1);
    myScreen.gText(0, 76, i32toa(chrono) + " ms");

    Serial.print("Original(=");
    Serial.print(orientation, DEC);
    Serial.print(")\t");
    Serial.println(chrono, DEC);

    
    chrono = millis();
    for (uint16_t i = 0; i < 64; i++)
    {
        for (uint16_t j = 0; j < 64; j++)
        {
            myScreen.point(myScreen.screenSizeX() / 2 + i, j,
                           myScreen.readPixel(i, j));
        }
    }
    chrono = millis() - chrono;
    myScreen.setFontSize(0);
    myScreen.gText(myScreen.screenSizeX() / 2, 66, "1. point readPixel");
    myScreen.setFontSize(1);
    myScreen.gText(myScreen.screenSizeX() / 2, 76, i32toa(chrono) + " ms");

    Serial.print("point(readPixel())\t");
    Serial.println(chrono, DEC);

    
    chrono = millis();
    myScreen.copyPaste(0, 0, 0, myScreen.screenSizeY() / 2, 64, 64);
    chrono = millis() - chrono;

    myScreen.setFontSize(0);
    myScreen.gText(0, myScreen.screenSizeY() / 2 + 66, "2. copyPaste");
    myScreen.setFontSize(1);
    myScreen.gText(0, myScreen.screenSizeY() / 2 + 76, i32toa(chrono) + " ms");

    Serial.print("copyPaste()\t");
    Serial.println(chrono, DEC);

    
    if (myScreen.isStorage())
    {
        uint32_t address;

        chrono = millis();
        address = 100;
        myScreen.copyArea(0, 0, 64, 64, address);
        address = 100;
        myScreen.pasteArea(myScreen.screenSizeX() / 2,
                           myScreen.screenSizeY() / 2, 64, 64, address);
        chrono = millis() - chrono;

        myScreen.setFontSize(0);
        myScreen.gText(myScreen.screenSizeX() / 2,
                       myScreen.screenSizeY() / 2 + 66, "3. copy-paste SRAM");
        myScreen.setFontSize(1);
        myScreen.gText(myScreen.screenSizeX() / 2,
                       myScreen.screenSizeY() / 2 + 76, i32toa(chrono) + " ms");

        Serial.print("copyArea()+pasteArea() SRAM\t");
        Serial.println(chrono, DEC);
    }
}





void protocolText()
{
    uint32_t chrono1, chrono2;
    uint16_t colour;
    uint8_t k = 0;

    
    myScreen.clear(grayColour);
    myScreen.setFontSolid(true);
    chrono1 = millis();
    for (uint8_t j = 0; j < 10; j++)
    {
        for (uint8_t i = 0; i < 4; i++)
        {
            if (k == 1)
                colour = redColour;
            else if (k == 2)
                colour = yellowColour;
            else if (k == 3)
                colour = greenColour;
            else if (k == 4)
                colour = cyanColour;
            else if (k == 5)
                colour = blueColour;
            else
                colour = violetColour;
            k++;
            k %= 7;

            myScreen.setPenSolid(false);
            myScreen.dRectangle(0, 0, myScreen.screenSizeX(),
                                myScreen.screenSizeY(), colour);

            myScreen.setOrientation(i);
            myScreen.setFontSize(0);
            myScreen.gText(4, 4, "font 0 on " + String(i), colour);
            myScreen.setFontSize(1);
            myScreen.gText(4, 14, "font 1 on " + String(i), colour);
            myScreen.setFontSize(2);
            myScreen.gText(4, 34, "font 2 on " + String(i), colour);
        }
    }
    chrono1 = millis() - chrono1;
    Serial.print("10xFontSolid(true)\t");
    Serial.println(chrono1, DEC);

    
    myScreen.clear(grayColour);
    myScreen.setFontSolid(false);
    chrono2 = millis();

    for (uint8_t j = 0; j < 10; j++)
    {
        for (uint8_t i = 0; i < 4; i++)
        {
            if (k == 1)
                colour = redColour;
            else if (k == 2)
                colour = yellowColour;
            else if (k == 3)
                colour = greenColour;
            else if (k == 4)
                colour = cyanColour;
            else if (k == 5)
                colour = blueColour;
            else
                colour = violetColour;
            k++;
            k %= 7;

            myScreen.setPenSolid(false);
            myScreen.dRectangle(0, 0, myScreen.screenSizeX(),
                                myScreen.screenSizeY(), colour);

            myScreen.setOrientation(i);
            myScreen.setFontSize(0);
            myScreen.gText(4, 4, "font 0 on " + String(i), colour);
            myScreen.setFontSize(1);
            myScreen.gText(4, 14, "font 1 on " + String(i), colour);
            myScreen.setFontSize(2);
            myScreen.gText(4, 34, "font 2 on " + String(i), colour);
        }
    }

    chrono2 = millis() - chrono2;
    Serial.print("10xFontSolid(false)\t");
    Serial.println(chrono2, DEC);

    Serial.print("Ratio%\t");
    Serial.println((uint32_t) ((uint64_t) (chrono1 * 100) / chrono2), DEC);

}

const int JOY_X = 2;
const int JOY_Y = 26;
const int SEL = 5;


const int MIC = 6;


const int ACC_X = 23;
const int ACC_Y = 24;
const int ACC_Z = 25;


const int SW1 = 33;
const int SW2 = 32;


const int BUZZ = 40;


const int RGB_RED = 39;
const int RGB_GRN = 38;
const int RGB_BLU = 37;


float tempReading = 0;
Adafruit_TMP006 tmp006;


opt3001 opt3001;

unsigned long readings = 0;


#define NOTE_C4_1 260
int melody[] = {
NOTE_C4_1,
                 NOTE_C4, NOTE_D4, NOTE_C4, NOTE_F4, NOTE_E4,
                 NOTE_C4_1,
                 NOTE_C4, NOTE_D4, NOTE_C4, NOTE_G4, NOTE_F4,
                 NOTE_C4_1,
                 NOTE_C4, NOTE_C5, NOTE_A4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_D4,
                 NOTE_AS4,
                 NOTE_AS4, NOTE_A4, NOTE_F4, NOTE_G4, NOTE_F4 };


int noteDurations[] = { 4, 4, 2, 2, 2, 1, 4, 4, 2, 2, 2, 1, 4, 4, 2, 2, 4, 4, 2,
                        1, 4, 4, 2, 2, 2, 1 };




void setup()
{
    
    Serial.begin(115200);
    delay(300);
    
    pinMode(SEL, INPUT);
    
    pinMode(SW1, INPUT);
    pinMode(SW2, INPUT);
    
    pinMode(BUZZ, OUTPUT);

    Serial.println(
            "Welcome to the Educational BoosterPack MKII Production Test:");

    tmp006.begin(TMP006_CFG_8SAMPLE); 
    opt3001.begin();
}

char *ftoa(char *a, float f, int precision)
{
    long p[] = { 0, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000 };

    char *ret = a;
    long heiltal = (long) f;
    itoa(heiltal, a, 10);
    while (*a != '\0')
        a++;
    *a++ = '.';
    long desimal = abs((long) ((f - heiltal) * p[precision]));
    itoa(desimal, a, 10);
    return ret;
}

void loop()
{
    int16_t i;
    uint16_t colour;

    Serial.println("*** LCD_screen test ****");
    Serial.println("(All times in ms)");

    myScreen.begin();
    Serial.println(myScreen.WhoAmI());
    Serial.print(myScreen.screenSizeX(), DEC);
    Serial.print("x");
    Serial.println(myScreen.screenSizeY(), DEC);

    myScreen.setFontSize(myScreen.fontMax());
    myScreen.clear(darkGrayColour);

    protocolSquare(300);
    protocolSquare(200);
    protocolSquare(100);
    protocolSquare(50);
    delay(2000);

    protocolText();
    delay(2000);

    if (myScreen.isReadable())
    {
        protocolCopyPaste(1);
        delay(2000);
    }

    myScreen.clear();
    Serial.println("-END OF SCREEN TEST--");
    Serial.println();

    myScreen.clear(grayColour);
    myScreen.setFontSolid(false);
    colour = redColour;

    myScreen.setOrientation(i);
    myScreen.setFontSize();

    
    myScreen.gText(0, 0, "  JoyStick Test", blueColour);

    myScreen.gText(0, 15, "Right", colour);
    int val = analogRead(JOY_X);
    while (val < 4000)
        val = analogRead(JOY_X);
    myScreen.gText(50, 15, " > Passed!", greenColour);

    myScreen.gText(0, 30, "Left", colour);
    while (analogRead(JOY_X) > 1000)
        ;
    myScreen.gText(50, 30, " > Passed!", greenColour);

    myScreen.gText(0, 45, "Up", colour);
    while (analogRead(JOY_Y) < 3000)
        ;
    myScreen.gText(50, 45, " > Passed!", greenColour);

    myScreen.gText(0, 60, "Down", colour);
    while (analogRead(JOY_Y) > 1000)
        ;
    myScreen.gText(50, 60, " > Passed!", greenColour);

    myScreen.gText(0, 75, "Center", colour);
    while (digitalRead(SEL) == 1)
        ;
    myScreen.gText(50, 75, " > Passed!", greenColour);

    delay(400);

    
    myScreen.clear(grayColour);
    myScreen.gText(0, 0, "   Tap  Mic", blueColour);

    while (analogRead(MIC) > 100)
        ;
    myScreen.gText(50, 10, " Passed!", greenColour);

    myScreen.gText(0, 20, "  Button Tests", blueColour);
    

    myScreen.gText(0, 40, "Press S1", colour);
    while (digitalRead(SW1) == 1)
        ;
    myScreen.gText(50, 40, " > Passed!", greenColour);

    
    myScreen.gText(0, 55, "Press S2", colour);
    while (digitalRead(SW2) == 1)
        ;
    myScreen.gText(50, 55, " > Passed!", greenColour);

    myScreen.gText(0, 70, "  Buzzer Test", blueColour);
    

    for (int thisNote = 0; thisNote < 26; thisNote++)
    {
        
        
        
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(BUZZ, melody[thisNote], noteDuration);
        int pauseBetweenNotes = noteDuration + 50;      
        delay(pauseBetweenNotes >> 2);
        noTone(BUZZ);                
    }
    myScreen.gText(0, 85, "S1&S2 if sound", colour);
    while (digitalRead(SW2) == 1 || digitalRead(SW1) == 1)
        ;
    myScreen.gText(0, 100, " PASSED!!", greenColour);
    delay(400);

    
    
    myScreen.clear(grayColour);
    myScreen.gText(0, 0, " Accelerometer", blueColour);

    myScreen.gText(0, 15, "Flat", colour);

    while (analogRead(ACC_X) < 1900 || analogRead(ACC_X) > 2100
            || analogRead(ACC_Y) > 2100 || analogRead(ACC_Y) < 1900
            || analogRead(ACC_Z) < 2700)
        ;
    myScreen.gText(50, 15, " > Passed!", greenColour);

    myScreen.gText(0, 30, "Left", colour);
    while (analogRead(ACC_X) > 1350 || analogRead(ACC_Y) > 2100
            || analogRead(ACC_Y) < 1900 || analogRead(ACC_Z) > 2100
            || analogRead(ACC_Z) < 1900)
        ;
    myScreen.gText(50, 30, " > Passed!", greenColour);

    myScreen.gText(0, 45, "Right", colour);
    while (analogRead(ACC_X) < 2650 || analogRead(ACC_Y) > 2100
            || analogRead(ACC_Y) < 1900 || analogRead(ACC_Z) > 2100
            || analogRead(ACC_Z) < 1900)
        ;
    myScreen.gText(50, 45, " > Passed!", greenColour);

    myScreen.gText(0, 60, "Away", colour);
    while (analogRead(ACC_X) < 1900 || analogRead(ACC_X) > 2000
            || analogRead(ACC_Y) < 2600 || analogRead(ACC_Z) < 1900
            || analogRead(ACC_Z) > 2100)
        ;
    myScreen.gText(50, 60, " > Passed!", greenColour);

    myScreen.gText(0, 75, "To you", colour);
    while (analogRead(ACC_X) < 1900 || analogRead(ACC_X) > 2100
            || analogRead(ACC_Y) > 1450 || analogRead(ACC_Z) < 1900
            || analogRead(ACC_Z) > 2100)
        ;
    myScreen.gText(50, 75, " > Passed!", greenColour);

    myScreen.gText(0, 90, "Upside Down", colour);
    while (analogRead(ACC_X) < 1900 || analogRead(ACC_X) > 2100
            || analogRead(ACC_Y) > 2100 || analogRead(ACC_Y) < 1900
            || analogRead(ACC_Z) > 1300)
        ;
    myScreen.gText(0, 105, "   PASSED!!", greenColour);
    delay(400);
    myScreen.clear(grayColour);
    
    float temp = tmp006.readObjTempC();
    char tempText[10];
    char ii;
    for (ii = 0; ii < 10; ii++)
        tempText[ii] = 0;
    ftoa((char *)tempText, temp, 4);
    myScreen.gText(0, 0, "   TMP006 Test", blueColour);
    myScreen.gText(0, 20, (char*) tempText, colour);
    myScreen.gText(60, 20, "*C", colour);

    
    
    myScreen.gText(0, 0, "   OPT3001 Test", blueColour);

    Serial.println("Cover the light sensor to test the OPT3001.");
    while(opt3001.readResult() > 30);
    Serial.println("Shine flashlight onto the light sensor ");
    while(opt3001.readResult() < 1000);

    Serial.println("OPT3001 testing successful!");

    
    myScreen.gText(0, 40, "   RGB LED Test", blueColour);

    i = 0;
    int brightness = 0;
    int fadeAmount = 5;

    for (brightness = 0; brightness < 255; brightness += fadeAmount)
    {
        analogWrite(RGB_RED, brightness);
        
        delay(10);
    }
    for (brightness = 255; brightness >= 0; brightness -= fadeAmount)
    {
        analogWrite(RGB_RED, brightness);
        
        delay(10);
    }
    for (brightness = 0; brightness < 255; brightness += fadeAmount)
    {
        analogWrite(RGB_GRN, brightness);
        
        delay(10);
    }
    for (brightness = 255; brightness >= 0; brightness -= fadeAmount)
    {
        analogWrite(RGB_GRN, brightness);
        
        delay(10);
    }
    for (brightness = 0; brightness < 255; brightness += fadeAmount)
    {
        analogWrite(RGB_BLU, brightness);
        
        delay(10);
    }
    for (brightness = 255; brightness >= 0; brightness -= fadeAmount)
    {
        analogWrite(RGB_BLU, brightness);
        
        delay(10);
    }
    myScreen.gText(0, 70, "S1 to Finish", colour);
    while (digitalRead(SW1) == 1)
        ;
    myScreen.gText(0, 90, "ALL TESTS PASSED", greenColour);

    while (1)
        ;
}



