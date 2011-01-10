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

	createActions();
	createMenus();

	//main layout for centralWidget
	mainLayout = new QHBoxLayout;
	mainLayout->setMargin(3);
	centralWidget->setLayout(mainLayout);

	//left central widget
	centralTabs = new QTabWidget;
	mainLayout->addWidget(centralTabs);

	//right central widget
	QGroupBox* automobileBox = new QGroupBox(tr("Vehicle Information"));
	QRadioButton* radio1 = new QRadioButton(tr("&Radio button 1"));

	QVBoxLayout* autoVBox = new QVBoxLayout;
	autoVBox->addWidget(radio1);
	autoVBox->addStretch();
	automobileBox->setLayout(autoVBox);

	mainLayout->addWidget(automobileBox);
	
	//added all widgets past this point, now initialize them

	//create an initial spreasheet
//	spreadsheets.push_back( new Spreadsheet(200, 5, centralTabs) );
//	centralTabs->addTab(spreadsheets.last(), tr("First Tab"));

	QString message = tr("Begin by opening a previous file or "
			"inputting new data");
	statusBar()->showMessage(message);

	currentFile = "Untitled";
	appName = "QMobile";
	setCurrentFile(currentFile);
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
		//clear spreadsheet list
		setCurrentFile(QString("Untitled"));
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

	//populate tab titles 
	QList<Vehicle*>::iterator i;
	for(i = vehicles->begin(); i != vehicles->end(); i++)
	{
		//populate tab names
		spreadsheets.push_back(new Spreadsheet(200, 4, centralTabs, *i));
		centralTabs->addTab(spreadsheets.last(), (*i)->make());

//		QList<Refuel>& refuels = (*i)->refuels();
//		//populate spreadsheet cells with refuels
//		QList<Refuel>::iterator i;
//		for(i = refuels.begin(); i != refuels.end(); i++)
//		{
//			spreadsheets.last()->addRowEntry(i);
//		}

	}
	
}

void MainWindow::closeEvent(QCloseEvent* event)
{
	if(okToContinue())
	{
		//write settings
		event->accept();
	}
	else
	{
		event->ignore();
	}
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

bool MainWindow::isWindowModified()
{
	return true;
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
		int r = QMessageBox::warning(this, tr("Spreadsheet"),
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
