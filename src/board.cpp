#include "core_simulation.h"
#include "mydevices.h"


int main(){
  // creation d'une board
  Board esp8266;
  // achat des senseurs et actionneurs
  AnalogSensorTemperature temperature(DELAY,TEMP);
  AnalogSensorLuminosity luminosity(DELAY);
  DigitalActuatorLED led1(DELAY);
  Vumeter vumetre1(DELAY);
  IntelligentDigitalActuatorLED led2(DELAY);
  I2CActuatorScreen screen;
  ExternalDigitalSensorButton button(DELAY);
  
  // capteur luminosite music
  Sound noSound(DELAY,"pas de son","SonsLuminosite/noSound.txt");
  Sound son1(DELAY,"sonLum1","SonsLuminosite/loc1.txt");
  Sound son2(DELAY,"sonLum2","SonsLuminosite/loc2.txt");
  Sound son3(DELAY,"sonLum3","SonsLuminosite/loc3.txt");
  Sound son4(DELAY,"sonLum4","SonsLuminosite/loc4.txt");
  Sound son5(DELAY,"sonLum5","SonsLuminosite/loc5.txt");
  AnalogSensorLuminositySoundDevice capteurMusical1(DELAY,&vumetre1);
  capteurMusical1.addSound(noSound);
  capteurMusical1.addSound(son1);
  capteurMusical1.addSound(son2);
  capteurMusical1.addSound(son3);
  capteurMusical1.addSound(son4);
  capteurMusical1.addSound(son5);
  
  //bouton music 1
  Sound son6(DELAY,"sonBoutton1","SonsBoutons/son1.txt");
  ButtonSoundDevice boutonSound1(DELAY,son6,"SonsBoutons/son1.txt");
    //bouton music 2
  Sound son7(DELAY,"sonBoutton2","SonsBoutons/son1.txt");
  ButtonSoundDevice boutonSound2(DELAY,son6,"SonsBoutons/son1.txt");
  
  //intsrument
  Instrument monInstrument(boutonSound1,boutonSound2,capteurMusical1);

  // branchement des capteurs actionneurs
  esp8266.pin(5,vumetre1);
  esp8266.pin(6,capteurMusical1);
  esp8266.pin(7,boutonSound1);
  esp8266.pin(8,boutonSound2); 
  monInstrument.run();
 
/* 
  esp8266.pin(3,led2);


  esp8266.pin(3,led2); */

  
  // allumage de la carte
  esp8266.run();
  return 0;
}


