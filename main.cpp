#include <QApplication>
#include <QtGui>
#include <iostream>

#include <stdlib.h>

#include "mainwindow.hpp"
#include "xmlstreamreader.hpp"
#include "vehicle.hpp"
#include "refuel.hpp"


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
                std::cerr << "Usage: xmlstreamreader <file_name>"
                        << std::endl;

					 exit(1);
        }

        QList<Vehicle> vehicle;

        XmlStreamReader reader(vehicle);
        reader.readFile(args[1]);
		  reader.printVehicleList();
        std::cout << "finished" << std::endl;
	return app.exec();
}
