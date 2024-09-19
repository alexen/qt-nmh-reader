#include <application.h>

#include <QDebug>

#include <ui_application.h>
#include <request_listener.h>
#include <response_sender.h>


namespace alexen {
namespace nmh {


Application::Application( QWidget *parent )
     : QMainWindow{ parent }
     , ui_{ new Ui::Application }
     , requestListener_{ new RequestListener{ stdin, this } }
     , responseSender_{ new ResponseSender{ this } }
{
     ui_->setupUi( this );
     qDebug() << __PRETTY_FUNCTION__;

     connect(
          requestListener_
          , SIGNAL(messageReceived(const QByteArray&))
          , this
          , SLOT(messageReceived(const QByteArray&))
          );
     connect(
          requestListener_
          , SIGNAL(inputChannelClosed())
          , this
          , SLOT(close())
          );
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


void Application::messageReceived( const QByteArray& message )
{
     qDebug() << __PRETTY_FUNCTION__ << message;
     ui_->plainTextEdit->insertPlainText( message );
     show();
}


} // namespace nmh
} // namespace alexen
