#include <application.h>
#include <ui_application.h>


namespace alexen {
namespace nmh {


Application::Application( QWidget *parent )
     : QMainWindow{ parent }
     , ui_{ new Ui::Application }
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
