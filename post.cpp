#include "post.h"

Post::Post(std::string title, std::string username, std::string subreddit, std::string url) {
	this->title = title;
	this->username = username;
	this->subreddit = subreddit;
	this->url = url;
	
	this->karma = 0;
}
