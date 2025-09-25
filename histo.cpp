#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include "ImageBase.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc > 1) {
        string inputFile = argv[1];
        ImagePGM img;

        img.load(inputFile);

        int width = img.width();
        int height = img.height();

        vector<int> histo(256, 0);

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int pixel = img(x, y);
                histo[pixel]++;
            }
        }

        ofstream outfile("histogramme.dat");

        if (!outfile) {
            cerr << "Erreur : impossible de créer le fichier histogramme.dat" << endl;
            return 1;
        }

        for (int i = 0; i < 256; i++) {
            outfile << i << " " << histo[i] << endl;
        }

        outfile.close();
        cout << "Histogramme écrit dans histogramme.dat" << endl;
    }
    else {
        cout << "Donnez un fichier .pgm en paramètre" << endl;
    }

    return 0;
}