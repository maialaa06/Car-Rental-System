#include <bits/stdc++.h>
#include <fstream>
#define dbg(x) cout << #x << "=" << x << endl;
using namespace std;
int const  Nusers = 3000;
int nextUser = 1;
int loggedUserId;

struct User
{
    int Id;
    string Uname;
    string Email;
    string Password;
};
User users[Nusers];

bool ValidateEmail (string email) {
    bool isvalid = true;

    regex pattern("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    if (!regex_match(email, pattern))
        isvalid = false;
        return isvalid;
}

void Registeration () {
    User u;
    u.Id = nextUser;

    cout << "==================================\n";
    cout << "             REGISTER             \n";
    cout << "==================================\n";   
    
    cout << "Enter Your Username\n";
    cin >>  u.Uname;
    cout << "Enter Your Email\n";
    cin >> u.Email;
    
    bool isvalid = ValidateEmail(u.Email);
    while (!isvalid) {
        cout << "invalid email\n"; 
        cout << "Try Again\n";
        cin >> u.Email;
        isvalid = ValidateEmail(u.Email);
    }    
    
    cout <<"Enter Your Password\n";
    cin >> u.Password;
    
    ofstream file("users.txt", ios::app);
    file << u.Id << '|' << u.Uname << '|' << u.Email << '|'; 
    file << u.Password << ';' << '\n'; 
    file.close();

    nextUser++;
}

bool IsUserExist(string username, string password) {
    bool seen = false;
    
    for (auto i : users)
        if (username == i.Uname && password == i.Password) {
            loggedUserId = i.Id;
            seen = true;
            break;
        }
    return seen;
}

void Login () {
    system("cls");
    string username, password;

    cout << "==================================\n";
    cout << "             SIGN IN              \n";
    cout << "==================================\n"; 
    
    cout << "Enter Your Username\n";
    cin >> username;
    cout << "Enter Your Password\n";
    cin >> password;

    bool seen = IsUserExist(username, password);
    while (!seen) {
        cout << "Username Or Password Is Wrong Try Again\n";
        cout << "Enter Your Username\n";
        cin >> username;
        cout << "Enter Your Password\n";    
        cin >> password;
        seen = IsUserExist(username, password);
    }    
}

User ParseUser (string userRow) {
    User parsedUser;
    string userId;
    stringstream userStream(userRow);

    getline(userStream, userId, '|');
    parsedUser.Id = stoi(userId);
    getline(userStream, parsedUser.Uname, '|');
    getline(userStream, parsedUser.Email, '|');
    getline(userStream, parsedUser.Password, ';');

    return parsedUser;
}

void SavingUserDataInStruct (User u) {
    int index = u.Id - 1;
    users[index].Id = u.Id;
    users[index].Uname = u.Uname;
    users[index].Email = u.Email;
    users[index].Password = u.Password;
}

void SavingUserDataFromFileToArray () {
    ifstream file ("users.txt");

    string s;
    while (getline(file, s)) {
        User u = ParseUser(s);
        SavingUserDataInStruct(u);
    }
    file.close();
}

void UpdateNextUser () {
    for (int i = 0; i < Nusers; i++)
        if (users[i].Id == 0) {
            nextUser = i + 1;
            break;
        }
}