#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <vector>
#include "reddit.h"
#include "post.h"
#include "post_widget.h"


class MainWindow : public QWidget {
	Q_OBJECT

	public:
		MainWindow(Reddit*);
		~MainWindow();

	private slots:
		void showAbout();
		void quit();
		// ADD YOUR CODE HERE
		// declare a quit function under "slots"
		
	private:
		void setupPosts(std::vector<Post*>);
		void clearPosts();

		Reddit* reddit;

		QVBoxLayout* layout;
		QLabel* welcomeLabel;
		QVBoxLayout* postsLayout;
		QWidget* postsContainerWidget;
		QPushButton* aboutButton;
		QPushButton* quitButton;

		// ADD YOUR CODE HERE
		// add a quit button

		std::vector<PostWidget*> postWidgets;
};

#endif

