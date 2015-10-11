# Lab 6 Extended - turning into an actual Reddit client

In Lab 6, we built a fake Reddit client: we were given a list of "fake Reddit posts", and we displayed them in a Qt window based on our modular design. Recall that there were three major "parts" of the program:

- **Reddit class** - This class handeld creation of the posts, and serves as a "database" to the rest of the program
- **PostWidget** - a widget that renders _one_ single Post using Qt GUI elements
- **MainWindow** - contained a collection os `PostWidget`s, as well as a bunch of other buttons

We used to generate a bunch of fake posts in the constructor of the `Reddit` class, but what if we can actually get _actual_ posts from Reddit? Well, with the help of some Qt utilities, we can.

In fact, the code is already done for you, and is ready for you to check out at the [labs](https://github.com/usc-csci104-fall2015/labs) repository, under the [`labs-extended`](https://github.com/usc-csci104-fall2015/labs/tree/master/lab6-extended) folder. Remember - **do not** run `qmake -project` after pulling - the project file has been changed, and doing so will override my changes. Simply `qmake`, `make`, and run with `./lab7`.

![Actual Reddit client](http://ptzlabs.com/files/43/l8cs0sp7msowk.png)

 But, you can also choose to read on, and learn about:

- Using Reddit API + Qt HTTP tools like `QNetworkAccessManager`
- Using custom signals

### Reddit API

Reddit comes with [an extensive set of API](http://www.reddit.com/dev/api). You've probably heard of the term "API" a lot, and you probably know it stands for "Application Programming Interface", but you might have been a little scared to check it out what it actually means and how to actually do anything with it.

In a nutshell, different applicaitons can access each other through APIs. Recently, the term is used much more in reference to a third-party application getting access to another service. You've probably seen this everywhere: Netflix reads your Facebook friends list to recommend movies, an alternative Twitter client on your phone, or a Chrome extension changing the way that a website looks, etc. Heck, `ptzbot` scrapes your homework and creates an issue to alert you through the Github API.

Likewise, our application can directly interface with Reddit through its API as well. Meaning, providing a Reddit username and password, we can get content from Reddit just as if we're accsesing from the website.

Now, our goal is to display the front-page posts for a logged in user. In order to do that, there are several steps:

#### 1. Authenticate as an user

Reddit API uses a common authentication called [OAuth](http://oauth.net/2/). It's quite confusing and it's not for the easily-fainted. But, the idea is this:

- identify who you (the third-party application) are
- give Reddit a username / password
- Reddit returns an "access token" that's specific for the user on your application
- Include the access token for every request that you make

You can see this happening in `Reddit::getAccessToken()` function, which uses the [`QNetworkAccessManager`](http://qt-project.org/doc/qt-4.8/qnetworkaccessmanager.html). The constructor to the Reddit class actually calls this function, to ensure that we have access to Reddit as early as possible. We send a HTTP Request to a specific URL, along with the following:

1. the "Authorization" header, which identifies this specific third-party program. I have created registered this app with Reddit already (through [this page](https://www.reddit.com/prefs/apps/)), and these are the credentials that they gave me. The constant `BASIC_AUTHORIZATION` is defined in `reddit.h`. This string is a base64-encoded version of the string `{client_id}:{client_secret}`.
2. the parameters of the request, stored in the variable `data`, include `grant_type`, `username`, and `password`. I've included the credentials to a throwaway account `ptzbot` for you, but if you want to change it, you'll have to create your own app credentials.

The request is going to be sent to Reddit's server, who is going to validate the credentials that you provided, and return an accessToken. The response is parsed through the `replyFinished()` function, which is magically called by the signal/slot connecttion called at [line 25](https://github.com/usc-csci104-spring2015/labs/blob/master/lab7-extended/reddit.cpp#L25).

#### 2. Send a request to the server with the access token

Now that we have an access token, we can make a request to get front end pages. The usage is similar, except instead of using the app credentials, we now use the access token that we received from Reddit. You can see this code in the `Reddit::refresh()` function.

Again, the response comes back to the `replyFinished()` function, where it will call the `parsePosts()` function with the result. Most HTTP requests are designed these days to return results in [JSON format](http://json.org/) - pretty much gigantic structs that can include any type of data. We use a library called Qt-Json which I included in the `lib/` library that helps us parse the data.

The response is going to contain a list of posts. You can see that I am creating a new `Post` object for each of the posts in the list, and then push back to the vector of posts.

#### 3. Emit a signal

When the parsing is done, at the end we emit a custom signal called `postsRefreshed()`. There is no implementation of this function, but if you look in `main_window.h`, it is declared under the "signals" section. If anybody is listening to this signal - and my modified version of `MainWindow` is (on [line 31 of main_window.cpp](https://github.com/usc-csci104-fall2015/labs/blob/master/lab6-extended/main_window.cpp#L31)) - it'll alert the listener that a new set of posts is available and appropriate action should be taken.

In this case, the appropriate action for `MainWindow` is to refresh the GUI elements - clear the existing `PostWidget`s, creating new ones with the new data, and displaying them again. Fortunately, we already have those functions ready to call from lab 7 - `clearPosts()` and `setupPosts()`.

### Conclusion

Really, most of the chnages to change our program to display actual Reddit posts is in the `Reddit` class. The rest is to change `MainWindow` to listen to a new signal that we created, and we can reuse many of the already existing functions. Next thing you know - you'd be building a full Reddit client based on Qt!

This is an extremely basic guide to making HTTP requests in Qt, and using APIs with OAuth. After all, 104 is not an app development class; but if you have any other questions, feel free to visit Peter in his office hours, and he'll be more than happy to discuss with you.

Some other resources worth checking out:

- [Reddit API Overview](http://www.reddit.com/dev/api)
- [Sample guide to authenticate with Reddit](https://github.com/reddit/reddit/wiki/OAuth2-Quick-Start-Example)
