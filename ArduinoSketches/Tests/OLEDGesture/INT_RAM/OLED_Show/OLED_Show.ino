/***********************************************************************************************************************
  | file       : OLED_Show
  | version    : V1.0
  | date       : 2017-12-12
  | function  :
  Brush screen use note: if using the internal RAM, RAM is small at the same time, in OLED_Driver.h
  to change the XByte and YByte value, these remarks related BYTE corresponding to the number
  of pixels, the corresponding changes.
  It is important to note that the X and Y values of the display function in the GUI should not
  exceed the display area specified above, otherwise the screen will be displayed.
  For the controller's RAM enough, it is recommended that the RAM be set to the maximum pixel
  of the screen to correspond, so that the control function is easy to use.
  For the controller's RAM, it is recommended to use external RAM, which is convenient for
  the controller, for example, this routine has 23K256 as the external RAM control.
***********************************************************************************************************************/
#include "OLED_Driver.h"
#include "OLED_GUI.h"
#include "DEV_Config.h"
#include "Show_Lib.h"
#include "Debug.h"

#include <Wire.h>
#include <SparkFun_APDS9960.h>


#define APDS9960_INT    2 // Needs to be an interrupt pin
#define PowerPin 3

SparkFun_APDS9960 apds = SparkFun_APDS9960();
int isr_flag = 0;

extern OLED_DIS sOLED_DIS;
void setup()
{
   // Serial.begin(9600);
  System_Init();

  pinMode(PowerPin, OUTPUT);
  digitalWrite(PowerPin, HIGH);

  pinMode(APDS9960_INT, INPUT);

  attachInterrupt(0, interruptRoutine, FALLING);

  if ( apds.init() ) 
  {
    Serial.println(F("APDS-9960 initialization complete"));
  } else 
  {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }
  
  // Start running the APDS-9960 gesture sensor engine
  if ( apds.enableGestureSensor(true) ) {
    Serial.println(F("Gesture sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during gesture sensor init!"));
  }


  // OLED
  Serial.println("OLED Init ");
  OLED_SCAN_DIR OLED_ScanDir = SCAN_DIR_DFT;
  OLED_Init( OLED_ScanDir );

  Serial.println("OLED_Show ");
  //GUI_Show();
  OLED_ClearBuf();
  OLED_ClearScreen(OLED_BACKGROUND);

  GUI_DrawLine(0, 8, sOLED_DIS.OLED_Dis_Column - 1, 8, WHITE, LINE_SOLID , DOT_PIXEL_DFT);
  OLED_DisPage(0, 0);
  OLED_DisPage(0, 7);
  OLED_ClearBuf();

  GUI_DisString_EN(33, 2, "Schaefer", &Font12, FONT_BACKGROUND, WHITE);
  OLED_DisPage(0, 1);
  OLED_ClearBuf();


   /**
  GUI_Disbitmap(0  , 2, Signal816  , 16, 8);
  GUI_Disbitmap(24 , 2, Bluetooth88, 8 , 8);
  GUI_Disbitmap(40 , 2, Msg816     , 16, 8);
  GUI_Disbitmap(64 , 2, GPRS88     , 8 , 8);
  GUI_Disbitmap(90 , 2, Alarm88    , 8 , 8);
  GUI_Disbitmap(112, 2, Bat816     , 16, 8);
  OLED_Display(0, 52, 128, 52 + 16);
  OLED_ClearBuf();
 */
  // GUI_DisString_EN(0 , 0, "MUSIC", &Font12, FONT_BACKGROUND, WHITE);
  GUI_DisString_EN(30, 0, "Nerdabend" , &Font12, FONT_BACKGROUND, WHITE);
  //GUI_DisString_EN(90, 0, "PHONE", &Font12, FONT_BACKGROUND, WHITE);
  OLED_Display(0, 96, 128, 96 + 16);
  OLED_ClearBuf();


            GUI_DisString_EN(30, 2, "UP", &Font12, FONT_BACKGROUND, WHITE);
           OLED_DisPage(0, 2);
             OLED_ClearBuf();

               Serial.println("Setup done");
}

void loop()
{
  // Uhr -----------------------------------------------------------
//  uint8_t sec = 0;
//  DEV_TIME sDev_time;
//  sDev_time.Hour = 12;
//  sDev_time.Min = 34;
//  sDev_time.Sec = 56;
//  Serial.print("Show time\r\n");
//  for (;;) 
//  {
//    sec++;
//    sDev_time.Sec = sec;
//    if (sec == 60) {
//      sDev_time.Min = sDev_time.Min + 1;
//      sec = 0;
//      if (sDev_time.Min == 60) {
//        sDev_time.Hour =  sDev_time.Hour + 1;
//        sDev_time.Min = 0;
//        if (sDev_time.Hour == 24) {
//          sDev_time.Hour = 0;
//          sDev_time.Min = 0;
//          sDev_time.Sec = 0;
//        }
//      }
//    }
//    OLED_ClearBuf();
//    GUI_Showtime(28, 0, 100, 16, &sDev_time, WHITE);
//    OLED_Display(0, 72, 128, 72 + 16);
//    Driver_Delay_ms(1000);//Analog clock 1s
//  }


  // Gesure Sensor

 if( isr_flag == 1 ) 
   {
  detachInterrupt(0);
   handleGesture();
  isr_flag = 0;
 attachInterrupt(0, interruptRoutine, FALLING);
 }

  //GUI_DisString_EN(30, 2, "Elevator", &Font12, FONT_BACKGROUND, WHITE);
  //OLED_DisPage(0, 2);
  //OLED_ClearBuf();
  
}


void interruptRoutine()
{
  isr_flag = 1;
}

void handleGesture() 
{
    if ( apds.isGestureAvailable() ) {
    switch ( apds.readGesture() ) {
      case DIR_UP:
        Serial.println("UP");
//          GUI_DisString_EN(30, 2, "UP", &Font12, FONT_BACKGROUND, WHITE);
//           OLED_DisPage(0, 2);
//             OLED_ClearBuf();
        break;
      case DIR_DOWN:
        Serial.println("DOWN");
//                  GUI_DisString_EN(30, 2, "DOWN", &Font12, FONT_BACKGROUND, WHITE);
//           OLED_DisPage(0, 2);
//             OLED_ClearBuf();
        break;
      case DIR_LEFT:
        Serial.println("LEFT");
//                  GUI_DisString_EN(30, 2, "LEF", &Font12, FONT_BACKGROUND, WHITE);
//           OLED_DisPage(0, 2);
//             OLED_ClearBuf();
        break;
      case DIR_RIGHT:
        Serial.println("RIGHT");
//                  GUI_DisString_EN(30, 2, "RIGHT", &Font12, FONT_BACKGROUND, WHITE);
//           OLED_DisPage(0, 2);
//             OLED_ClearBuf();
        break;
      case DIR_NEAR:
        Serial.println("NEAR");
        break;
      case DIR_FAR:
        Serial.println("FAR");
        break;
      default:
        Serial.println("NONE");
    }
  }
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
