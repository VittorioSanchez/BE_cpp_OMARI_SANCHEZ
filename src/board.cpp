#include "core_simulation.h"
#include "mydevices.h"


int main(){
  // creation d'une board
  Board esp8266;
  // achat des senseurs et actionneurs
  AnalogSensorTemperature temperature(DELAY,TEMP);
  AnalogSensorLuminosity luminosity(DELAY);
  DigitalActuatorLED led1(DELAY);
  Vumeter vumetre1(DELAY,"LUM");
  Vumeter vumetre2(DELAY,"PROX");
  IntelligentDigitalActuatorLED led2(DELAY);
  I2CActuatorScreen screen;
  ExternalDigitalSensorButton button(DELAY);
  
  // capteur luminosite music
  Sound son1(DELAY,"SON LUM 1","SonsLuminosite/loc1.wav");
  Sound son2(DELAY,"SON LUM 2","SonsLuminosite/loc2.wav");
  Sound son3(DELAY,"SON LUM 3","SonsLuminosite/loc3.wav");
  Sound son4(DELAY,"SON LUM 4","SonsLuminosite/loc4.wav");
  Sound son5(DELAY,"SON LUM 5","SonsLuminosite/loc5.wav");
  AnalogSensorLuminositySoundDevice capteurMusical1(DELAY,&vumetre1);
  capteurMusical1.addSound(son1);
  capteurMusical1.addSound(son2);
  capteurMusical1.addSound(son3);
  capteurMusical1.addSound(son4);
  capteurMusical1.addSound(son5);

  Sound son6(DELAY,"SON PROX 1","SonsProximite/loc6.wav");
  Sound son7(DELAY,"SON PROX 2","SonsProximite/loc7.wav");
  Sound son8(DELAY,"SON PROX 3","SonsProximite/loc8.wav");
  Sound son9(DELAY,"SON PROX 4","SonsProximite/loc9.wav");
  Sound son10(DELAY,"SON PROX 5","SonsProximite/loc10.wav");
  AnalogSensorUltrasoundSoundDevice capteurMusical2(DELAY,&vumetre2);
  capteurMusical2.addSound(son6);
  capteurMusical2.addSound(son7);
  capteurMusical2.addSound(son8);
  capteurMusical2.addSound(son9);
  capteurMusical2.addSound(son10);
  
  //bouton music 1
  Sound son11(DELAY,"BOUTON 1","SonsBoutons/son1.wav");
  ButtonSoundDevice boutonSound1(DELAY,son11,"SonsBoutons/son1.txt");
  //bouton music 2
  Sound son12(DELAY,"BOUTON 2","SonsBoutons/son2.wav");
  ButtonSoundDevice boutonSound2(DELAY,son12,"SonsBoutons/son2.txt");
  
  //intsrument
  Instrument monInstrument(boutonSound1,boutonSound2,capteurMusical1);

  // branchement des capteurs actionneurs
  esp8266.pin(5,vumetre1);
  esp8266.pin(6,capteurMusical1);
  esp8266.pin(7,boutonSound1);
  esp8266.pin(8,boutonSound2);
  esp8266.pin(9,capteurMusical2);
  esp8266.pin(10,vumetre2);
  monInstrument.run();
 
/* 
  esp8266.pin(3,led2);


  esp8266.pin(3,led2); */

  
  // allumage de la carte
  esp8266.run();
  return 0;
}


