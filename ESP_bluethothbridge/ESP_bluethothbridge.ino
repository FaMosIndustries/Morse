/*
 * Written By Dakota, alias Fabian Morgenthaler
 * 
 * (c) by FaMo'sIndustries
 * all rigths reserved
 *
 * written at 12.03.2019 by Dakota
 * v2.0
 * 
 * This Code is for the ESP32 Bord witch comunicate with the Pro Mini over Serial
 */
 
//BluetoothSerial
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

//OLED Display
#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`

//SSD1306  display(I2C-Adress,Pin_SDA,Pin_SCL); //5,4  21,22 4,15
SSD1306  display(0x3c, 21, 22); //SDA,SCL  5,4  21,22 4,15
// SH1106 display(0x3c, D3, D5)

// Fonts for OLED Display
// create more fonts at http://oleddisplay.squix.ch/

u_long next;
u_long n_LED;

bool b_stat =0;
char c;
String mes;
String Blue_Name = "ESP32_Morse";

void setup() {
  Serial.begin(115200);
  SerialBT.begin(Blue_Name); //Bluetooth device name
  // Serial.println("The device started, now you can pair it with bluetooth!");
  // Initialising the UI will init the display too.
  display.init();
  display.flipScreenVertically();
  pinMode(LED_BUILTIN,OUTPUT);
}

void drawProgressBarDemo(int progress) {
  // draw the progress bar
  display.drawProgressBar(0, 32, 120, 10, progress);
  // draw the percentage as String
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 15, String(progress) + "%");
}

void drawMainScrean() {
    display.clear();
    display.setFont(DejaVu_Sans_8);
    display.setTextAlignment(TEXT_ALIGN_RIGHT);
    display.drawString(80, 8, String(millis()));
    display.drawString(120, 0,  Blue_Name);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.drawString(0, 8, "This is:");
    display.drawString(95, 7, "by FMI");
    display.drawString(0, 0, "conect to:");
    display.setFont(ArialMT_Plain_24);
    display.drawString(20, 20, "MORSE");
    display.setFont(Yellowtail_Regular_24);
    display.drawString(30, 35, "Aurora");   
    display.drawHorizontalLine(0, 16, 128);
    display.drawHorizontalLine(0, 63, 128);
    // Draw a line horizontally
    display.drawVerticalLine(0, 16, 48); 
    display.drawVerticalLine(127, 16, 48);
    display.display();
}

void drawSendScrean(String text) {
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(DejaVu_Sans_40);
    //display.setFont(Yellowtail_Regular_62);
    display.drawString(0, 16, text);
    display.display();
    next = millis() + 3000;
}

void loop() {
  if (Serial.available()) {
      mes = Serial.readStringUntil('\n');
    // SerrialBT.Print is not suportet so ... we need to do it other wise
    // Length (with one extra character for the null terminator)
    int str_len = mes.length() + 1; 
    // Prepare the character array (the buffer) 
    char char_array[str_len];
    // Copy it over 
    mes.toCharArray(char_array, str_len);
    for(size_t ind = 0; ind < str_len; ind++)
    {
        SerialBT.write(char_array[ind]);
    } 
    drawSendScrean(mes);
  }
  if (SerialBT.available()) {
    c = SerialBT.read();
    Serial.write(c);
  }
  if(millis()>next)drawMainScrean();
  if(millis()>n_LED)
  {
    b_stat =! b_stat;
    n_LED = millis() + 500;
    digitalWrite(LED_BUILTIN,b_stat);
  }
}
