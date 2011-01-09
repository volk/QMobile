#ifndef VEHICLE_HPP
#define VEHICLE_HPP

class QString;
class Refuel;
template <class T>
class QList;

class Vehicle
{
	public:
		Vehicle();
		void setMake(const QString& q);
		void setModel(const QString& q);
		void setYear(int q);
		void addRefuel(const Refuel&);
		Refuel& lastRefuel(); //returns last refuel
		int year();
		QString model();
		QString make();
		void print(); //debugging purposes

	private:
		QString _make;
		QString _model;
		int _year;
		QList<Refuel> _refuels;
};

#endif
