#include <io_tools.h>

#include <QFile>
#include <QByteArray>
#include <QDebug>


namespace alexen {
namespace nmh {


quint32 readMessageLength( QFile& input )
{
     quint32 len = {};
     input.read( reinterpret_cast< char* >( &len ), sizeof( len ) );
     return len;
}

bool readMessage( QFile& input, const quint32 len, QByteArray& output )
{
     if( len > 0 )
     {
          output = input.read( len );
          return static_cast< quint32 >( output.size() ) == len;
     }
     return false;
}


bool readMessage( QFile& input, QByteArray& output )
{
     return readMessage( input, readMessageLength( input ), output );
}


} // namespace nmh
} // namespace alexen
