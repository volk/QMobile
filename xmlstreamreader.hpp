#ifndef XMLSTREAMREADER_HPP
#define XMLSTREAMREADER_HPP


class QString;
template <class T>
class QList;
class Vehicle;
class QXmlStreamReader;

//standard recursive descent parser
class XmlStreamReader 
{
	public:
		bool readFile(const QString& fileName);
		XmlStreamReader(QList<Vehicle*>* list);

	private:
		void readAutomobileDBElement();
		void readVehicle();
		void readMake();
		void readModel();
		void readYear();
		void readRefill(); // stub
		void readDate(); // stub
		void readMiles();
		void readPrice(); // stub
		void readVolume(); //stub
		void skipUnknownElement();

		QList<Vehicle*>* vehicleList;
		QXmlStreamReader reader;

};

#endif
