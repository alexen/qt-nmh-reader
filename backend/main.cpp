#include <iostream>

#include <QApplication>
#include <application.h>

#include <nmh/io.h>


int main( int argc, char *argv[] )
{
     try
     {
          QApplication app{ argc, argv };

          alexen::nmh::Application application;
          application.start();

          return app.exec();
     }
     catch( const std::exception& e )
     {
          std::cerr << "exception: " << e.what() << '\n';
     }
     return 0;
}
