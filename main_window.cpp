#include <QLabel>
#include <QMessageBox>
#include <QApplication>
#include "main_window.h"

MainWindow::MainWindow(Reddit* r) {
	reddit = r;

	layout = new QVBoxLayout();

	welcomeLabel = new QLabel("Welcome to CS104 Reddit!!");
	layout->addWidget(welcomeLabel);

	// setup the new posts container widget
	postsLayout = new QVBoxLayout();
	postsContainerWidget = new QWidget();
	postsContainerWidget->setLayout(postsLayout);

	// add the container widget to the main layout
	layout->addWidget(postsContainerWidget);

	setupPosts(r->getPosts());

	aboutButton = new QPushButton("About CS104 Reddit");
	layout->addWidget(aboutButton);

	quitButton = new QPushButton("Quit");
	layout->addWidget(quitButton);
	// Create a new button with the text "Quit"
	
	setLayout(layout);
	show();

	connect(aboutButton, SIGNAL(clicked()), this, SLOT(showAbout()));

	connect(quitButton, SIGNAL(clicked()), this, SLOT(quit()));
	// Connect the quit button to the quit slot function
}

MainWindow::~MainWindow() {
	clearPosts();

	delete postsLayout;
	delete layout;
	delete postsContainerWidget;

	delete welcomeLabel;
	delete aboutButton;

	delete quitButton;
	// Delete the quit button pointer
}

void MainWindow::setupPosts(std::vector<Post*> posts) {
	clearPosts();

	for(Post * p : posts){
		PostWidget * pw = new PostWidget(p);
		layout->addWidget(pw);
		postWidgets.push_back(pw);
	}
	// Take in the vector of posts and for each of them:
	// 1. create a PostWidget
	// 2. add the PostWidget to the correct layout
	// 3. add the PostWidget to the vector so that we can delete the pointers later
}

void MainWindow::clearPosts() {
	for(PostWidget * pw : postWidgets){
		layout->removeWidget(pw);
		delete pw;
	}

	postWidgets.clear();
	// For each PostWidget pointer in the vector
	// 1. remove them from layout with removeWidget(QWidget*)
	// 2. delete the pointer
	// Then clear the vector
}

void MainWindow::showAbout() {
	QMessageBox::information(this, "About", "Simple Qt app for lab7!");
}

void MainWindow::quit(){
	QApplication::exit();
}
// Create a quit function, that serves as a slot for the exit button.
