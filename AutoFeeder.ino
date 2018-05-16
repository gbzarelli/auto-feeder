#include "Sensor_HX711.h"
#include "Display.h"
#include "Buttons.h"
#include "UPS.h"

#define PIN_RELE        13
#define STAGE_MAIN      1
#define STAGE_CONFIG_1  3
#define STAGE_CONFIG_2  4
#define STAGE_CONFIG_3  5
#define STAGE_RUNNING   2

void processRunning();
void processConfig3(int btPressed);
void processConfig2(int btPressed);
void processConfig(int btPressed);

int stage = STAGE_MAIN;

int secLoop=0;
int weightMin=1;
int weightMax=200;
boolean inFeeder=false;

void setup() {
  Serial.begin(9600);
 
  pinMode(PIN_RELE, OUTPUT);
  digitalWrite(PIN_RELE, LOW);
  
  setupDisplay();
  setupButtons();
  setupHX711();

  
  printWelcome();
  delay(2000);
  printStart("Iniciar config.");
}

void loop() {
  startLoop();

  int btPressed = getBtPress();
  
  if(STAGE_MAIN==stage && BT_SELECT == btPressed){
    stage = STAGE_CONFIG_1;
    secLoop=0;
  }else{
    if(ups==500 || BT_NONE != btPressed){
       switch(stage){
          case STAGE_CONFIG_1: processConfig1(btPressed); break;
          case STAGE_CONFIG_2: processConfig2(btPressed); break;
          case STAGE_CONFIG_3: processConfig3(btPressed); break;
          case STAGE_RUNNING: processRunning();
       }
    }
  }
  secLoop = endLoop();
}

void processConfig1(int btPressed){
  if(BT_UP==btPressed){
    weightMin++;
  }else if(BT_DOWN==btPressed && weightMin>1){
    weightMin--;
  }else if(BT_SELECT == btPressed || BT_RIGHT == btPressed){
     stage = STAGE_CONFIG_2;
     return;
  }
  printConfigWeight("Peso de acionam.",weightMin,readSensor());
}

void processConfig2(int btPressed){
  if(BT_UP==btPressed){
    weightMax++;
  }else if(BT_DOWN==btPressed && weightMax>1){
    weightMax--;
  }else if(BT_SELECT == btPressed || BT_RIGHT == btPressed){
     stage = STAGE_CONFIG_3;
     return;
  }else if(BT_LEFT == btPressed){
     stage = STAGE_CONFIG_1;
     return;
  }
  printConfigWeight("Peso pausa motor",weightMax,readSensor());
}

void processConfig3(int btPressed){
  if(BT_SELECT == btPressed){
     stage = STAGE_RUNNING;
     return;
  }if(BT_LEFT == btPressed){
     stage = STAGE_CONFIG_2;
     return;
  }
  printStart("Iniciar sistema.");
}

void processRunning(){
  int sensorValue = readSensor();
  if(inFeeder){
    if(sensorValue < weightMax){
      printFeeder(weightMax,sensorValue);
    }else{
      digitalWrite(PIN_RELE,LOW);
      inFeeder=false;
    }
  }else if(sensorValue < weightMin){
    inFeeder=true;
    digitalWrite(PIN_RELE,HIGH);
  } else {
    printRunning(weightMin,weightMax,sensorValue);
  }
}

