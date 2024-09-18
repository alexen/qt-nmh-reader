#pragma once

#include <QObject>


namespace alexen {
namespace nmh {


class ResponseSender : public QObject {
     Q_OBJECT
public:
     explicit ResponseSender( QObject* parent = nullptr );
};


} // namespace nmh
} // namespace alexen
