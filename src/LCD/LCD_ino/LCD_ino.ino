#include <LiquidCrystal.h> //Inclusão biblioteca LCD

LiquidCrystal lcd(9, 8, 5, 4, 3, 2); //Ligação dos pinos do LCD

//Declaracao novos caracteres
byte p1[8] = {0x10,0x10,0x10,0x1f,0x10,0x10,0x10,0x10};
byte p2[8] = {0x18,0x18,0x18,0x1f,0x18,0x18,0x18,0x18};
byte p3[8] = {0x1C,0x1C,0x1C,0x1f,0x1C,0x1C,0x1C,0x1C};
byte p4[8] = {0x1E,0x1E,0x1E,0x1f,0x1E,0x1E,0x1E,0x1E};
byte p5[8] = {0x1F,0x1F,0x1F,0x1f,0x1F,0x1F,0x1F,0x1F};

int cpu = 0;
int mem = 0;


String inputString = "";         // a string to hold incoming data
boolean stringComplete = false; 

long lastUpdate = 0;


void setup(){
 
  delay(100);
  //Inicia a porta serial
  Serial.begin(9600);
  
  //Salva os novos caracteres no LCD
  lcd.createChar(0, p1);
  lcd.createChar(1, p2);
  lcd.createChar(2, p3);
  lcd.createChar(3, p4);
  lcd.createChar(4, p5);
 
  //Inicia o LCD com 16 caracteres com duas linhas
  lcd.begin(16, 2);
  
  
  inputString.reserve(200);
}

void loop(){

  
  if (stringComplete) {

    // clear the string:
    
    //char valueArray[inputString.length() + 1];
    //int value = atoi(valueArray);
    
    Serial.println(inputString);     
    drawInfoBar("CPU","%",0,9,7,inputString.toInt());
    String command = inputString.substring(0,3);

    if (command == "cpu"){
        cpu = inputString.substring(4).toInt();
        lastUpdate = millis();
    } else if (command == "cpu"){
        mem = inputString.substring(4).toInt();
        lastUpdate = millis();
    }
    
    inputString = "";
    stringComplete = false;
    
  }
  
  unsigned long currentMillis = millis();
 
  if(currentMillis - lastUpdate < 10000) {
  
  drawInfoBar("CPU","%",0,9,7,cpu);
  drawInfoBar("MEM","%",1,9,7,mem);
  
  }else{
      lcd.clear();
      lcd.print("Sem comunicacao");
      delay(500);
  }
}

void drawInfo(String info, int line){
  lcd.setCursor(0,line);
  lcd.print("                ");
  lcd.setCursor(0,line);
  lcd.print(info);
  
}
void drawInfoBar(String info, String signal, int line, int positionBar, int sizeBar, int value){
    
    lcd.setCursor(0,line);
    lcd.print("                ");
    lcd.setCursor(0,line);
    if (value!= 100){
      lcd.print(info+": ");
    }else{
      lcd.print(info+ " ");
    }
    
    lcd.print(value);
    lcd.print(signal);
    drawBar(value,line,positionBar,sizeBar);
}

void drawBar(int value, int lineBar, int positionBar, int sizeBar){
   lcd.setCursor(positionBar, lineBar);
  //quantidade de barrinhas
  int barras=((5*sizeBar)*value)/100; //Define a quantidade de barras necessarias
  
  //Itera até obter a barra completa.
  for (int i=0;i<=(sizeBar-1);i++){
    if (barras >= 5){
      //imprime quadrados completos (5 barras)
      lcd.print((char)4);
      barras = barras - 5;  
    }else{
      //imprime quadrados parciais (brancos ou até 4 barras)
      switch (barras) {
      case 0:
        lcd.print("-");
        break;
      case 1:
        lcd.print((char)0);
        barras = barras - 1; 
        break;
      case 2:
        lcd.print((char)1);
        barras = barras - 2; 
        break;
      case 3:
        lcd.print((char)2);
        barras = barras - 3; 
        break;
      case 4:
        lcd.print((char)3);
        barras = barras - 4; 
        break;
      }
    }
  }
}
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    } 
  }
}
