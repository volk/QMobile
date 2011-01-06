#include <QtCore>

#include "vehicle.hpp"

Vehicle::Vehicle(){}

void Vehicle::setMake(const QString& q){ _make = q; }
void Vehicle::setModel(const QString& q){ _model = q; }
void Vehicle::setYear(int q){ _year = q; }

		
int Vehicle::year(){ return _year; }
QString Vehicle::model(){ return _model; }
QString Vehicle::make(){ return _make; }

