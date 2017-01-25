/**
* @file
* @author  Paige Marincak <http://twitter.com/paigemarincak/>
* @version 1.0.0
*
* @section LICENSE
*
* (The MIT License)
*
* Copyright (c) 2017 Paige Marincak
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*
* @section DESCRIPTION
*
* Action which allows music to cross fade
*/

#include "CrossFadeAction.h"
#include "Constants.h"
#include <AudioEngine.h>

CrossFadeAction* CrossFadeAction::create(float duration, int oldSound,
		int partA, int partB) {
	CrossFadeAction *ret = new (std::nothrow) CrossFadeAction();

	if (ret) {
		if (ret->init(duration, oldSound, partA, partB)) {
			ret->autorelease();
		} else {
			delete ret;
			ret = nullptr;
		}
	}

	return ret;
}

bool CrossFadeAction::init(float duration, int oldSound, int partA, int partB) {
	bool ret = false;

	if (ActionInterval::initWithDuration(duration)) {
		oldSoundID = oldSound;
		partASoundID = partA;
		partBSoundID = partB;
		ret = true;
	}

	return ret;
}

void CrossFadeAction::stop() {
	ActionInterval::stop();
	//When the action ends make sure that the old sound volume is 0 and the new one is the max
	experimental::AudioEngine::setVolume(oldSoundID, 0);
	experimental::AudioEngine::setVolume(partASoundID, Constants::maxBGMVolume);
	experimental::AudioEngine::setVolume(partBSoundID, Constants::maxBGMVolume);
}

void CrossFadeAction::update(float time) {
	//Set the volume level of the sound IDs over time
	float percentage = time / (_duration/Constants::maxBGMVolume);

	experimental::AudioEngine::setVolume(oldSoundID,
			Constants::maxBGMVolume - percentage);

	experimental::AudioEngine::setVolume(partASoundID, percentage);
	experimental::AudioEngine::setVolume(partBSoundID, percentage);

}
