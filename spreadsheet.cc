#include <QtGui>

#include "spreadsheet.hpp"

Spreadsheet::Spreadsheet(int r, int c, QWidget* parent) : QTableWidget(parent)
{
	setRowCount(r);
	setColumnCount(c);
}
