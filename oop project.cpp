#include <iostream>
#include <string>
#include "Image_Class.h"
using namespace std;


void invertFilter(Image& img) {
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            for (int k = 0; k < img.channels; ++k) {
                img(i, j, k) = 255 - img(i, j, k);
            }
        }
    }
}

int main() {
    string filename;
    cout << "Enter image filename to load: ";
    cin >> filename;
    Image img(filename);
    invertFilter(img);
    string saveName;
    cout << "Enter filename to save inverted image: ";
    cin >> saveName;
    img.saveImage(saveName);
    cout << "Filter applied and image saved successfully!" << endl;

    return 0;
}