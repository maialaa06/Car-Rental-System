#include <bits/stdc++.h>
#include <conio.h>
#include "cars.h"
#define dbg(x) cout << #x << "=" << x << endl;
using namespace std;

void RestoreAppState () {
    LoadUsersDataFromFile();
    LoadCarsDataFromFile();
}

int main () {
    //RestoreAppState();

    cout << "==================================\n";
    cout << "   WELCOME TO CAR RENTAL SYSTEM   \n";
    cout << "==================================\n\n\n";

    char order;
    cout << "1 - Sign Up\n";
    cout << "2 - Sign In\n";
    cin >> order;
    if (order == '1') {
        SignUp();
        LoadUsersDataFromFile();
        SignIn();
    }    
    else if (order == '2')
        SignIn();

    
        
    char pressedkey;
    ListCars();

    while (true){
        
        //cout << car[3].ownerId << '\n';
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
            // 0 to exit
            case '0':
                return 0;

        }
    }
    system("pause");

    return 0;
}


