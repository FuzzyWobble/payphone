//fuzzywobble
//oct 2016


//0 – waiting
//1 – proximity triggered, ringing
//2 – in use
//3 – hangup, idle for XXXXms
int MODE = 0;


long MODE_1_TIMER_START;
int MODE_1_DURATION = 13000;

long MODE_3_TIMER_START;
int MODE_3_DURATION = 7000;





//#############################################################
//#############################################################

//_________________________________________________________
//_________________________________________________________ HANDSET HANGUP SWITCH
//we are reading the handset switch on pin 40
//low when hung up
//high when used
int PIN_HANDSET_SWITCH = 40;

//_________________________________________________________
//_________________________________________________________ PROXIMITY SENSOR
int PROXIMITY_THRESHOLD = 310;
int PIN_PROXIMITY_SENSOR = A8;
int PROXIMITY_VAL_PREV = 0;

//_________________________________________________________
//_________________________________________________________ MP3 SHIELD
// include SPI, MP3 and SD libraries
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>
#define SHIELD_RESET  -1      // VS1053 reset pin (unused!)
#define SHIELD_CS     7      // VS1053 chip select pin (output)
#define SHIELD_DCS    6      // VS1053 Data/command select pin (output)
// These are common pins between breakout and shield
#define CARDCS 4     // Card chip select pin
// DREQ should be an Int pin, see http://arduino.cc/en/Reference/attachInterrupt
#define DREQ 3       // VS1053 Data request, ideally an Interrupt pin
Adafruit_VS1053_FilePlayer musicPlayer = Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

//_________________________________________________________
//_________________________________________________________ KEYPAD
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





//#############################################################
//#############################################################
void setup() {

  Serial.begin(9600);

  //_________________________________________________________ HANDSET HANGUP SWITCH
  pinMode(PIN_HANDSET_SWITCH, INPUT_PULLUP);

  //_________________________________________________________ MP3 SHIELD
  if (! musicPlayer.begin()) { // initialise the music player
     Serial.println(F("Couldn't find MP3 Shield, do you have the right pins defined?"));
     while (1);
  }
  Serial.println(F("MP3 shield found"));
  SD.begin(CARDCS);
  musicPlayer.setVolume(100,100); //weird, low is loud! left speaker is handset. right speaker is bell. 
  // If DREQ is on an interrupt pin (on uno, #2 or #3) we can do background
  // audio playing
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int
  
}







//#############################################################
//#############################################################
void loop() {


  switch (MODE) {



    case 1: //1 – proximity triggered, ringing

      musicPlayer.setVolume(80,10); //handset quiet. speaker very loud.
      musicPlayer.startPlayingFile("track111.mp3"); //bell sound
      Serial.println("MODE 1");
      while (musicPlayer.playingMusic){
        Serial.println("Playing in MODE 1");
        if(digitalRead(PIN_HANDSET_SWITCH)==HIGH){
          musicPlayer.stopPlaying();
          MODE = 2;   
        }
        if(millis() - MODE_1_TIMER_START > MODE_1_DURATION){
          musicPlayer.stopPlaying();
          MODE = 0; 
        }
        delay(100);
      }
      break;


      
    case 2: //2 – in use

      musicPlayer.setVolume(20,100); //handset mid-loud. speaker quiet.  
      Serial.println("MODE 2");
      if(digitalRead(PIN_HANDSET_SWITCH)==LOW){
        musicPlayer.stopPlaying();
        MODE = 3;
        MODE_3_TIMER_START = millis();
      }
      keypad_to_song();
      musicPlayer.startPlayingFile("track008.mp3");
      while (musicPlayer.playingMusic){
        Serial.println("Playing in MODE 2");
        keypad_to_song();
        if(digitalRead(PIN_HANDSET_SWITCH)==LOW){
          musicPlayer.stopPlaying();
          MODE = 3;
          MODE_3_TIMER_START = millis();
        }
      }
      break;


      
    case 3: //3 – hangup, idle for XXXXms

      Serial.println("MODE 3");
      if(millis() - MODE_3_TIMER_START > MODE_3_DURATION){
        MODE = 0;
      }
      break;


      
    default: //0 – waiting

      Serial.println("MODE 0");
      if(analogRead(PIN_PROXIMITY_SENSOR) > PROXIMITY_THRESHOLD && PROXIMITY_VAL_PREV > PROXIMITY_THRESHOLD){
        MODE = 1;
        MODE_1_TIMER_START = millis();
      }
      PROXIMITY_VAL_PREV = analogRead(PIN_PROXIMITY_SENSOR);
      delay(100);
    
    break;


    
  }


  


}


void keypad_to_song(){
  char key = kpd.getKey();
  if(key=='1'){musicPlayer.startPlayingFile("track001.mp3");} 
  if(key=='2'){musicPlayer.startPlayingFile("track002.mp3");}
  if(key=='3'){musicPlayer.startPlayingFile("track003.mp3");}
  if(key=='4'){musicPlayer.startPlayingFile("track004.mp3");}
  if(key=='5'){musicPlayer.startPlayingFile("track005.mp3");}
  if(key=='6'){musicPlayer.startPlayingFile("track006.mp3");}
  if(key=='7'){musicPlayer.startPlayingFile("track007.mp3");}
  if(key=='8'){musicPlayer.startPlayingFile("track008.mp3");}
  if(key=='9'){musicPlayer.startPlayingFile("track009.mp3");}
  if(key=='*'){musicPlayer.stopPlaying();}
  if(key=='0'){musicPlayer.stopPlaying();}
  if(key=='#'){musicPlayer.stopPlaying();}
}





