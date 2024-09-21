#pragma once

#include <QObject>

QT_FORWARD_DECLARE_CLASS( QJsonObject );


namespace alexen {
namespace nmh {


/// Класс принимает входящее NMH-сообщение, воспринимает его
/// в качестве ожидемого запроса, парсит, валидирует, определяет тип
/// запроса и выбрасывает сигнал, соответствующий типу запроса, или
/// badRequestAccepted(), если запрос не удалось распознать.
class RequestRouter : public QObject {
     Q_OBJECT
public:
     /// Легкий конструктор не реальзует никакого функционала
     explicit RequestRouter( QObject *parent = nullptr );

signals:
     /// Входящее сообщение не удалось распознать как запрос
     void badRequestAccepted( const QString& errorMessage );
     /// Поступил запрос на авторизацию
     void authRequestAccepted( const QByteArray& data );
     /// Поступил запрос с кодом авторизации
     void authCodeAccepted( int );
     /// Поступил запрос на останов (чтобы, черт побери, это ни значило)
     void stopRequestAccepted();

public slots:
     /// Разбирает и маршрутизирует входящее NMH-сообщение
     void routeRequest( const QByteArray& request );

private:
     /// Маршрутизирует входящий запрос уже в виде JSON
     void routeJsonRequest( const QJsonObject& );
     /// Выбрасывает сигнал badRequestAccepted()
     /// с одинаковым сообщением об ошибке
     void emitInvalidRequestFormat();
};


} // namespace nmh
} // namespace alexen
