#pragma once
#include <string>
#include<fstream>
class Car
{
public:
	Car();
	Car(std::string owner, int id, int regNumber);
	Car(const Car& car);
	Car& operator=(const Car& car);
	~Car();
	friend std::istream& operator>>(std::istream& in, Car &car);
	friend std::ostream& operator<<(std::ostream& out, const Car& car);
	int getId()const;
	int getRegNumber()const;
	int getPower()const;
	std::string getOwnerName()const;

private:
	std::string owner;
	int id;
	int regNumber;
};

