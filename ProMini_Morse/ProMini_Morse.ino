/*
 * More advanced example to send data from serial 
 * 
 * Written By Dakota, alias Fabian Morgenthaler
 * 
 * (c) by FaMo'sIndustries
 * all rigths reserved
 *
 * written at 21.02.2019 by Dakota
 * v2.0
 * 
 * This Code is for the Arduino Pro Mini witch convert the serrial input to morse code
 *  
 * 
 */
#include <Morse_F.h>
#define LED 9
bool b_stat = 0;
unsigned long milisnext;
//unsigned int milisnext;
char c;
Morse_F Morse(LED,250);//Morse_F(LED-Pin,Unit-in-ms)set Output to pin 13  and a unit duration of 250ms

void setup()
{
    pinMode(LED_BUILTIN,OUTPUT);
    digitalWrite(LED_BUILTIN,HIGH);
    Serial.begin(115200);
    Serial.println("entering Setup");
    digitalWrite(LED,HIGH);
    Serial.println("dump mors table");
    Morse.dump();
    Serial.println("Serial link established!");
    digitalWrite(LED,LOW);
    digitalWrite(LED_BUILTIN,LOW);
    Serial.println("leaving Setup");
}

void loop()
{
    while ((c = Serial.read()) > 0) {
        if(c >= 'a')
        {
          c = c-'a'+'A';
        }
        Morse.send(c);
    }
    if(millis() > milisnext)
    {
      milisnext = millis() + 500;
      b_stat = !b_stat;
    }
    digitalWrite(LED_BUILTIN,b_stat);
}
