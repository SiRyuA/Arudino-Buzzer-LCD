void lcd_Clear(void) {
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
}

void Button_Read(void) {
  ButtonRead = digitalRead(BUTTON);
  
  if (ButtonRead == HIGH) {
    delay(500);
    Modetype ++;
    lcd_Clear();
  }
  
  if (Modetype > Modetype_Max) {
    Modetype = 0;
  }
}
