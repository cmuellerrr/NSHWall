#pragma once

#include "animation.h"
#include "ofxAnimatableOfPoint.h"

class pointAnimation : public animation {

    public:
		pointAnimation(ofPoint* ref, ofPoint to, float duration, 
			AnimCurve curve = EASE_IN_EASE_OUT, AnimRepeat repeat = PLAY_ONCE, float delay = 0) {

			reference = ref;

			animatedPoint.setPosition(*ref);
			animatedPoint.animateToAfterDelay(to, delay);
			animatedPoint.setDuration(duration);
			animatedPoint.setRepeatType(repeat);
			animatedPoint.setCurve(curve);	
		}

		~pointAnimation() {};

		void update() {
			animatedPoint.update(1.0f / ofGetFrameRate());
			reference->set(animatedPoint.getCurrentPosition());
		}
		
		bool isDone() {
			return !animatedPoint.isOrWillBeAnimating();
		}

	private:
		ofxAnimatableOfPoint animatedPoint;
		ofPoint* reference;
};