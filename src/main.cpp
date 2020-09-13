#include "utils.hpp"

#include <Wt/WApplication.h>
#include <Wt/WBootstrapTheme.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WMenu.h>
#include <Wt/WNavigationBar.h>
#include <Wt/WPushButton.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WText.h>
#include <Wt/WTextArea.h>

#include <memory>

class HelloApplication : public Wt::WApplication
{
private:
public:
  HelloApplication(const Wt::WEnvironment& env);

private:
  constexpr void linebreak() noexcept
  {
    root()->addWidget(std::make_unique<Wt::WBreak>());
  }
};

HelloApplication::HelloApplication(const Wt::WEnvironment& env) : Wt::WApplication(env)
{
  setTitle("Hello world");
  setTheme(std::make_shared<Wt::WBootstrapTheme>());

  fai::loaned_ptr nav{root()->addNew<Wt::WNavigationBar>()};
  nav->setResponsive(true);
  fai::loaned_ptr<Wt::WStackedWidget> contents{root()->addNew<Wt::WStackedWidget>()};
  fai::loaned_ptr<Wt::WMenu>          menu{
    nav->addMenu(std::make_unique<Wt::WMenu>(contents.to_raw()))};
  menu->addItem("Intro", std::make_unique<Wt::WTextArea>("Test area 1"));
  menu->addItem("CV", std::make_unique<Wt::WTextArea>("Test area 2"));
  menu->addItem("Portfolio", std::make_unique<Wt::WTextArea>("Test area 3"));
}

int main(int argc, char** argv)
{
  return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
    return std::make_unique<HelloApplication>(env);
  });
}