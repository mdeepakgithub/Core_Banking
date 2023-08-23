#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <cmath>
using namespace std;
class Bank
{
private:
    /* data */
    vector<string> row;
	vector< vector<string> > content;
	int AccountIDSrc,AccountIDDst,TransID,Account_Number;
	char type;
	double Amount;
public:
    //account(/* args */);
    void update_amount()////Functon to update ACCOUNT.CSV//////// 1
{
    cout<<"Transfer Money"<<endl;
	// File pointer
	fstream fin, fout;
    // Open an existing record
	fin.open("account.csv", ios::in);
    // Create a new file to store updated data
	fout.open("new_account.csv", ios::out);
    int acc ,count1 = 0,count2 = 0;
	int index;
	string line, word;
    cout << "Enter the Acc. Number form which you want to debit the money: "<<endl;
    cin>>AccountIDSrc;
    cout << "Enter the Acc. Number for credit the money: "<<endl;
    cin>>AccountIDDst;
    cout<<"Enter Amount"<<endl;
    cin>>Amount;
    bool a =false,b=false;
    while (!fin.eof()) {
		row.clear();
		getline(fin, line);
		stringstream s(line);
		while (getline(s, word, ',')) {
			row.push_back(word);
		}
            if(stoi(row[0])==AccountIDSrc)
            a=true;
            else if(stoi(row[0])==AccountIDDst)
            b=true;
    }
	fin.close();
	fin.open("account.csv", ios::in);


    if(a && b){
/*DEBIT AND CREDIT*/
while (!fin.eof()) {
		row.clear();

		getline(fin, line);
		stringstream s(line);
		while (getline(s, word, ',')) {
			row.push_back(word);
		}

		acc = stoi(row[0]);
		int row_size = row.size();

		if (acc == AccountIDSrc) {
			double ans=stod(row[4])- Amount;
			ans=round(ans*100);
			ans=ans/100;
			count1 = 1;
			//stringstream convert;
			//convert<<credit;
			row[4] =to_string(ans);

			if (!fin.eof()) {
				for (int i = 0; i < row_size - 1; i++) {
					fout <<row[i]<< ",";
				}

				fout <<row[row_size - 1]<<endl;
			}
		}
        else if(acc==AccountIDDst){
			double ans=stod(row[4])+ Amount;
			ans=round(ans*100);
			ans=ans/100;
			count2 = 1;
			//stringstream convert;
			//convert<<credit;
			row[4] =to_string(ans);

			if (!fin.eof()) {
				for (int i = 0; i < row_size - 1; i++) {
					fout <<row[i]<< ",";
				}

				fout <<row[row_size - 1]<<endl;
			}
        }
		else {
			if (!fin.eof()) {
				for (int i = 0; i < row_size - 1; i++) {
					fout <<row[i]<< ",";
				}
				fout <<row[row_size - 1]<<endl;
			}
		}
		if (fin.eof())
			break;
	}
    }

	if ((count1 == 1) && (count2 == 1))
		cout <<"Rs."<< Amount<<" amount transfered!"<<endl;
    else{
        if(a==false)
        cout<<"Account "<<AccountIDSrc<<" not found"<<endl; 
        if(b==false)
        cout<<"Account "<<AccountIDDst<<" not found"<<endl; 
    }   

	fin.close();
	fout.close();

	// removing the existing file
	remove("account.csv");

	// renaming the updated file with the existing file name
	rename("new_account.csv", "account.csv");
	appendToTransactionFile();
}





void data()////Function to read TRANSACTION.CSV data/////////  2
    {
        content.clear();
        row.clear();

        string line, word;

        fstream file("transaction.csv", ios::in);
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
        // else
        //     cout << "Could not open the transaction file\n";
    }



void appendToTransactionFile()//Function to add data in TRANSACTION.CSV / 3
    {
        fstream fout;
        data();
        TransID=content.size()+1;
        
        fout.open("transaction.csv", ios::out | ios::app);
        if (!fout)
        {
            cout << "ERROR IN CREATING FILE USER.CSV" << endl;
            return;
        }
		Account_Number=AccountIDSrc;
		type='C';
        fout << TransID << "," << type << "," << AccountIDSrc << "," << AccountIDDst<< "," << Amount <<","<<Account_Number<< endl;

		Account_Number=AccountIDDst;
		type='D';
        fout << TransID+1 << "," << type << "," << AccountIDSrc << "," << AccountIDDst<< "," << Amount <<","<<Account_Number<< endl;
        fout.close();
	}



	void customer_transactions(int accNo){  //4
		vector<string> row;
		fstream fin;
		int accNo2,count=0;
		string line,word,temp;
		fin.open("transaction.csv", ios::in);
		while(!fin.eof()){
			row.clear();
			getline(fin,line);
			stringstream s(line);
			while(getline(s,word,',')){
				row.push_back(word);
			}
			accNo2=stoi(row[5]);
			if(accNo2==accNo){
				count=1;
				cout<<"Trans id: "<<row[0]<<", Trans type: "<<row[1]<<", src: "<<row[2]<<", des: "<<row[3]<<", amt: "<<row[4]<<endl;
			}
		}
		if(count==0)
		cout<<"Account Number Not Found!"<<endl;
	}
void update_amount_record(int src)     //5
{

    cout<<"Transfer Amount..."<<endl;
	// File pointer
	fstream fin, fout;

	// Open an existing record
	fin.open("account.csv", ios::in);

	// Create a new file to store updated data
	fout.open("new_account.csv", ios::out);

	int acc ,count1 = 0,count2 = 0;
	int index;
	string line, word;

	AccountIDSrc=src;
    cout << "Please provide Acc. Number for credit Amount: "<<endl;
    cin>>AccountIDDst;

    cout<<"Enter Amount"<<endl;
    cin>>Amount;
    bool a =false,b=false;
    while (!fin.eof()) {
		row.clear();
		getline(fin, line);
		stringstream s(line);
		while (getline(s, word, ',')) {
			row.push_back(word);
		}
            if(stoi(row[0])==AccountIDSrc)
            a=true;
            else if(stoi(row[0])==AccountIDDst)
            b=true;
    }
	fin.close();
	fin.open("account.csv", ios::in);


    if(a && b){

while (!fin.eof()) {
		row.clear();

		getline(fin, line);
		stringstream s(line);
		while (getline(s, word, ',')) {
			row.push_back(word);
		}

		acc = stoi(row[0]);
		int row_size = row.size();

		if (acc == AccountIDSrc) {
			double ans=stod(row[4])- Amount;
			count1 = 1;
			row[4] =to_string(ans);

			if (!fin.eof()) {
				for (int i = 0; i < row_size - 1; i++) {
					fout <<row[i]<< ",";
				}

				fout <<row[row_size - 1]<<endl;
			}
		}
        else if(acc==AccountIDDst){
			double ans=stod(row[4])+ Amount;
			count2 = 1;
			row[4] =to_string(ans);

			if (!fin.eof()) {
				for (int i = 0; i < row_size - 1; i++) {
					fout <<row[i]<< ",";
				}

				fout <<row[row_size - 1]<<endl;
			}
        }
		else {
			if (!fin.eof()) {
				for (int i = 0; i < row_size - 1; i++) {
					fout <<row[i]<< ",";
				}
				fout <<row[row_size - 1]<<endl;
			}
		}
		if (fin.eof())
			break;
	}
    }

	if ((count1 == 1) && (count2 == 1))
		cout << Amount<<" amount transfered!"<<endl;
    else{
        if(a==false)
        cout<<"Account "<<AccountIDSrc<<" not found"<<endl; 
        if(b==false)
        cout<<"Account "<<AccountIDDst<<" not found"<<endl; 
    }   

	fin.close();
	fout.close();

	// removing the existing file
	remove("account.csv");

	// renaming the updated file with the existing file name
	rename("new_account.csv", "account.csv");
	appendToTransactionFile();
}

};
