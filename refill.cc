#include <QtCore>

#include "refill.hpp"

Refill::Refill(){}
void Refill::setDate(const QDate& q){ _date = q; }
void Refill::setMiles(double q){ _miles = q; }
void Refill::setPrice(double q){ _price = q; }
void Refill::setVolume(double q){ _volume = q; }

QDate Refill::date(){ return _date; }
double Refill::miles(){ return _miles; }
double Refill::price(){ return _price; }
double Refill::volume(){ return _volume; }
