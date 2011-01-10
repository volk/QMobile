#include <QtCore>
#include <QXmlStreamReader>
#include <iostream>

#include "xmlstreamreader.hpp"
#include "vehicle.hpp"
#include "refuel.hpp"

XmlStreamReader::XmlStreamReader(QList<Vehicle*>* list) : vehicleList(list)
{
	if(list == NULL)
		list = new QList<Vehicle*>();
} 

void XmlStreamReader::readModel()
{
	QString model = reader.readElementText();
	vehicleList->last()->setModel( model );

	if(reader.isEndElement())
		reader.readNext();

}

void XmlStreamReader::readYear()
{
	int year = reader.readElementText().toInt();
	vehicleList->last()->setYear( year );

	if(reader.isEndElement())
		reader.readNext();

}

void XmlStreamReader::readDateMonth()
{
	QString month = reader.readElementText();
	QDate& date = vehicleList->last()->lastRefuel().date();
	date.setDate( date.year(), month.toInt(), date.day() );

	if(reader.isEndElement())
		reader.readNext();
}

void XmlStreamReader::readDateYear()
{
	QString year = reader.readElementText();
	QDate& date = vehicleList->last()->lastRefuel().date();
	date.setDate( year.toInt(), date.month(), date.day() );

	if(reader.isEndElement())
		reader.readNext();

}

void XmlStreamReader::readDateDay()
{
	QString day = reader.readElementText();
	QDate& date = vehicleList->last()->lastRefuel().date();
	date.setDate( date.year(), date.month(), day.toInt() );

	if(reader.isEndElement())
		reader.readNext();
}

void XmlStreamReader::readDate()
{
	QDate refuelDate;
	vehicleList->last()->lastRefuel().setDate(refuelDate);

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
			if(reader.name() == "month")
			{
				readDateMonth();
			}
			else if(reader.name() == "day")
			{
				readDateDay();
			}
			else if(reader.name() == "year")
			{
				readDateYear();
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

void XmlStreamReader::readDistance()
{
	QString distance = reader.readElementText();
	vehicleList->last()->lastRefuel().setDistance(distance.toDouble());
	
	if(reader.isEndElement())
		reader.readNext();
}

void XmlStreamReader::readPrice()
{
	QString distance = reader.readElementText();
	vehicleList->last()->lastRefuel().setPrice(distance.toDouble());
	
	if(reader.isEndElement())
		reader.readNext();

}

void XmlStreamReader::readVolume()
{
	QString distance = reader.readElementText();
	vehicleList->last()->lastRefuel().setVolume(distance.toDouble());
	
	if(reader.isEndElement())
		reader.readNext();

}

void XmlStreamReader::readRefuel()
{
	Refuel newRefuel;
	vehicleList->last()->addRefuel(newRefuel);
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
			else if(reader.name() == "distance")
			{
				readDistance();
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


void XmlStreamReader::readMake()
{
	QString make = reader.readElementText();
	vehicleList->last()->setMake( make );

	if(reader.isEndElement())
		reader.readNext();
	

}

void XmlStreamReader::readVehicle()
{
	Vehicle* newVehicle = new Vehicle();
	vehicleList->push_back(newVehicle);

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
			else if(reader.name() == "refuel")
			{
				readRefuel();
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

void XmlStreamReader::printVehicleList()
{
	if(!vehicleList->empty())
	{
		for(QList<Vehicle*>::iterator i = vehicleList->begin(); i != vehicleList->end() ; ++i)
		{
			(*i)->print();
		}
	}
}
