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
	unsigned int withdraw_amount;
public:
	void new_account();					//funtcion that will creates a new account, takes data from the user
	void show_account()const;			//function that shows the account details
	void modify_account();				//function that will let the user modify/add new data
	void deposit_amount(int x);			//function to deposit money, add to balance 
	void withdraw_amount(int x);		//function to withdraw money, substract from balance
	void tab_report();					//function to show data in tabular format
	int return_acc_number() const;		//function to return account number
	int return_balance() const;			//function to return accounts balance
	void close_account();


	account(int Account_number, char Persons_name, unsigned int Deposit, unsigned int Withdraw_amount,
		char Type_of_account) {
		account_number = Account_number;
		persons_name[50] = Persons_name;
		deposit = Deposit;
		Withdraw_amount = withdraw_amount;
		type_of_account = Type_of_account;
	}
};

void account::new_account() {
	cout << "\n Enter the account number: ";
	cin >> account_number;

	cout << "\n Enter your name: ";
	cin.ignore();
	cin.getline(persons_name, 50);

	cout << "\n Enter type of account: ";
	cin >> type_of_account;
	type_of_account = toupper(type_of_account);

	cout << "\n Enter the initial amount (100$ or more for Saving and 200$ or more for Current)";
	cin >> deposit;
	if (deposit >= 100 && deposit <= 199) {
		cout << "Account created successfully. Deposit for savings account." << endl;
	}
	else if (deposit < 100) {
		cout << "Please enter valid amount(must be atleast 100$)" << endl;
		while (deposit < 100) {
			cout << "Enter again: ";
			cin >> deposit;
			cout << endl;
		}
	}
	else {
		cout << "Account created successfully." << endl;
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
	return 
}

int main() {

	return 0;
}