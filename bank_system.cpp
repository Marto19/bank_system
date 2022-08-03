#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;

class account {
private:
	int account_number;
	char persons_name[50];
	char type_of_account;
	unsigned int deposit;
	unsigned int withdraw_am;
public:
	void new_account();					//funtcion that will creates a new account, takes data from the user
	void show_account()const;			//function that shows the account details
	void modify_account();				//function that will let the user modify/add new data
	void deposit_amount(int x);			//function to deposit money, add to balance 
	void withdraw_amount(int x);		//function to withdraw money, substract from balance
	void tab_report();					//function to show data in tabular format
	int return_acc_number() const;		//function to return account number
	int return_balance() const;			//function to return accounts balance
	char return_type() const;			//function to return type of account
	void close_account();				//function to close account

	account(){}						//default constructor
	/*account(int Account_number, char Persons_name, unsigned int Deposit, unsigned int Withdraw_amount,
		char Type_of_account) {
		account_number = Account_number;
		persons_name[50] = Persons_name;
		deposit = Deposit;
		Withdraw_amount = withdraw_am;
		type_of_account = Type_of_account;
	}*/
};

void account::new_account() {
	cout << "\n Enter the account number(for example 108): ";
	cin >> account_number;

	cout << "\n Enter your name(for example MARTIN): ";
	cin.ignore();
	cin.getline(persons_name, 50);

	cout << "\n Enter type of account(C-for Current / S-for Saving): ";
	cin >> type_of_account;
	type_of_account = toupper(type_of_account);

	cout << "\n Enter the initial amount (100$ or more for Saving and 200$ or more for Current)";
	cin >> deposit;
	if (deposit >= 100 && deposit <= 199) {
		cout << "Account created successfully. Deposit for savings account." << endl;
	}
	else if (deposit < 100) {
		cout << "\n Please enter valid amount(must be atleast 100$)" << endl;
		while (deposit < 100) {
			cout << "Enter again: ";
			cin >> deposit;
			cout << endl;
		}
		cout << "\nAccount created successfully." << endl;
	}
	else {
		cout << "\nAccount created successfully." << endl;
	}
}

void account::show_account()const{
	cout << "\n Account number: " << account_number;
	cout << "\n Acount holder: " << persons_name;
	cout << "\n Type of account: " << type_of_account;
	cout << "\n Last deposit: " << deposit;
}

void account::modify_account() {
	cout << "You've entered the funtion to modify your current account." << endl;

	cout << "\n Account number: ";
	cin >> account_number;

	cout << "\n Modify Name: ";
	cin.ignore();
	cin.getline(persons_name, 50);

	cout << "\n Modify type of account: ";
	cin >> type_of_account;
	type_of_account = toupper(type_of_account);

	cout << "\n Modify current account balance:";
	cin >> deposit;
}

void account::deposit_amount(int x) {
	deposit += x;
}

void account::withdraw_amount(int x) {
	deposit -= x;
}

void account::tab_report() {
	cout << account_number << setw(10) << " " << type_of_account << setw(6) << deposit << endl;
}

int account::return_acc_number() const{
	return account_number;
}

int account::return_balance() const {
	return deposit;
}

char account::return_type() const {
	return type_of_account;
}

//below this line is the function declaration

void write_account(); 				//function to write data to the binary file
void show_acc_details(int); 		//function to show account details
void modify_acc(int); 				//function to modify account details in the binary file
void delete_acc(int); 				//function to delete account records from the binary file
void display_all(); 				//function to display all the account records from the binary file
void deposit_withdraw(int, int); 	//function to deposit or withdraw money from the account
void intro(); 						//function to display the intro screen

int main() {
	char ch;
	int num;
	intro();

	do{
		system("cls");
		cout << "\n\n\n\t MAIN MENU";
		cout << "\n\n\t 1. Create a new account";
		cout << "\n\n\t 2. Deposit from an existing account";
		cout << "\n\n\t 3. Withdraw from an existing account";
		cout << "\n\n\t 4. Balance enquiry";
		cout << "\n\n\t 5. All account holder list";
		cout << "\n\n\t 6. Close an account";
		cout << "\n\n\t 7. Modify an existing account";
		cout << "\n\n\t 8. Exit";
		cout << "\n\n\t Enter your choice(by number): ";
		cin >> ch;

		switch(ch){
		case '1':
			write_account();
			break;
		case '2':
			cout << "\n Enter the account number: ";
			cin >> num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout << "\n Enter the account number: ";
			cin >> num;
			deposit_withdraw(num, 2);
			break;
		case '4':
			cout << "\n Enter the account number: ";
			cin >> num;
			show_acc_details(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout << "\n Enter the account number: ";
			cin >> num;
			delete_acc(num);
			break;
		case '7':
			cout << "\n Enter the account number: ";
			cin >> num;
			modify_acc(num);
			break;
		case '8':
			cout << "\n\n\t Thank you for using our bank services.";
			break;
		default:
			cout << "\a";
		}
		cin.ignore();
		cin.get();
	}while(ch != '8');
	return 0;
}

//function to write in file

void write_account() {
	account acc;
	ofstream outFile;
	outFile.open("account.dat", ios::binary | ios::app);
	acc.new_account();
	outFile.write(reinterpret_cast<char *> (&acc), sizeof(account));
	outFile.close();
}

//function to read specific record from file

void show_acc_details(int num) {
	account acc;
	bool flag = false;
	ifstream inFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile) {
		cout << "\n File could not be open !! Press any key to exit. ";
		return;
	}
	while (inFile.read(reinterpret_cast<char *> (&acc), sizeof(account))) {
		if (acc.return_acc_number() == num) {
			acc.show_account();
			flag = true;
		}
	}
	inFile.close();
	if (flag == false) {
		cout << "\n No record found/Account number does not exist";
	}
}

void modify_acc(int n){
	bool found = false;
	account acc;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if(!File){
		cout << "File could not be open !! Press any key to exit...";
		return;
	}
	while(!File.eof() && found == false ){
		File.read(reinterpret_cast<char *> (&acc), sizeof(account));
		if(acc.return_acc_number() == n){
			acc.show_account();
			cout << "\n\n\t Do you want to modify this record(y/n)?";
			acc.modify_account();
			int pos = (-1)*static_cast<int>(sizeof(account));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char *> (&acc), sizeof(account));
			cout << "\n\n\t Record Updated";
			found = true;
		}
	}
	File.close();
	if(found == false){
		cout << "\n\n Record not found ";
	}
}

//function to delete record from file

void delete_acc(int n){
	account acc;
	ifstream inFile;
	ofstream outFile;
	inFile.open("accountq.dat", ios::binary);
	outFile.open("temp.dat", ios::binary);
	if(!inFile){
		cout << "File could not be open !! Press any key to exit...";
		return;
	}
	outFile.open("temp.dat", ios::binary);
	inFile.seekg(0, ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&acc), sizeof(account))){
		if(acc.return_acc_number() != n){
			outFile.write(reinterpret_cast<char *> (&acc), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("temp.dat", "account.dat");
	cout << "\n\n\tRecord Deleted...";
}

//function to display all account deposit list

void display_all(){
	account acc;
	ifstream inFile;
	inFile.open("account.dat" , ios::binary);
	if(!inFile){
		cout << "File could not be open !! Press any key to exit...";
		return;
	}
	cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout << "====================================================\n";
	cout << "Account Number		Name	 Balance\n\n";
	cout << "====================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&acc), sizeof(account))){
		acc.show_account();
	}
	inFile.close();
}

//function to deposit or withdraw amount from account

void deposit_withdraw(int n, int option){
	int amount;
	bool found = false;
	account acc;
	fstream File;
	File.open("account.dat" , ios::binary | ios::in | ios::out);
	if(!File){
		cout << "File could not be open !! Press any key to exit...";
		return;
	}
	while(!File.eof() && found == false){
		File.read(reinterpret_cast<char *> (&acc), sizeof(account));
		if(acc.return_acc_number() == n){
			acc.show_account();
			if(option == 1){
				cout << "\n\n\t How much do you want to deposit?";
				cin >> amount;
				acc.deposit_amount(amount);
			}
			else{
				cout << "\n\n\t How much do you want to withdraw?";
				cin >> amount;
				acc.withdraw_amount(amount);
			}
		}
	}
	File.close();
	if(found == false){
		cout << "\n\n Record not found ";
	}
}


//intro function

void intro(){
	cout << "\n\n\n\t BANK";
	cout << "\n\n\tMANAGEMENT";
	cout << "\n\n\tSYSTEM";
	cout << "\n\n\n\nMADE BY: MARTIN TRENKOV";
	cout << "\n\nUNIVERSITY: NEW BULGARIAN UNIVERSITY";
}