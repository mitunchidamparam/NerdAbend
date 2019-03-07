/**
 *  @filename   :   epd4in2-demo.ino
 *  @brief      :   4.2inch e-paper display demo
 *  @author     :   Yehui from Waveshare
 *
 *  Copyright (C) Waveshare     August 4 2017
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documnetation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to  whom the Software is
 * furished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <SPI.h>
#include "epd4in2.h"
#include "imagedata.h"
#include "epdpaint.h"
#include <stdint.h>



#define COLORED     0
#define UNCOLORED   1


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  Epd epd;

  if (epd.Init() != 0) {
    Serial.print("e-Paper init failed");
    return;
  }

  /* This clears the SRAM of the e-paper display */
  epd.ClearFrame();
/* This displays the data from the SRAM in e-Paper module */
  epd.DisplayFrame();

delay(20);
Serial.println("Display cleared");

  /**
    * Due to RAM not enough in Arduino UNO, a frame buffer is not allowed.
    * In this case, a smaller image buffer is allocated and you have to 
    * update a partial display several times.
    * 1 byte = 8 pixels, therefore you have to set 8*N pixels at a time.
    */
  unsigned char image[16000];
  Paint paint(image, 400, 300);    //width should be the multiple of 8 
  paint.SetWidth(400);
  paint.SetHeight(300);


  paint.Clear(UNCOLORED);
  
 paint.DrawFilledCircle(32, 32, 8, COLORED);
 epd.SetPartialWindow(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight(),2);
 epd.DisplayFrameQuick();
 epd.WaitUntilIdle();
 
 paint.DrawFilledCircle(16, 16, 8, COLORED);
 epd.SetPartialWindow(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight(),2);
 epd.DisplayFrameQuick();
 epd.WaitUntilIdle();
 
 paint.DrawFilledCircle(40, 32, 18, COLORED);
 epd.SetPartialWindow(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight(),2);
 epd.DisplayFrameQuick();
 epd.WaitUntilIdle();

 paint.DrawFilledCircle(64, 64, 24, COLORED);
 epd.SetPartialWindow(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight(),2);
 epd.DisplayFrameQuick();
 epd.WaitUntilIdle();

 paint.DrawFilledCircle(200, 150, 50, COLORED);
 epd.SetPartialWindow(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight(),2);
 epd.DisplayFrameQuick();
 epd.WaitUntilIdle();
 
  paint.DrawFilledCircle(250, 75, 80, COLORED);
 epd.SetPartialWindow(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight(),2);
 epd.DisplayFrameQuick();
epd.WaitUntilIdle();
 
 paint.DrawFilledCircle(100, 250, 80, COLORED);
 epd.SetPartialWindow(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight(),2);
 epd.DisplayFrameQuick();
epd.WaitUntilIdle();
 
 paint.DrawFilledCircle(100, 250, 50, UNCOLORED);
 epd.SetPartialWindow(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight(),2);
 epd.DisplayFrameQuick();
 epd.WaitUntilIdle();
 paint.DrawFilledCircle(250, 75, 50, UNCOLORED);
 epd.SetPartialWindow(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight(),2);
 epd.DisplayFrameQuick();
 epd.WaitUntilIdle();

 paint.DrawFilledCircle(200, 150, 20, UNCOLORED);
 epd.SetPartialWindow(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight(),2);
 epd.DisplayFrameQuick();
 epd.WaitUntilIdle();
delay(3000);

 paint.Clear(UNCOLORED);
 epd.DisplayFrame();


float phase = 0.0;
float twopi = 3.14159 * 2;
elapsedMillis msec = 0;

static char outstr[15];
while(phase < 8)
{
 paint.Clear(UNCOLORED);
 paint.DrawStringAt((int)30+phase*10, 30, dtostrf(msec,4,0, outstr), &Font24, COLORED);
 paint.DrawFilledCircle(200+80*sin(phase), 150+80*cos(phase), 20, COLORED);
 epd.SetPartialWindow(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight(),2);
  epd.DisplayFrameQuick();
  epd.WaitUntilIdle();
phase=phase+0.2;
}

for(int i = 0; i<2;i++)
{
  paint.Clear(UNCOLORED);
epd.SetPartialWindow(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight(),2);
  epd.DisplayFrame();
  delay(10);
}


  /* This displays an image */
  epd.DisplayFrame(IMAGE_BUTTERFLY);
 delay(4000);
epd.DisplayFrame(IMAGE_ASCIENCE);
delay(4000);
 epd.DisplayFrame(IMAGE_PLAYBUTTON);
  /* Deep sleep */
  epd.Sleep();
}

void loop() {
  // put your main code here, to run repeatedly:

}

