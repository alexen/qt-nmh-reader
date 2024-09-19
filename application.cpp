#include <application.h>

#include <QDebug>
#include <QMessageBox>
#include <QStringLiteral>

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
     qDebug() << __PRETTY_FUNCTION__;

     ui_->setupUi( this );

     qInfo() << "Initializing Application: connect RequestListener signals";
     connect(
          requestListener_
          , SIGNAL(readMessageError(const QString&))
          , this
          , SLOT(readMessageError(const QString&))
          );
     connect(
          requestListener_
          , SIGNAL(inputStreamClosed())
          , this
          , SLOT(shutdownApplication())
          );
     connect(
          requestListener_
          , SIGNAL(messageReceived(const QByteArray&))
          , this
          , SLOT(messageReceived(const QByteArray&))
          );
}


Application::~Application()
{
     delete ui_;
     qDebug() << __PRETTY_FUNCTION__;
}


void Application::run()
{
     qDebug() << __PRETTY_FUNCTION__;
     requestListener_->start();
     show();
}


void Application::readMessageError( const QString& message )
{
     qDebug() << __PRETTY_FUNCTION__ << message;
//     QMessageBox::critical( this, QStringLiteral( "Read message error" ), message );
     ui_->statusLabel->setText( message );
}


void Application::messageReceived( const QByteArray& message )
{
     qDebug() << __PRETTY_FUNCTION__ << message;
     ui_->plainTextEdit->appendPlainText( message );
}


void Application::shutdownApplication()
{
     qDebug() << __PRETTY_FUNCTION__;
     close();
}


void Application::showMessage( const QString& message )
{
     ui_->plainTextEdit->insertPlainText( message );
     show();
}


} // namespace nmh
} // namespace alexen
