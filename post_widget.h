#ifndef POST_WIDGET_H
#define POST_WIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include "post.h"

class PostWidget : public QWidget {
	Q_OBJECT

	public:
		PostWidget(Post*);
		~PostWidget();

	private:
		Post* post;
		QGridLayout* layout;
		QLabel* titleLabel;
		QLabel* usernameLabel;
		QLabel* subredditLabel;
		QLabel* urlLabel;
		QLabel* karmaLabel;

		// Sneak peak of next lab!
		// QPushButton* upvoteButton;
		// QPushButton* downvoteButton;
};

#endif
