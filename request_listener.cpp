#include <request_listener.h>

#include <cstdio>

#include <QFile>
#include <QStringLiteral>
#include <QDebug>


#define EMIT_AND_RETURN( signal ) \
     do { qDebug() << __PRETTY_FUNCTION__ << "emitting signal" << #signal; emit signal; return; } while( false )



namespace alexen {
namespace nmh {


RequestListener::RequestListener( FILE* istream, QObject* parent )
     : QObject{ parent }
     , istream_{ istream }
     , readNotifier_{ new QSocketNotifier{ fileno( istream_ ), QSocketNotifier::Read, this } }
{
     qDebug() << __PRETTY_FUNCTION__;
     readNotifier_->setEnabled( false );
     connect(
          readNotifier_
          , SIGNAL(activated(int))
          , this
          , SLOT(readMessage())
          );
}


RequestListener::~RequestListener()
{
     qDebug() << __PRETTY_FUNCTION__;
     readNotifier_->setEnabled( false );
}


void RequestListener::start()
{
     qDebug() << __PRETTY_FUNCTION__;
}


void RequestListener::readMessage()
{
     qDebug() << __PRETTY_FUNCTION__;
     QFile inputFile;

     if( !inputFile.open( istream_, QIODevice::ReadOnly ) )
     {
          EMIT_AND_RETURN( readMessageError( QStringLiteral( "cannot connect to input stream" ) ) );
     }

     std::int32_t messageLen = 0;
     const auto actualReadBytes = inputFile.read( reinterpret_cast< char* >( &messageLen ), sizeof( messageLen ) );

     if( actualReadBytes != sizeof( messageLen ) or messageLen < 0 )
     {
          if( inputFile.atEnd() )
          {
               EMIT_AND_RETURN( inputStreamClosed() );
          }
          EMIT_AND_RETURN( readMessageError( QStringLiteral( "message length reading error" ) ) );
     }
     const auto message = inputFile.read( messageLen );
     if( message.size() != messageLen )
     {
          EMIT_AND_RETURN( readMessageError( QStringLiteral( "message body reading error" ) ) );
     }
     EMIT_AND_RETURN( messageReceived( message ) );
}


} // namespace nmh
} // namespace alexen
