
#include "wall.h"
#include "twitterTile.h"
#include "webInterface.h"

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

void twitterTile::set(int id, string tag, ofRectangle gridRect) {
	state = HIDDEN;
	this->id = id;
	this->tag = tag;
	this->gridRect = gridRect;
	this->clickable = false;
	lastSwitch = ofGetElapsedTimeMillis();

	activeTweet = 0;

	setupTileRect();
	defaultPosition = ofPoint(tileRect.x, tileRect.y);
	offscreenPosition = ofPoint(tileRect.x, -ofGetWindowHeight());

	setupTweets();
}

void twitterTile::update() {
	tile::update();

	if (state != HIDDEN) {
		//Based on timing differences, change the current tweet
		if (ofGetElapsedTimeMillis() - lastSwitch >= DISPLAY_THRESHOLD) {
			setState(FADE_OUT);
		}
	}
}

void twitterTile::draw() {
	tile::draw();

	if (state != HIDDEN) {
		//Display the active tweet
		if (activeTweet != 0) {
			ofSetColor(0, 0, 0);
			ofDrawBitmapString(activeTweet->userName + ": " + activeTweet->text, tileRect.x + 12, tileRect.y + 12);
		}
	}
}

void twitterTile::checkStateTransition() {
	if (state == ENTER && animations.empty()) setState(FADE_IN);
	if (state == FADE_IN && animations.empty()) setState(ACTIVE);
	if (state == FADE_OUT && animations.empty()) setState(FADE_IN);
	if (state == EXIT && animations.empty()) setState(HIDDEN);
}

void twitterTile::setState(int newState) {
	std::cout<<"Setting tile ("<<id<<") state to "<<newState<<'\n';

	switch (newState) {
		case ENTER:
			//Move the tile off screen
			tileRect.setPosition(offscreenPosition);
			animations.push_front(new pointAnimation(&tileRect.position, defaultPosition, 1.5, TANH, PLAY_ONCE, ofRandom(.5)));
			break;
		case EXIT:
			animations.push_front(new pointAnimation(&tileRect.position, offscreenPosition, 1.5, TANH, PLAY_ONCE, ofRandom(.5)));
			break;
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
	state = newState;
}

void twitterTile::setTag(string newTag) {
	tag = newTag;
	//TODO Clear out the current tweets
	setupTweets();
}

void twitterTile::setupTweets() {
	ofxJSONElement jsonTweets = webInterface::getTweets(tag);
	ofxJSONElement jsonResults = jsonTweets["results"];

	for (int i = 0; i < jsonResults.size(); i++) {
		tweets.push_back(parseTweet(jsonResults[i]));
	}
}

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