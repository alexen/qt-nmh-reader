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
     const auto& jsonDoc = QJsonDocument::fromJson( request, &error );
     if( jsonDoc.isNull() or not jsonDoc.isObject() )
     {
          qDebug() << __PRETTY_FUNCTION__ << ": emit badRequest()";
          emit badRequestAccepted(
               request
               , QStringLiteral( "invalid JSON: " ) % error.errorString()
               );
     }
     else
     {
          routeJsonRequest( request, jsonDoc.object() );
     }
}


void RequestRouter::routeJsonRequest( const QByteArray& request, const QJsonObject& jo )
{
     static const QString typeKey = "type";
     static const QString authRequestKey = "authRequest";
     static const QString authCodeKey = "authCode";
     static const QString stopKey = "stop";

     if( const auto& type = jo[ typeKey ]; type.isUndefined() )
     {
          emit badRequestAccepted( request, QStringLiteral( "invalid format: missing key " ) % typeKey );
     }
     else if( not type.isString() )
     {
          emit badRequestAccepted( request, QStringLiteral( "invalid key type: " ) % typeKey );
     }
     else if( type == authRequestKey )
     {
          static const QString dataKey = "data";

          if( const auto& data = jo[ dataKey ]; data.isUndefined() )
          {
               emit badRequestAccepted( request, QStringLiteral( "invalid format: missing key " ) % dataKey );
          }
          else if( not data.isString() )
          {
               emit badRequestAccepted( request, QStringLiteral( "invalid key type: " ) % dataKey );
          }
          else
          {
               emit authRequestAccepted( QByteArray::fromHex( data.toString().toLocal8Bit() ) );
          }
     }
     else if( type == authCodeKey )
     {
          qDebug() << __PRETTY_FUNCTION__ << ": not implemented yet";
     }
     else if( type == stopKey )
     {
          qDebug() << __PRETTY_FUNCTION__ << ": not implemented yet";
     }
     else
     {
          emit badRequestAccepted( request, QStringLiteral( "invalid request type: " ) % type.toString() );
     }
}


} // namespace nmh
} // namespace alexen
