#include <bits/stdc++.h>
#include <conio.h>
#include "cars.h"
#define dbg(x) cout << #x << "=" << x << endl;
using namespace std;

int main () {
     //ios::sync_with_stdio(false);
     //cin.tie(NULL);
    char order;
    cout << "If You Don`t Have An Account Click r\n";
    cout << "Otherwise Click l\n";
    cin >> order;
    if (order == 'r') {
        UpdateNextUser();
        Registeration();
        SavingUserDataFromFileToArray();
        Login();
    }    
    else if (order == 'l') {
        SavingUserDataFromFileToArray();
        Login();
    }

    SavingCarDataFromFileToArray();
    UpdateNextCar();
    ListCars();
    
    char pressedkey;
    while (true) {
        
        //cout << car[3].ownerId << '\n';
        pressedkey = _getch();
        //cout << "pre: " << pressedkey << '\n'; 
        switch(pressedkey) {
            case 49:
                AddCar();
                SavingCarDataFromFileToArray();
                break;
            // up arrow
            case 72:
                // down arrowxhjkl;eweruio67890
            case 80:
                highlitedCarId = GetNextHighltedCarId(highlitedCarId, pressedkey);                
                ListCars();
                break;
            case 13:
                DisplayCarInfoById(highlitedCarId);
                break;
            case 50:
                RemoveCar();
                ResavingDataInFileAfterChange();
                //cout << car[3].isDeleted << '\n';
                break;
            case 51:
                UpdateCarInfo();
                ResavingDataInFileAfterChange();
                break;
            case '0':
                return 0;

        }
    }

    system("pause");

    return 0;
}



