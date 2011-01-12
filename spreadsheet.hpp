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
		Vehicle* vehicle();
		void clear();

	private:
		Vehicle* _vehicle;
		void recalculate();
		void populate();

		bool autoRecalc;

	signals:
		void modified();

	private slots:
		void spreadsheetModified();
};

#endif
