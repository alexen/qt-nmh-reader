#pragma once

#include <QtGlobal>

QT_FORWARD_DECLARE_CLASS( QFile );
QT_FORWARD_DECLARE_CLASS( QByteArray );


namespace alexen {
namespace nmh {

quint32 readMessageLength( QFile& input );
bool readMessage( QFile& input, const quint32 len, QByteArray& output );
bool readMessage( QFile& input, QByteArray& output );


} // namespace nmh
} // namespace alexen
