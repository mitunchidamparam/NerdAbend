
bool REG_Ein = false; // Regler ein
int SW = 0; // Sollwert
int IW = 0; // Istwert
int SH = 0; // Schalthysterese
bool STG = false; // Stellgr��e


int ER = 0; // Regelabweichung
float SP_Pos = 0; // ???
float SP_Neg = 0; // ???

#define pinRegleraus 2
#define pinReglerein 5


void setup()
{
// 
pinMOde(pinRegleraus, OUTPUT);
pinMode(pinReglerein, INPUT);
}



void loop()
{

  // todo noch PT100 einlesen
 IW = digitalRead(pinReglerein);


if(REG_Ein)
{
 STG = false;	
}

else
{

	ER = SW  - IW;
	SP_Pos = SW * SH * 0.005;
	SP_Neg = -SW * SH * 0.005;

	if(ER < SP_Neg)
	{
		STG = 0;
	}
	else if(ER > SP_Pos)
	{
		STG = 1;
	}
}

digitalWrite(pinRegleraus, STG);
}
