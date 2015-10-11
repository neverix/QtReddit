#include <QApplication>
#include <vector>
#include "main_window.h"
#include "post.h"
#include "reddit.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
 
 	Reddit* r = new Reddit();
  MainWindow mw(r);
  
  mw.setWindowTitle("CS104 Reddit");
  mw.show();

  return app.exec();
}

