#include <request_router.h>

#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QStringLiteral>
#include <QStringBuilder>


namespace alexen {
namespace nmh {


RequestRouter::RequestRouter( QObject *parent )
     : QObject{ parent }
{}


void RequestRouter::routeRequest( const QByteArray& request )
{
     qDebug() << __PRETTY_FUNCTION__ << ":" << request;
     QJsonParseError error;

     const auto& jo = QJsonDocument::fromJson( request, &error ).object();
     if( jo.isEmpty() )
     {
          emitInvalidRequestFormat();
     }
     else
     {
          routeJsonRequest( jo );
     }
}


void RequestRouter::routeJsonRequest( const QJsonObject& jo )
{
     static const QString typeKey = "type";
     static const QString authRequestKey = "authRequest";
     static const QString authCodeKey = "authCode";
     static const QString stopKey = "stop";

     static const QString noStrData = "-- no data --";

     if( const auto& type = jo[ typeKey ].toString( noStrData ); type == noStrData )
     {
          emitInvalidRequestFormat();
     }
     else if( type == authRequestKey )
     {
          static const QString dataKey = "data";

          if( const auto& data = jo[ dataKey ].toString(); data == noStrData )
          {
               emitInvalidRequestFormat();
          }
          else
          {
               emit authRequestAccepted( QByteArray::fromHex( data.toLocal8Bit() ) );
          }
     }
     else if( type == authCodeKey )
     {
          static const QString codeKey = "code";
          static const int noIntData = -1;

          if( const auto& code = jo[ codeKey ].toInt( noIntData ); code == noIntData )
          {
               emitInvalidRequestFormat();
          }
          else
          {
               emit authCodeAccepted( code );
          }
     }
     else if( type == stopKey )
     {
          emit stopRequestAccepted();
     }
     else
     {
          emitInvalidRequestFormat();
     }
}


void RequestRouter::emitInvalidRequestFormat()
{
     static const QString message = "invalid request format";
     emit badRequestAccepted( message );
}


} // namespace nmh
} // namespace alexen
