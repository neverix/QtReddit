#include <QString>
#include <QFont>
#include "post_widget.h"

PostWidget::PostWidget(Post* p) {
	post = p;

	QFont karmaFont;
	karmaFont.setBold(true);
	karmaFont.setPointSize(25);

	QFont titleFont;
	titleFont.setBold(true);
	titleFont.setPointSize(14);

	layout = new QGridLayout();

	karmaLabel = new QLabel(QString::number(p->karma));
	karmaLabel->setFont(karmaFont);
	layout->addWidget(karmaLabel, 0, 0, 3, 1);

	titleLabel = new QLabel(QString::fromStdString(p->title));
	titleLabel->setFont(titleFont);
	titleLabel->setWordWrap(true);
	titleLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
	layout->addWidget(titleLabel, 0, 1, 2, 2);

	subredditLabel = new QLabel(QString::fromStdString(p->subreddit));
	layout->addWidget(subredditLabel, 2, 1, 1, 1);

	usernameLabel = new QLabel(QString::fromStdString(p->username));
	layout->addWidget(usernameLabel, 2, 2, 1, 1);

	urlLabel = new QLabel(QString::fromStdString("<a href=\"" + p->url + "\">" + p->url + "</a>"));
	urlLabel->setOpenExternalLinks(true);
	layout->addWidget(urlLabel, 3, 1, 1, 1);

	layout->setColumnMinimumWidth(0, 100);
	layout->setColumnStretch(1, 1);
	setLayout(layout);
}

PostWidget::~PostWidget() {
	delete titleLabel;
	delete usernameLabel;
	delete subredditLabel;
	delete urlLabel;
	delete karmaLabel;
	delete layout;
}
