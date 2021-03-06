#include <QtGui>
#include <QtCore>
#include <iostream>

#include "mainwindow.hpp"
#include "spreadsheet.hpp"
#include "xmlstreamreader.hpp"
#include "vehicle.hpp"
#include "refuel.hpp"

MainWindow::MainWindow()
{
	centralWidget = new QWidget;
	setCentralWidget(centralWidget);

	createLayout();
	createActions();
	createMenus();
	
	QString message = tr("Begin by opening a previous file or inputting"
			" new data");
	statusBar()->showMessage(message);

	appName = "QMobile";
	setCurrentFile("");
}

void MainWindow::createLayout()
{
	//main layout for centralWidget
	QHBoxLayout* mainLayout = new QHBoxLayout;
	mainLayout->setMargin(3);
	centralWidget->setLayout(mainLayout);

	//left central widget
	centralTabs = new QTabWidget;
	mainLayout->addWidget(centralTabs);

	//right central widget
	QGroupBox* automobileBox = new QGroupBox(tr("Automobile Information"));
	QGridLayout* rightGrid = new QGridLayout;

	QLabel* makeLabel = new QLabel(tr("Make"));
	QLabel* modelLabel = new QLabel(tr("Model"));
	QLabel* yearLabel = new QLabel(tr("Year"));
	makeLineEdit = new QLineEdit();
	modelLineEdit = new QLineEdit();
	yearLineEdit = new QLineEdit();

	rightGrid->addWidget(makeLabel, 0, 0);
	rightGrid->addWidget(modelLabel, 1, 0);
	rightGrid->addWidget(yearLabel, 2, 0);
	rightGrid->addWidget(makeLineEdit, 0, 1);
	rightGrid->addWidget(modelLineEdit, 1, 1);
	rightGrid->addWidget(yearLineEdit, 2, 1);

	QVBoxLayout* mobileVBox = new QVBoxLayout;
	mobileVBox->addLayout(rightGrid);
	mobileVBox->addStretch();

	automobileBox->setLayout(mobileVBox);
	mainLayout->addWidget(automobileBox);
}

void MainWindow::setCurrentFile(const QString& fileName)
{
	currentFile = fileName;
	setWindowModified(false);

	QString newTitleFile = tr("Untitled");
	if(!currentFile.isEmpty())
		newTitleFile = MainWindow::strippedFileName(currentFile);

	setWindowTitle(newTitleFile + tr("[*] - ") + appName);
}

QString MainWindow::strippedFileName(const QString& fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

void MainWindow::createActions()
{
	newAction = new QAction(tr("&New"), this);
	newAction->setShortcuts(QKeySequence::New);
	newAction->setStatusTip(tr("Create a new file"));
	connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));

	openAction = new QAction(tr("&Open"), this);
	openAction->setShortcuts(QKeySequence::Open);
	openAction->setStatusTip(tr("Open an existing file"));
	connect(openAction, SIGNAL(triggered()), this, SLOT(openFile()));

	saveAction = new QAction(tr("&Save"), this);
	saveAction->setShortcuts(QKeySequence::Save);
	saveAction->setStatusTip(tr("Save to an existing file"));
	connect(saveAction, SIGNAL(triggered()), this, SLOT(saveFile()));

	saveAsAction = new QAction(tr("Save &As"), this);
	saveAsAction->setShortcuts(QKeySequence::SaveAs);
	saveAsAction->setStatusTip(tr("Save the current file to a different name"));
	connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAsFile()));

	exitAction = new QAction(tr("&Close"), this);
	exitAction->setShortcuts(QKeySequence::Close);
	exitAction->setStatusTip(tr("Exit program"));
	connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

	aboutAction = new QAction(tr("&About"), this);
	aboutAction->setStatusTip(tr("About this application"));
	connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

	aboutQtAction = new QAction(tr("About &Qt"), this);
	aboutQtAction->setStatusTip(tr("About Qt framework"));
	connect(aboutQtAction, SIGNAL(triggered()), this, SLOT(aboutQt()));

	connect(centralTabs, SIGNAL(currentChanged(int)), this, 
			SLOT(updateMobileBox()));
	
	connect(newAction, SIGNAL(triggered()), this, SLOT(updateMobileBox()));
	connect(openAction, SIGNAL(triggered()), this, SLOT(updateMobileBox()));
}

void MainWindow::updateMobileBox()
{
	if(centralTabs->currentIndex() == -1 || !centralTabs->count())
	{
		makeLineEdit->setText("");
		modelLineEdit->setText("");
		yearLineEdit->setText("");
	}
	else
	{
		Vehicle* vehicle = spreadsheets.at(centralTabs->currentIndex())->vehicle();

		QString makeString = vehicle->make();
		makeLineEdit->setText(makeString);

		QString modelString = vehicle->model();
		modelLineEdit->setText(modelString);

		int year	= vehicle->year();
		yearLineEdit->setText( QString::number(year) );
	}

}

void MainWindow::createMenus()
{
	//file menu
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(newAction);
	fileMenu->addAction(openAction);
	fileMenu->addAction(saveAction);
	fileMenu->addAction(saveAsAction);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAction);
	
	//help menu
	helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(aboutAction);
	helpMenu->addAction(aboutQtAction);
}

//void MainWindow::contextMenuEvent(QContextMenuEvent* event)
//{
//	QMenu menu(this);
//	menu.addAction(cutAction);
//	menu.addAction(copyAction);
//	menu.addAction(pasteAction);
//	menu.exec(event->globalPos());
//}

void MainWindow::newFile()
{
	if(okToContinue())
	{
		QList<Spreadsheet*>::iterator i;
		for(i = spreadsheets.begin(); i != spreadsheets.end(); ++i)
			delete *i;

		spreadsheets.clear();

		//Qt automatically takes care of pointers for us 
		centralTabs = new QTabWidget;

		setCurrentFile(QString(""));
	}
}

void MainWindow::openFile()
{
	if(okToContinue())
	{
		QString newFile = QFileDialog::getOpenFileName(this, tr("Open File"), 
				tr("vehicle XML files (*.xml)"));

		if(!newFile.isEmpty())
			loadFile(newFile);
	}
}

void MainWindow::loadFile(const QString& fileName)
{
	centralTabs->clear();
	
	//read the file to populate the Vehicle structures which will then
	//be used to fill out the spreadsheets and tabs
	QList<Vehicle*>* vehicles = new QList<Vehicle*>();
	XmlStreamReader reader(vehicles);
	reader.readFile(fileName);

	setCurrentFile(fileName);

	//populate tab titles 
	QList<Vehicle*>::iterator i;
	for(i = vehicles->begin(); i != vehicles->end(); i++)
	{
		//populate tab names
		spreadsheets.push_back(new Spreadsheet(200, 6, centralTabs, *i));
		centralTabs->addTab(spreadsheets.last(), (*i)->model());
		connect(spreadsheets.last(), SIGNAL(modified()), this, 
				SLOT(documentModified()));
	}
	
}

void MainWindow::documentModified()
{
	setWindowModified(true);
	std::cout << std::string("BINGO") << isWindowModified() <<  std::endl;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
	if(okToContinue())
	{
		//write settings
		event->accept();
	}
	else
		event->ignore();
}

bool MainWindow::saveFile()
{
////	infoLabel->setText(tr("Involved <b>File|Save</b>"));
	return true;
}

bool MainWindow::saveAsFile()
{
	return true;
}

void MainWindow::aboutQt()
{

}

void MainWindow::about()
{
////	QMessageBox::about(this, tr("About Menu"), 
////			tr("The <b>Menu</b> example shows how to create "
////				"menu-bar menus and context menus."));
}

/*-----------------------------------------------------------------------------
 *  returns true if all the file processing(saving, unsaving, etc) is done
 *  returns false if it is not safe to proceed
 *  use this whenever you wish to swap out a file, close the file, open a new 
 *  file, and etc
 *
 *  displays a dialog box asking the user what he/she wishes to do with the file
 *-----------------------------------------------------------------------------*/
bool MainWindow::okToContinue()
{
	if(isWindowModified())
	{
		int r = QMessageBox::warning(this, tr("Spreadsheets"),
				tr("This document has been modified.\n"
					"Do you want to save your changes?"),
				QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

		if(r == QMessageBox::Yes)
		{
			return saveFile();
		}
		else if(r == QMessageBox::Cancel)
		{
			return false;
		}

	}

	return true;
}
