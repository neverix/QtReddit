#include <QString>
#include <QFont>
#include "post_widget.h"
#include <QLabel>

PostWidget::PostWidget(Post* p) {
	post = p;

	//Set up Labels
	karmaLabel = new QLabel(QString::number(p->karma));
	titleLabel = new QLabel(QString::fromStdString(p->title));
	subredditLabel = new QLabel(QString::fromStdString(p->subreddit));
	usernameLabel = new QLabel(QString::fromStdString(p->username));
	urlLabel = new QLabel(QString::fromStdString("<a href=\"" + p->url + "\">" + p->url + "</a>"));
	urlLabel->setOpenExternalLinks(true);

	//Set up the fonts
	QFont karmaFont;
	karmaFont.setBold(true);
	karmaFont.setPointSize(16);
	karmaLabel->setFont(karmaFont);

	QFont titleFont;
	titleFont.setBold(true);
	titleFont.setPointSize(14);
	titleLabel->setFont(titleFont);

	QFont smallFont;
	smallFont.setPointSize(11);
	usernameLabel->setFont(smallFont);
	usernameLabel->setStyleSheet("color: #ABABAB");
	subredditLabel->setFont(smallFont);
	subredditLabel->setStyleSheet("color: #ABABAB");


	//Set up the layout
	layout = new QGridLayout();

	layout->addWidget(karmaLabel, 0, 0, 3, 1);
	layout->addWidget(titleLabel, 0, 1, 1, 4);
	layout->addWidget(subredditLabel, 1, 1, 1, 2);
	layout->addWidget(usernameLabel, 1, 5, 1, 2);
	layout->addWidget(urlLabel, 2, 1, 1, 2);

	setLayout(layout);
	// Create the suitable labels and add them to GridLayout properly.
}

PostWidget::~PostWidget() {
	delete titleLabel;
	delete usernameLabel;
	delete subredditLabel;
	delete urlLabel;
	delete karmaLabel;
	delete layout;
}
