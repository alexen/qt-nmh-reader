#pragma once

#include <QObject>


namespace alexen {
namespace nmh {


class RequestListener : public QObject {
     Q_OBJECT
public:
     explicit RequestListener( QObject* parent = nullptr );
};


} // namespace nmh
} // namespace alexen
