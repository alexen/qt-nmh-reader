#include <application.h>
#include <ui_application.h>
#include <request_listener.h>
#include <response_sender.h>


namespace alexen {
namespace nmh {


Application::Application( QWidget *parent )
     : QMainWindow{ parent }
     , ui_{ new Ui::Application }
     , requestListener_{ new RequestListener{ this } }
     , responseSender_{ new ResponseSender{ this } }
{
     ui_->setupUi( this );
}


Application::~Application()
{
     delete ui_;
}


void Application::run()
{
     show();
}


} // namespace nmh
} // namespace alexen
