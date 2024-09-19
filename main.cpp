#include <iostream>

#include <QApplication>
#include <application.h>

#include <QFile>
#include <QByteArray>
#include <QDebug>


int main( int argc, char *argv[] )
{
     try
     {
          QApplication app{ argc, argv };

          alexen::nmh::Application application;
          application.run();

          return app.exec();
     }
     catch( const std::exception& e )
     {
          std::cerr << "exception: " << e.what() << '\n';
     }
     return 0;
}
