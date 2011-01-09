#include <QtCore>
#include <iostream>

#include "refill.hpp"

using std::cout;		using std::endl;

Refuel::Refuel() : _date(), _distance(1), _price(1), _volume(1) { }
Refuel::Refuel(QDate date, double distance, double price, double volume) : _date(date), _distance(distance), _price(price), _volume(volume){}

void Refuel::setDate(const QDate& q)
{ 	
	_date.setDate( q.year(), q.month(), q.day() );
}

void Refuel::setDistance(double q)
{ 
	_distance = q; 
}

void Refuel::setPrice(double q)
{ 
	_price = q; 
}

void Refuel::setVolume(double q)
{ 
	_volume = q; 
}

QDate& Refuel::date(){ return _date; }
double Refuel::distance(){ return _distance; }
double Refuel::price(){ return _price; }
double Refuel::volume(){ return _volume; }

void Refuel::print()
{
	//throw exception
	if(_date.isValid())
	{
		cout << _date.month() << "/" << _date.day() << "/" << _date.year() 
			<< " : " << _distance << " mi \t$" << _price << "\t" << _volume << " gallons" << endl;
	}
}
