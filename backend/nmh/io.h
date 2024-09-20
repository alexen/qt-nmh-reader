#pragma once

#include <QtGlobal>

QT_FORWARD_DECLARE_CLASS( QIODevice );
QT_FORWARD_DECLARE_CLASS( QByteArray );


namespace alexen {
namespace nmh {
namespace io {


bool readMessage( QIODevice& input, QByteArray& output );
bool readMessage( QIODevice& input, const quint32 len, QByteArray& output );
quint32 readMessageLength( QIODevice& input );


bool writeMessage( const QByteArray& data, QIODevice& output );


} // namespace io
} // namespace nmh
} // namespace alexen
