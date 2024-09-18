#include <iostream>

#include <QApplication>
#include <application.h>

#include <QFile>
#include <QByteArray>
#include <QDebug>


namespace alexen {
namespace nmh {
namespace io {


QByteArray read( FILE* istream  = stdin )
{
     QFile inputFile;
     qDebug() << inputFile.open( istream, QIODevice::ReadOnly );

     std::int32_t nmhLen = {};
     if( inputFile.read( reinterpret_cast< char* >( &nmhLen ), sizeof( nmhLen ) ) != sizeof( nmhLen )
          || nmhLen < 0 )
     {
          throw std::runtime_error{ "data length read failed" };
     }
     if( inputFile.atEnd() )
     {
          throw std::runtime_error{ "eof reached" };
     }
     const auto data = inputFile.read( nmhLen );
     if( data.size() != nmhLen )
     {
          throw std::runtime_error{ "data body read failed" };
     }
     qDebug() << data;
     return data;
}


void write( const QByteArray& data, FILE* ostream = stdout )
{
     QFile outputFile;
     qDebug() << outputFile.open( ostream, QIODevice::WriteOnly );
     const std::int32_t nmhLen = data.size();
     qDebug() << "Write len:" << outputFile.write( reinterpret_cast< const char* >( &nmhLen ), sizeof( nmhLen ) );
     qDebug() << "Write data:" << outputFile.write( data );
}


} // namespace io
} // namespace nmh
} // namespace alexen



int main( int argc, char *argv[] )
{
     try
     {
          alexen::nmh::io::write( alexen::nmh::io::read() );

          return 0;

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
