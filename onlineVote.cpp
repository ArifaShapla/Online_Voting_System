#include <bits/stdc++.h>

using namespace std;

int main() {
    unordered_map<string, string> um;
    um["mim"] = "069";
    um["diya"] = "009";
    um["shafin"] = "073";
    um["arman"] = "008";
    while (true) {
        string option;
        cout << "1. Login\n2. Exit\nEnter option: ";
        cin >> option;
        if (option == "1") {
            string username, password;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            if (um.find(username) != um.end() && um[username] == password) {
                cout << "Login successful" << endl;
            } else {
                cout << "Invalid username or password" << endl;
            }
        } else if (option == "2") {
            cout << "Exiting..." << endl;
            break;
        } else {
            cout << "Invalid option, please try again" << endl;
        }
    }
    return 0;
}
