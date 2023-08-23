#include <iostream>  
#include <fstream>
#include "Login.h"

using namespace std;

int main()
{
    int choice;

    cout << endl;
    cout<<  " ____________________________________________________________"<<endl;
    // cout<<  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
    // cout << " ____________________________________________________________" << endl;
    cout << endl;
    cout << "\t\t\tWELCOME TO CORE BANKING SYSTEM" << endl;
    cout << endl;
    // cout << " _____________________________________________________________" << endl;
    // cout<<  " ************************************************************"<<endl;
    cout<<  " _____________________________________________________________"<<endl;
    cout << endl;
    cout << "\t\tENTER YOUR CHOICE" << endl;
    cout<<"_____________________________________________________________"<<endl;
    cout << " 1: Banking Employee" << endl;
    cout << " 2: Customers " << endl;
    cout<<"Enter Here: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
    {
        char cid[20];
        char pass[20];
        cout << "___________________________________________________________" << endl;
        // cout << "***********************************************************" << endl;
        cout << endl;
        cout << "\t\t\tBank Employee" << endl;
        cout << endl;
        // cout << "***********************************************************" << endl;
        cout << "___________________________________________________________" << endl;
        cout << endl;
        // cout << "**************************************" <<endl;
        cout << "_____________LOGIN PAGE_______________" <<endl;
        // cout << "______________________________________" <<endl;
        cout << "Enter Your Login ID:" << endl;
        cin.ignore(1);
        cin.getline(cid, 20);
        cout << "Enter Your Password:" << endl;
        //cin.ignore(1);
        cin.getline(pass, 20);

        MyLogin login;
        login.setUserType('A');
        login.setCustomer_ID(cid);
        login.setPassword(pass);
        login.auth();

        break;
    }

    case 2:
    {
        char cid[20];
        char pass[20];
        // cout << "***********************************************************" << endl;
        cout << "___________________________________________________________" << endl;
        cout << endl;
        cout << "\t\t\tCUSTOMER" << endl;
        cout << endl;
        cout << "___________________________________________________________" << endl;
        // cout << "***********************************************************" << endl;
        cout << endl;
        // cout << "**************************************" <<endl;
        cout << "_____________LOGIN PAGE_______________" <<endl;
        // cout << "**************************************" <<endl;
        cout << "Enter Your Login ID:" << endl;
        cin.ignore(1);
        cin.getline(cid, 20);
        cout << "Enter Your Password:" << endl;
        //cin.ignore(1);
        cin.getline(pass, 20);

        MyLogin login;
        login.setUserType('U');
        login.setCustomer_ID(cid);
        login.setPassword(pass);
        login.auth();

        break;
    }

    default:
        cout << "Wrong Choice!" << endl;
    }
}
