#include "mydevices.h"
using namespace std;
extern int luminosite_environnement=200;


//classe ExternalDigitalSensorButton
ExternalDigitalSensorButton::ExternalDigitalSensorButton(int d):Device(),temps(d){
	val=0;
}
void ExternalDigitalSensorButton::run(){
	while (1){
		if(ifstream("on.txt")){
			val=1;
			*ptrmem=val;
		}
		else{
			val=0;
			*ptrmem=val;
		}
			
		sleep(temps);
	}
}


//classe AnalogSensorLuminosity
AnalogSensorLuminosity::AnalogSensorLuminosity(int d):Device(),val(luminosite_environnement),temps(d){
	alea=1;
}

void AnalogSensorLuminosity::run(){
  while(1){
    val=luminosite_environnement;
    alea=1-alea;
    if(ptrmem!=NULL)
      *ptrmem=val+alea;
    sleep(temps);
  }
}
//classe AnalogSensorTemperature
AnalogSensorTemperature::AnalogSensorTemperature(int d,int  t):Device(),val(t),temps(d){
  alea=1;
}

void AnalogSensorTemperature::run(){
  while(1){
    alea=1-alea;
    if(ptrmem!=NULL)
      *ptrmem=val+alea;
    sleep(temps);
  }
}

//classe DigitalActuatorLED
DigitalActuatorLED::DigitalActuatorLED(int t):Device(),state(LOW),temps(t){
}

void DigitalActuatorLED::run(){
  while(1){
    if(ptrmem!=NULL)
      state=*ptrmem;
    if (state==LOW)
      cout << "((((eteint))))\n";
    else
      cout << "((((allume))))\n";
    sleep(temps);
    }
}

void IntelligentDigitalActuatorLED::run(){
  int old_state;
  while(1){
    if(ptrmem!=NULL){
      state=*ptrmem;
    }
    if (state==LOW){
      cout << "((((Ieteint))))\n";
      if(state != old_state){
	luminosite_environnement -=50;
      }
    }
    else{
      cout << "((((Iallume))))\n";
      if(state != old_state){
	luminosite_environnement +=50;
      }
    }
    sleep(temps);
    old_state=state;
  }
}

// classe I2CActuatorScreen
I2CActuatorScreen::I2CActuatorScreen ():Device(){
  }

void I2CActuatorScreen::run(){
  while(1){
    if ( (i2cbus!=NULL)&&!(i2cbus->isEmptyRegister(i2caddr))){
      Device::i2cbus->requestFrom(i2caddr, buf, I2C_BUFFER_SIZE);
      cout << "---screen :"<< buf << endl;
    }
    sleep(1);
    }
}





