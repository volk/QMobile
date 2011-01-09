#include <QtCore>
#include <iostream>
#include <assert.h>

#include "refuel.hpp"
#include "vehicle.hpp"

using std::cout;		using std::endl;

Vehicle::Vehicle(){}
int Vehicle::year(){ return _year; }
QString Vehicle::model(){ return _model; }
QString Vehicle::make(){ return _make; }
void Vehicle::setMake(const QString& q){ _make = q; }
void Vehicle::setModel(const QString& q){ _model = q; }
void Vehicle::setYear(int q){ _year = q; }

void Vehicle::addRefuel(const Refuel& refuel)
{
//	Refuel newRefuel(refuel.date(), refuel.distance(), refuel.price(), refuel.volume());
	Refuel newRefuel(refuel);
	_refuels.push_back(newRefuel);
}

//debugging purposes
void Vehicle::print()
{
	std::cout << std::string(30, '=') << '\n';
	std::cout << "Year : " << _year << '\n';
	std::cout << "Model : " << _model.toStdString() << '\n';
	std::cout << "Make : " << _make.toStdString() << std::endl;

	if(!_refuels.isEmpty())
	{
		for(QList<Refuel>::iterator i = _refuels.begin(); i != _refuels.end() ; ++i)
		{
			(*i).print();
		}
	}
	else
	{
		cout << "No refuels for this vehicle" << endl;
	}
}

 //returns last refuel
Refuel& Vehicle::lastRefuel()
{
	if(_refuels.isEmpty())
	{
		std::cout << "REFUELS IS EMPTY, CANNOT GET TOP" << std::endl;
		assert(true);
		assert(false);
	}

	return _refuels.back();
}
