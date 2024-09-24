#include <interval_timer.h>

#include <QDebug>
#include <QTimer>


namespace alexen {
namespace nmh {


IntervalTimer::IntervalTimer( QObject *parent )
     : QObject{ parent }
     , totalTimer_{ new QTimer{ this } }
     , intervalTimer_{ new QTimer{ this } }
{
     connect(
          totalTimer_
          , &QTimer::timeout
          , this
          , &IntervalTimer::timeout
          );
     connect(
          intervalTimer_
          , &QTimer::timeout
          , this
          , &IntervalTimer::emitInterval
          );
}


void IntervalTimer::start( std::chrono::milliseconds total, std::chrono::milliseconds interval )
{
     totalTimer_->start( total );
     intervalTimer_->start( interval );
}


void IntervalTimer::stop()
{
     totalTimer_->stop();
     intervalTimer_->stop();
}


std::chrono::milliseconds IntervalTimer::remainingTime() const
{
     return totalTimer_->remainingTimeAsDuration();
}


void IntervalTimer::emitInterval()
{
     emit interval( totalTimer_->remainingTimeAsDuration() );
}


} // namespace nmh
} // namespace alexen
