#include <fstream> 
#include <iostream> 
#include <vector>  
#include <sstream>  
#include <string>
#include "customer.h"
#include "bankaccount.h"
using namespace std;
class MyLogin
{
private:
    /* data */
    int User_ID;
    char Customer_ID[20];
    char Password[20];
    char UserType;
    int LoginStatus;

public:
    // Login(/* args */);
    void setLoginStatus(int status)
    {
        LoginStatus = status;
    }
    int getLoginStatus()
    {
        return LoginStatus;
    }
    void setUser_ID(char Uid)
    {
        User_ID = Uid;
    }
    void setCustomer_ID(char Cid[])
    {
        strcpy(Customer_ID, Cid);
    }
    void setPassword(char password[])
    {
        strcpy(Password, password);
    }
    void setUserType(char u_type)
    {
        UserType = u_type;
    }


    
    void auth()
    {
        UserInfo user;
        user.mydata();
        vector< vector<string> > content = user.getContent();
        //Encrypt the password
        for(int i=0;Password[i] != '\0';i++){
            Password[i]+=1;
        }
        
        int f=0;
        for (int i = 0; i < content.size(); i++)
        {
            if ((content[i][1] == Customer_ID) && (content[i][2] == Password) && (content[i][3].at(0) == UserType) && (stoi(content[i][4]) == 0))
            {
                f=1;
                cout << "LogedIn Success" << endl;
                cout << endl;
                setLoginStatus(1);
                updateLoginStatus();
                if(UserType=='A'){
                    int choice;
                     choice_label:
                     cout<<"__________________________________________________________"<<endl;
                    // cout<<"_______________________****_______________________________"<<endl;
                    cout<<"Press...."<<endl;
                    cout<<" 1: To Add Customer"<<endl;
                    cout<<" 2: Delete "<<endl;
                    cout<<" 3: Modify a Customer"<<endl;
                    cout<<" 4: Credit/Debit Money <<--->> Customer Account"<<endl;
                    cout<<" 5: Query/Report on Customer Account "<<endl;
                    cout<<" 6: Query/Report on Customer Transaction"<<endl;
                    cout<<" 7: Quit"<<endl;
                    cout<<"__________________________________________________________"<<endl;
                    // cout<<"_______________________****_______________________________"<<endl;
                    cout<<"Enter Here..."<<endl;
                    cin>>choice;
                    switch(choice){
                        case 1:{
                            cin.ignore(1);
                            cout<<"Details of customers..."<<endl;
                            user.ToUserFile();
                            goto choice_label;
                            break;
                        }
                        case 2:{
                            cout<<"Delating a customer..."<<endl;
                            user.delete_User();
                            goto choice_label;
                            break;
                        }
                        case 3:{
                        cout<<"Modifing a customer..."<<endl;
                        user.update_customer();
                        goto choice_label;
                        break;
                        }
                        case 4:{
                        cout<<"Money <<-->> Customer Account..."<<endl;
                        Bank b;
                        b.update_amount();
                        goto choice_label;
                        break;
                        }
                        case 5:{
                        cout<<"Query/Report on Customer Account ..."<<endl;
                        user.Customer_data();
                        goto choice_label;
                        break;
                        }
                        case 6:{
                        cout<<"Query/Report on Customer Transaction..."<<endl;
                        int AccNo;
                        cout<<"Enter the Acc. number to display  transactions details"<<endl;
                        Bank b;
                        b.customer_transactions(AccNo);
                        goto choice_label;
                        break;
                        }
                        case 7:{
                            cout << "Loged Out" << endl;
                            cout << endl;
                            setLoginStatus(0);
                            updateLoginStatus();
                            break;
                        }
                        default:{
                            cout<<"Wrong Choice..."<<endl;   
                            goto choice_label; 
                            break;
                        }
                    }
                }
                else if(UserType=='U'){
                    cout<<"Customer"<<endl;
                    int choice;
                    userlabel2:
                    // cout<<"*************************************************"<<endl;
                    cout<<"_________________________________________________"<<endl;
                    cout<<"Enter 1: Customer Details"<<endl;
                    cout<<"Enter 2: Transfer Money"<<endl;
                    cout<<"Enter 3: Query your Account & Transaction Details"<<endl;
                    cout<<"Enter 4: Quit"<<endl;
                    cout<<"_________________________________________________"<<endl;
                    // cout<<"*************************************************"<<endl;
                    cin>>choice;
                    cout<<endl;
                    cout<<endl;
                     switch(choice){
                    case 1:{
                        cout<<"Your Details are: "<<endl;
                        UserInfo cstmr;
                        cstmr.customer_detail(stoi(content[i][0]));
                        goto userlabel2;
                        break;
                    }
                    case 2:{
                        Bank b;
                        b.update_amount_record(stoi(content[i][0]));
                        goto userlabel2;
                        break;
                    }
                    case 3:{
                        Bank b;
                        cout<<"\t\tTransactional Detail"<<endl;
                        b.customer_transactions(stoi(content[i][0]));
                        cout<<endl;

                        UserInfo u;
                        cout<<"\t\tAccount Detail"<<endl;
                        u.read_customer_account(stoi(content[i][0]));
                        goto userlabel2;
                        break;
                    }
                    case 4:{
                        cout << "Loged Out" << endl;
                        cout << endl;
                        setLoginStatus(0);
                        updateLoginStatus();
                        break;
                    }
                    default:
                    cout<<"Wrong Choice"<<endl;
                    }
                }
            
            }
            else if ((content[i][1] == Customer_ID) && (content[i][2] == Password) && (content[i][3].at(0) == UserType) && (stoi(content[i][4]) == 1))
            {
                f=1;
                cout << "Already LogedIn"<<endl;
                break;
            }
            
        }
        if(f==0)
            {
                cout << "Invalid User Id or Password"<<endl;
                
            }
    }
    void updateLoginStatus()
    {
        fstream fin, fout;
        fin.open("user.csv", ios::in);
        fout.open("new_user.csv", ios::out);
        int new_status = getLoginStatus();
        string line, word;
        int count = 0, i;
        vector<string> row;
        string cid1;
        while (!fin.eof())
        {
            row.clear();
            getline(fin, line);
            stringstream s(line);
            while (getline(s, word, ','))
            {
                row.push_back(word);
            }
            cid1 = row[1];
            int row_size = row.size();
            if (cid1 == Customer_ID)
            {
                count = 1;
                stringstream convert;
                convert << new_status;
                row[4] = convert.str();
                if (!fin.eof())
                {
                    for (int i = 0; i < row_size - 1; i++)
                    {
                        fout<<row[i]<< ",";
                    }
                    fout<<row[row_size - 1]<<endl;
                }
            }
            else
            {
                if (!fin.eof())
               {
                    for (int i = 0; i < row_size - 1; i++)
                    {
                        fout<<row[i]<< ",";
                    }
                    fout<<row[row_size - 1]<<endl;
                }
            }
            if (fin.eof())
                break;
        }
        if (count == 0)
            cout << "Records not Found"<<endl;
        fin.close();
        fout.close();
        remove("user.csv");
        rename("new_user.csv", "user.csv");
    }
    ~MyLogin() {}
};
