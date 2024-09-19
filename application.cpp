#include <application.h>

#include <QDebug>
#include <QMessageBox>
#include <QStringLiteral>
#include <QThread>
#include <QEvent>

#include <ui_application.h>
#include <request_listener.h>
#include <response_sender.h>


namespace alexen {
namespace nmh {


Application::Application( QWidget *parent )
     : QMainWindow{ parent }
     , ui_{ new Ui::Application }
     , responseSender_{ new ResponseSender{ this } }
{
     ui_->setupUi( this );
     qDebug() << __PRETTY_FUNCTION__;
}


Application::~Application()
{
     delete ui_;
     qDebug() << __PRETTY_FUNCTION__;
}


void Application::start()
{
     qDebug() << __PRETTY_FUNCTION__;
     RequestListener* listener = new RequestListener{ stdin };
     QThread* thread = new QThread;

     listener->moveToThread( thread );

     /// Вызов необходим для старта потокового воркера
     connect( thread, SIGNAL(started()), listener, SLOT(start()) );
     /// Вызов необходим для корректного выключения? потока
     connect( listener, SIGNAL(inputChannelClosed()), thread, SLOT(quit()) );
     /// Необходим для корректного удаления объекта класса listener
     connect( listener, SIGNAL(inputChannelClosed()), listener, SLOT(deleteLater()) );
     /// Необходим для корректного удаления объекта класса QThread
     connect( thread, SIGNAL(finished()), thread, SLOT(deleteLater()) );

     connect(
          listener
          , SIGNAL(messageReceived(const QByteArray&))
          , this
          , SLOT(messageReceived(const QByteArray&))
          );

     thread->start();
}

void Application::closeEvent( QCloseEvent* event )
{
     event->ignore();
     hide();
}


void Application::messageReceived( const QByteArray& message )
{
     qDebug() << __PRETTY_FUNCTION__ << message;
     ui_->plainTextEdit->insertPlainText( message );
     show();
}


} // namespace nmh
} // namespace alexen
