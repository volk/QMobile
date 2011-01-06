#ifndef VEHICLE_HPP
#define VEHICLE_HPP

class QString;
template <class T>
class QList;
class Refill;

class Vehicle
{
	public:
		Vehicle();
		void setMake(const QString& q);
		void setModel(const QString& q);
		void setYear(int q);
		int year();
		QString model();
		QString make();

	private:
		QString _make;
		QString _model;
		int _year;
		//QList<Refill> _refills;
};

#endif
