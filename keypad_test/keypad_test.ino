
#include <Keypad.h>
const byte ROWS = 4; // Four rows
const byte COLS = 3; // Three columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 33, 34, 35, 36 };
// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { 30, 31, 32 }; 
// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  Serial.begin(9600);

}

void loop() {

  char key = kpd.getKey();
  
  if(key=='1'){Serial.println("1");} 
  if(key=='2'){Serial.println("2");}
  if(key=='3'){Serial.println("3");}
  if(key=='4'){Serial.println("4");}
  if(key=='5'){Serial.println("5");}
  if(key=='6'){Serial.println("6");}
  if(key=='7'){Serial.println("7");}
  if(key=='8'){Serial.println("8");}
  if(key=='9'){Serial.println("9");}
  if(key=='*'){Serial.println("*");}
  if(key=='0'){Serial.println("0");}
  if(key=='#'){Serial.println("#");}
  
}
