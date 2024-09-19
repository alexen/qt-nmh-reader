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

     void start();

signals:
     void finish();

protected:
     void closeEvent( QCloseEvent* );

private slots:
     void messageReceived( const QByteArray& );

private:
     Ui::Application *ui_ = {};
     ResponseSender* responseSender_ = {};
};


} // namespace nmh
} // namespace alexen
