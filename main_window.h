#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QVBoxLayout>
#include <QPushButton>
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
		void refreshPosts();
		void refreshButtonClicked();
		
	private:
		void setupPosts(std::vector<Post*>);
		void clearPosts();

		Reddit* reddit;

		QVBoxLayout* layout;
		QVBoxLayout* postsLayout;
		QWidget* postsContainerWidget;
		QPushButton* aboutButton;
		QPushButton* refreshButton;

		std::vector<PostWidget*> postWidgets;
};

#endif

