#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QtGui>

class QAction;
class QActionGroup;
class QLabel;
class QMenu;
class QTableWidget;
class Spreadsheet;
template <class T>
class QList;
class Vehicle;
class Refuel;

class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:
		MainWindow();

	protected:
		//		void contextMenuEvent(QContextMenuEvent *event);
		void closeEvent(QCloseEvent* event);

	signals:
		void modified();

	private slots:
		void newFile();
		void openFile();
		bool saveFile();
		bool saveAsFile();
		void about();
		void aboutQt();

	private:
		void createActions();
		void createMenus();
		void loadFile(const QString&);
		bool okToContinue();	//returns true if 
		bool isWindowModified();
		void setCurrentFile(const QString&);
		static QString strippedFileName(const QString& fullFileName);

		//all the widgets will be attached to this widget
		QWidget* centralWidget;
		QList<Spreadsheet*> spreadsheets;
		QTabWidget* centralTabs;

		QMenu *fileMenu;
		QAction* newAction;
		QAction* openAction;
		QAction* saveAction;
		QAction* saveAsAction;
		QAction* exitAction;

		QMenu *helpMenu;
		QAction* aboutAction;
		QAction* aboutQtAction;

		QString currentFile;
		QString appName;

		//central layout boxes
		//everything should be attached to them
		QHBoxLayout* mainLayout;

};

#endif
