#pragma once

#include <QObject>
#include <QByteArray>
#include <QSocketNotifier>


namespace alexen {
namespace nmh {


class RequestListener : public QObject {
     Q_OBJECT
public:
     explicit RequestListener( FILE* istream, QObject* parent = nullptr );
     ~RequestListener();

     void start();
     void stop();

signals:
     void readMessageError( const QString& );
     void inputStreamClosed();
     void messageReceived( const QByteArray& );

private slots:
     void readMessage();

private:
     FILE* istream_ = {};
     QSocketNotifier* readNotifier_ = {};
};


} // namespace nmh
} // namespace alexen
