#include <request_listener.h>

#include <cstdio>

#include <QFile>
#include <QStringLiteral>
#include <QDebug>
#include <QSocketNotifier>

#include <io_tools.h>


#define EMIT_DEBUG( signal ) \
     do { qDebug() << __PRETTY_FUNCTION__ << "emitting signal" << #signal; emit signal; } while( false )



namespace alexen {
namespace nmh {


RequestListener::RequestListener( FILE* istream, QObject* parent )
     : QObject{ parent }
     , istream_{ istream }
     , readNotifier_{ new QSocketNotifier{ fileno( istream_ ), QSocketNotifier::Read, this } }
{
     qDebug() << __PRETTY_FUNCTION__;
     disableListening();
     connect(
          readNotifier_
          , SIGNAL(activated(int))
          , this
          , SLOT(acceptMessage())
          );
}


RequestListener::~RequestListener()
{
     qDebug() << __PRETTY_FUNCTION__;
}


void RequestListener::start()
{
     qDebug() << __PRETTY_FUNCTION__;
     enableListening();
}


void RequestListener::acceptMessage()
{
     qDebug() << __PRETTY_FUNCTION__;

     QFile inputFile;
     inputFile.open( istream_, QIODevice::ReadOnly );
     if( inputFile.atEnd() )
     {
          EMIT_DEBUG( inputChannelClosed() );
          disableListening();
     }
     else if( QByteArray message; readMessage( inputFile, message ) )
     {
          EMIT_DEBUG( messageReceived( message ) );
     }
}


void RequestListener::enableListening()
{
     qDebug() << __PRETTY_FUNCTION__;
     readNotifier_->setEnabled( true );
}


void RequestListener::disableListening()
{
     qDebug() << __PRETTY_FUNCTION__;
     readNotifier_->setEnabled( false );
}


} // namespace nmh
} // namespace alexen
