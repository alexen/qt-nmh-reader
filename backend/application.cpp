#include <application.h>

#include <chrono>

#include <QDebug>
#include <QTime>
#include <QTimer>

#include <ui_application.h>

#include <request_listener.h>
#include <request_router.h>
#include <response_sender.h>
#include <interval_timer.h>


namespace alexen {
namespace nmh {


Application::Application( QWidget *parent )
     : QMainWindow{ parent }
     , ui_{ new Ui::Application }
     , requestListener_{ new RequestListener{ stdin, this } }
     , requestRouter_{ new RequestRouter{ this } }
     , responseSender_{ new ResponseSender{ this } }
{
     ui_->setupUi( this );
     qDebug() << __PRETTY_FUNCTION__;

     /// Принятое сообщение направляем в маршрутизатор
     connect(
          requestListener_, &RequestListener::messageReceived
          , requestRouter_, &RequestRouter::routeRequest
          );
     connect(
          requestRouter_, &RequestRouter::badRequestAccepted
          , responseSender_, &ResponseSender::sendErrorResponse
          );
     connect(
          requestRouter_, &RequestRouter::authRequestAccepted
          , this, &Application::authorize
          );
     connect(
          requestRouter_, &RequestRouter::authCodeAccepted
          , this, &Application::authCode
          );
     connect(
          requestRouter_, &RequestRouter::stopRequestAccepted
          , this, &Application::stop
          );
     connect(
          requestListener_, &RequestListener::inputChannelClosed
          , []{ qApp->quit(); }
          );

     /// FOR DEBUG ONLY
     connect(
          requestListener_
          , &RequestListener::messageReceived
          , this
          , &Application::showMessage
          );
     /// FOR DEBUG ONLY

     IntervalTimer* itimer = new IntervalTimer{ this };
     connect(
          itimer
          , &IntervalTimer::timeout
          , []{ qDebug() << "Time is up!"; qApp->quit(); }
          );
     connect(
          itimer
          , &IntervalTimer::interval
          , this
          , &Application::visualTimerCountdown
          );
     itimer->start( std::chrono::seconds{ 30 }, std::chrono::seconds{ 1 } );
     visualTimerCountdown( itimer->remainingTime() );
     show();
}


Application::~Application()
{
     delete ui_;
     qDebug() << __PRETTY_FUNCTION__;
}


void Application::start()
{
//     requestListener_->start();

//     QTimer* timer = new QTimer{ this };
//     connect(
//          timer
//          , &QTimer::timeout
//          , this
//          , &Application::visualTimerCountdown
//          );
//     timer->start( 1000 );
//     visualTimerCountdown();
}


void Application::closeEvent( QCloseEvent* event )
{
     qDebug() << __PRETTY_FUNCTION__;
     event->ignore();
     hide();
}


void Application::showMessage( const QByteArray& message )
{
     static bool newlineRequired = false;
     qDebug() << __PRETTY_FUNCTION__ << message;
     if( newlineRequired )
     {
          ui_->plainTextEdit->insertPlainText( "\n" );
     }
     ui_->plainTextEdit->insertPlainText( message );
     newlineRequired = true;
}


void Application::authorize( const QByteArray& authData )
{
     qDebug() << __PRETTY_FUNCTION__ << ": data:" << authData.toHex();
}


void Application::authCode( int code )
{
     qDebug() << __PRETTY_FUNCTION__ << ": code:" << code;
}


void Application::stop()
{
     qDebug() << __PRETTY_FUNCTION__;
}


void Application::visualTimerCountdown( std::chrono::milliseconds ms )
{
     qDebug() << __PRETTY_FUNCTION__;

     QTime time;
     time.setHMS( 0, 0, std::chrono::duration_cast< std::chrono::seconds >( ms ).count() );
     ui_->timerLabel->setText( time.toString( "mm:ss" ) );
}


} // namespace nmh
} // namespace alexen
