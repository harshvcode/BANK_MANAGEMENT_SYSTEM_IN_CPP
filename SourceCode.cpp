/*
_._._._._harshvcode_._._._._
hvsreal.223@gmail.com
01:03 AM 18-07-2020
BANK MANAGEMENT SYSTEM IN C++
*/
#include<iostream>
#include<vector>
#include<conio.h>
#include<fstream>
using namespace std;
class Data{
	protected:
		int maxavailable;
		vector<Data> lis;
		string passwd;
	public:
		int ac;
		string fname,sname;
		long  bal;
		void infoApp();
		void welc();
		void view();
		void new_ac();
		void depos();
		void withdr();
		void saver();
		void loader();
		void changePw();
		void delet();
};
string secure(){
	int i = 0;
	char arr[18];
    for(i = 0; i < 18; i++) arr[i] = 0;
	i=0;
	while((arr[i]=getch()) != '\r'){
		cout << '*';
		i++;
	}
	cout << '\n';
	string st = arr;
	return st.substr(0,i);
}
void Data::changePw(){
	system("cls");
	printf("Enter Account No: ");
	int acno;
	cin >> acno;
	printf("Enter your old password: ");
	bool f=false;
	int total = lis.size();
	for(int i = 0; i < total; i++){
		if(lis[i].ac == acno && lis[i].passwd == secure()){
			printf("Enter New Password(less than 18 characters: ");
			lis[i].passwd = secure();
			cout << "\tPassword changed Successfully!\n";
			f = true;
			break;
		}
	}
	if(!f)
		cout<<"Wrong Account No. OR Password Entered!\n";
}
void Data::delet(){
	system("cls");
	printf("Enter Account No: ");
	int acno;
	cin >> acno;
	printf("Enter your account password: ");
	bool f=false;
	int total = lis.size();
	for(int i = 0; i < total; i++){
		if(lis[i].ac == acno && lis[i].passwd == secure()){
			printf("Are you sure to delete your account?(Y/N): ");
			char res;
			cin >> res;
			if(toupper(res) == 'Y'){
				lis.erase(lis.begin() + i);
				cout << "\tAccount Successfully deleted!\n";
				f = true;
				break;
			}
			cout << "Failed to delete Your Account!\n";
			f=true;
		}
	}
	if(!f)
		cout<<"Wrong Account No. OR Password Entered!\n";
}
void Data::view(){
	system("cls");
	printf("Enter Account No: ");
	int acno;
	cin >> acno;
	printf("Enter your account password: ");
	bool f=false;
	for(Data e:lis){
		if(e.ac == acno && e.passwd == secure()){
			cout<<"\n\n{\nAccount No.: "<<e.ac<<'\n';
			cout<<"Name: ";
			int len=e.fname.size();
			for(int i=0; i<len; i++)
				if(e.fname[i] == '-') cout << ' '; else cout <<e.fname[i];
			cout << ' ';
			cout << e.sname<<'\n';
			cout<<"Balance: Rs. "<<e.bal<<"\n}\n\n";
			f=true;
			break;
		}
	}
	if(!f)
			cout<<"Wrong Account No. OR Password Entered!\n";
}
void Data::new_ac(){
	system("cls");
	Data n_en;
	string fn,sn;
	printf("Enter Your First Name(Use \"-\" instead of space): ");
	cin >> fn;
	printf("Enter Your Last Name: ");
	cin >> sn;
	n_en.fname = fn;
	n_en.sname = sn;
	printf("Create your account password(less than 18 characters): ");
	n_en.passwd = secure();
	printf("\nEnter initial amount to be deposited: ");
	long nb;
	cin >> nb;
	n_en.ac = maxavailable++;
	n_en.bal = nb;
	cout << "\nYour New Account Number is: " << n_en.ac << '\n';
	cout << "\tPLEASE, REMEMBER IT FOR FUTURE USE!\n";
	lis.push_back(n_en);
	cout << "\n\t\tCONGRATULATIONS, ACCOUNT CREATED SUCCESSFULLY!\n\n";
}
void Data::depos(){
	system("cls");
	printf("Enter Account No: ");
	int acno;
	cin >> acno;
	long am;
	printf("Enter amount to deposit: ");
	cin >> am;
	bool f = false;
	int total = lis.size();
	for(int i = 0; i < total; i++){
		if(lis[i].ac == acno){
			lis[i].bal = lis[i].bal + am;
			cout << "\t\tCONGRATULATIONS, DEPOSITED SUCCESSFULLY!\n";
			cout << "Your New Balance: Rs. " << lis[i].bal << "\n\n";
			f = true;
			break;
		}
	}
	if(!f)
		cout << "Wrong Account No. Entered!\n";
}
void Data::withdr(){
	system("cls");
	printf("Enter Account No: ");
	int acno;
	cin >> acno;
	long am;
	printf("Enter amount to withdraw: ");
	cin >> am;
	printf("Enter your account password: ");
	bool f = false;
	int total = lis.size();
	for(int i = 0; i < total; i++){
		if(lis[i].ac == acno && lis[i].passwd == secure()){
			if(lis[i].bal-am<0){
				cout<<"\nSorry! You don't have sufficient ";
				cout<<"balance to withdraw this amount\n";
				cout<<"Withdraw Failed!\n\n";
				return;
			}
			lis[i].bal = lis[i].bal - am;
			cout<<"\t\tCONGRATULATIONS, WITHDREW SUCCESSFULLY!\n";
			cout<<"Your New Balance: Rs. "<<lis[i].bal<<"\n\n";
			f = true;
			break;
		}
	}
	if(!f)
			cout << "Wrong Account No. OR Password Entered!\n";
}
void Data::saver(){
	system("cls");
	remove("data.dat");
	ofstream os("data.dat");
	int n=lis.size();
	for(int i=0;i<n;i++){
		os<<lis[i].ac<<' '<<lis[i].fname<<'_'<<lis[i].sname<<' '<<lis[i].passwd<<' '<<lis[i].bal<<'\n';
	}
	os.close();
	cout << "Data was successfully saved!\n\n";
}
void Data::loader(){
	ifstream is("data.dat");
	int acno;
	string nam;
	string passw;
	long am;
	while(is >> acno >> nam >> passw >> am){
		Data n_e;
		n_e.ac=acno;
		maxavailable=max(maxavailable, acno);
		n_e.passwd=passw;
		n_e.bal=am;
		int j=0;
		for(auto i=strtok(&nam[0],"_");i!=NULL;i=strtok(NULL,"_")){
			if(j == 0){ n_e.fname=i;}
			if(j == 1){ n_e.sname=i; j++;break;}
			j++;
		}
		lis.push_back(n_e);
	}
	maxavailable++;
	cout<<"\nData Successfully Loaded!\n\n";
}
void Data::welc(){
	system("cls");
	cout<<"\n\t\t\tWELCOME TO CITY BANK\n";
	cout<<"\t\t     WE ARE HAPPY TO SERVE YOU!\n\n";
}
void Data::infoApp(){
	system("cls");
	cout << "******************************\n";
	cout << "\nCreated By: Harshvardhan Singh\n";
	cout << "Mail: hvsreal.223@gmail.com\n\tOR\n";
	cout << "      harshvardhan.singh_cs18@gla.ac.in\n";
	cout << "Github Link: https://github.com/harshvcode\n";
	cout << "******************************\n\n\n\n";
}
int main(){
	Data obj;
	obj.loader();
	obj.welc();
	while(true){
		printf("\nPress N to create a New Account\n");
		printf("\tPress V to view Account Details\n");
		printf("\t\tPress D to deposit amount\n");
		printf("\t\t\tPress W to withdraw amount\n");
		printf("\t\t\t\tPress C to change Password\n");
		printf("\t\t\t\t\tPress R to delete your account\n");
		printf("\t\t\t\t\t\tPress E to exit\n");
		printf("\t\t\t\t\t\t\tPress I to see About Info of this application: ");
		char res;
		cin >> res;
		res = toupper(res);
		if(res == 'N') obj.new_ac();
		else if(res == 'V') obj.view();
		else if(res == 'D') obj.depos();
		else if(res == 'W') obj.withdr();
		else if(res == 'C') obj.changePw();
		else if(res == 'R') obj.delet();
		else if(res == 'E'){
			char res;
			printf("Do you want to save the Account's Data(Y/N): ");
			cin >> res;
			if(toupper(res) == 'Y'){
				obj.saver();
			}
			cout << "\n\tSee you soon\n\n";
			break;
		}
		else if(res == 'I') obj.infoApp();
		else{
			system("cls");
			cout << "\tWrong value pressed\n\tTry Again!\n";
		}
	}
	return 0;
}
