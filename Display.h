#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setupDisplay(){
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Carregando...");
}

void printWelcome(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Bem vindo");
  lcd.setCursor(0,1);
  lcd.print("AUTOFEEDER");
}

void printFeeder(int maxi, int current){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ALIMENTANDO...");
  lcd.setCursor(0,1);
  lcd.print("M:"+String(maxi)+"g - A:"+String(current)+"g");
}

void printStart(String txt){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(txt);
  lcd.setCursor(0,1);
  lcd.print("Press. SELECT");
}

void printRunning(int mini,int maxi,int current){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Min/ Max/ Atual");
  lcd.setCursor(0,1);
  lcd.print(String(mini)+"g/ "+String(maxi)+"g/ "+String(current)+"g");
}

void printConfigWeight(String txt, int value,int current){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(txt);
  lcd.setCursor(0,1);
  lcd.print(String(value)+"g"+" - A:"+String(current)+"g");
}

