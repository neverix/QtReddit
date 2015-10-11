#include "reddit.h"

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
}

Reddit::~Reddit() {
	clearPosts();
}

std::vector<Post*> Reddit::getPosts() {
	return posts;
}

void Reddit::clearPosts() {
	for (auto it = posts.begin(); it != posts.end(); it++) {
		delete (*it);
	}
	posts.clear();
}
