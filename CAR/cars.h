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

struct VISA
{
	string cvv;
	string bank_name;
	string card_number;
	string holder_name;
	string expiry_date;
};

struct Car
{
    int Id;
    int OwnerId;
    int RenterId;
    string Brand;
    string Model;
    string Color;
    double Distance_Traveled;
    double Price;
    bool IsDeleted;
    bool IsAvailable;

    string toString() {
        return
            to_string(Id) + "|" + 
            to_string(OwnerId) + "|" + 
            to_string(RenterId) + "|" +
            Brand + "|" +
            Model + "|" + 
            Color + "|" + 
            to_string(Distance_Traveled) + "|" + 
            to_string(Price) + "|" + 
            to_string(IsDeleted) + "|" + 
            to_string(IsAvailable) + ";\n";
    }
};

Car cars[N] = {};

void AddCarToFile(Car c) {
    ofstream file("cars.txt", ios::app);
    file << c.toString();
    file.close();
}

int readInt(string message) {
    int x;
    cout << message;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Enter a valid integer: ";
    }
    return x;
}


void AddCar() {
    system("cls");

    char choice;
    Car c;
    while (true) {
        c.Id = nextCar;
        c.OwnerId = loggedInUserId;
        c.IsDeleted = false;
        c.IsAvailable = true;
        cout << "Enter Car Brand: ";
        cin.ignore();
        getline(cin, c.Brand);

        cout << "\nEnter Car Model: ";
        // cin.ignore();
        getline(cin, c.Model);

        cout << "\nEnter Car Color: ";
        // cin.ignore();
        getline(cin, c.Color);

        c.Distance_Traveled = readInt("\nEnter Distance Traveled By Car: "); 
        c.Price = readInt("\nEnter Car Price: ");


        AddCarToFile(c);
        nextCar++;
        cout << "Car Added Successfully!\n";
        
        cout << "Do You Want To Add Another Car? (y/n): ";
        cin >> choice;
        if (choice == 'n' || choice == 'N')
            break;
        
        system("cls");
    }
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
            if(!cars[carId - 1].IsDeleted)
                return carId;

            cntChecked++;
        }
    }
    else if(pressedKey == 80){
        while(cntChecked < nextCar - 1) {
            currentHighlightedCarId++;
            int carId = (currentHighlightedCarId >= nextCar)? currentHighlightedCarId - nextCar + 1 : currentHighlightedCarId;
            if(!cars[carId - 1].IsDeleted)
                return carId;

            cntChecked++;
        }
    }
    return -1;
}

void ListCars() {
    system("cls");

    cout << "==================================\n";
    cout << "   WELCOME TO CAR RENTAL SYSTEM   \n";
    cout << "==================================\n";

    cout << "1- Add Car\n";
    cout << "2- Remove car\n";
    cout << "3- Update car\n";
    cout << "4- Rent Car\n";
    cout << "5- Return Car\n";
    cout << "0- Exit\n";
    cout << "Enter your choice...\n\n\n"; 


    for(auto i : cars) {
        if(!i.Id)
            break;
        
        if(i.IsDeleted)
            continue;
        
        if(i.Id == highlitedCarId)
            DisplayCarInfoSummaryHighlighted(i);
        else
            DisplayCarInfoSummary(i);
    
    }
}


void DisplayCarInfo(Car car) {
    cout << "*****************\n";
    cout << "     CAR INFO    \n";
    cout << "*****************\n";

    cout << "BRAND : " << car.Brand << '\n';
    cout << "MODEL : " <<car.Model << '\n';
    cout << "COLOR : " << car.Color << '\n';
    cout << "DISTANCE TRAVELED : " << car.Distance_Traveled << '\n';
    cout << "PRICE : " << car.Price << '\n';
    cout << "Available For Rent : ";
    (car.IsAvailable) ? cout << "Yes\n" : cout << "No\n";
}

void DisplayCarInfoById( int id ) {
    system("cls");
    
    DisplayCarInfo(cars[id - 1]);
}

void UpdateDataInFile () {
    ofstream file("cars.txt");
    for (auto i : cars)
        if (i.Id)
            file << i.toString();

    file.close();   
}

void RemoveCar() {
    if (cars[highlitedCarId - 1].OwnerId == loggedInUserId) {
        cars[highlitedCarId - 1].IsDeleted = true;
        UpdateDataInFile();
        highlitedCarId = GetNextHighltedCarId(highlitedCarId, 72);
        ListCars();
    }
    else
        cout << "\n\nYou Can`t Delete This Car\n";
}

void UpdateCarInfo () {
    if (loggedInUserId != cars[highlitedCarId - 1].OwnerId) {
        cout << "\n\nYou Can`t Update This Car\n";
        return;
    }
    system("cls");
    char order;
    string color;
    double distanceTraveled, price;
    cout << "1 - Change Color \n";
    cout << "2 - Change Distance Traveled \n";
    cout << "3 - Change Price \n";

    cin >> order;
    switch (order) {
        case '1':
        
            cout << "Enter The New Color: ";
            cin.ignore();
            getline(cin, color);
            cars[highlitedCarId - 1].Color = color;
            break;
        case '2':
            distanceTraveled = readInt("Enter The New Distance Traveled: ");
            cars[highlitedCarId - 1].Distance_Traveled = distanceTraveled;
            break;
        case '3':
            price = readInt("Enter The New Price: ");
            cars[highlitedCarId - 1].Price = price;
            break;
    }
    UpdateDataInFile();
    ListCars();
}


Car ReadCar (string carRow) {
    Car c;
    string s;
    stringstream carStream(carRow);

    getline(carStream, s, '|');
    c.Id = stoi(s);
    // cout << "s = " << s << '\n';
    
    getline(carStream, s, '|');
    c.OwnerId = stoi(s);

    getline(carStream, s, '|');
    c.RenterId = stoi(s);
    
    getline(carStream, c.Brand, '|');
    getline(carStream, c.Model, '|');
    getline(carStream, c.Color, '|');
    // cout << "s = " << s << '\n';

    getline(carStream, s, '|');
    c.Distance_Traveled = stod(s);
    // cout << "s = " << s << '\n';
    
    getline(carStream, s, '|');
    c.Price = stod(s);
    // cout << "s = " << s << '\n';

    getline(carStream, s, '|');
    if (stoi(s) == 0)
        c.IsDeleted = false;
    else
        c.IsDeleted = true;

    getline(carStream, s, ';');
    if (stoi(s) == 0)
        c.IsAvailable = false;
    else
        c.IsAvailable = true;

    return c;  
}
    
void UpdateNextCar () {
    for (int i = 0; i < N; i++) 
        if (cars[i].Id == 0) {
            nextCar = i + 1;
            break;
        }
}

void LoadCarsDataFromFile () {
    ifstream file("cars.txt");
    string s;
    while (getline(file, s)) {
        Car c = ReadCar(s);
        cars[c.Id - 1] = c;
    }
    file.close();
    UpdateNextCar();
}


bool ProcessPayment()
{
	int Cash = 1;
	int Visa = 2;
	int option;
	cout << "How would you like to pay?\n";
	cout << "1.Cash\n";
	cout << "2.Visa\n";
	cin >> option;
	if (option == 1) {
        return true;
    }
	else if (option == 2)
	{
		VISA user;
		cout << "Enter bank name\n";
		cin.ignore();
		getline(cin, user.bank_name);
		cout << "Enter card number\n";
		cin >> user.card_number;
		cout << "Enter holder name\n";
		cin.ignore();
		getline(cin, user.holder_name);
		cout << "Enter expiry date\n";
		cin >> user.expiry_date;
		cout << "Enter cvv\n";
		cin >> user.cvv;
        return true;
    }
	else 
        return false;
}

void RentCar(Car cars[] , int size , int id) {
    system("cls");
    bool occupied = false, isPaymentSuccessfull = false, isNotAvailable = false;
    for (int i = 0 ; i < size ; i++) {
        if (cars[i].Id == id ) {
            occupied = true ;
        if(loggedInUserId == cars[i].OwnerId) {
            cout << "You Can`t Rent Your Own Car\n";
            break;
        }
        if (cars[i].IsAvailable) {
            isPaymentSuccessfull = ProcessPayment();
            if(isPaymentSuccessfull) {
                cars[i].IsAvailable = false;
                cars[i].RenterId = loggedInUserId;
            }
        }
        else {
            isNotAvailable = true;
        }
    }
    
}
if (!occupied) {
    cout << "Car not found." << endl;
}

ListCars();

if(isPaymentSuccessfull) {
    
    UpdateDataInFile();
    cout << "\n\n\nPAYMENT SUCCESSFUL\n";
    cout << "Car rented successfully!\n";
}
else if(isNotAvailable) {
    cout << "\n\nSorry, this car is not available.\n";
}

}

void ReturnCar(Car cars[], int size, int id) {
    bool found = false;

    for (int i = 0 ; i < size ; i++) {

        if (cars[i].Id == id ) {
            found = true;

            if (!cars[i].IsAvailable) {
                if(loggedInUserId != cars[i].RenterId){
                    cout << "Invalid Action\n";
                    break;
                }

                cars[i].IsAvailable = true;
                UpdateDataInFile();
                cout << "\n\nCar returned successfully!" << endl;

            }
            else {
                cout << "This car is already available" << endl;
            }

        }
    }

    if (!found) {
        cout << "Car not found" ;
    }
}






#endif