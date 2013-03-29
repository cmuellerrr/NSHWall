#pragma once

#include "animation.h"
#include "ofxAnimatableOfPoint.h"

class dimensionAnimation : public animation {

    public:
		dimensionAnimation(float* refX, float* refY, ofPoint to, float duration, 
			AnimCurve curve = EASE_IN_EASE_OUT, AnimRepeat repeat = PLAY_ONCE, float delay = 0) {

			referenceX = refX;
			referenceY = refY;

			animatedPoint.setPosition(ofPoint(*refX, *refY));
			animatedPoint.animateToAfterDelay(to, delay);
			animatedPoint.setDuration(duration);
			animatedPoint.setRepeatType(repeat);
			animatedPoint.setCurve(curve);	
		}

		~dimensionAnimation() {};

		void update() {
			animatedPoint.update(1.0f / ofGetFrameRate());
			ofPoint curPos = animatedPoint.getCurrentPosition();
			*referenceX = curPos.x;
			*referenceY = curPos.y;
		}
		
		bool isDone() {
			return !animatedPoint.isOrWillBeAnimating();
		}

	private:
		ofxAnimatableOfPoint animatedPoint;
		float* referenceX;
		float* referenceY;
};