#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <regex> 
#include <ctime> 
using namespace std;
class UserInfo
{
    public:
    string Customer_ID;
private:
    int User_ID;
    
    char Password[30];
    char UserTypes;
    int LoginStatus;


    
    string Name;
    string Type;
    string Address;
    string street;
    string Colony;
    string City;
    string State;
    string Country;
    string Pincode;
    string PhoneNumber;
    string Emailid;
    string PancardNumber;

    string account_type;
    string account_status;
    double account_balance;
    string account_opening_date;

    
    vector< vector<string> > content;
    vector<string> row;

public:
    vector< vector <string> > getContent()
    {
        return content;
    }

bool c(){
        for(int i=0;i<content.size();i++){
            if(content[i][1]==Customer_ID){
                cout<<"ID already occupied! Please Try Again..."<<endl;
                return false;
            }
        }
            return true;
}
    void readConsole()//To read data from console
    {
        mydata();
        customerIDlabel:
        cout<<"Enter Customer ID(Login ID)"<<endl;
        getline(cin, Customer_ID);
        
        if(c()==false)
        goto customerIDlabel;
        

        //CustomerID=Customer_ID;

        cout<<"Enter Name"<<endl;
        getline (cin, Name);

        cout<<"Enter Type --> individual or corporate"<<endl;
        getline (cin, Type);

        cout<<"Enter Address"<<endl;
        getline (cin, Address);

        cout<<"Enter street"<<endl;
        getline (cin, street);

        cout<<"Enter colony"<<endl;
        getline (cin, Colony);

        cout<<"Enter City"<<endl;
        getline (cin, City);

        cout<<"Enter State"<<endl;
        getline (cin, State);

        cout<<"Enter Country"<<endl;
        getline (cin, Country);

        pincode:
        cout<<"Enter Pincode"<<endl;
        getline (cin, Pincode);
        const regex pattern1("^[1-9]{1}[0-9]{2}\\s{0,1}[0-9]{3}$");
        if(Pincode.empty()){
            cout<<"Pin code can't be empty"<<endl;
            goto pincode;
        }
        if (regex_match(Pincode, pattern1)==false){
            cout<<"Invalid Pincode"<<endl;
            goto pincode;
        }

        phoneNumber:
        cout<<"Enter Phone Number"<<endl;
        getline (cin, PhoneNumber);
        const regex pattern2("(0|91)?[6-9][0-9]{9}");
        if(regex_match(PhoneNumber, pattern2)==false){
            cout<<"Invalid Mobile Number"<<endl;
            goto phoneNumber;
        }


        email:
        cout<<"Enter Email"<<endl;
        getline (cin, Emailid);
        if(is_valid(Emailid)==false){
    
            cout<<"Invalid Email!"<<endl;
            goto email;
        }

        pan:
        cout<<"Enter Pan Number"<<endl;
        getline (cin, PancardNumber);
        const regex pattern3("[A-Z]{5}[0-9]{4}[A-Z]{1}");
        if(PancardNumber.empty()){
            cout<<"Pan Number Can't be empty"<<endl;
            goto pan;
        }
        if(regex_match(PancardNumber, pattern3)==false){
            cout<<"Invalid Pan Number"<<endl;
            goto pan;
        }

        password:
        cout << "Enter Password" << endl;
        cin.getline(Password, 30);
        if(isValidPassword(Password)==false){
            cout<<endl;
            cout<<"A password must contains at least one -"<<endl;
            cout<<"-> Lowercase"<<endl;
            cout<<"-> Uppercase"<<endl;
            cout<<"-> Special character"<<endl;
            cout<<"-> Digit and "<<endl;
            cout<<"-> Length is least 8."<<endl;
            cout<<endl;
            goto password;
        }
        encrypt();

        UserTypes='U';
        LoginStatus=0;



        cout<<"Enter Customer Account Information"<<endl;
        cout<<"Enter Account Type --> Saving Account or Current Account"<<endl;
        getline (cin, account_type);

        cout<<"Enter Account Status"<<endl;
        getline (cin, account_status);

        cout<<"Enter Account Balance"<<endl;
        cin>>account_balance;

         time_t tt;
         struct tm * ti;
         time(&tt);
         ti=localtime(&tt);
         account_opening_date=asctime(ti);
    }

    void ToUserFile()
    {
        fstream fout;
        readConsole();
        mydata();
        int uid=content.size()+1;
        
        fout.open("user.csv", ios::out | ios::app);
        if (!fout)
        {
            cout << "ERROR IN CREATING FILE USER.CSV" << endl;
            return;
        }
        fout << uid << "," << Customer_ID << "," << Password << "," << UserTypes << "," << LoginStatus << endl;
        fout.close();





        fout.open("customer.csv", ios::out | ios::app);
        if (!fout)
        {
            cout << "ERROR IN CREATING FILE CUSTOMER.CSV" << endl;
            return;
        }
        fout <<uid<<","<< Name<<","<<Type<<","<<Address<<","<<street<<","<<Colony<<","<<City<<","<<State<<","<<Country<<","<<Pincode<<","<<PhoneNumber<<","<<Emailid<<","<<PancardNumber<<endl;
        fout.close();



        fout.open("account.csv", ios::out | ios::app);
        if (!fout)
        {
            cout << "ERROR IN CREATING FILE ACCOUNT.CSV" << endl;
            return;
        }
        fout <<uid<<","<<account_type<<","<<Customer_ID<<","<<account_status<<","<<account_balance<<","<<account_opening_date<<endl;
        fout.close();

        cout << "Details Added Sucessfully" << endl;
    }

    void mydata()//To read user.csv data
    {
        content.clear();
        row.clear();

        string line, word;

        fstream file("user.csv", ios::in);
        if (file.is_open())
        {
            while (getline(file, line))
            {
                row.clear();

                stringstream str(line);

                while (getline(str, word, ','))
                    row.push_back(word);
                content.push_back(row);
            }
        }
        else
            cout << "Could not open the user file\n";
    }

    void displayAll()//To display all data of user.csv
    {
        mydata();
        for (int i = 0; i < content.size(); i++)
        {
            for (int j = 0; j < content[i].size(); j++)
            {
                cout << content[i][j] << " ";
            }
            cout << "\n";
        }
    }

    bool isValidPassword(char input[]){//To validate Password
        int n=strlen(input);
        bool hasLower = false, hasUpper = false;
        bool hasDigit = false, specialChar = false;
        
        for (int i = 0; i < n; i++) {
        if (islower(input[i]))
            hasLower = true;
        else if (isupper(input[i]))
            hasUpper = true;
        else if (isdigit(input[i]))
            hasDigit = true;
        else
            specialChar = true;
    }
    if (hasLower && hasUpper && hasDigit && specialChar && (n >= 8))
    return true;
    else
    return false;
    }

    void encrypt(){// encrypt
        for(int i=0;Password[i] != '\0';i++){
            Password[i]+=1;
        }
    }



//To Check validity of email
    bool isChar(char c)
{
    return ((c >= 'a' && c <= 'z')
            || (c >= 'A' && c <= 'Z'));
}
  
bool isDigit(const char c)
{
    return (c >= '0' && c <= '9');
}
  
// Function to check email id is
// valid or not
bool is_valid(string email)
{
    if (!isChar(email[0])) {
  
        return 0;
    }
    int At = -1, Dot = -1;
    for (int i = 0;
         i < email.length(); i++) {
  
        if (email[i] == '@') {
  
            At = i;
        }
  
        else if (email[i] == '.') {
  
            Dot = i;
        }
    }
  
    // If At or Dot is not present
    if (At == -1 || Dot == -1)
        return 0;
  
    // If Dot is present before At
    if (At > Dot)
        return 0;
  
    // If Dot is present at the end
    return !(Dot >= (email.length() - 1));
}


void delete_User()//to delete record from user.csv
{

	fstream fin, fout;

	// Open the existing file
	fin.open("user.csv", ios::in);

	// Create a new file to store the non-deleted data
	fout.open("new_user.csv", ios::out);

	int uid, uid1, count = 0, i;
	string line, word;
	vector<string> row;

	// to decide the data to be deleted
	cout << "Enter the User ID which you want to delete: "<<endl;
	cin >> uid;

	// Check if this record exists
	// If exists, leave it and
	// add all other data to the new file
	while (!fin.eof()) {

		row.clear();
		getline(fin, line);
		stringstream s(line);

		while (getline(s, word, ',')) {
			row.push_back(word);
		}

		int row_size = row.size();
		uid1 = stoi(row[0]);

		// writing all records,
		// except the record to be deleted,
		// into the new file 'reportcardnew.csv'
		// using fout pointer
		if (uid1 != uid) {
			if (!fin.eof()) {
				for (i = 0; i < row_size - 1; i++) {
					fout <<row[i]<< ",";
				}
				fout << row[row_size - 1] << "\n";
			}
		}
		else {
            //cusID=row[1];
			count = 1;
		}
		if (fin.eof())
			break;
	}
	if (count == 1)
		cout << "Record deleted from User File\n";
	else
		cout << "Record not found in User File\n";

	// Close the pointers
	fin.close();
	fout.close();

	// removing the existing file
	remove("user.csv");

	// renaming the new file with the existing file name
	rename("new_user.csv", "user.csv");
    delete_Customer(uid);
}





void delete_Customer(int cusID)//To delete record from CUSTOMER.CSV
{
	// Open FIle pointers
	fstream fin, fout;

	// Open the existing file
	fin.open("customer.csv", ios::in);

	// Create a new file to store the non-deleted data
	fout.open("new_customer.csv", ios::out);

    int cusID1;
	int count = 0, i;
	string line, word;
	vector<string> row;


	// Check if this record exists
	// If exists, leave it and
	// add all other data to the new file
	while (!fin.eof()) {

		row.clear();
		getline(fin, line);
		stringstream s(line);

		while (getline(s, word, ',')) {
			row.push_back(word);
		}

		int row_size = row.size();
		cusID1 = stoi(row[0]);

		// writing all records,
		// except the record to be deleted,
		// into the new file 'reportcardnew.csv'
		// using fout pointer
		if (cusID1 != cusID) {
			if (!fin.eof()) {
				for (i = 0; i < row_size - 1; i++) {
					fout <<row[i]<< ",";
				}
				fout << row[row_size - 1] << "\n";
			}
		}
		else {
            //cusID=row[1];
			count = 1;
		}
		if (fin.eof())
			break;
	}
	if (count == 1)
		cout << "Record deleted From Customer file\n";
	else
		cout << "Record not found in Customer file\n";

	// Close the pointers
	fin.close();
	fout.close();

	// removing the existing file
	remove("customer.csv");

	// renaming the new file with the existing file name
	rename("new_customer.csv", "customer.csv");
    delete_record_Account(cusID);
}


void delete_record_Account(int cusID)//To delete record from ACCOUNT.CSV
{
	// Open FIle pointers
	fstream fin, fout;

	// Open the existing file
	fin.open("account.csv", ios::in);

	// Create a new file to store the non-deleted data
	fout.open("new_account.csv", ios::out);

    int cusID1;
	int count = 0, i;
	string line, word;
	vector<string> row;

	while (!fin.eof()) {

		row.clear();
		getline(fin, line);
		stringstream s(line);

		while (getline(s, word, ',')) {
			row.push_back(word);
		}

		int row_size = row.size();
		cusID1 = stoi(row[0]);

		// writing all records,
		// except the record to be deleted,
		// into the new file 'reportcardnew.csv'
		// using fout pointer
		if (cusID1 != cusID) {
			if (!fin.eof()) {
				for (i = 0; i < row_size - 1; i++) {
					fout <<row[i]<< ",";
				}
				fout << row[row_size - 1] << "\n";
			}
		}
		else {
            //cusID=row[1];
			count = 1;
		}
		if (fin.eof())
			break;
	}
	if (count == 1)
		cout << "Record deleted From Account file\n";
	else
		cout << "Record not found in Account file\n";

	// Close the pointers
	fin.close();
	fout.close();

	// removing the existing file
	remove("account.csv");

	// renaming the new file with the existing file name
	rename("new_account.csv", "account.csv");
     delete_record_Transaction(cusID);
}



void delete_record_Transaction(int cusID)/////Function to delete record from TRANSACTION.CSV
{
	// Open FIle pointers
	fstream fin, fout;

	// Open the existing file
	fin.open("transaction.csv", ios::in);

	// Create a new file to store the non-deleted data
	fout.open("new_transaction.csv", ios::out);

    int cusID1;
	int count = 0, i;
	string line, word;
	vector<string> row;

	while (!fin.eof()) {

		row.clear();
		getline(fin, line);
		stringstream s(line);

		while (getline(s, word, ',')) {
			row.push_back(word);
		}

		int row_size = row.size();
		cusID1 = stoi(row[5]);

		
		if (cusID1 != cusID) {
			if (!fin.eof()) {
				for (i = 0; i < row_size - 1; i++) {
					fout <<row[i]<< ",";
				}
				fout << row[row_size - 1] << "\n";
			}
		}
		else {
            //cusID=row[1];
			count = 1;
		}
		if (fin.eof())
			break;
	}
	if (count == 1)
		cout << "Record deleted From Transaction file\n";
	else
		cout << "Record not found in Transaction file\n";

	// Close the pointers
	fin.close();
	fout.close();

	// removing the existing file
	remove("transaction.csv");

	// renaming the new file with the existing file name
	rename("new_transaction.csv", "transaction.csv");
}





void update_customer()//to update customer.CSV
{

    cout<<"Updating a Record..."<<endl;
	// File pointer
	fstream fin, fout;

	// Open an existing record
	fin.open("customer.csv", ios::in);

	// Create a new file to store updated data
	fout.open("new_customer.csv", ios::out);

	int uid, uid1, count = 0, i;
	int index;
	string line, word;
	vector<string> row;

	cout << "Enter the User id of the record to be updated: "<<endl;
	cin >> uid;

   int choice;
	// Get the data to be updated
    cout<<"_______________________###___________________________"<<endl;
    cout<<"Press...."<<endl;
	cout<<" 1: To UPDATE Name"<<endl;
    cout<<" 2: To UPDATE Type"<<endl;
    cout<<" 3: To UPDATE Address1"<<endl;
    cout<<" 4: To UPDATE Address2"<<endl;
    cout<<" 5: To UPDATE Address3"<<endl;
    cout<<" 6: To UPDATE City"<<endl;
    cout<<" 7: To UPDATE State"<<endl;
    cout<<" 8: To UPDATE Country"<<endl;
    cout<<" 9: To UPDATE Pincode"<<endl;
    cout<<" 10: To UPDATE Phone Number"<<endl;
    cout<<" 11: To UPDATE Email"<<endl;
    cout<<" 12: To UPDATE Pan"<<endl;
    cout<<"*_______________________###___________________________*"<<endl;
    cout<<"Enter here..."<<endl;

    choice_label:
    cin>>choice;
    string new_upadte;
    switch(choice){
        case 1:{
        index=1;
        cout<<"Enter new Name"<<endl;
        break;
        }

        case 2:{
        index=2;
        cout<<"Enter new Type"<<endl;
        break;
        }

        case 3:{
        index=3;
        cout<<"Enter new Address"<<endl;
        break;
        }

        case 4:{
        index=4;
        cout<<"Enter street name"<<endl;
        break;
        }

        case 5:{
        index=5;
        cout<<"Enter colony"<<endl;
        break;
        }
        
        case 6:{
        index=6;
        cout<<"Enter new City"<<endl;
        break;
        }

        case 7:{
        index=7;
        cout<<"Enter new State"<<endl;
        break;
        }

        case 8:{
        index=8;
        cout<<"Enter new Country"<<endl;
        break;
        }

        case 9:{
        index=9;
        cout<<"Enter new Pincode"<<endl;
        break;
        }

        case 10:{
        index=10;
        cout<<"Enter new Phone Number"<<endl;
        break;
        }

        case 11:{
        index=11;
        cout<<"Enter new Email"<<endl;
        break;
        }

        case 12:{
        index=12;
        cout<<"Enter new Pan"<<endl;
        break;
        }

        default:{
        cout<<"Wrong choice..Try Again..."<<endl;
        goto choice_label;
        }
    }

	cin.ignore(1);
    new_data:
	getline (cin,new_upadte);
    if(index==9){
        const regex pattern1("^[1-9]{1}[0-9]{2}\\s{0,1}[0-9]{3}$");
        if(new_upadte.empty()){
            cout<<"Pin code can't be empty"<<endl;
            goto new_data;
        }
        if (regex_match(new_upadte, pattern1)==false){
            cout<<"Invalid Pincode"<<endl;
            goto new_data;
        }
    }
        else if(index==10){
            const regex pattern2("(0|91)?[6-9][0-9]{9}");
        if(regex_match(new_upadte, pattern2)==false){
            cout<<"Invalid Mobile Number"<<endl;
            goto new_data;
        }
    }
    else if(index==11){
        if(is_valid(new_upadte)==false){
            cout<<"Invalid Email!"<<endl;
            goto new_data;
    }
    }
    else if(index==12){
        const regex pattern3("[A-Z]{5}[0-9]{4}[A-Z]{1}");
        if(new_upadte.empty()){
            cout<<"Pan Number Can't be empty"<<endl;
            goto new_data;
        }
        if(regex_match(new_upadte, pattern3)==false){
            cout<<"Invalid Pan Number"<<endl;
            goto new_data;
        }
    }

	// Traverse the file
	while (!fin.eof()) {

		row.clear();

		getline(fin, line);
		stringstream s(line);

		while (getline(s, word, ',')) {
			row.push_back(word);
		}

		uid1 = stoi(row[0]);
		int row_size = row.size();

		if (uid1 == uid) {
			count = 1;

			
			row[index] = new_upadte;

			if (!fin.eof()) {
				for (i = 0; i < row_size - 1; i++) {

					// write the updated data
					// into a new file 'reportcardnew.csv'
					// using fout
					fout <<row[i]<< ",";
				}

				fout <<row[row_size - 1]<<endl;
			}
		}
		else {
			if (!fin.eof()) {
				for (i = 0; i < row_size - 1; i++) {

					// writing other existing records
					// into the new file using fout.
					fout <<row[i]<< ",";
				}

				// the last column data ends with a '\n'
				fout <<row[row_size - 1]<<endl;
			}
		}
		if (fin.eof())
			break;
	}
	if (count == 0)
		cout << "Record not found\n";
    else
    cout<<"Record Updated Successfully..."<<endl;    

	fin.close();
	fout.close();

	// removing the existing file
	remove("customer.csv");

	// renaming the updated file with the existing file name
	rename("new_customer.csv", "customer.csv");
}


void Customer_data()////Function to read CUSTOMER.CSV data/////////
    {
        content.clear();
        row.clear();

        string line, word;

        fstream file("customer.csv", ios::in);
        if (file.is_open())
        {
            while (getline(file, line))
            {
                row.clear();

                stringstream str(line);

                while (getline(str, word, ','))
                    row.push_back(word);
                content.push_back(row);
            }
        }
        else
            cout << "Could not open the user file\n";
    
        for (int i = 0; i < content.size(); i++)
        {
            for (int j = 0; j < content[i].size(); j++)
            {
                cout << content[i][j] << " ";
            }
            cout << "\n";
        }
        cout<<endl;
    }




void customer_detail(int uid){//////READ ONE DATA FROM CUSTOMER.CSV
		//row.clear();
		//content.clear();
		vector<string> row;
		fstream fin;
		int uid2,count=0;
		string line,word,temp;
		fin.open("customer.csv", ios::in);
		while(!fin.eof()){
			row.clear();
			getline(fin,line);
			stringstream s(line);
			while(getline(s,word,',')){
				row.push_back(word);
			}
			uid2=stoi(row[0]);
			if(uid2==uid){
				count=1;
                cout<<"*******************************"<<endl;
				cout<<"CusId: "<<row[0]<<endl;
                cout<<"Name: "<<row[1]<<endl;
                cout<<"Type: "<<row[2]<<endl;
                cout<<"Address1: "<<row[3]<<endl;
                cout<<"streetname: "<<row[4]<<endl;
                cout<<"fullAddress: "<<row[5]<<endl;
                cout<<"City: "<<row[6]<<endl;
                cout<<"State: "<<row[7]<<endl;
                cout<<"Country: "<<row[8]<<endl;
                cout<<"Pin Code: "<<row[9]<<endl;
                cout<<"Phonr Number: "<<row[10]<<endl;
                cout<<"Email: "<<row[11]<<endl;
                cout<<"Pan: "<<row[12]<<endl;
                cout<<"*******************************"<<endl;
				break;
			}
		}
		if(count==0)
		cout<<"Account Number Not Found!"<<endl;
	}








void read_customer_account(int uid){
		//row.clear();
		//content.clear();
		vector<string> row;
		fstream fin;
		int accNo2,count=0;
		string line,word,temp;
		fin.open("account.csv", ios::in);
		while(!fin.eof()){
			row.clear();
			getline(fin,line);
			stringstream s(line);
			while(getline(s,word,',')){
				row.push_back(word);
			}
			accNo2=stoi(row[0]);
			if(accNo2==uid){
				count=1;
				cout<<"AccNo: "<<row[0]<<", Type: "<<row[1]<<", CustomerID: "<<row[2]<<", Status: "<<row[3]<<", Balance: "<<row[4]<<", Opening Date"<<row[5]<<endl;
			}
		}
		if(count==0)
		cout<<"Account Number Not Found!"<<endl;
	}

};
