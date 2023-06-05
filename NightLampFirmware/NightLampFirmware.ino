#include <IRremote.h>
#include <IRremoteInt.h>

IRrecv irrecv(A0); // IR receiver pin
decode_results results;

const int PIN_RED   = 9;
const int PIN_GREEN = 10;
const int PIN_BLUE  = 6;

unsigned int Val_R = 255;
unsigned int Val_G = 255;
unsigned int Val_B = 255;
unsigned int Brightness = 255;
bool enabled = true;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); // Receiving IR
  //Serial.println("Started!");
}

void loop() {
  if (irrecv.decode(&results)) // IR signal catched 
  {
    //Serial.println(results.value); // IR code -> console

    if (enabled){ //Change colors only if switched on
      switch(results.value){
        case 16195807: setValues(255, 0, 0); break;
        case 16228447: setValues(0, 255, 0); break;
        case 16212127: setValues(0, 0, 255); break;
        case 16244767: setValues(255, 255, 255); break;
        case 16203967: enabled = false; break;
        case 16236607: enabled = true; break;
        case 16187647: riseBrightness(); break;
        case 16220287: lowerBrightness(); break;
        case 16191727: setValues(255, 0, 16); break;
        case 16224367: setValues(0, 255, 10); break;
        case 16208047: setValues(0, 128, 255); break;
        case 16199887: setValues(255, 27, 0); break;
        case 16232527: setValues(0, 255, 255); break;
        case 16216207: setValues(180, 0, 255); break;
        case 16189687: setValues(255, 96, 0); break;
        case 16222327: setValues(0, 144, 255); break;
        case 16206007: setValues(240, 0, 255); break;
        case 16197847: setValues(255, 200, 0); break;
        case 16230487: setValues(0, 78, 255); break;
        case 16214167: setValues(255, 0, 180); break;
      }
    }
    else if(results.value == 16236607){
      enabled = true;
    }

    irrecv.resume(); // Receiving next signal
  }

  if (enabled){
    updateLed();
  }
  else{
    turnOff();
  }
  

  delay(100);
}

void setValues(int red, int green, int blue){
  Val_R = red;
  Val_G = green;
  Val_B = blue;
}

void updateLed(){
  analogWrite(PIN_RED,   map(Val_R * Brightness, 0, 65025, 0, 255));
  analogWrite(PIN_GREEN, map(Val_G * Brightness, 0, 65025, 0, 255));
  analogWrite(PIN_BLUE,  map(Val_B * Brightness, 0, 65025, 0, 255));
}

void turnOff(){
  analogWrite(PIN_RED,   0);
  analogWrite(PIN_GREEN, 0);
  analogWrite(PIN_BLUE,  0);
}

void riseBrightness(){
  if (Brightness < 255){
    Brightness = Brightness << 1;
    Brightness++;
  }
}

void lowerBrightness(){
  if (Brightness > 0){
    Brightness = Brightness >> 1;
  }
}