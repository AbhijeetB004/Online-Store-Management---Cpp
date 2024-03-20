#include <bits/stdc++.h>
#include "admin_buyer.hpp"

using namespace std;
void delaydisplay(string s)
{
    for (int i = 0; i < s.size(); i++)
    {
        cout << s[i];
        usleep(50000);
    }
    cout << endl;
}

int main()
{
    // cout << "\033[2J\033[47m";
    Store store;
    Administrator administrator(store);
    Buyer buyer(store);
    system("CLS");
    cout << "\n\t\t\t\t\t\t\t";
    delaydisplay("Welcome to Shopping Mart");
    cout << endl;
    sleep(1);
    cout << "\n\t\t\t\tHey there,";
    cout << "\n\t\t\t\t";
    delaydisplay("I am your Assistant to help you out with your things:D");
    sleep(1);
    x:
    cout << "\n\t\t\t\tLogin as?";
    cout << "\n\t\t\t\t1. Administrator";
    cout << "\n\t\t\t\t2. Buyer\n";
    cout << "\n\t\t\t\tEnter your choice: ";
    int choice;
    cin >> choice;
    switch (choice)
    {
        case 1:
        {
            administrator.adminoperations();
            break;
        }
        case 2:
        {
            buyer.buyeroperations();
            break;
        }

        default:
        {
            cout << "Invalid Entry:D \nBye" << endl;
            exit(0);
        }
        break;
    }
    goto x;
}   