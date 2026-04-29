#ifndef CARS_H
#define CARS_H
#include <bits/stdc++.h>
#include<windows.h>
#include"users.h"
#define dbg(x) cout << #x << "=" << x << endl;
using namespace std;
int const  N = 3000;
int highlitedCarId = 1;
int nextCar= 4;

struct Date
{
    int day;
    int month;
    int year;
};

struct Booking
{
    Date from;
    Date to;
};

struct Car
{
    int Id;
    int ownerId;
    string Brand;
    string Model;
    string Color;
    double Distance_Traveled;
    double dayPrice;
    Booking Bookings[N];
    int nOfBookings;
    bool isDeleted;
};

Car cars[N] = {
    {1, 0, "Toyota", "Corolla", "White", 45230.5, 600, false},
    {2, 0, "Hyundai", "Elantra", "Black", 31890.0, 700, false},
    {3, 0, "Kia", "Sportage", "Red", 27440.8, 600, false}
};


void AddCar() {
    system("cls");

    char choice;
    Car c;
    while (true) {
        c.Id = nextCar;
        c.ownerId = loggedUserId; 
        cout << "Enter Car Brand: ";
        cin >> c.Brand;
        cout << "\nEnter Car Model: ";
        cin >> c.Model;
        cout << "\nEnter Car Color: ";
        cin >> c.Color;
        cout << "\nEnter Distance Traveled By Car: ";
        cin >> c.Distance_Traveled;
        cout << "\nEnter Car Day Price: ";
        cin >> c.dayPrice;
        cout << "Car Added Successfully!\n";

        cout << "Do You Want To Add Another Car? (y/n): ";
        cin >> choice;
        if (choice == 'n' || choice == 'N')
            break;
    }

    ofstream file("cars.txt", ios::app);
    file << c.Id << '|' << c.ownerId << '|' << c.Brand << '|' << c.Model << '|';
    file << c.Color << '|' << c.Distance_Traveled << '|';
    file << c.dayPrice << '|' << "false" << ';' << '\n';
    file.close();
    nextCar++;
}


void DisplayCarInfoSummary(Car car) {
    cout << "Brand: " << car.Brand << " | Model: " << car.Model << " | Color: " << car.Color << '\n';
}

void DisplayCarInfoSummaryHighlighted(Car car) {
     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleTextAttribute(hConsole, 14);
     DisplayCarInfoSummary(car);
     SetConsoleTextAttribute(hConsole, 7);
}

int GetNextHighltedCarId(int currentHighlightedCarId, char pressedKey) {
    
    int cntChecked = 0;
    if(pressedKey == 72) {
        while(cntChecked < nextCar - 1) {
            currentHighlightedCarId--;
            int carId = (currentHighlightedCarId >= 1)? currentHighlightedCarId : currentHighlightedCarId + nextCar - 1;
            if(!cars[carId - 1].isDeleted)
                return carId;

            cntChecked++;
        }
    }
    else if(pressedKey == 80){
        while(cntChecked < nextCar - 1) {
            currentHighlightedCarId++;
            int carId = (currentHighlightedCarId >= nextCar)? currentHighlightedCarId - nextCar + 1 : currentHighlightedCarId;
            if(!cars[carId - 1].isDeleted)
                return carId;

            cntChecked++;
        }
    }
    return -1;
}

void ListCars() {
    system("cls");
    
    for(auto i : cars) {
        if(!i.Id)
            break;
        
        if(i.isDeleted)
            continue;
        
        if(i.Id == highlitedCarId)
            DisplayCarInfoSummaryHighlighted(i);
        else
            DisplayCarInfoSummary(i);
    
    }

    cout << "If You Want To Add Car Click 1\n";
    cout << "If You Want To Remove This Car Click 2\n";
    cout << "If You Want To Update This Car Click 3\n";
}


void DisplayCarInfo(Car car) {
    cout << "*****************\n";
    cout << "     CAR INFO    \n";
    cout << "*****************\n";

    cout << "BRAND : " << car.Brand << '\n';
    cout << "MODEL : " <<car.Model << '\n';
    cout << "COLOR : " << car.Color << '\n';
    cout << "DISTANCE TRAVELED : " << car.Distance_Traveled << '\n';
    cout << "Day PRICE : " << car.dayPrice << '\n';
}

void DisplayCarInfoById( int id ) {
    system("cls");

    //for (int i = 0; i < N; i++)
        //if (cars[i].Id ==  id) {
            DisplayCarInfo(cars[id - 1]);
        //}
}

void RemoveCar() {
    //for (auto &i : cars) {
        //if(!i.Id)
            //return;

        if (cars[highlitedCarId - 1].ownerId == loggedUserId) {
            cars[highlitedCarId - 1].isDeleted = true;
            //cout << "deleting car with id: " << i.Id << '\n';
            //cout << "isdeleted: " << i.isDeleted << '\n';
        }
        else
            cout << "You Can`t Delete This Car\n";
    //}
    
}

void UpdateCarInfo () {
    system("cls");
    if (loggedUserId != cars[highlitedCarId - 1].ownerId) {
        cout << "You Can`t Update This Car\n";
        return;
    }    
    char order;
    string color;
    double distanceTraveled, price;
    cout << "Change Color Click c \n";
    cout << "Change Distance Traveled Click d \n";
    cout << "Change Price Click p \n";
    cin >> order;
    switch (order) {
        case 'c':
            cout << "Enter The New Color: ";
            cin >> color;
            cars[highlitedCarId - 1].Color = color;
            break;
        case 'd':
            cout << "Enter The New Distance Traveled: ";
            cin >> distanceTraveled;
            cars[highlitedCarId - 1].Distance_Traveled = distanceTraveled;
            break;
        case 'p':
            cout << "Enter The New Day Price: ";
            cin >> price;
            cars[highlitedCarId - 1].dayPrice = price;
            break;
    }
}

void ResavingDataInFileAfterChange () {
    ofstream file("cars.txt");
    for (auto i : cars) 
        if (i.Id) {
            file << i.Id << '|' << i.ownerId <<'|' << i.Brand << '|';
            file << i.Model << '|' << i.Color << '|' << i.Distance_Traveled << '|';
            file << i.dayPrice << '|' << i.isDeleted << ';' << '\n';
        }

    file.close();
    
}

Car ParseCar (string carRow) {
    Car parsedCar;
    string carId, ownerId, distanceTraveled, isDeleted, dayPrice;
    stringstream carStream(carRow);
    getline(carStream, carId, '|');
    parsedCar.Id = stoi(carId);
    getline(carStream, ownerId, '|');
    parsedCar.ownerId = stoi(ownerId);
    getline(carStream, parsedCar.Brand, '|');
    getline(carStream, parsedCar.Model, '|');
    getline(carStream, parsedCar.Color, '|');
    getline(carStream, distanceTraveled, '|');
    parsedCar.Distance_Traveled = stod(distanceTraveled);
    getline(carStream, dayPrice, '|');
    parsedCar.dayPrice = stod(dayPrice);
    getline(carStream, isDeleted, ';');
    if (stoi(isDeleted) == 0)
        parsedCar.isDeleted = false;
    else
        parsedCar.isDeleted = true;

    return parsedCar;  
}

void SavingCarDataInStruct (Car c) {
    int index = c.Id - 1;
    cars[index].Id = c.Id;
    cars[index].ownerId = c.ownerId;
    cars[index].Brand = c.Brand;
    cars[index].Model = c.Model;
    cars[index].Color = c.Color;
    cars[index].Distance_Traveled = c.Distance_Traveled;
    cars[index].dayPrice = c.dayPrice;
    cars[index].isDeleted = c.isDeleted;
}

void SavingCarDataFromFileToArray () {
    ifstream file("cars.txt");
    string s;
    while (getline(file, s)) {
        Car c = ParseCar(s);
        SavingCarDataInStruct(c);
    }
    file.close();
}

void UpdateNextCar () {
    for (int i = 0; i < N; i++) 
        if (cars[i].Id == 0) {
            nextCar = i + 1;
            break;
        }
}

void RentCar (int id, Booking b) {

}

bool IsDate_A_GreaterThanDate_B (Date a, Date b) {
    if (a.year > b.year)
        return true;
    else if (a.year == b.year) {
        if (a.month > b.month) 
            return true;
        else if (a.month == b.month) {
            if (a.day > b.day)
                return true;
        }
    }
    return false;
}

bool IsBookingValid (Booking b1, Booking b2) {
    if (IsDate_A_GreaterThanDate_B(b1.from, b2.to) || IsDate_A_GreaterThanDate_B(b2.from, b1.to))
        return true;
    return false;
}

bool CheckCarAvailability (int id, Booking b) {
    for (int i = 0; i < cars[id - 1].nOfBookings; i++) {
        if (!IsBookingValid(cars[id - 1].Bookings[i], b))
            return false;
    }
return true;
}

int CalculateBookingDays (Date from, Date to) {
    return 0;
}

double CalculateBookingPrice (int id, Booking b) {
    return 0;
}

bool ProcessPayment (double price) {
return true;
}

void AddBooking (int id, Booking b ) {
    int nextBookingIndex = cars[id - 1].nOfBookings;
    cars[id - 1].Bookings[nextBookingIndex] = b;
    cars[id - 1].nOfBookings++;
}



#endif