#include <QApplication>
#include <QtGui>
#include <iostream>

#include "mainwindow.hpp"
#include "xmlstreamreader.hpp"
#include "vehicle.hpp"


int main(int argc, char* argv[])
{
    /*
	QApplication app(argc, argv);
	MainWindow window;
	window.show();
        */
        QApplication app(argc, argv);
        QStringList args = QApplication::arguments();

        if(args.count() < 2)
        {
                std::cerr << "Usage: xmlstreamreader <file_name> [<file_name>]"
                        << std::endl;
        }

        QList<Vehicle*>* vehicle = new QList<Vehicle*>();

        XmlStreamReader reader(vehicle);
        reader.readFile(args[1]);
		  reader.printVehicleList();
        std::cout << "finished" << std::endl;
	return app.exec();
}
