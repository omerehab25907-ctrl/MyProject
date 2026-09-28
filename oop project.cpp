#include <iostream>
#include <string>
#include <algorithm>
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

void lightenDarkenFilter(Image& img, char choice) {
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            for (int k = 0; k < img.channels; ++k) {
                if (choice == 'l' || choice == 'L') {
                    img(i, j, k) = min(255, (int)(img(i, j, k) * 1.5));
                }
                else if (choice == 'd' || choice == 'D') {
                    img(i, j, k) = (int)(img(i, j, k) * 0.5);
                }
            }
        }
    }
}

int main() {
    string filename;
    cout << "Enter image filename to load: ";
    cin >> filename;

    Image img(filename);

    cout << "\nChoose Filter:\n";
    cout << "3. Invert Image\n";
    cout << "7. Lighten / Darken Image\n";
    cout << "Choice: ";
    int choice;
    cin >> choice;

    if (choice == 3) {
        invertFilter(img);
    }
    else if (choice == 7) {
        cout << "Enter (L) to Lighten or (D) to Darken: ";
        char mode;
        cin >> mode;
        lightenDarkenFilter(img, mode);
    }

    string saveName;
    cout << "Enter filename to save image: ";
    cin >> saveName;

    img.saveImage(saveName);
    cout << "Filter applied and image saved successfully!\n";

    return 0;
}