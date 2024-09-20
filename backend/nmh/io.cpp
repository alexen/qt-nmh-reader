#include <nmh/io.h>

#include <QIODevice>
#include <QByteArray>


namespace alexen {
namespace nmh {
namespace io {


quint32 readMessageLength( QIODevice& input )
{
     quint32 len = {};
     input.read( reinterpret_cast< char* >( &len ), sizeof( len ) );
     return len;
}

bool readMessage( QIODevice& input, const quint32 len, QByteArray& output )
{
     if( len > 0 )
     {
          output = input.read( len );
          return static_cast< quint32 >( output.size() ) == len;
     }
     return false;
}


bool readMessage( QIODevice& input, QByteArray& output )
{
     return readMessage( input, readMessageLength( input ), output );
}


bool writeMessage( const QByteArray& data, QIODevice& output )
{
     const quint32 len = data.size();
     return output.write( reinterpret_cast< const char* >( &len ), sizeof( len ) ) == sizeof( len )
          and output.write( data ) == data.size();
}


} // namespace io
} // namespace nmh
} // namespace alexen
