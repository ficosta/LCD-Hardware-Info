//http://www.electronicsblog.net
//Arduino LCD horizontal progress bar using custom characters
#include <LiquidCrystal.h>
 
#define lenght 16.0
 
int percent=100;
unsigned char b;
unsigned int peace;
 
// custom charaters
 
LiquidCrystal lcd(9, 8, 5, 4, 3, 2);
byte p1[8] = {
  0x10,
  0x10,
  0x10,
  0x10,
  0x10,
  0x10,
  0x10,
  0x10};
 
byte p2[8] = {
  0x18,
  0x18,
  0x18,
  0x18,
  0x18,
  0x18,
  0x18,
  0x18};
 
byte p3[8] = {
  0x1C,
  0x1C,
  0x1C,
  0x1C,
  0x1C,
  0x1C,
  0x1C,
  0x1C};
 
byte p4[8] = {
  0x1E,
  0x1E,
  0x1E,
  0x1E,
  0x1E,
  0x1E,
  0x1E,
  0x1E};
 
byte p5[8] = {
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F};
 
void setup()   {
 
  delay(100);
  lcd.createChar(0, p1);
  lcd.createChar(1, p2);
  lcd.createChar(2, p3);
  lcd.createChar(3, p4);
  lcd.createChar(4, p5);
 
  lcd.begin(16, 2);
 
}
 
void loop()
{
 
  lcd.setCursor(0, 0);
 
  percent = 100;
 
  lcd.print(percent);
  lcd.print(" %   ");
 
  lcd.setCursor(0,1);
 
  int a=lenght/100*percent;
 
 // drawing black rectangles on LCD
 
  if (a>=1) {
 
    for (int i=1;i<a;i++) {
 
      lcd.write(4);
 
      b=i;
    }
 
    a=a-b;
 
  }
 
  peace=a*5;
 
// drawing charater's colums
 
  switch (peace) {
 
  case 0:
 
    break;
 
  case 1:
    lcd.print((char)0);
 
    break;
 
  case 2:
    lcd.print((char)1);
    break;
 
  case 3:
    lcd.print((char)2);
    break;
 
  case 4:
    lcd.print((char)3);
    break;
 
  }
 
//clearing line
  for (int i =0;i<(lenght-b);i++) {
 
    lcd.print(" ");
  }
 
  ;
}
