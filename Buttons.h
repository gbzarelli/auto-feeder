#define BT_NONE   -1
#define BT_RIGHT  1
#define BT_UP     2
#define BT_DOWN   3
#define BT_LEFT   4
#define BT_SELECT 5

#define PIN_BT    A0

int tmpBtPress = -1;
boolean tmpBtPressState = false;
int countToBtPress;

void setupButtons(){
  pinMode(PIN_BT, INPUT);
}


// read the buttons
int getBtPress(){
 int adc_key_in = analogRead(PIN_BT);
 
 if (adc_key_in < 50){
  tmpBtPressState = true;
  tmpBtPress =  BT_RIGHT;  
 }else if (adc_key_in < 195){
  tmpBtPressState = true;
  tmpBtPress =  BT_UP; 
 }else if (adc_key_in < 380){
  tmpBtPressState = true;
  tmpBtPress =  BT_DOWN; 
 }else  if (adc_key_in < 555){
  tmpBtPressState = true;
  tmpBtPress =  BT_LEFT; 
 }else if (adc_key_in < 790){
  tmpBtPressState = true;
  tmpBtPress =  BT_SELECT;  
 }else if (tmpBtPressState) {
    tmpBtPressState = false;
    countToBtPress=0;
    return tmpBtPress;
 }

 if(tmpBtPressState && countToBtPress++ >10){
   return tmpBtPress;
 }

 return BT_NONE;
}

