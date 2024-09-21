#pragma once

#include <QObject>

QT_FORWARD_DECLARE_CLASS( QString );
QT_FORWARD_DECLARE_CLASS( QByteArray );
QT_FORWARD_DECLARE_CLASS( QSocketNotifier );


namespace alexen {
namespace nmh {


/// Класс-слушатель входного потока
/// в ожидании поступления NMH-сообщения
class RequestListener : public QObject {
     Q_OBJECT
public:
     /// Создает слушатель на стандартном потке ввода @a stdin
     explicit RequestListener( QObject* parent = nullptr );
     /// Создает слушатель на произвольном файловом потоке @a istream
     explicit RequestListener( FILE* istream, QObject* parent = nullptr );
     ~RequestListener();

signals:
     /// Сигнал генерируется при успешном получении NMH-сообщении
     void messageReceived( const QByteArray& );
     /// Сигнал генерируется при закрытии прослушиваемого потока ввода
     void inputChannelClosed();

public slots:
     /// Запускает прослушивание потока ввода
     void start();

private slots:
     /// Реализует функционал чтения данных из входного ввода
     /// и генерацию соответствующих сигналов
     void acceptMessage();

private:
     void enableListening();
     void disableListening();

     FILE* istream_ = {};
     QSocketNotifier* readNotifier_ = {};
};


} // namespace nmh
} // namespace alexen
