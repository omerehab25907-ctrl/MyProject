#include <iostream>
#include <algorithm>
#include "Image_Class.h"

using namespace std;

void filter_Grayscale(Image& img) {
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            int avg = (img(i, j, 0) + img(i, j, 1) + img(i, j, 2)) / 3;
            img(i, j, 0) = avg;
            img(i, j, 1) = avg;
            img(i, j, 2) = avg;
        }
    }
}

void filter_BlackAndWhite(Image& img) {
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            int avg = (img(i, j, 0) + img(i, j, 1) + img(i, j, 2)) / 3;
            int bw = (avg >= 128) ? 255 : 0;
            img(i, j, 0) = bw;
            img(i, j, 1) = bw;
            img(i, j, 2) = bw;
        }
    }
}

void filter_Invert(Image& img) {
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            for (int k = 0; k < img.channels; ++k) {
                img(i, j, k) = 255 - img(i, j, k);
            }
        }
    }
}

void filter_Merge(Image& img1, Image& img2, Image& mergedImg) {
    int minW = min(img1.width, img2.width);
    int minH = min(img1.height, img2.height);
    mergedImg = Image(minW, minH);

    for (int i = 0; i < minW; ++i) {
        for (int j = 0; j < minH; ++j) {
            for (int k = 0; k < img1.channels; ++k) {
                mergedImg(i, j, k) = (img1(i, j, k) + img2(i, j, k)) / 2;
            }
        }
    }
}

int main() {
    string filename;
    cout << "Enter the image file name to load: ";
    cin >> filename;

    Image img(filename);

    int choice;
    do {
        cout << "\n--- filters Menu ---\n";
        cout << "1. Grayscale Filter\n";
        cout << "2. Black and White Filter\n";
        cout << "3. Invert Image Filter\n";
        cout << "4. Merge Images\n";
        cout << "5. Save Image\n";
        cout << "0. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1) {
            filter_Grayscale(img);
            cout << "Grayscale filter applied successfully!\n";
        }
        else if (choice == 2) {
            filter_BlackAndWhite(img);
            cout << "Black and White filter applied successfully!\n";
        }
        else if (choice == 3) {
            filter_Invert(img);
            cout << "Invert filter applied successfully!\n";
        }
        else if (choice == 4) {
            string filename2;
            cout << "Enter the second image file name to merge: ";
            cin >> filename2;
            Image img2(filename2);
            Image mergedImg;
            filter_Merge(img, img2, mergedImg);
            img = mergedImg;
            cout << "Images merged successfully!\n";
        }
        else if (choice == 5) {
            string outputFilename;
            cout << "Enter the output image filename (e.g., output.jpg): ";
            cin >> outputFilename;
            img.saveImage(outputFilename);
            cout << "Image saved successfully!\n";
        }
        else if (choice == 0) {
            cout << "Exiting program. Goodbye!\n";
        }
        else {
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}