#include "mydevices.h"
#include <vector>

using namespace std;

extern int luminosite_environnement=200;
extern int VAL_MAX_ANALOG_SENSOR_LUM = 200;
extern int VAL_MIN_ANALOG_SENSOR_LUM = 5;
extern int VAL_MAX_ULTRASOUND = 200;
extern int VAL_MIN_ULTRASOUND = 10;


void Sound::playSound(){
  ifstream soundFile(fileLocation);
  if(soundFile){
    string line;
    while(getline(soundFile, line)){
      cout << " ****** "+soundTag+" :  " << line <<" ****** " << endl;
    }
  }
  soundFile.close();
}

string Sound::getSoundTag(){
  return soundTag;
}


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


void DigitalActuatorLED::setState(int d){
	state=d;
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


Vumeter::Vumeter(int t):Device(){
	intensity=0;
	state=0;
	temps=t;
	DigitalActuatorLED LED1(DELAY);
	DigitalActuatorLED LED2(DELAY);
	DigitalActuatorLED LED3(DELAY);
	DigitalActuatorLED LED4(DELAY);
	DigitalActuatorLED LED5(DELAY);

	vectorLED.push_back(LED1);
	vectorLED.push_back(LED2);
	vectorLED.push_back(LED3);
	vectorLED.push_back(LED4);
	vectorLED.push_back(LED5);
}


void Vumeter::turnOnLight(int d){
	vectorLED[d].setState(HIGH);
}
void Vumeter::turnOffLight(int d){
	vectorLED[d].setState(LOW);
}

void Vumeter::setIntensity(int intens){
  intensity = intens; 
}


void Vumeter::run(){
	while (1){
		int j=0;
		if(ptrmem!=NULL)
			state=*ptrmem;
		if (intensity==0)
			cout<<"Vumeter est eteint"<<endl;
		else	{
			cout<<"Vumeter est allume"<<endl;
			for (int i=0;i<vectorLED.size();i++){
				if (i<intensity){
					turnOnLight(i);
					j++;
				}
				else{
					turnOffLight(i);
				}
			}
			cout<<j<<" voyants sont allumés"<<endl;
		}	
		sleep(temps);
	}
}


AnalogSensorLuminositySoundDevice::AnalogSensorLuminositySoundDevice(int t,Sound pasDeSon ,Sound son1,Sound son2,Sound son3,Sound son4,Sound son5,Vumeter *vu):AnalogSensorLuminosity(t){
	vectorSound.push_back(pasDeSon);
	vectorSound.push_back(son1);
	vectorSound.push_back(son2);
	vectorSound.push_back(son3);
	vectorSound.push_back(son4);
	vectorSound.push_back(son5);
	m_Vumeter=vu;
	cout<<"creation d'un AnalogSensorLuminositySoundDevice avec succès"<<endl; 

}


void AnalogSensorLuminositySoundDevice::run(){
	while (1){
		val=luminosite_environnement;
		alea=1-alea;
		if(ptrmem!=NULL){
		  *ptrmem=val+alea;
		  int intensity = *ptrmem/((VAL_MAX_ANALOG_SENSOR_LUM-VAL_MIN_ANALOG_SENSOR_LUM)/5);		  // attention, nb sons codé en dur
		  vectorSound[intensity].playSound();
		  m_Vumeter->setIntensity(intensity);
		}
		sleep(temps);
	}
}


void ButtonSoundDevice::run(){
  while(1){
    if(ifstream(fileButton)){
      val=1;
      *ptrmem=val;
      sound.playSound();
    }
    else{
      val=0;
      *ptrmem=val;
    }
    sleep(temps);
  }
}

 Instrument::Instrument(ButtonSoundDevice BSD1,ButtonSoundDevice BSD2, AnalogSensorLuminositySoundDevice LSD1){
	 modules.push_back(BSD1);
	 modules.push_back(BSD2);
	 modules.push_back(LSD1);
	 state=0;
 }

void Instrument::run(){
	if (state==1){
		for (int i=0;i<modules.size();i++){
			modules[i].run();
		}
	}
	else {
		cout<<"instrument eteint"<<endl;
	}

}