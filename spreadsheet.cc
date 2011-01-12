#include <QtGui>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <iostream>
#include <assert.h>

#include "spreadsheet.hpp"
#include "vehicle.hpp"
#include "refuel.hpp"

Spreadsheet::Spreadsheet(int r, int c, QWidget* parent, Vehicle* vehicle) 
:  QTableWidget(r,c,parent), _vehicle(vehicle)
{
	if(_vehicle == NULL)
		_vehicle = new Vehicle();

	//setting up spreadsheet horizontal header titles like date, distance,etc
	setHorizontalHeaderItem(0, new QTableWidgetItem(tr("Date")));
	setHorizontalHeaderItem(1, new QTableWidgetItem(tr("Price($ USD)")));
	setHorizontalHeaderItem(2, new QTableWidgetItem(tr("Distance(mi.)")));
	setHorizontalHeaderItem(3, new QTableWidgetItem(tr("Volume(gal.)")));
	setHorizontalHeaderItem(4, new QTableWidgetItem(tr("mi./$")));
	setHorizontalHeaderItem(5, new QTableWidgetItem(tr("mi./gal.")));

	populate();
	recalculate();

	autoRecalc = true;
}

void Spreadsheet::clear()
{

}

void Spreadsheet::recalculate()
{
	QList<Refuel>& refuels = _vehicle->refuels();

	QList<Refuel>::iterator i;
	int r = 0;	//row number in spreadsheet
	for(i = refuels.begin(); i != refuels.end(); ++i)
	{
		//c is the column number in the spreadsheet
		for(int c = 0; c < columnCount(); c++)
		{
			switch(c % columnCount())
			{
				case 4:
					{
						//distance per price
						QString disPerPric = QString::number(i->distance() / 
								i->price());
						setItem(r, c, new QTableWidgetItem(disPerPric));
					}
					break;
				case 5:
					{
						//distance per gallon
						QString disPerVol = QString::number(i->distance() / 
								i->volume());
						setItem(r, c, new QTableWidgetItem(disPerVol));
					}
					break;
			}

		}

		r++;
	}

}

void Spreadsheet::spreadsheetModified()
{
	if(autoRecalc)
		recalculate();

	emit modified();
}

void Spreadsheet::populate()
{
	QList<Refuel>& refuels = _vehicle->refuels();

	QList<Refuel>::iterator i;
	int r = 0;	//row number in spreadsheet
	for(i = refuels.begin(); i != refuels.end(); ++i)
	{
		//c is the column number in the spreadsheet
		for(int c = 0; c < columnCount(); c++)
		{
			switch(c % columnCount())
			{
				case 0:
					{
						QString dateString;
						dateString = QString::number(i->date().month()) + "/" 
							+ QString::number(i->date().day()) + "/" 
							+ QString::number(i->date().year());

						setItem(r, c, new QTableWidgetItem(dateString));
					}
					break;
				case 1:
					{
						QString price = QString::number( i->price() );
						setItem(r, c, new QTableWidgetItem(price));
					}
					break;
				case 2:
					{
						QString distance = QString::number( i->distance() );
						setItem(r, c, new QTableWidgetItem(distance));
					}
					break;
				case 3:
					{
						QString volume = QString::number( i->volume() );
						setItem(r, c, new QTableWidgetItem(volume));
					}
					break;
			}

		}

		r++;
	}

}

Vehicle* Spreadsheet::vehicle()
{
	return _vehicle;
}
