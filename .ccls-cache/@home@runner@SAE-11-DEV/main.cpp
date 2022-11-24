#include <cstdlib>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <chrono>
#include <thread>

using namespace std;

template <class Rep, class Period> //Crée un petit délai entre le joueur et ordinateur
void sleep_for (const chrono::duration<Rep,Period>& rel_time);

void saisie(string *nom, int *nb_allumette, char *difficulte, string *prem) {	//Procédure saisie
	cout << "Quel est le nom du joueur ?" << endl; // nom du joueurs
	cin >> *nom;
	do {
		cout << "Choisissez le nombre d'allumettes de départ"<< endl; // nombre alumette de départ
		cin >> *nb_allumette;
		if ((*nb_allumette > 30) || (*nb_allumette < 1)) { // Si nombre alumette n'est pas entre 1 et 30
			cout << "Le nombre d'allumettes doit être compris entre 1 et 30 "<< endl;
		}
	} while ((*nb_allumette > 30) || (*nb_allumette < 1));
	do {
		cout << "Quel niveau de difficulté choisissez-vous pour l'ordinateur ? N - naif : E - Expert "<< endl; // Défini la difficulté
		cin >> *difficulte;
    if ((*difficulte != 'N') && (*difficulte != 'e') &&
			 (*difficulte != 'n') && (*difficulte != 'E')) { // Si entre une autre caratère
			cout << "Ce niveau n'existe pas. Erreur réssayez !"<< endl;
		}
	} while ((*difficulte != 'e') && (*difficulte != 'E') && //Redemande tant que n et e n'est pas saisie
			 (*difficulte != 'n') && (*difficulte != 'N'));
do{
	cout << "Qui commence à jouer en 1er ? Taper le nom du joueur ou 'ordi'. "; // Définir qui commence
	cin >> *prem;
  if ((*prem!=*nom)&&(*prem!="ordi")){ //Si entre une autre chose
    cout<<"Erreur de saisie : Taper le nom du joueur ("<<*nom<<") ou taper 'ordi'"<<endl;
  }
}while((*prem!=*nom)&&(*prem!="ordi")); //Répète si le nom ou ordi n'est pas encore saisie
}

void affiche(int nb_allumette) {  //Procédure Affiche les allumette
	int i, j, reste;
	reste = nb_allumette % 5;
	for (i = 1; i <= (nb_allumette - reste) / 5; i++) { // Tri de 5 alumettes par ligne
		for (j = 1; j <= 5; j++) {
			cout << " ! ";
		}
		cout << endl;
	}
	for (i = 1; i <= reste; i++) { // Tri des dernière alumettes sur la dernière ligne
		cout << " ! ";
	}
	cout << endl << endl;
}

void jeualterne(string *tour, char *difficulte, string *nom, int *nb_allumette) {
	int joueOrdi_N(int nb_allumette),jouejoueur(int nb_allumette, string nom),joueOrdi_E(int nb_allumette);
	int retir = 0;
	srand(time(NULL));
	if ((*tour == "ordi")) { //Si tour ordinateur alors
		if ((*difficulte == 'N') || (*difficulte == 'n')) {
			retir = joueOrdi_N(*nb_allumette); //Appelle la fonction si l'ordi est naîf
		} else {
			retir = joueOrdi_E(*nb_allumette); //Sinon appelle de la fonction ordi expert
		}
		*tour = *nom; //Une fois l'ordinateur joué passe le tour au joueur quand la procédure est de nouveau appelé
	}
  else{
	if ((*tour == *nom)) {  //Si tour joueur alors
		retir = jouejoueur(*nb_allumette, *nom); //Appelle la fonction de jouer le joueur
		*tour = "ordi"; //Une fois le joueur joué passe le tour à l'ordinateur quand la procédure est de nouveau appelé
	}}
	*nb_allumette = *nb_allumette - retir; //Retire le nombre allumette selon le nombre retiré par le joueur ou ordinateur
}

int joueOrdi_N(int nb_allumette) {  //Fonction joue ordinateur Naîf
	int retire;
	srand(time(NULL));
  do{
	retire = rand()%3+1; //Retire un nombre aléatoire entre 1 et 3
  }while(nb_allumette<retire); //Si Retire est plus grand que le nombre allumettes qui reste alors relance un nouveaux nombre
  cout<<"ORDI naïf à retirer "<<retire<<" alumette(s)"<<endl<<endl;
	return retire;
}

int joueOrdi_E(int nb_allumette) {  //Fonction joue ordinateur expert
int retire,k;
k=nb_allumette%4; //Prend le mod de 4
if(nb_allumette==1){ //Si il reste qu'une alumettes ordi retire la dernière
  retire=1;
}
else {
  switch(k){
    case 0 : retire = 3; break; //Si 4k alors retire 3 allumettes
    case 2 : retire = 1; break; //Si 4k+2 alors retire 1 allumette
    case 3 : retire = 2; break; //Si 4k+3 alors retire 3 allumettes
    default : retire = rand()%3+1; break; //Si 4k+1 alors la victoire n'est pas sertain donc retire un nombre aléatoire entre 1 et 3
  }
}
cout<<"ORDI expert à retirer "<<retire<<" alumette(s)"<<endl<<endl;
return retire;
}

int jouejoueur(int nb_allumette, string nom){
	int retire,abando=0;
  char p='n';
  cout<<"C'est au tour de "<<nom<<endl;
  do{
    cout<<"Choisissez le nombre alumette(s) à retirer"<<endl; //Saisir retire
  cin>>retire;
  if(retire>nb_allumette){ //Si retire autant allumette qui reste
    cout<<"Vous avez tenté de retirer autant allumette qui reste réssayer"<<endl;
  }
  else{
  if(retire>3)  //Si retire plus de 3 allumette
  {
    cout<<"Vous pouvez retirer maximum 3 allumette réssayez"<<endl<<endl;
  }
  else{
  if(retire<0){ //Si entre un nombre négatif
    cout<<"Vous ne pouvez pas entrer un nombre négatif, réssayez"<<endl<<endl;
  }
  else{
  
  if(retire==0){  //Si utilisateur qui souhaite abandonner
    abando=2;
    cout<<"Êtes vous sûr de vouloir abandonner ? O - oui | N - non ?"<<endl<<endl; //Demande confimation
    do{
    cin>>p;
    if ((p=='O') || (p=='o')){ //Confimation accepeter
    cout<<"Vous avez abandonné ."<<endl<<endl;
    retire=nb_allumette; //Retire tout les allumette afin d'avoir retire la dernière allumette
    abando=1;
  }
  else {
    if ((p=='n')||(p=='N')){  //Confimation refusé
      cout<<"Reprise du jeu"<<endl;
      abando=0;
    }
  }
  if (abando==2){  //Si entre une autre valeur
    cout<<"Erreur de saisie réssayez"<<endl;
  }
  }while(abando==2); //Répète si entre un autre valeur
  }
  }
  }
  }
  }while(((retire>nb_allumette)||(retire<1)||(retire>3)) && (abando==0)); //Répète si utilisateur entre pas un nombre valide si il continue à jouer
  if(abando==0){
  cout<<"Vous avez retiré "<<retire<<" alumette(s)"<<endl<<endl;
  }
	return retire;
}

int main() { // Début du programme
	int nb_allumette;
	string nom, prem;
	char difficultes;

	saisie(&nom,&nb_allumette,&difficultes,&prem); // Saisie des paramètre avant de commencer le jeu
    cout<<endl<<"Début de la partie"<<endl<<endl;
	while (nb_allumette > 0) { // Tant que le jeu n'est pas termine les fonctions execute en boucle
		affiche(nb_allumette); // Affiche nb_allumette chaque fois un tour est fini
    std::this_thread::sleep_for(std::chrono::seconds(1));
		jeualterne(&prem, &difficultes, &nom, &nb_allumette); // Execution d'un tour
	}
  if(prem=="ordi"){  //Annoce le gagnant de ordi
    cout<<"L'ORDI a gagné";
  }
  else
  {
    if (prem==nom){  //Annoce le ganant du joueur
      cout<<nom<<" a gagné !";
    }
  }
} // Fin du grogramme