#pragma once

#include <QtGlobal>

QT_FORWARD_DECLARE_CLASS( QIODevice );
QT_FORWARD_DECLARE_CLASS( QByteArray );


namespace alexen {
namespace nmh {


bool readMessage( QIODevice& input, QByteArray& output );
bool readMessage( QIODevice& input, const quint32 len, QByteArray& output )
quint32 readMessageLength( QIODevice& input )


} // namespace nmh
} // namespace alexen
