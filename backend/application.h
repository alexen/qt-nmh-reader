#pragma once

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class Application; }
QT_END_NAMESPACE


namespace alexen {
namespace nmh {


class RequestListener;
class ResponseSender;
class RequestRouter;


class Application : public QMainWindow {
     Q_OBJECT
public:
     Application( QWidget *parent = nullptr );
     ~Application();

     void start();

     void closeEvent( QCloseEvent* );

private slots:
     void showMessage( const QByteArray& );

private:
     Ui::Application *ui_ = {};
     RequestListener* requestListener_ = {};
     RequestRouter* requestRouter_ = {};
     ResponseSender* responseSender_ = {};
};


} // namespace nmh
} // namespace alexen
