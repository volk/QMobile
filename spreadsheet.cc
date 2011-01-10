#include <QtGui>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <iostream>
#include <assert.h>

#include "spreadsheet.hpp"
#include "vehicle.hpp"
#include "refuel.hpp"

Spreadsheet::Spreadsheet(int r, int c, QWidget* parent, Vehicle* vehicle) :  QTableWidget(r,c,parent), _vehicle(vehicle)
{
	if(_vehicle == NULL)
		_vehicle = new Vehicle();

	//setting up spreadsheet horizontal header titles like date, distance,etc
	setHorizontalHeaderItem(0, new QTableWidgetItem(tr("Date")));
	setHorizontalHeaderItem(1, new QTableWidgetItem(tr("Price($ USD)")));
	setHorizontalHeaderItem(2, new QTableWidgetItem(tr("Distance(mi.)")));
	setHorizontalHeaderItem(3, new QTableWidgetItem(tr("Volume(gal.)")));

	populate();
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

						std::cout << "(" << r << "," << c << ")"
							<< " = " << dateString.toStdString() << std::endl;
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
				default:
					std::cout << "not supposed to reach here" << std::endl;
					assert(true);
					assert(false);
			}

		}

		r++;
//		setItem(c/rows, c%rows, new QTableWidgetItem(tr())); 
	}
}

