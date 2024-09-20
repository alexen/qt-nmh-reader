#pragma once

#include <QObject>

QT_FORWARD_DECLARE_CLASS( QJsonObject );


namespace alexen {
namespace nmh {


class RequestRouter : public QObject {
     Q_OBJECT
public:
     explicit RequestRouter( QObject *parent = nullptr );

signals:
     void badRequestAccepted( const QByteArray& request, const QString& errorMessage );
     void authRequestAccepted( const QByteArray& data );

public slots:
     void routeRequest( const QByteArray& request );

private:
     void routeJsonRequest( const QByteArray&, const QJsonObject& );
};


} // namespace nmh
} // namespace alexen
