#include <stdio.h>
#include <iostream>
#include <vector>
#include "ImageBase.h"

using namespace std;


void carre()
{
	ImagePGM carre(100,100);

	int debut = 30;
	int fin = 70;

	for (int y = debut; y < fin; y++) {
        for (int x = debut; x < fin; x++) {
            carre(x, y) = 255;
        }
    }

 	cout<< "l'image carré fait " << carre.width() << " par " << carre.height() << "pixels"<<endl;

 	cout<< "la valeur du pixel 10,15 est de " << (int)carre(10,15) <<endl;

	carre.save("carre_centre_blanc.pgm");
}

void damier()
{
	ImagePGM damier(100,100);

	for (int y = 0; y < 100; y++) {
		for (int x = 0; x < 100; x++) {
			if ((x/10 + y/10) % 2 == 0) {
                damier(x, y) = 255;
            } else {
                damier(x, y) = 0;
            }
		}
	}
 	
	damier.save("damier.pgm");
}

void degrade()
{
	ImagePGM degrade(100,100);
	
	for (int y = 0; y < 100; y++) {
        for (int x = 0; x < 100; x++) {
            int val = (x * 255) / 99; 
            degrade(x, y) = val;
        }
    }

	degrade.save("degrade.pgm");
}

void drapeau()
{
	//ImagePNG drapeau(100,150);
 	
	//drapeau.save("drapeau.png");
}

void transparence()
{
	//ImagePNG transparence(100,150);
 	
	//transparence.save("transparence.png");
}

void lineaire()
{
	//ImagePNG drapeau(100,150);
 	
	//drapeau.save("drapeau.png");
}

int main(int argc, char** argv) {
	carre();
	damier();
	degrade();
	drapeau();
	transparence();
	lineaire();
  	return 0;
}