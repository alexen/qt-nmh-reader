#pragma once

#include <QFile>

QT_FORWARD_DECLARE_CLASS( QJsonObject );


namespace alexen {
namespace nmh {


class ResponseSender : public QObject {
     Q_OBJECT
public:
     explicit ResponseSender( QObject* parent = nullptr );

public slots:
     void sendErrorResponse( const QString& error );

private:
     void sendResponse( const QJsonObject& );

     QFile ostream_;
};


} // namespace nmh
} // namespace alexen
