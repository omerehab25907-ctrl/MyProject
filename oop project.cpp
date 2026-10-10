#include <iostream>
#include <string>
#include <algorithm>
#include "Image_Class.h"

using namespace std;

// Filter 3: Invert Image
void filter_Invert(Image& img) {
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            for (int k = 0; k < img.channels; ++k) {
                img(i, j, k) = 255 - img(i, j, k);
            }
        }
    }
}

// Filter 7: Darken and Lighten Image
void filter_LightenDarken(Image& img, bool lighten) {
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            for (int k = 0; k < img.channels; ++k) {
                int val = img(i, j, k);
                if (lighten) {
                    val = val + (255 - val) * 0.5;
                }
                else {
                    val = val * 0.5;
                }
                img(i, j, k) = min(255, max(0, val));
            }
        }
    }
}

// Filter 11: Resizing Images
void filter_Resize(Image& img, int newWidth, int newHeight) {
    Image target(newWidth, newHeight);
    double scaleX = (double)img.width / newWidth;
    double scaleY = (double)img.height / newHeight;

    for (int i = 0; i < newWidth; ++i) {
        for (int j = 0; j < newHeight; ++j) {
            int srcX = i * scaleX;
            int srcY = j * scaleY;
            for (int k = 0; k < img.channels; ++k) {
                target(i, j, k) = img(srcX, srcY, k);
            }
        }
    }
    img = target;
}

// Filter 15: TV Effect
void filter_TVEffect(Image& img) {
    for (int j = 0; j < img.height; ++j) {
        if (j % 2 == 0) {
            for (int i = 0; i < img.width; ++i) {
                for (int k = 0; k < img.channels; ++k) {
                    img(i, j, k) = img(i, j, k) * 0.5;
                }
            }
        }
    }
}

int main() {
    string filename;
    cout << "Enter input image filename: ";
    cin >> filename;

    Image img(filename);
    int choice;

    while (true) {
        cout << "\n--- Image Processing Menu ---\n";
        cout << "1. Filter 3: Invert Image\n";
        cout << "2. Filter 7: Lighten / Darken Image\n";
        cout << "3. Filter 11: Resize Image\n";
        cout << "4. Filter 15: TV Effect\n";
        cout << "5. Save and Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1) {
            filter_Invert(img);
            cout << "Invert filter applied.\n";
        }
        else if (choice == 2) {
            int subChoice;
            cout << "1. Lighten\n2. Darken\nChoice: ";
            cin >> subChoice;
            filter_LightenDarken(img, subChoice == 1);
            cout << "Lighten/Darken filter applied.\n";
        }
        else if (choice == 3) {
            int w, h;
            cout << "Enter new width: ";
            cin >> w;
            cout << "Enter new height: ";
            cin >> h;
            filter_Resize(img, w, h);
            cout << "Resize filter applied.\n";
        }
        else if (choice == 4) {
            filter_TVEffect(img);
            cout << "TV Effect filter applied.\n";
        }
        else if (choice == 5) {
            string outFilename;
            cout << "Enter output image filename: ";
            cin >> outFilename;
            img.saveImage(outFilename);
            cout << "Image saved successfully. Exiting...\n";
            break;
        }
        else {
            cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}