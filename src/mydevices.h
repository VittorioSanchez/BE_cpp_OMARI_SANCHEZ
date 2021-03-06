#ifndef MYDEVICES_H
#define MYDEVICES_H

#include <iostream>
#include <thread>
#include <unistd.h>
#include <string.h>
#include "core_simulation.h"
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <SFML/Audio.hpp>



class Sound {
 protected:
  int time;
  string soundTag;
  string fileLocation;
  sf::SoundBuffer buffer;
  sf::Sound son;

 public:
 Sound(int time,string tag,string loc): time(time),soundTag(tag), fileLocation(loc) {
    buffer.loadFromFile(fileLocation);
    son.setBuffer(buffer);};
  void playSound();
  void setVolume(int vol);
  string getSoundTag();
  
};

class ExternalDigitalSensorButton:public Device{
	protected :
		int val;
		int temps;
		
	public:
		ExternalDigitalSensorButton(int d);
		virtual void run();		
};

class AnalogSensorLuminosity: public Device {
protected:
  // fait osciller la valeur du capteur de 1
  int alea;
  // valeur de temperature mesuree
  int val;
  // temps entre 2 prises de valeurs
  int temps;
  
public:
  //constructeur ne pas oublier d'initialiser la classe mere
  AnalogSensorLuminosity(int d);
  // thread representant le capteur et permettant de fonctionner independamment de la board
  virtual void run();
};

// exemple de capteur analogique de temperature, ne pas oublier d'heriter de Device
class AnalogSensorTemperature: public Device {
private:
  // fait osciller la valeur du cpateur de 1
  int alea;
  // valeur de temperature mesuree
  int val;
  // temps entre 2 prises de valeurs
  int temps;
  
public:
  //constructeur ne pas oublier d'initialiser la classe mere
  AnalogSensorTemperature(int d,int  t);
  // thread representant le capteur et permettant de fonctionner independamment de la board
  virtual void run();
};

// exemple d'actionneur digital : une led, ne pas oublier d'heriter de Device
class DigitalActuatorLED: public Device {
protected:
  // etat de la LED
  int state;
  // temps entre 2 affichage de l etat de la led
  int temps;
  
public:
    // initialisation du temps de rafraichiisement
  DigitalActuatorLED(int t);
  // thread representant l'actionneur et permettant de fonctionner independamment de la board
  virtual void run();
  void setState(int d);
  int getState();
};

class IntelligentDigitalActuatorLED: public DigitalActuatorLED{
public:
    // initialisation du temps de rafraichiisement
 IntelligentDigitalActuatorLED(int t): DigitalActuatorLED(t){};
  
  virtual void run();
};

// exemple d'actionneur sur le bus I2C permettant d'echanger des tableaux de caracteres : un ecran, ne pas oublier d'heriter de Device
class I2CActuatorScreen : public Device{
protected:
    // memorise l'affichage de l'ecran
  char buf[I2C_BUFFER_SIZE];
  
public:
  // constructeur
  I2CActuatorScreen ();
  // thread representant le capteur et permettant de fonctionner independamment de la board
  virtual void run();
};

class Vumeter: public Device{
	protected:
	int numeroVumeter;
	vector <DigitalActuatorLED> vectorLED;
	string moduleTag;
	int intensity;
	int temps;
	int state;
	
	public:
		// initialisation du temps de rafraichiisement
	  Vumeter(int t, string name,int numVum);
	  // thread representant l'actionneur et permettant de fonctionner independamment de la board
	  virtual void run();
	  vector <DigitalActuatorLED> getVectorLED();
	  // allume les LED en fonction de l'intensite
	  void turnOnLight(int d);
	  void turnOffLight(int d);
	  void setIntensity(int intens);	  
};


class AnalogSensorLuminositySoundDevice:public AnalogSensorLuminosity{
	private:
        int nbSounds;
	vector <Sound> vectorSound;
	Vumeter *m_Vumeter;
	
	public:
	AnalogSensorLuminositySoundDevice(int t,Vumeter *vu);
	void addSound(Sound son);
	int getValLum();
	virtual void run(); 
	
};


class AnalogSensorUltrasoundSoundDevice:public AnalogSensorLuminosity{
	private:
        int nbSounds;
	vector <Sound> vectorSound;
	Vumeter *m_Vumeter;
	
	public:
	AnalogSensorUltrasoundSoundDevice(int t,Vumeter *vu);
	void addSound(Sound son);
	int getValProximity();
	virtual void run(); 
};


class ButtonSoundDevice: public ExternalDigitalSensorButton {
 private:
  string fileButton;
  Sound sound;

 public:
 ButtonSoundDevice(int t, Sound son, string fileLoc) : ExternalDigitalSensorButton(t), sound(son), fileButton(fileLoc) {};
  virtual void run();
  
};


class Instrument{
 protected:
  vector<Device> modules;
  int state;

 public:
 Instrument(ButtonSoundDevice BSD1,ButtonSoundDevice BSD2, AnalogSensorLuminositySoundDevice LSD1);
 void run();
 
 
};

#endif
