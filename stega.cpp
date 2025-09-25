#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include "ImageBase.h"

using namespace std;

void valeursPair(char * filename)
{
	ImagePGM valPair;

    valPair.load(filename);

    int width = valPair.width();
    int height = valPair.height();

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int pixel = valPair(x, y);
            if (pixel % 2 != 0) {
                valPair(x, y) = pixel - 1;
            }
        }
    }

    valPair.save("imgPair.pgm");
    cout << "Image sauvegardée sous imgPair.pgm" << endl;
}

void imageDecode(char * filename)
{
	ImagePGM src;
    src.load(filename);

    int width = src.width();
    int height = src.height();
    ImagePGM decoded(width, height);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int pixel = src(x, y);
            if (pixel % 2 == 0)
                decoded(x, y) = 0;
            else
                decoded(x, y) = 255;
        }
    }

    decoded.save("decoded.pgm");
    cout << "Image décodée sauvegardée sous decoded.pgm" << endl;
}

void imageEncode(char * filename1, char * filename2)
{
	ImagePGM cover, secret;

    cover.load(filename1);
    secret.load(filename2);

    int width = cover.width();
    int height = cover.height();

    if (secret.width() != width || secret.height() != height) {
        cout << "Les images doivent avoir les mêmes dimensions !" << endl;
        return;
    }

    ImagePGM encoded(width, height);

    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            int pixelCover = cover(x, y);
            int pixelSecret = secret(x, y);

            int newPixel = (pixelCover & ~1) | (pixelSecret > 0 ? 1 : 0);
            encoded(x, y) = newPixel;
        }
    }

    encoded.save("encoded.pgm");
    cout << "Image encodée sauvegardée sous encoded.pgm" << endl;
}

int main(int argc, char** argv) {
	if (argc > 1)
	{  
		valeursPair(argv[1]);
		imageEncode("lena.pgm", "ovmz.pgm");
        imageDecode("lena_riendesuspect.pgm");		
	}
	else
		cout << "Donnez un fichier .pgm en paramètre" << endl;

  	return 0;
}