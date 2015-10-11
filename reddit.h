#ifndef REDDIT_H
#define REDDIT_H

#include <vector>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "post.h"
#include "lib/json.h"


class Reddit : public QObject {
	Q_OBJECT

	public:
		Reddit();
		~Reddit();
		std::vector<Post*> getPosts();
		void refresh();
		void clearPosts();

	signals:
		void postsRefreshed();

	private slots:
		void replyFinished(QNetworkReply*);

	private:
		void getAccessToken();
		void parsePosts(QtJson::JsonObject);

		std::vector<Post*> posts;
		QNetworkAccessManager *manager;
		QString accessToken;

		const QUrl ACCESS_TOKEN_URL = QUrl("https://www.reddit.com/api/v1/access_token");
		const QUrl HOT_POSTS_URL = QUrl("https://oauth.reddit.com/hot?limit=5");

		// You might wnat to change the following values:
		const QString BASIC_AUTHORIZATION = "OEpIZ3ZITlBKcEVFeEE6Rk5OTjR4OHEwYnBvSDRvaWNQYy11cDh0cFBV";
		const QString USERNAME = "ptzbot";
		const QString PASSWORD = "developer";
};
#endif
