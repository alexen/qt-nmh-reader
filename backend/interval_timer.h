#pragma once

#include <QObject>

QT_FORWARD_DECLARE_CLASS( QTimer );
Q_DECLARE_METATYPE( std::chrono::microseconds );


namespace alexen {
namespace nmh {


class IntervalTimer : public QObject {
     Q_OBJECT
public:
     explicit IntervalTimer( QObject *parent = nullptr );

     void start( std::chrono::milliseconds total, std::chrono::milliseconds interval );
     void stop();

     std::chrono::milliseconds remainingTime() const;

signals:
     void timeout();
     void interval( std::chrono::milliseconds );

private slots:
     void emitInterval();

private:
     QTimer* totalTimer_;
     QTimer* intervalTimer_;
};


} // namespace nmh
} // namespace alexen

