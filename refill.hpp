#ifndef REFILL_HPP
#define REFILL_HPP

class QString;
template <class T>
class QList;

class Refill
{
	public:
		Refill();
		void setDate(const QDate& q);
		void setMiles(double q);
		void setPrice(double q);
		void setVolume(double q);
		QDate date();
		double miles();
		double price();
		double volume();

	private:
		QDate _date;
		double _miles;
		double _price;
		double _volume;

};

#endif
