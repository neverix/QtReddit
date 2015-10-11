#include <QLabel>
#include <QMessageBox>
#include <QApplication>
#include "main_window.h"

MainWindow::MainWindow(Reddit* r) {
	reddit = r;

	layout = new QVBoxLayout();
	layout->addWidget(new QLabel("Welcome to CS104 Reddit!"));

	// setup the new posts container widget
	postsLayout = new QVBoxLayout();
	postsContainerWidget = new QWidget();
	postsContainerWidget->setLayout(postsLayout);

	// add the container widget to the main layout
	layout->addWidget(postsContainerWidget);

	aboutButton = new QPushButton("About CS104 Reddit");
	layout->addWidget(aboutButton);
	
	refreshButton = new QPushButton("Refresh posts");
	layout->addWidget(refreshButton);

	setLayout(layout);
	show();

	connect(aboutButton, SIGNAL(clicked()), this, SLOT(showAbout()));
	connect(refreshButton, SIGNAL(clicked()), this, SLOT(refreshButtonClicked()));
	connect(r, SIGNAL(postsRefreshed()), this, SLOT(refreshPosts()));
}

MainWindow::~MainWindow() {
}

void MainWindow::setupPosts(std::vector<Post*> posts) {
	clearPosts();

	for(auto it = posts.begin(); it != posts.end(); it++) {
		PostWidget* newPostWidget = new PostWidget(*it);
		postsLayout->addWidget(newPostWidget);
		postWidgets.push_back(newPostWidget);
	}	
}

void MainWindow::clearPosts() {
	for (auto it = postWidgets.begin(); it != postWidgets.end(); it++) {
		postsLayout->removeWidget(*it);
		delete *it;
	}
	postWidgets.clear();
}

void MainWindow::refreshButtonClicked() {
	reddit->refresh();
}

void MainWindow::refreshPosts() {
	setupPosts(reddit->getPosts());
}

void MainWindow::showAbout() {
	QMessageBox::information(this, "About", "Simple Qt app for lab7!");
}

void MainWindow::quit() {
	QApplication::exit();
}


