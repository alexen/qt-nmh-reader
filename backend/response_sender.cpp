#include <response_sender.h>

#include <cstdio>

#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>

#include <nmh/io.h>


namespace alexen {
namespace nmh {


ResponseSender::ResponseSender( QObject* parent )
     : QObject{ parent }
{
     ostream_.open( stdout, QIODevice::WriteOnly );
}


void ResponseSender::sendErrorResponse( const QString& error )
{
     sendResponse({
          { "type", "error" },
          { "message", error }
          });
}


void ResponseSender::sendResponse( const QJsonObject& jo )
{
     qDebug() << __PRETTY_FUNCTION__ << QJsonDocument{ jo }.toJson( QJsonDocument::Compact );
     io::writeMessage( QJsonDocument{ jo }.toJson( QJsonDocument::Compact ), ostream_ );
     ostream_.flush();
}


} // namespace nmh
} // namespace alexen
