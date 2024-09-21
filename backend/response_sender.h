#pragma once

#include <QFile>

QT_FORWARD_DECLARE_CLASS( QJsonObject );


namespace alexen {
namespace nmh {


/// Класс, отвечающий за формирование и отправку NMH-ответа
/// в корректном и ожидаемом формате
class ResponseSender : public QObject {
     Q_OBJECT
public:
     explicit ResponseSender( QObject* parent = nullptr );

public slots:
     /// Формирует и отправляет ответ с информацией об ошибке
     void sendErrorResponse( const QString& error );

private:
     /// Реализует отправку любого ответа в формате JSON, определяемом
     /// объектом @p QJsonObject
     void sendResponse( const QJsonObject& );

     QFile ostream_;
};


} // namespace nmh
} // namespace alexen
