#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include "ImageBase.h"

using namespace std;

int main(int argc, char** argv) {
	ImagePGM histogramme;
	//histogramme.load("monImage.pgm");

	if(argc > 1)
	{  
		//ofstream outfile("nomFichier.dat");
		
		//outfile << "j'ai ecris un truc dedans ..." << endl;

	  	//outfile.close();
	}
	else
		cout << "Donnez un fichier .pgm en paramètre" << endl;

  	return 0;
}