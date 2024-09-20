#include <application.h>

#include <QDebug>

#include <ui_application.h>

#include <request_listener.h>
#include <request_router.h>
#include <response_sender.h>


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
          requestListener_
          , &RequestListener::messageReceived
          , requestRouter_
          , &RequestRouter::routeRequest
          );
     /// Bad request пробрасываем в отправитель ответов,
     /// с записью инцидента в журнал приложения.
     connect(
          requestRouter_
          , &RequestRouter::badRequest
          , this
          , [=]( const QByteArray& request, const QString& error ){
               qCritical() << "Bad request:" << request;
               responseSender_->sendErrorResponse( error );
          }
          );
     connect(
          requestListener_
          , &RequestListener::inputChannelClosed
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
}


Application::~Application()
{
     delete ui_;
     qDebug() << __PRETTY_FUNCTION__;
}


void Application::start()
{
     requestListener_->start();
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
     show();
}


} // namespace nmh
} // namespace alexen
