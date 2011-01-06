#include <QtGui>
#include <QtCore>

#include "mainwindow.hpp"
#include "spreadsheet.hpp"

MainWindow::MainWindow()
{
	QWidget* centralWidget = new QWidget;
	setCentralWidget(centralWidget);

	//main layout for centralWidget
	QHBoxLayout* layout = new QHBoxLayout;
	layout->setMargin(3);
	centralWidget->setLayout(layout);

	//left central widget
	centralTabs = new QTabWidget;
	layout->addWidget(centralTabs);

	//right central widget
	QGroupBox* automobileBox = new QGroupBox(tr("Automobile Information"));
	QRadioButton* radio1 = new QRadioButton(tr("&Radio button 1"));

	QVBoxLayout* autoVBox = new QVBoxLayout;
	autoVBox->addWidget(radio1);
	autoVBox->addStretch();
	automobileBox->setLayout(autoVBox);

	layout->addWidget(automobileBox);
	
	//added all widgets past this point, now initialize them

	sp = new Spreadsheet(200,5, centralTabs);

	centralTabs->addTab(sp, tr("First Tab"));






//	createActions();
//	createMenus();

	QString message = tr("Begin by opening a previous file ");
	statusBar()->showMessage(message);

	setWindowTitle(tr("Menus"));
}
//
//void MainWindow::createActions()
//{
//	newAction = new QAction(tr("&New"), this);
//	newAction->setShortcuts(QKeySequence::New);
//	newAction->setStatusTip(tr("Create a new file"));
//	connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));
//
//	openAction = new QAction(tr("&Open"), this);
//	openAction->setShortcuts(QKeySequence::Open);
//	openAction->setStatusTip(tr("Open an existing file"));
//	connect(openAction, SIGNAL(triggered()), this, SLOT(openFile()));
//
//	saveAction = new QAction(tr("&Save"), this);
//	saveAction->setShortcuts(QKeySequence::Save);
//	saveAction->setStatusTip(tr("Save to an existing file"));
//	connect(saveAction, SIGNAL(triggered()), this, SLOT(saveFile()));
//
//	exitAction = new QAction(tr("&Close"), this);
//	exitAction->setShortcuts(QKeySequence::Close);
//	exitAction->setStatusTip(tr("Exit program"));
//	connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
//
//	aboutAction = new QAction(tr("&About"), this);
//	aboutAction->setStatusTip(tr("Show the application's About box"));
//	connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
//
//}
//
//void MainWindow::createMenus()
//{
//	fileMenu = menuBar()->addMenu(tr("&File"));
//	fileMenu->addAction(newAction);
//	fileMenu->addAction(openAction);
//	fileMenu->addAction(saveAction);
//	fileMenu->addSeparator();
//	fileMenu->addAction(exitAction);
//
//	helpMenu = menuBar()->addMenu(tr("&Help"));
//	helpMenu->addAction(aboutAction);
//}
//
////void MainWindow::contextMenuEvent(QContextMenuEvent* event)
////{
////	QMenu menu(this);
////	menu.addAction(cutAction);
////	menu.addAction(copyAction);
////	menu.addAction(pasteAction);
////	menu.exec(event->globalPos());
////}
//
//void MainWindow::newFile()
//{
//	if(okToContinue())
//	{
//		//clear spreadsheet queue
//		//and set new current file
//	}
//}
//
//void MainWindow::openFile()
//{
//
//}
//
//bool MainWindow::saveFile()
//{
////	infoLabel->setText(tr("Involved <b>File|Save</b>"));
//	return true;
//}
//
//bool MainWindow::saveAsFile()
//{
//	return true;
//}
//
////void MainWindow::leftAlign()
////{
////	infoLabel->setText(tr("Invoked leftAlign()"));
////}
////
////void MainWindow::rightAlign()
////{
////	infoLabel->setText(tr("Invoked rightAlign()"));
////}
////
////void MainWindow::justify()
////{
////	infoLabel->setText(tr("Invoked centerAlign()"));
////}
//
////void MainWindow::about()
////{
////	QMessageBox::about(this, tr("About Menu"), 
////			tr("The <b>Menu</b> example shows how to create "
////				"menu-bar menus and context menus."));
////}
////
////bool MainWindow::isWindowModified()
////{
////	return true;
////}
////bool MainWindow::okToContinue()
////{
////	if(isWindowModified())
////	{
////		int r = QMessageBox::warning(this, tr("Spreadsheet"),
////				tr("The document has been modified.\n"
////					"Do you want to save your changes?"),
////				QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
////
////		if(r == QMessageBox::Yes)
////		{
////			return saveFile();
////		}
////		else if(r == QMessageBox::Cancel)
////		{
////			return false;
////		}
////
////	}
////	return true;
////}
