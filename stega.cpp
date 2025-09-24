#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include "ImageBase.h"

using namespace std;

void valeursPair(char * filename)
{
	//ImagePGM valPair;
	//valPair.load(filename);

	//valPair.save("imgPair.pgm");
}

void imageDecode(char * filename)
{

}

void imageEncode(char * filename1,char * filename2)
{
	
}

int main(int argc, char** argv) {
	if(argc > 1)
	{  
		valeursPair(argv[1]);
//		imageEncode("imgPair.pgm","secret.pgm");
//		imageDecode("lena_riendesuspect.pgm");		
	}
	else
		cout << "Donnez un fichier .pgm en paramètre" << endl;

  	return 0;
}