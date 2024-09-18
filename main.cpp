#include <QApplication>
#include <application.h>


int main( int argc, char *argv[] )
{
     QApplication app{ argc, argv };

     alexen::nmh::Application application;
     application.run();

     return app.exec();
}
