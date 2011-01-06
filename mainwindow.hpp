#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

class QAction;
class QActionGroup;
class QLabel;
class QMenu;
class QTableWidget;
class Spreadsheet;
template <class T>
class QQueue;

class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:
		MainWindow();

	protected:
//		void contextMenuEvent(QContextMenuEvent *event);

	private slots:
//		void newFile();
//		void openFile();
//		void about();
//		bool saveFile();
//		bool saveAsFile();

	private:
//		void createActions();
//		void createMenus();
//		bool okToContinue();
//		bool isWindowModified();

		Spreadsheet* sp;
		QQueue<Spreadsheet*> spreadsheetList();
		QTabWidget* centralTabs;

		QMenu *fileMenu;
		QMenu *helpMenu;
		QAction* newAction;
		QAction* openAction;
		QAction* saveAction;
		QAction* saveAsAction;
		QAction* exitAction;
		QAction* aboutAction;

};

#endif
