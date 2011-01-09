#ifndef XMLSTREAMREADER_HPP
#define XMLSTREAMREADER_HPP


class QString;
template <class T>
class QList;
class Vehicle;
class QXmlStreamReader;
class Refuel;
class QDate;

//standard recursive descent parser
//all the read functions refer to the vehicleList->last() to input all
//the necessary attributes
class XmlStreamReader 
{
	public:
		bool readFile(const QString& fileName);
		XmlStreamReader(QList<Vehicle> list);
		void printVehicleList(); //debugging purposes

	private:
		void readAutomobileDBElement();
		void readVehicle();
		void readMake();
		void readModel();
		void readYear();
		void readRefuel(); 
		void readDate(); 
		void readDateMonth(); 
		void readDateDay(); 
		void readDateYear(); 
		void readDistance();
		void readPrice(); 
		void readVolume(); 
		void skipUnknownElement();

		QList<Vehicle> vehicleList;
		QXmlStreamReader reader;

};

#endif
