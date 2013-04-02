/*
 * A class representing tiles which display tweets according to a specific tag.  Tweets
 * are cycled through according to the threshold set in the header file.
 */

#include "wall.h"
#include "twitterTile.h"
#include "webInterface.h"

/*
 * Create the tile with the given parameters.  Every constructor
 * calls the 'set' function with default parameters if not required by 
 * the constructor.
 */
twitterTile::twitterTile() {
	set(ofRandom(1000), "#robowall", ofRectangle(0, 5.5, 4, .5));
}

twitterTile::twitterTile(int id) {
	set(id, "#robowall", ofRectangle(0, 5.5, 4, .5));
}

twitterTile::twitterTile(string tag) {
	set(ofRandom(1000), tag, ofRectangle(0, 5.5, 4, .5));
}

twitterTile::twitterTile(int id, string tag) {
	set(id, tag, ofRectangle(0, 5.5, 4, .5));
}

twitterTile::twitterTile(int id, string tag, ofRectangle gridRect) {
	set(id, tag, gridRect);
}

twitterTile::~twitterTile() {

}

/*
 * Do the actual work for setting up the tile.
 */
void twitterTile::set(int id, string tag, ofRectangle gridRect) {
	state = HIDDEN;
	this->id = id;
	this->tag = tag;
	this->gridRect = gridRect;
	this->clickable = false;
	lastSwitch = ofGetElapsedTimeMillis();

	activeTweet = 0;

	translateGridDimensions();

	setupTweets();
}

/*
 * Update the tile as normal then account for the transition between
 * tweets.
 */
void twitterTile::update() {
	routineTile::update();

	if (state != HIDDEN) {
		//Based on timing differences, change the current tweet
		if (ofGetElapsedTimeMillis() - lastSwitch >= DISPLAY_THRESHOLD) {
			setState(FADE_OUT);
		}
	}
}

/*
 * Draw the tile as normal but then display the active tweet on it.
 * TODO think about displaying the user's profile picture too.
 */
void twitterTile::draw() {
	routineTile::draw();

	if (state != HIDDEN) {
		ofPushStyle();

		//Display the active tweet
		if (activeTweet != 0) {
			ofSetColor(0, 0, 0);
			ofDrawBitmapString(activeTweet->userName + ": " + activeTweet->text, tileRect.x + 12, tileRect.y + 12);
		}

		ofPopStyle();
	}
}

/*
 * Get a pointer to the routine at the specified index.
 */
void twitterTile::checkStateTransition() {
	if (state == ENTER && animations.empty()) setState(FADE_IN);
	if (state == FADE_IN && animations.empty()) setState(ACTIVE);
	if (state == FADE_OUT && animations.empty()) setState(FADE_IN);
	if (state == EXIT && animations.empty()) setState(HIDDEN);
}

/*
 * Get a pointer to the routine at the specified index.
 */
void twitterTile::setState(int newState) {
	routineTile::setState(newState);

	switch (newState) {
		case FADE_IN:
			{//This needs its own scope
				//Swap tweets
				if (!tweets.empty()) {
					int nextTweetIndex = getTweetIndex(activeTweet) + 1;
					if (nextTweetIndex >= tweets.size()) nextTweetIndex = 0;
					activeTweet = getTweetAt(nextTweetIndex);
				
					//TODO add fade in animation
				}
				lastSwitch = ofGetElapsedTimeMillis();
				break;
			}
		case FADE_OUT:
			//TODO add fade out animation
			break;
	}	
}

/*
 * Set the tile's current tag.  Refresh the list of
 * tweets accordingly.
 */
void twitterTile::setTag(string newTag) {
	tag = newTag;
	//TODO Clear out the current tweets
	setupTweets();
}

/*
 * Setup the tweets to be displayed by this tile.  Use the 
 * web interface to get the json results for the tile's tag
 * and then parse them into a list of tweet objects.
 */
void twitterTile::setupTweets() {
	ofxJSONElement jsonTweets = webInterface::getTweets(tag);
	ofxJSONElement jsonResults = jsonTweets["results"];

	for (int i = 0; i < jsonResults.size(); i++) {
		tweets.push_back(parseTweet(jsonResults[i]));
	}
}

/*
 * Create a tweet object for the given json object.
 */
tweet twitterTile::parseTweet(ofxJSONElement json) {
	tweet newTweet;
	newTweet.date = json["created_at"].asString();
	newTweet.userId = json["from_user_id"].asInt();
	newTweet.userName = json["from_user"].asString();
	newTweet.profileImageUrl = json["profile_image_url"].asString();
	newTweet.text = json["text"].asString();
	return newTweet;
}

/*
 * Get the index of the given routine.
 */
int twitterTile::getTweetIndex(tweet* t) {
	int index = 0;
	for (list<tweet>::iterator it = tweets.begin(); it != tweets.end(); it++) {
		if (&*it == t) return index;
		index++;
	}
	return -1;
}

/*
 * Get a pointer to the routine at the specified index.
 */
tweet* twitterTile::getTweetAt(int index) {
    list<tweet>::iterator it = tweets.begin();
	advance(it, index);
	return &*it;
}