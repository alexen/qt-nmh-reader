#pragma once

#include <QtGlobal>

QT_FORWARD_DECLARE_CLASS( QIODevice );
QT_FORWARD_DECLARE_CLASS( QByteArray );


namespace alexen {
namespace nmh {
namespace io {


/// Читает NMH-сообщение из устройства ввода/вывода @a input в буфер @a output
///
/// @attention Устройство @a input должно быть предварительно открыто!
/// @note Ф-ция не проверяет достижения потока данных для чтения, данная обязанность
/// возлагается на вызывающую сторону.
///
/// Пример использования со стандарнтым потоком ввода:
/// @code
/// QFile inFile;
/// inFile.open( fileno(stdin), QIODevice::ReadOnly );
/// QByteArray message;
/// while( not inFile.atEnd() and nmh::io::readMessage( inFile, message ) ) {
///     processReadMessage( message );
/// }
/// @endcode
///
/// Пример использования с любым файлом:
/// @code
/// QFile inFile{ "filename.nmh" };
/// inFile.open( QIODevice::ReadOnly );
/// QByteArray message;
/// while( not inFile.atEnd() and nmh::io::readMessage( inFile, message ) ) {
///     processReadMessage( message );
/// }
/// @endcode
///
/// @return @p true, если чтение сообщения прошло успешно и @p false в противном случае
bool readMessage( QIODevice& input, QByteArray& output );


/// Записывает данные @a data в устройство ввода/вывода @a output в формате NMH
///
/// @return @p true, если данные записаны успешно и @p false в противном случае
bool writeMessage( const QByteArray& data, QIODevice& output );


} // namespace io
} // namespace nmh
} // namespace alexen
