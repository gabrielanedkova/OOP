#include <iostream>
#include <sstream>
#include <string>
#include "Car.h"
using namespace std;


void saveCarsToBinaryFile(const Car* cars, int size)
{
	ofstream out("db-save.dat", ios::binary);
	for (int i = 0; i < size; ++i)
	{
		out << cars[i];
	}
	out.close();
}
double getAveragePower(const Car* cars, int size)
{
	int sum = 0;
	for (int i = 0; i < size; ++i)
	{
		sum += cars[i].getPower();
	}
	double avgPower = sum / size;
	return avgPower;
}

int getMax(int counter[4])
{
	int value = 0;
	int index = 0;
	for (int i = 0; i < 4; ++i)
	{
		if (counter[i] > value)
		{
			value = counter[i];
			index = i;
		}
	}
	return index;
}

string getMostPopularCar(const Car* cars, int size)
{
	int counter[4]{};
	string carName;
	for (int i = 0; i < size; ++i)
	{
		counter[cars[i].getId()]++;
	}
	int max = getMax(counter);
	switch (max)
	{
	case 0:
		carName =  "Lambordgini Murcielago";
		break;
	case 1:
		carName =  "Mercedes - AMG";
		break;
	case 2:
		carName =  "Pagani Zonda R";
		break;
	case 3:
		carName = "Bugatti Veyron";
		break;
	}
	return carName;
}

bool isRegNumberUnique(const Car* cars, int size, Car car)
{
	for (int i = 0; i < size; ++i)
	{
		if (cars[i].getRegNumber() == car.getRegNumber())
			return false;
	}
	return true;
}
int linesCount()
{
	int counter = 0;
	ifstream in("db-save.dat", ios::binary);
	string line;
	while (getline(in, line))
	{
		++counter;
	}
	in.close();
	return counter;
}
void loadCarsFromFile(Car*& cars, int& size)
{
	size = linesCount();
	cars = new Car[size];
	ifstream in("db-save.dat", ios::binary);
	for (int i = 0; i < size; ++i)
	{
		in >> cars[i];
	}
	in.close();
}

bool addNewCar(Car*& cars, int& size, const Car& car)
{
	if (!isRegNumberUnique(cars, size, car))
		return false;
	Car* temp = new Car[size + 1];
	for (int i = 0; i < size; ++i)
	{
		temp[i] = cars[i];
	}
	temp[size++] = car;
	delete[] cars;
	cars = temp;
	return true;
}
bool* getUniqueOwners(const Car* cars, int size)
{
	bool* isUniqie = new bool[size];
	for (int i = 0; i < size; ++i)
	{
		isUniqie[i] = true;
		for (int j = 0; j < i; j++)
		{
			if (cars[i].getOwnerName() == cars[j].getOwnerName())
			{
				isUniqie[i] = false;
				break;
			}
		}
	}
	return isUniqie;
}
int getTotalPowerForOwner(const Car* cars, int size, int index, string name)
{
	int totalPower = cars[index].getPower();
	for (int i = index + 1; i < size; ++i)
	{
		if (name == cars[i].getOwnerName())
		{
			totalPower += cars[i].getPower();
		}
	}
	return totalPower;
}
void generateTxtFile(const Car* cars, int size)
{
	if (size < 1)
		return;
	ofstream out("car-report.txt");
	out << "Most popular car: " << getMostPopularCar(cars, size) << endl;
	out << "Average power: " << getAveragePower(cars, size) << endl;
	bool* uniqueOwners = getUniqueOwners(cars, size);
	for (int i = 0; i < size; ++i)
	{
		if (uniqueOwners[i])
		{
			out << "Owner name: " << cars[i].getOwnerName();
			out << " Total power: "<< getTotalPowerForOwner(cars, size, i, cars[i].getOwnerName()) << endl;
		}
	}
	out.close();
}

void printMenu()
{
	cout << "----------Menu----------------" << endl;
	cout << "------1.Add car---------------" << endl;
	cout << "------2.Generate file(txt)----" << endl;
	cout << "------3.Generate file(binary)-" << endl;
	cout << "------4.Exit------------------" << endl;
	cout << "Select option: ";
}

void printIdOptions()
{
	cout << "------0.Lambordgini Murcielago-----" << endl;
	cout << "------1.Mercedes - AMG-------------" << endl;
	cout << "------2.Pagani Zonda R-------------" << endl;
	cout << "------3.Bugatti Veyron-------------" << endl;
	cout << "Select option: ";
}
int main()
{
	Car* cars = nullptr;
	int size = 0;
	loadCarsFromFile(cars, size);
	int option;
	do
	{
		printMenu();
		cin >> option;
		switch (option)
		{
		case 1:
		{
			string owner;
			int id;
			int regNumber;
			cout << "Enter owner name(up to 23 signs): ";
			cin >> owner;
			if (owner.size() > 23)
			{
				cout << "Invalid name. Please try again!" << endl;
				continue;
			}
			printIdOptions();
			cout << "Enter id: ";
			cin >> id;
			if (id < 0 || id > 3)
			{
				cout << "Invalid id. Please try again!" << endl;
				continue;
			}
			if (id < 0 || id > 3)
			{
				cout << "Invalid id. Please try again!" << endl;
				continue;
			}
			cout << "Enter registration number(number between 1000 and 9999): ";
			cin >> regNumber;
			if (regNumber < 1000 || regNumber > 9999)
			{
				cout << "Invalid registration number. Please try again!" << endl;
			}
			Car car(owner, id, regNumber);
			if (!addNewCar(cars, size, car))
			{
				cout << "The registration is already taken. Record not added." << endl;
			}
		}
			break;
		case 2:
			generateTxtFile(cars, size);
			break;
		case 3:
			saveCarsToBinaryFile(cars, size);
			break;
		}
	} while (option != 4);

	system("pause");
}