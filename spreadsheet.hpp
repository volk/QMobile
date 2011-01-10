#ifndef SPREADSHEET_HPP
#define SPREADSHEET_HPP

#include <QTableWidget>
class Vehicle;
class QTableWidgetItem;

class Spreadsheet : public QTableWidget
{
	Q_OBJECT

	public:
		Spreadsheet(int rows, int columns, QWidget *parent = 0, Vehicle* = NULL);

	private:
		Vehicle* _vehicle;


/*-----------------------------------------------------------------------------
 *  populates the spreadsheet by reading the Vehicle object
 *-----------------------------------------------------------------------------*/
		void populate();
};

#endif
