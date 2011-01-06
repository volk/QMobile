#ifndef SPREADSHEET_HPP
#define SPREADSHEET_HPP

#include <QTableWidget>

class Spreadsheet : public QTableWidget
{
	Q_OBJECT

	public:
		Spreadsheet(int r, int c, QWidget *parent = 0);

	private:
};

#endif
