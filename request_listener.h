#pragma once

#include <QObject>
#include <QByteArray>


namespace alexen {
namespace nmh {


class RequestListener : public QObject {
     Q_OBJECT
public:
     explicit RequestListener( QObject* parent = nullptr );

signals:
     void inputStreamConnectError();
     void readMessageLengthError();
     void readMessageBodyError();
     void inputStreamClosed();

private:
     QByteArray read( FILE* istream  = stdin );
};


} // namespace nmh
} // namespace alexen
