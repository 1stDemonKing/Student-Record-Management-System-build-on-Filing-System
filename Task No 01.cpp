#include<iostream>
#include<fstream>
using namespace std;
int menu();
void inputData(char*, char*, int&);
int insertMenu();
void insertRecod(const char*);
void insertAtStart(const char*,char*,char*,int);
void insertAtEnd(const char*, char*, char*, int);
void insertAt(const char*, char*, char*, int);
void duplicateData(const char* writingFile, const char* readingFile,int =0);
void readTill(ifstream&,int);
int positiveNumber();
bool match(char*, char*, int = 0);
bool updateRecord(const char* );
bool deleteRecord(const char*);
void display(const char*);
int main()
{
	const char* filename = "StudentRecord.csv";
	char arr1[] = "hello";
	char arr2[] = "hello";
	int option = 0;
	
	do
	{
		option = menu();
		if (option == 1)
			insertRecod(filename);
		else if (option == 2)
			if (updateRecord(filename))
				cout << "Data Updated Sucessufully" << endl << endl;
			else
				cout << "Record doesn't exist" << endl << endl;
		else if (option == 3)
			if (deleteRecord(filename))
				cout << "Data Updated Sucessufully" << endl << endl;
			else
				cout << "Record doesn't exist" << endl << endl;
		else if (option == 4)
			display(filename);
	} while (option != 5);
}
int menu()
{
	int choice = 0;
	cout << "Press 1 for insert student record in a csv file comma separated value" << endl;
	cout << "Press 2 for update student record in a csv file comma separated value" << endl;
	cout << "Press 3 for delete student record in a csv file comma separated value" << endl;
	cout << "Press 4 for display all student records of a csv file comma separated value" << endl;
	cout << "Press 5 for terminate the program" << endl;
	cout << "Enter your choice: ";
	cin >> choice;
	cout << endl;
	return choice;
}
int insertMenu()
{
	int choice = 0;
	cout << "Press 1 for insert at start in a csv file comma separated value" << endl;
	cout << "Press 2 for insert at end in a csv file comma separated value" << endl;
	cout << "Press 3 for insert at specific position in a csv file comma separated value" << endl;
	cout << "Enter your choice: ";
	cin >> choice;
	cout << endl;
	return choice;
}
void inputData(char* name, char* contact, int& age)
{
	const int size = 100;
	cout << "Enter your name: ";
	cin.getline(name, size - 1);
	cout << "Enter your age: ";
	cin >> age;
	cin.ignore();
	cout << "Enter your contact: ";
	cin.getline(contact, size - 1);
	cout << endl;
	//cin.ignore();
}
void insertRecod(const char* filename)
{
	const int size = 100;
	char name[size]{};
	char contact[size]{};
	int age = 0;
	int choice = insertMenu();
	cin.ignore();
	if (choice == 1)
	{
		inputData(name, contact, age);
		insertAtStart(filename, name, contact, age);
	}
	else if (choice == 2)
	{
		inputData(name, contact, age);
		insertAtEnd(filename, name, contact, age);

	}
	else if (choice == 3)
	{
		inputData(name, contact, age);
		insertAt(filename, name, contact, age);
	}
}
void insertAtStart(const char*filename, char* name, char* contact, int age)
{
	const int size = 100;
	ifstream fin(filename);
	if (!fin)
		cout << "File doesn't exist" << endl;
	else
	{
		ofstream fout("temp.csv");
		fout << name << ',' << age << ',' << contact << endl;
		while (fin.getline(name, size, ','))
		{
			fin >> age;
			fin.ignore();
			fin.getline(contact, size);
			fout << name << ',' << age << ',' << contact << endl;
		}
		fin.close();
		fout.close();
		duplicateData(filename, "temp.csv");
	}
	
	
}
void duplicateData(const char* writingFile, const char* readingFile,int limit)
{
	const int size = 100;
	char line[size]{};
	ifstream fin(readingFile);
	if (!fin)
		cout << "File doesn't exist" << endl;
	else
	{
		ofstream fout(writingFile);

		if (!limit)
			while (fin.getline(line, size))
				fout << line << endl;
		else
			for (int x = 0; x < limit; x++)
			{
				fin.getline(line, size);
				fout << line << endl;
			}
		
		fin.close();
		fout.close();
	}
}
void readTill(ifstream& fin,int limit)
{
	const int size = 100;
	char line[size]{};
	for (int x = 0; x < limit; x++)
		fin.getline(line, size - 1);
}
void insertAtEnd(const char* filename, char* name, char* contact, int age)
{
	ofstream fout(filename, ios::app);
	fout << name << ',' << age << ',' << contact << endl;
	fout.close();
}
void insertAt(const char* filename, char* name, char* contact, int age)
{
	const int size = 100;
	char line[size]{};
	int position = 0;
	cout << "Enter the position you want to insert at: ";
	position = positiveNumber();
	cout << endl;
	ifstream fin(filename);
	if (!fin)
		cout << "File doesn't exist" << endl;
	else
	{
		if (position == 1)
			insertAtStart(filename, name, contact, age);
		duplicateData("temp.csv", filename, position-1);
		ofstream fout("temp.csv",ios::app);
		fout << name << ',' << age << ',' << contact << endl;
		readTill(fin, position - 1);
		while (fin.getline(line, size - 1))
			fout << line << endl;
		fin.close();
		fout.close();
		
		duplicateData(filename, "temp.csv");
	}
}
int positiveNumber()
{
	int num = 0;
	cin >> num;
	while (num < 1)
	{
		cout << "Enter a value greather than 0" << endl;
		cout << "Enter the value: ";
		cin >> num;
	}
	return num;
}
bool updateRecord(const char* filename)
{
	const int size = 100;
	char name[size]{};
	char contact[size]{};
	int age = 0;
	char rName[size]{};
	char rContact[size]{};
	int rAge = 0;
	bool lamp = false;
	cin.ignore();
	cout << "Enter the data that to be updated" << endl;
	inputData(name, contact, age);
	ifstream fin(filename);
	if (!fin)
		cout << "File doesn't exist" << endl;
	else
	{
		ofstream fout("temp.csv");
		while (fin.getline(rName, size - 1, ','))
		{
			
			fin >> rAge;
			fin.ignore();
			fin.getline(rContact, size - 1);
			if (match(name, rName) && match(contact, rContact) && age == rAge)
			{
				cout << "Enter the values to update" << endl;
				inputData(name, contact, age);
				fout << name << ',' << age << ',' << contact << endl;
				lamp = true;
			}
			else
				fout << rName << ',' << rAge << ',' << rContact << endl;
		}
		duplicateData(filename, "temp.csv");
		fin.close();
		fout.close();
	}
	return lamp;
}
bool match(char* arr1, char* arr2, int x)
{
	if ((arr1[x] == '\0' && arr2[x] != '\0')|| (arr1[x] != '\0' && arr2[x] == '\0'))
		return false;
	if (arr1[x] != arr2[x])
		return false;
	if (arr1[x] == '\0' && arr2[x] == '\0')
		return true;
	match(arr1, arr2, ++x);
}
bool deleteRecord(const char* filename)
{
	const int size = 100;
	char name[size]{};
	char contact[size]{};
	int age = 0;
	char rName[size]{};
	char rContact[size]{};
	int rAge = 0;
	bool lamp = false;
	cin.ignore();
	cout << "Enter the data that to be deleted" << endl;
	inputData(name, contact, age);
	ifstream fin(filename);
	if (!fin)
		cout << "File doesn't exist" << endl;
	else
	{
		ofstream fout("temp.csv");
		while (fin.getline(rName, size - 1, ','))
		{

			fin >> rAge;
			fin.ignore();
			fin.getline(rContact, size - 1);
			if (match(name, rName) && match(contact, rContact) && age == rAge)
				lamp = true;
			else
				fout << rName << ',' << rAge << ',' << rContact << endl;
		}
		duplicateData(filename, "temp.csv");
		fin.close();
		fout.close();
	}
	return lamp;
}
void display(const char* filename)
{
	ifstream fin(filename);
	const int size = 100;
	char line[size]{};
	if (!fin)
		cout << "File doesn't exist" << endl;
	else
	{
		while (fin.getline(line, size))
			cout << line << endl;
		cout << endl;
		fin.close();
	}
}