#ifndef POST_H
#define POST_H

#include <string>

class Post {
	public:
		Post(std::string, std::string, std::string, std::string);

		std::string title;
		std::string username;
		std::string subreddit;
		std::string url;
		int karma;
};

#endif
