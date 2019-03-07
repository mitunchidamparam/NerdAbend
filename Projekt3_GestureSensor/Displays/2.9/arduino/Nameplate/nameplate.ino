

#include <SPI.h>
#include "epd2in9b.h"
//#include "imagedata.h"
#include "epdpaint.h"

#define COLORED     0
#define UNCOLORED   1

void setup() 
{

  Serial.begin(9600);
  Epd epd;

  if (epd.Init() != 0) 
  {
    Serial.print("e-Paper init failed");
    return;
  }

  /* This clears the SRAM of the e-paper display */
  epd.ClearFrame();

  /**
    * Due to RAM not enough in Arduino UNO, a frame buffer is not allowed.
    * In this case, a smaller image buffer is allocated and you have to 
    * update a partial display several times.
    * 1 byte = 8 pixels, therefore you have to set 8*N pixels at a time.
    */

      
  unsigned char image[1024];
  Paint paint(image, 128, 18);    //width should be the multiple of 8 

  //paint.SetRotate(1);

  paint.SetWidth(128);
  paint.SetHeight(20);


  paint.Clear(COLORED);
  paint.DrawStringAt(0 , 0, "Line1", &Font12, UNCOLORED);
  epd.SetPartialWindowRed(paint.GetImage(), 24, 32, paint.GetWidth() , paint.GetHeight()  + 10 );



  paint.Clear(COLORED);
  paint.DrawStringAt(5, 2, "Line2", &Font12, UNCOLORED);
  epd.SetPartialWindowBlack(paint.GetImage(), 0, 80, paint.GetWidth(), paint.GetHeight());
  
  paint.SetWidth(64);
  paint.SetHeight(64);

  epd.DisplayFrame();
  //epd.Sleep();
  
 /*

  paint.Clear(UNCOLORED);
  paint.DrawRectangle(0, 0, 40, 50, COLORED);
  paint.DrawLine(0, 0, 40, 50, COLORED);
  paint.DrawLine(40, 0, 0, 50, COLORED);
  epd.SetPartialWindowBlack(paint.GetImage(), 8, 120, paint.GetWidth(), paint.GetHeight());
  
  paint.Clear(UNCOLORED);
  paint.DrawCircle(32, 32, 30, COLORED);
  epd.SetPartialWindowBlack(paint.GetImage(), 64, 120, paint.GetWidth(), paint.GetHeight());

  paint.Clear(UNCOLORED);
  paint.DrawFilledRectangle(0, 0, 40, 50, COLORED);
  epd.SetPartialWindowRed(paint.GetImage(), 8, 200, paint.GetWidth(), paint.GetHeight());

  paint.Clear(UNCOLORED);
  paint.DrawFilledCircle(32, 32, 30, COLORED);
  epd.SetPartialWindowRed(paint.GetImage(), 64, 200, paint.GetWidth(), paint.GetHeight());



  



epd.DisplayFrame();
  epd.Sleep(); */
}

void loop() 
{
  // put your main code here, to run repeatedly:

}
