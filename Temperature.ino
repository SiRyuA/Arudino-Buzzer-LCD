int Temps_Read = 0;
long Temps_X=0,
     Temps_VCC = 4840;
float Temps_TH=0,
      Temps_CE=0;

void Temperature(void) {
  Temps_Read = analogRead(TEMPS);
  Temps_X = map(Temps_Read, 0, 1023, 0, Temps_VCC);
  Temps_TH = (((float)(Temps_VCC - Temps_X)*10.0)/(float)Temps_X)*1000.0;
  Temps_CE = ((log(4.0*Temps_TH - 3000.0)/(-0.024119329)+473)-32.0)/1.8;
  
  Temps_Out = Temps_CE;
}

void Temperature_lcd(void) {
  lcd.setCursor(0, 0);
  lcd.print("Temperature");  
  lcd.setCursor(0, 1);
  lcd.print(Temps_Out);
  lcd.setCursor(2, 1);
  lcd.print("C");
}
