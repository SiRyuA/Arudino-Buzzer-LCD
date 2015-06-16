int Time_Second = 0,
    Time_Minute = 0,
    Time_Hour = 0,
    Time_Day = 0;

void Clock(void) {
  Time_Day = Time_Time/86400 +1;
  Time_Hour = Time_Time%86400/3600;
  Time_Minute = Time_Time%86400%3600/60;
  Time_Second = Time_Time%86400%3600%60;
}

void lcd_Clock(void) {
  Clock();
  
  lcd.setCursor(0, 0);
  lcd.print("Digital Clock");
  
  lcd.setCursor(0, 1);
  lcd.print(Time_Day);
  lcd.setCursor(2, 1);
  lcd.print("Day");
  
  lcd.setCursor(6, 1);
  lcd.print(Time_Hour);
  lcd.setCursor(8, 1);
  lcd.print(":");
  
  lcd.setCursor(9, 1);
  lcd.print(Time_Minute);
  lcd.setCursor(11, 1);
  lcd.print(":");
  
  lcd.setCursor(12, 1);
  lcd.print(Time_Second);
  
  if(Time_Time / 60 == Time_LCD) {
    lcd_Clear();
    Time_LCD ++;
  }
}
