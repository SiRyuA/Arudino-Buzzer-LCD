#include <LiquidCrystal.h>

#define BUTTON A5
#define BUZZERPIN 12
#define TEMPS A3

LiquidCrystal lcd(8,9,5,6,7,3);

int Time_Time = 0,
    Time_LCD = 0,
    Temps_Out = 0;

char Modetype = 0,
     Modetype_Max = 0,
     ButtonRead = 0;
     
void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.print("Hello World");
  
  pinMode(BUTTON, INPUT);
  pinMode(TEMPS, INPUT);
  pinMode(BUZZERPIN, OUTPUT);
  
  lcd_Clear();
  
  Time_LCD = 1;
  Modetype_Max = 1;
}

void loop() {
  // put your main code here, to run repeatedly:
  
  Time_Time = (millis()/1000);
  Temperature();
  
  Button_Read();

  if(Modetype == 0)  {
    lcd.setCursor(15, 0);
    lcd.print("1");
    lcd_Clock();
  }
  if(Modetype == 1)  {
    lcd.setCursor(15, 0);
    lcd.print("2");
    Temperature_lcd();
  }
  
  if(Temps_Out > 27) playMuze();
}
