#include <bits/stdc++.h>
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