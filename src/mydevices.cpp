#include "mydevices.h"

using namespace std;

extern int luminosite_environnement=200;
extern int VAL_MAX_ANALOG_SENSOR_LUM = 200;
extern int VAL_MIN_ANALOG_SENSOR_LUM = 5;
extern int VAL_MAX_ULTRASOUND = 200;
extern int VAL_MIN_ULTRASOUND = 10;


void Sound::playSound(){
  cout << " ****** "+soundTag+" playing  " <<" ****** " << endl;
  son.play();
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


AnalogSensorUltrasoundSoundDevice::AnalogSensorUltrasoundSoundDevice(int t,Vumeter *vu):AnalogSensorLuminosity(t){
	m_Vumeter=vu;
	nbSounds=0;
	cout<<"creation d'un AnalogSensorUltrasoundSoundDevice avec succès"<<endl; 
}


void AnalogSensorUltrasoundSoundDevice::addSound(Sound son){
  vectorSound.push_back(son);
  nbSounds+=1;
}


int AnalogSensorUltrasoundSoundDevice::getValProximity(){
  ifstream file("PROXIMITY.txt");
  int valProx=0;
  if(file){
    string line;
    while(getline(file, line)){
      valProx=stoi(line);
    }
  }
  else
    valProx=-1;
  file.close();
  return valProx;
}


void AnalogSensorUltrasoundSoundDevice::run(){
	while (1){
		int aux_val=getValProximity();
	        if(aux_val != -1)
		  val=aux_val;
		alea=1-alea;
		if(ptrmem!=NULL){
		  *ptrmem=val+alea;
		  int intensity = *ptrmem/((VAL_MAX_ULTRASOUND-VAL_MIN_ULTRASOUND)/nbSounds);
		  if( intensity < nbSounds){
		    vectorSound[intensity].playSound();
		    m_Vumeter->setIntensity(intensity);
		  }
		  else
		    m_Vumeter->setIntensity(0);
		}
		sleep(temps);
	}
}


AnalogSensorLuminositySoundDevice::AnalogSensorLuminositySoundDevice(int t,Vumeter *vu):AnalogSensorLuminosity(t){
	m_Vumeter=vu;
	nbSounds=0;
	cout<<"creation d'un AnalogSensorLuminositySoundDevice avec succès"<<endl; 
}


void AnalogSensorLuminositySoundDevice::addSound(Sound son){
  vectorSound.push_back(son);
  nbSounds+=1;
}


int AnalogSensorLuminositySoundDevice::getValLum(){
  ifstream file("LUM_ENV.txt");
  int valLum=0;
  if(file){
    string line;
    while(getline(file, line)){
      valLum=stoi(line);
    }
  }
  else
    valLum=-1;
  file.close();
  return valLum;
}


void AnalogSensorLuminositySoundDevice::run(){
	while (1){
      	        int aux_val=getValLum();
	        if(aux_val != -1)
		  val=aux_val;
		alea=1-alea;
		if(ptrmem!=NULL){
		  *ptrmem=val+alea;
		  int intensity = *ptrmem/((VAL_MAX_ANALOG_SENSOR_LUM-VAL_MIN_ANALOG_SENSOR_LUM)/nbSounds);
		  if(intensity >= nbSounds)
		    intensity = nbSounds-1; // si on est supérieur à la valeur max, on maintien le son correspondant à l'intensité max, c'est la différence avec l'ultrason
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
