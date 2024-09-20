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
          emit badRequestAccepted( QStringLiteral( "invalid JSON: " ) % error.errorString() );
     }
     else
     {
          routeJsonRequest( jsonDoc.object() );
     }
}


void RequestRouter::routeJsonRequest( const QJsonObject& jo )
{
     static const QString typeKey = "type";
     static const QString authRequestKey = "authRequest";
     static const QString authCodeKey = "authCode";
     static const QString stopKey = "stop";

     if( const auto& type = jo[ typeKey ]; type.isUndefined() )
     {
          emit badRequestAccepted( QStringLiteral( "invalid format: missing key " ) % typeKey );
     }
     else if( not type.isString() )
     {
          emit badRequestAccepted( QStringLiteral( "invalid key type: " ) % typeKey );
     }
     else if( type == authRequestKey )
     {
          static const QString dataKey = "data";

          if( const auto& data = jo[ dataKey ]; data.isUndefined() )
          {
               emit badRequestAccepted( QStringLiteral( "invalid format: missing key " ) % dataKey );
          }
          else if( not data.isString() )
          {
               emit badRequestAccepted( QStringLiteral( "invalid key type: " ) % dataKey );
          }
          else
          {
               emit authRequestAccepted( QByteArray::fromHex( data.toString().toLocal8Bit() ) );
          }
     }
     else if( type == authCodeKey )
     {
          static const QString codeKey = "code";

          if( const auto& code = jo[ codeKey ];code.isUndefined() )
          {
               emit badRequestAccepted( QStringLiteral( "invalid format: missing key " ) % codeKey );
          }
          else if( code.isDouble() and code.toInt( -1 ) != -1 )
          {
               emit authCodeAccepted( code.toInt() );
          }
          else
          {
               emit badRequestAccepted( QStringLiteral( "invalid key type: " ) % codeKey );
          }
     }
     else if( type == stopKey )
     {
          emit stopRequestAccepted();
     }
     else
     {
          emit badRequestAccepted( QStringLiteral( "invalid request type: " ) % type.toString() );
     }
}


} // namespace nmh
} // namespace alexen
