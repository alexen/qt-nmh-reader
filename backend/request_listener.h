#pragma once

#include <QObject>

QT_FORWARD_DECLARE_CLASS( QString );
QT_FORWARD_DECLARE_CLASS( QByteArray );
QT_FORWARD_DECLARE_CLASS( QSocketNotifier );


namespace alexen {
namespace nmh {


class RequestListener : public QObject {
     Q_OBJECT
public:
     explicit RequestListener( FILE* istream, QObject* parent = nullptr );
     explicit RequestListener( QObject* parent = nullptr );
     ~RequestListener();

signals:
     void readMessageError( const QString& );
     void messageReceived( const QByteArray& );
     void inputChannelClosed();

public slots:
     void start();

private slots:
     void acceptMessage();

private:
     void enableListening();
     void disableListening();

     FILE* istream_ = {};
     QSocketNotifier* readNotifier_ = {};
};


} // namespace nmh
} // namespace alexen
