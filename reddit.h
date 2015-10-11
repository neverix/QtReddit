#ifndef REDDIT_H
#define REDDIT_H

#include <vector>
#include "post.h"

class Reddit {
	public:
		Reddit();
		~Reddit();
		std::vector<Post*> getPosts();
		void clearPosts();

	private:
		std::vector<Post*> posts;
};

#endif
