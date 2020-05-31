#include <unistd.h>
#include "core_simulation.h"
#include <vector>
#include	"mydevices.h"
#define NB_LED 5
#define NB_VUMETRE 2
// la fonction d'initialisation d'arduino
void Board::setup(){
  // on configure la vitesse de la liaison
  Serial.begin(9600);
// on fixe les pin en entree et en sorite en fonction des capteurs/actionneurs mis sur la carte
  pinMode(0,OUTPUT);
  pinMode(1,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);

}

// la boucle de controle arduino
void Board::loop(){
  char buf[100];
  int val5;
  int val6;
  static int cpt=0;
  static int bascule=0;
  int i=0;
  vector <DigitalActuatorLED> vecteurLED;
  vector <int> tabPinLED = {0,1,2,3,4,5,6,7,8,9};
  for(int j=0;j<NB_VUMETRE;j++){
	  for(int i=0;i<vecteurLED.size();i++){
		  if(vecteurLED[i].getState() == HIGH){
			  if(j==0){
				digitalWrite(tabPinLED[i],HIGH);
			  }
			else {
				digitalWrite(tabPinLED[NB_LED+i],HIGH);
			}
		  }
		else{
			if(j==0){
				digitalWrite(tabPinLED[i],LOW);
			}
			else {
				digitalWrite(tabPinLED[NB_LED+i],LOW);
			}
		}
	  }
  }
  
  
  
  
  for(i=0;i<10;i++){
/*     // lecture sur la pin 1 : capteur de temperature
    val=analogRead(1);
    sprintf(buf,"temperature %d",val);
	Serial.println(buf);
    if(cpt%5==0){
        // tous les 5 fois on affiche sur l ecran la temperature
      sprintf(buf,"%d",val);
      bus.write(1,buf,100);
    }
       	// lecture sur la pin 2 : capteur de luminosite
	 val2=analogRead(2);
	 sprintf(buf,"luminosity %d",val2);
	 Serial.println(buf);
	 if(cpt%5==0){
	   sprintf(buf,"%d",val2);
	   bus.write(1,buf,100);
	 }
	 // lecture sur la pin 4 : button externe
	 val4=analogRead(4);
	 sprintf(buf,"etat bouton %d",val4);
	 Serial.println(buf);
	 if(cpt%5==0){
	   sprintf(buf,"%d",val4);
	   bus.write(1,buf,100);
	 } */
	  // lecture sur la pin 5 : vumetre
	 //val5=analogRead(5);
	 //val6=analogRead(6);

	 
    cpt++;
    sleep(1);
  }
/* on eteint et on allume la LED
  if(bascule){
    digitalWrite(0,HIGH);
    digitalWrite(3,HIGH);
  }
  else{
    digitalWrite(0,LOW);
    digitalWrite(3,LOW);
  }
  bascule=1-bascule; */
  
  cout<< "\n";
}


