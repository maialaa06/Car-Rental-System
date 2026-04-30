#include <bits/stdc++.h>
#include <conio.h>
#include "cars.h"
#define dbg(x) cout << #x << "=" << x << endl;
using namespace std;

void RestoreAppState () {
    LoadUsersDataFromFile();
    LoadCarsDataFromFile();
}

void WelcomeScreen() {
    system("cls");
    cout << "==================================\n";
    cout << "   WELCOME TO CAR RENTAL SYSTEM   \n";
    cout << "==================================\n\n\n";

    string order;
    cout << "1 - Sign Up\n";
    cout << "2 - Sign In\n";
    cout << "Enter your choice: ";        

    while(true) {
        getline(cin, order);
        if (order == "1") {
            SignUp();
            LoadUsersDataFromFile();
            SignIn();
            break;
        }
        else if (order == "2") {
            SignIn();
            break;
        }
        cout << "Enter a Valid  Choice\n";
    }

    ListCars();
    char pressedkey;
    while (true){
        pressedkey = _getch();
        //cout << "pre: " << pressedkey << '\n'; 
        switch(pressedkey) {
            // up arrow
            // down arrow
            case 72:
            case 80:
                highlitedCarId = GetNextHighltedCarId(highlitedCarId, pressedkey);
                ListCars();
                break;
            // enter key
            case 13:
                DisplayCarInfoById(highlitedCarId);
                break;
            // 1 to add car
             case 49:
                 AddCar();
                 LoadCarsDataFromFile();
                 ListCars();
                 break;
            // 2 to remove car
            case 50:
                RemoveCar();                                
                break;
            // 3 to update car
            case 51:
                UpdateCarInfo();        
                break;
            // 4 to rent car
            case 52:
                RentCar(cars, nextCar, highlitedCarId);                
                break;
            // 5 to return car
            case 53:
                ReturnCar(cars, nextCar, highlitedCarId);
                break;
            // 6 check available
            case 54:
                check_out_car(cars, nextCar, highlitedCarId);
                break;
            // 7 list available cars
            case 55:
                list_available_cars(cars, nextCar);
                break;
            // 8 to logout
            case 56:
                WelcomeScreen();
            // 0 to exit
            case '0':
                return;
        }
    }
}

int main () {
    RestoreAppState();
    WelcomeScreen();


    system("pause");
    return 0;
}


