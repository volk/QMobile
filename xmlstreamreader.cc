#include <QtCore>
#include <QXmlStreamReader>
#include <iostream>

#include "xmlstreamreader.hpp"
#include "vehicle.hpp"

XmlStreamReader::XmlStreamReader(QList<Vehicle*>* list) : vehicleList(list) 
{
	if(vehicleList == NULL)
		vehicleList = new QList<Vehicle*>();
}

void XmlStreamReader::readModel()
{
	QString model = reader.readElementText();
	vehicleList->last()->setModel( model );

	std::cout << model.toStdString() << std::endl;
	
	if(reader.isEndElement())
		reader.readNext();

}

void XmlStreamReader::readYear()
{
	int year = reader.readElementText().toInt();
	vehicleList->last()->setYear( year );

	std::cout <<year << std::endl;

	if(reader.isEndElement())
		reader.readNext();

}

void XmlStreamReader::readPrice()
{
	QString q = reader.readElementText();

	if(reader.isEndElement())
		reader.readNext();

}

void XmlStreamReader::readDate()
{
	QString q = reader.readElementText();

	if(reader.isEndElement())
		reader.readNext();

}

void XmlStreamReader::readRefill()
{
	
	reader.readNext();

	while(!reader.atEnd())
	{
		if(reader.isEndElement())
		{
			reader.readNext();
			break;
		}

		if(reader.isStartElement())
		{
			if(reader.name() == "date")
			{
				readDate();
			}
			else if(reader.name() == "miles")
			{
				readMiles();
			}
			else if(reader.name() == "price")
			{
				readPrice();
			}
			else if(reader.name() == "volume")
			{
				readVolume();
			}
			else
			{
				skipUnknownElement();
			}
		}
		else
		{
			reader.readNext();
		}
	}
}

void XmlStreamReader::readMiles()
{
	QString miles = reader.readElementText();
//	vehicleList->last()->setMiles( miles );
	std::cout << miles.toStdString() << std::endl;
	
	if(reader.isEndElement())
		reader.readNext();

}

void XmlStreamReader::readVolume()
{
	QString volume = reader.readElementText();
//	vehicleList->last()->setMiles( miles );
	std::cout << volume.toStdString() << std::endl;
	
	if(reader.isEndElement())
		reader.readNext();

}

void XmlStreamReader::readMake()
{
	QString make = reader.readElementText();
	vehicleList->last()->setMake( make );

	std::cout << make.toStdString() << std::endl;

	if(reader.isEndElement())
		reader.readNext();
	

}

void XmlStreamReader::readVehicle()
{
	Vehicle* veh = new Vehicle;
	vehicleList->push_back(veh);

	reader.readNext();
	while(!reader.atEnd())
	{

		if(reader.isEndElement())
		{
			reader.readNext();
			break;
		}

		if(reader.isStartElement())
		{
			if(reader.name() == "make")
			{
				readMake();
			}
			else if(reader.name() == "model")
			{
				readModel();
			}
			else if(reader.name() == "year")
			{
				readYear();
			}
			else if(reader.name() == "refill")
			{
				readRefill();
			}
			else
			{
				skipUnknownElement();
			}
		}
		else
		{
			reader.readNext();
		}
	}

}

void XmlStreamReader::readAutomobileDBElement()
{
	reader.readNext();

	while(!reader.atEnd())
	{
		if(reader.isEndElement())
		{
			reader.readNext();
			break;
		}

		if(reader.isStartElement())
		{
			if(reader.name() == "vehicle")
			{
				readVehicle();
			}
			else
			{
				skipUnknownElement();
			}
		}
		else
		{
			reader.readNext();
		}
	}

}

bool XmlStreamReader::readFile(const QString& fileName)
{
	QFile file(fileName);
	if( !file.open(QFile::ReadOnly | QFile::Text))
	{
		std::cerr << "Error: Cannot read file" << qPrintable(fileName)
			<< ": " << qPrintable(file.errorString())
			<< std::endl;
		
		return false;
	}

	reader.setDevice(&file);

	reader.readNext();
	while(!reader.atEnd())
	{
		if(reader.isStartElement())
		{
			if(reader.name() == "automobileDB")
			{
				readAutomobileDBElement();
			}
			else
			{
				reader.raiseError(QObject::tr("Not an automobileDB file"));
			}
		}
		else
		{
			reader.readNext();
		}
	}

	file.close();
	if(reader.hasError())
	{
		std::cerr << "Error: failed to parse file "
			<< qPrintable(fileName) << ": "
			<< qPrintable(reader.errorString()) << std::endl;

		return false;
	}
	else if(file.error() != QFile::NoError)
	{
		std::cerr << "Error: Cannot read file " << qPrintable(fileName)
			<< ": " << qPrintable(file.errorString())
			<< std::endl;

		return false;
	}

	return true;
}

void XmlStreamReader::skipUnknownElement()
{
	reader.readNext();
	while(!reader.atEnd())
	{

		if(reader.isEndElement())
		{
			reader.readNext();
			break;
		}

		if(reader.isStartElement())
		{
			skipUnknownElement();
		}
		else
		{
			reader.readNext();
		}
	}
}
