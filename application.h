#pragma once

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class Application; }
QT_END_NAMESPACE


namespace alexen {
namespace nmh {


class RequestListener;
class ResponseSender;


class Application : public QMainWindow {
     Q_OBJECT
public:
     Application( QWidget *parent = nullptr );
     ~Application();

     void run();

private slots:
     void readMessageError( const QString& );
     void messageReceived( const QByteArray& );
     void shutdownApplication();

private:
     void showMessage( const QString& message );

     Ui::Application *ui_ = {};
     RequestListener* requestListener_ = {};
     ResponseSender* responseSender_ = {};
};


} // namespace nmh
} // namespace alexen
