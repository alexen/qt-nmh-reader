#include <request_listener.h>

#include <QFile>


namespace alexen {
namespace nmh {


RequestListener::RequestListener( QObject* parent )
     : QObject{ parent }
{}


QByteArray RequestListener::read( FILE* istream )
{
     QFile inputFile;

     if( !inputFile.open( istream, QIODevice::ReadOnly ) )
     {
          emit inputStreamConnectError();
          return {};
     }

     std::int32_t nmhLen = 0;
     if( inputFile.read( reinterpret_cast< char* >( &nmhLen ), sizeof( nmhLen ) ) != sizeof( nmhLen )
          || nmhLen < 0 )
     {
          if( inputFile.atEnd() )
          {
               emit inputStreamClosed();
          }
          else
          {
               emit readMessageLengthError();
          }
          return {};
     }
     const auto data = inputFile.read( nmhLen );
     if( data.size() != nmhLen )
     {
          emit readMessageBodyError();
     }
     return data;
}


} // namespace nmh
} // namespace alexen
