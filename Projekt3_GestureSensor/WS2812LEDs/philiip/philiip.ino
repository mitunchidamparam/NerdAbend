#include <Adafruit_NeoPixel.h>
 
#define PIN 3

Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);

void setup() 
{
   strip.begin();
  strip.setBrightness(2); //adjust brightness here
  strip.show(); // Initialize all pixels to 'off'


 strip.setPixelColor(10, strip.Color(255,0,0)); strip.show();
delay(1000); 


 strip.setPixelColor(12, strip.Color(255,0,0)); strip.show();
delay(1000);
  Serial.begin(9600);

}

void loop() 
{


  for(int i =  0; i<strip.numPixels(); i++)
  {
    Serial.print(i); Serial.print("-------");
     strip.setPixelColor(i, strip.Color(255,0,0));
     delay(100);
     strip.show();
     Serial.println(i);
  }
  for(int i = 15  ; i>=0 ; i--)
  {
    Serial.println(i);
     strip.setPixelColor(i, strip.Color(0,0,0));
     delay(100);
     strip.show();
  }

    for(int i = 15  ; i>=0 ; i--)
  {
    Serial.println(i);
     strip.setPixelColor(i, strip.Color(0,255,0));
     delay(100);
     strip.show();
  }
    for(int i =  0; i<strip.numPixels(); i++)
  {
    Serial.print(i); Serial.print("-------");
     strip.setPixelColor(i, strip.Color(0,0,255));
     delay(100);
     strip.show();
     Serial.println(i);
  }

  for(int i =  0; i<strip.numPixels(); i++)
  {
    //Serial.print(i); Serial.print("-------");
    if((i%2) == 0)
    {
       //strip.setBrightness(255); //adjust brightness here
           strip.setPixelColor(i, strip.Color(255,0,0));
          delay(100);
          strip.show();
    }
    else
    {
     // strip.setBrightness(2); 
       strip.setPixelColor(i, strip.Color(0,0,255));
       delay(100);
       strip.show();
    }
      
  }


      // Notlicht
     for(int i =  0; i<strip.numPixels(); i++)
     {
       strip.setPixelColor(i, strip.Color(255,255,255));
     }
      strip.setBrightness(255); 
      strip.show();

      delay(2000);
      strip.setBrightness(2); 
  

  

}
