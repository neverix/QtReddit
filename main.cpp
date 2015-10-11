#include <QApplication>
#include <vector>
#include "main_window.h"
#include "post.h"
#include "reddit.h"
#include "post_widget.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
 
 	Reddit* r = new Reddit();

 	// Testing for PostWidget. Create one and show that.
 	// COMMENT THE NEXT TWO LINES WHEN YOU FINISH POST_WIDGET
 	//PostWidget pw(r->getPosts()[0]);
 	//pw.show();

 	// Testing with the MainWindow, which should display a list of post widgets
 	// UNCOMMENT THE NEXT THREE LINES WHEN YOU FINISH POST_WIDGET
  MainWindow mw(r);
  mw.setWindowTitle("CS104 Reddit!");
  mw.show();

  return app.exec();
}

