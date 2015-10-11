#include "reddit.h"
#include <QNetworkRequest>
#include <QString>
#include <QDebug>

Reddit::Reddit() {
	Post* a = new Post("TIL Betty White is older than sliced bread",
		"ptzhk",
		"r/todayilearned",
		"http://bits.usc.edu/cs104");
	Post* b = new Post("Reddit, I found this gem on my way home today",
		"ruyanche",
		"r/aww",
		"http://bits.usc.edu/cs104");
	Post* c = new Post("I am a null pointer. AMA.",
		"mredekopp",
		"r/shttyprogramming",
		"http://bits.usc.edu/cs104");
	
	posts.push_back(a);
	posts.push_back(b);
	posts.push_back(c);

	manager = new QNetworkAccessManager(this);
	connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

	getAccessToken();
}

Reddit::~Reddit() {
	clearPosts();
}

std::vector<Post*> Reddit::getPosts() {
	return posts;
}

void Reddit::refresh() {
	if (!accessToken.isEmpty()) {
		QString auth = "bearer " + accessToken;

		QNetworkRequest request;
		request.setUrl(HOT_POSTS_URL);
		request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
		request.setRawHeader("Authorization", auth.toAscii());
		manager->get(request);
	}
}

void Reddit::getAccessToken() {
	QString auth = "Basic " + BASIC_AUTHORIZATION;
	QString params = "grant_type=password&username=" + USERNAME + "&password=" + PASSWORD;

	QNetworkRequest request;
	request.setUrl(ACCESS_TOKEN_URL);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
	request.setRawHeader("Authorization", auth.toAscii());
	manager->post(request, params.toAscii());
}

void Reddit::replyFinished(QNetworkReply* reply) {
	QString replyString = QString(reply->readAll());
	bool ok;
	QtJson::JsonObject result = QtJson::parse(replyString, ok).toMap();

	if (reply->request().url() == ACCESS_TOKEN_URL) {
		accessToken = result["access_token"].toString();
		refresh();
		qDebug() << "Loaded access token";
	} else {
		parsePosts(result);
	}
}

void Reddit::parsePosts(QtJson::JsonObject result) {
	clearPosts();
	QtJson::JsonObject data = result["data"].toMap();


	foreach(QVariant post, data["children"].toList()) {
		QtJson::JsonObject parsedPost = post.toMap()["data"].toMap();

		Post* newPost = new Post(parsedPost["title"].toString().toStdString(),
			parsedPost["author"].toString().toStdString(),
			"r/" + parsedPost["subreddit"].toString().toStdString(),
			parsedPost["url"].toString().toStdString());
		newPost->karma = parsedPost["score"].toInt();

		posts.push_back(newPost);
	}
	qDebug() << "Loaded posts";
	emit postsRefreshed();
}

void Reddit::clearPosts() {
	for (auto it = posts.begin(); it != posts.end(); it++) {
		delete (*it);
	}
	posts.clear();
}
