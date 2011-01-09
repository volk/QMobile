#ifndef REFILL_HPP
#define REFILL_HPP

class QString;
template <class T>
class QList;

class Refuel
{
	public:
		Refuel();
		Refuel(QDate date, double distance, double price, double volume);
		void setDate(const QDate& q);
		void setDistance(double q);
		void setPrice(double q);
		void setVolume(double q);
		QDate& date();
		double distance();
		double price();
		double volume();
		//debugging purposes
		void print();

	private:
		QDate _date;
		double _distance;
		double _price;
		double _volume;

};

#endif
