#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void creerFichier(string nomFichier){
  ofstream fichier(nomFichier.c_str());
  fichier.close();
}

void ecrireFichierVal(string loc, int val){
  ofstream fichier(loc.c_str());
  fichier << val << endl;
  fichier.close();
}


int main(){
  string son_bouton1("SonsBoutons/son1.txt");
  string son_bouton2("SonsBoutons/son2.txt");
  string locLuminosity("LUM_ENV.txt");
  string locProximity("PROXIMITY.txt");
  int tabLum[10]= {10,100,35,175,85,205,120,2,50,190};
  int tabProx[10]= {100,175,50,2,205,10,35,190,250,85};
  int index=0;
  
  while(1){
    for(int i=0; i<4;i++){
      if(i==0){
		creerFichier(son_bouton2);
		 ecrireFichierVal(locLuminosity,tabLum[(index)%10]);
      }
      if(i==2){
		  creerFichier(son_bouton2);
      }     
	  creerFichier(son_bouton1);
	  ecrireFichierVal(locProximity,tabProx[index%10]);
	  
      sleep(1);
      remove(son_bouton1.c_str());
      remove(son_bouton2.c_str());
	  index+=1;
    }

  }
}
