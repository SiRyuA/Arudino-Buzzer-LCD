#include <LiquidCrystal.h>
 
// Set pins.
#define BUTTON_PIN A5    // The number of the push-button pin.
#define LCD_LIGHT_PIN A4 // The number of the pin where anode of the display backlight is.
#define BUZZER A3
 
#define LCD_LIGHT_ON_TIME 60000 // How long (in milliseconds) should lcd light stay on?
 
unsigned int currentLcdLightOnTime = 0;
// For calculating the lcd light on time.
unsigned long lcdLightOn_StartMillis;
 
boolean isLcdLightOn;
 
// For checking push-button state.
int buttonState = 0;
 
// Initialize the LiquidCrystal library with the numbers of the interface pins.
//LiquidCrystal(rs, e, d4, d5, d6, d7);
LiquidCrystal lcd(8, 9, 5, 6, 7, 3);

//Buzzer Setup
int speakerPin = 12;

int length = 15; // the number of notes
char notes[] = "ccggaagffeeddc "; // a space represents a rest
int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
int tempo = 300;

//Buzzer Funtion
void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}


void setup(){
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
 
  // Set the lcd number of columns and rows.
  lcd.begin(16, 2);
 
  // Print the message to the lcd.
  lcd.setCursor(0, 0); // First row.
  lcd.print("Test lcd light");
  lcd.setCursor(3, 1); // Second row.
  lcd.print("SiRyuA");
  lcd.display();
 
  // Set the push-button pin as an input.
  pinMode(BUTTON_PIN, INPUT);
  // Set the lcd display backlight anode pin as an output.
  pinMode(LCD_LIGHT_PIN, OUTPUT);
  // Set the lcd display backlight anode pin to low - lcd light off.
  digitalWrite(LCD_LIGHT_PIN, LOW);
  isLcdLightOn = false;
  // Set Buzzer
  pinMode(speakerPin, OUTPUT);

  delay(10000);
  
  // Print the message to the lcd.
  lcd.setCursor(0, 0); // First row.
  lcd.print("                                ");
  lcd.setCursor(3, 1); // Second row.
  lcd.print("                                ");
  lcd.display();
}
 
void loop(){
  // Check the state of the push-button.
  buttonState = digitalRead(BUTTON_PIN);
 
  if (buttonState == HIGH){
    // Button pressed.
    Serial.println("Button pressed - HIGH");
 
    lcdLightOn_StartMillis = millis();
    currentLcdLightOnTime = 0;
    isLcdLightOn = true;
    digitalWrite(LCD_LIGHT_PIN, HIGH);
  }
  else{
    // Button not pressed.
    //Serial.println("Button not pressed - LOW");
 
    if(isLcdLightOn){
      currentLcdLightOnTime = millis() - lcdLightOn_StartMillis;
      if(currentLcdLightOnTime > LCD_LIGHT_ON_TIME){
        isLcdLightOn = false;
        digitalWrite(LCD_LIGHT_PIN, LOW);
      }
    }
  }
  
  if(currentLcdLightOnTime > 10000)
  {
    for (int i = 0; i < length; i++) {
      if (notes[i] == ' ') {
        delay(beats[i] * tempo); // rest
      } else {
        playNote(notes[i], beats[i] * tempo);
      }
  
      // pause between notes
      delay(tempo / 2); 
    }
    
    currentLcdLightOnTime = 0;
  }
  
  Serial.print("Lcd light time:");
  Serial.println(currentLcdLightOnTime);
  
  // Print the message to the lcd.
  lcd.setCursor(0, 0); // First row.
  lcd.print("Lcd light time:");
  lcd.setCursor(1, 1); // Second row.
  lcd.print(currentLcdLightOnTime);
  lcd.display();
}
                               
