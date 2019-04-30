#include "Car.h"
#include <string>


Car::Car()
{
}

Car::Car(std::string owner, int id, int regNumber)
{
	this->owner = owner;
	this->id = id;
	this->regNumber = regNumber;
}

Car::Car(const Car & car)
{
	this->owner = car.owner;
	this->id = car.id;
	this->regNumber = car.regNumber;
}

Car & Car::operator=(const Car & car)
{
	if (this != &car)
	{
		this->owner = car.owner;
		this->id = car.id;
		this->regNumber = car.regNumber;
	}
	return *this;
}

Car::~Car()
{
}

int Car::getId() const
{
	return id;
}

int Car::getRegNumber() const
{
	return regNumber;
}

int Car::getPower() const
{
	int power = 0;
	switch (id)
	{
	case 0:
		power = 670;
		break;
	case 1:
		power = 503;
		break;
	case 2:
		power = 740;
		break;
	case 3:
		power = 1020;
		break;
	}
	return power;
}

std::string Car::getOwnerName() const
{
	return owner;
}

std::istream & operator>>(std::istream & in, Car & car)
{
	in >> car.owner >> car.id >> car.regNumber;
	return in;
}

std::ostream & operator<<(std::ostream & out, const Car& car)
{
	out << car.owner << " " << car.id << " " << car.regNumber << '\n';
	return out;
}

