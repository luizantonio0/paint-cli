#include <iostream>
#include <fstream>
#include "Draw.cc"

#define RED {0, 0, 255}
#define BLUE {255, 0, 0}
#define GREEN {0, 255, 0}


using namespace std;

Color printColors() {
    int option;
    cout << "Colors available:" << endl;
    cout << "1. RED " << endl;
    cout << "2. BLUE " << endl;
    cout << "3. GREEN " ;
    cin >> option;
    switch (option) {
        case 1:
            return RED;
        case 2:
            return BLUE;
        case 3:
            return GREEN;
        default:
            cout << "Invalid option. Defaulting to RED." << endl;
            return RED;
    }
}
int printSize()
{
    int size;
    cout << "Enter circle size (1-400): ";
    cin >> size;
    if (size < 1 || size > 400) {
        cout << "Invalid size. Defaulting to 200." << endl;
        return 200;
    }
    return size;
}

int main() {
    cout << "Paint CLI, started!" << endl;
    Canva canva = Canva("canva.bmp", 800, 800);
    IDraw* drawService = new DrawCircle();

    while (1){
        int option;

        cout << "Choose an option:" << endl;
        cout << "1. Draw a circle" << endl;
        cout << "2. Exit" << endl;
        cin >> option;
        

        switch (option) {
            case 1:{
                Color color = printColors();
                int size = printSize();
                drawService->draw(canva, 400, 400, size, color);
                break;}
            case 2:
                cout << "Exiting Paint CLI." << endl;
                return 0;
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    }

    return 0;
}
