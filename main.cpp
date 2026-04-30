#include <bits/stdc++.h>
#include <conio.h>
#include<windows.h>
#include <fstream>
#define dbg(x) cout << #x << "=" << x << endl;

#define MAX_USERS 300
int userCount = 0;
int loggedInUserId;

using namespace std;

struct Address 
{
    string bldgNo;
    string street;
    string city;
    
    string toString() {
        return bldgNo + "," + street + "," + city; 
    }
};
        
struct Customer 
{
    int id;
    string nationalId;
    string username;
    string email;
    string password;     // Added password field for authentication
    string phoneNo;
    string job;
    Address addrress;

    string toString() {
        return to_string(id) + "|" + 
        nationalId + "|" +
        username + "|" +
        email + "|" +
        password + "|" +
        phoneNo + "|" +
        job + "|" +
        addrress.toString() + ";\n";
    }
};

Customer users[MAX_USERS];
        
bool isEmailValid (string email) {
    bool isvalid = true;

    regex pattern("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    if (!regex_match(email, pattern))
        isvalid = false;
        return isvalid;
}

void AddUserToFile (Customer c) {
    ofstream file("users.txt", ios::app);
    file << c.toString();
    file.close();
}

bool isUsernameAvailable(string username) {
    for(int i = 0; i < userCount; i++) {
        if(users[i].username == username)
            return false;
    }
    return true;
}
        
void SignUp() {
    system("cls");
    if (userCount >= MAX_USERS) {
        cout << "Users limit reached. Cannot sign up more users." << endl;
        return;
    }

    Customer newUser;
    newUser.id = userCount + 1;

    cout << "==================================\n";
    cout << "             SIGN UP              \n";
    cout << "==================================\n"; 

    
    cout << "Enter username: ";
    while(true) {
        cin >> newUser.username;
        if(isUsernameAvailable(newUser.username)) 
            break;
        cout << "this username is not available.\nEnter username: ";
    }
    
    string email;
    cout << "Enter Your Email: ";
    cin >> email;
    while(!isEmailValid(email)) {
        cout << "Enter a Valid Email\n";
        cin >> email;
    }
    newUser.email = email;

    cout << "Enter phone number: ";
    cin >> newUser.phoneNo;
    
    cout << "Enter your national Id: ";
    cin >> newUser.nationalId;
    
    cout << "Enter password: ";
    cin.ignore();
    getline(cin, newUser.password);  
  
    cout << "Enter city: ";
    getline(cin, newUser.addrress.city);
    cout << "Enter street: ";
    getline(cin, newUser.addrress.street);  
    cout << "Enter building number: ";
    cin >> newUser.addrress.bldgNo;

    cout << "Enter job: ";
    cin.ignore();                  
    getline(cin, newUser.job); 
   
    AddUserToFile(newUser);      // Add the new user to the array
    userCount++;       // Increment user count after adding the new user to the array
}
      
void SignIn () {
    system("cls");
    string username, password;
    
    cout << "==================================\n";
    cout << "             Sign In              \n";
    cout << "==================================\n"; 

    while(true) {
        string username, password;
        cout << "Enter username: ";                        // Clear the input buffer before reading the username
        getline(cin, username);              // Use getline to allow spaces in the username
        cout << "Enter password: ";
        getline(cin, password);              // Use getline to allow spaces in the password

        for (int i = 0; i < userCount; i++) {
            if (users[i].username == username && users[i].password == password) {
                cout << "Login successful! Welcome, " << users[i].username << "!" << endl;
                loggedInUserId = users[i].id;
                return;
            }
        }
        cout << "Invalid username or password. Please try again." << endl;
    } 
}

void UpdateUserCount () {
    for (int i = 0; i < MAX_USERS; i++)
        if (users[i].id == 0) {
            userCount = i;
            break;
        }
}

Customer ReadUser (string userRow) {
    Customer c;
    string userId;
    stringstream userStream(userRow);

    getline(userStream, userId, '|');
    c.id = stoi(userId);
    getline(userStream, c.nationalId, '|');
    getline(userStream, c.username, '|');
    getline(userStream, c.email, '|');
    getline(userStream, c.password, '|');
    getline(userStream, c.phoneNo, '|');
    getline(userStream, c.job, '|');
    getline(userStream, c.addrress.bldgNo, ',');
    getline(userStream, c.addrress.street, ',');
    getline(userStream, c.addrress.city, ';');

    return c;
}

void LoadUsersDataFromFile () {
  ifstream file ("users.txt");
  if (file.peek() == EOF)
     return;

  string s;
  while (getline(file, s)) {
       Customer u = ReadUser(s);
       users[u.id - 1] = u;
   }
    file.close();
   UpdateUserCount();
}

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
        getline(cin, c.Brand);

        cout << "\nEnter Car Model: ";
        getline(cin, c.Model);

        cout << "\nEnter Car Color: ";
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
    cout << "6- Check Car Availability\n";
    cout << "7- List Available Cars\n";
    cout << "8- Logout\n";
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
    
    getline(carStream, s, '|');
    c.OwnerId = stoi(s);

    getline(carStream, s, '|');
    c.RenterId = stoi(s);
    
    getline(carStream, c.Brand, '|');
    getline(carStream, c.Model, '|');
    getline(carStream, c.Color, '|');

    getline(carStream, s, '|');
    c.Distance_Traveled = stod(s);
    
    getline(carStream, s, '|');
    c.Price = stod(s);

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
     ifstream file ("cars.txt");
     if (file.peek() == EOF)
        return;

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
    bool occupied = false, isPaymentSuccessfull = false, isNotAvailable = false, isOwnCar = false;
    for (int i = 0 ; i < size ; i++) {
        if (cars[i].Id == id ) {
            occupied = true ;
            if(loggedInUserId == cars[i].OwnerId) {
                isOwnCar = true;
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

    if (!occupied)
        cout << "Car not found.\n";

    ListCars();

    if(isPaymentSuccessfull) {
        
        UpdateDataInFile();
        cout << "\n\n\nPAYMENT SUCCESSFUL\n";
        cout << "Car rented successfully!\n";
    }
    else if(isNotAvailable)
        cout << "\n\nSorry, this car is not available.\n";
    else if(isOwnCar)
        cout << "\n\nYou Can`t Rent Your Own Car\n";
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


void list_available_cars(Car cars[], int currentavailable) {
    system("cls");
    cout << "==================================\n";
    cout << "        AVAILABLE CARS ARE        \n";
    cout << "==================================\n";
    
    bool  carfound = false;
	for (int i = 0;i < currentavailable; i++)
	{
        if(cars[i].IsDeleted)
            continue;

        if (cars[i].IsAvailable)
		{
            cout << "Brand : " << cars[i].Brand << " | Model : " << cars[i].Model <<" | Price : " << cars[i].Price << '\n';           
			carfound = true;
		}
	}
	if (!carfound)
	{
		cout << "No cars available at the moment.\n";
	}
}


void check_out_car(Car cars[], int currentavailable, int targetid)
{
	bool carfound = false, isRented = false;
	for (int i = 0; i < currentavailable;i++)
	{

		if (cars[i].Id == targetid) {
            carfound = true;
            
            if (cars[i].IsAvailable)
                isRented = false;            
            else 
                isRented = true;
            break;
        }
	}

    ListCars();

    if(isRented)
        cout << "the car is currently rented.\n";
    else
        cout << "the car is currently available.\n";

	if (!carfound) {
		cout << "This Car Not Found In Record.\n: ";
	}
}

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
