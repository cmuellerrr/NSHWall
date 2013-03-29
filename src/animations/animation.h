#pragma once

#include "ofMain.h"

class animation {

    public:

		virtual ~animation() {};

		virtual void update() = 0;
		virtual bool isDone() = 0;
};