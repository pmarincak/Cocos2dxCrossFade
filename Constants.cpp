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
* Generic constants file
*/

#include "Constants.h"
#include <AudioEngine.h>
using namespace std;

float Constants::maxBGMVolume = 0.5;

//Must formally create this entity in your first scene
/**
* if (!Constants::AudioEntity) {
*	Constants::AudioEntity = Node::create();
*	CC_SAFE_RETAIN(Constants::AudioEntity);
* }
*/
Node* Constants::AudioEntity = 0;
BGMCouple Constants::playingBGM = BGMCouple();
BGMCouple Constants::previousBGM = BGMCouple();
int Constants::playingBGMID = -1;
int Constants::partBID = -1;
map<string, int> Constants::audioIDList = map<string, int>();
CrossFadeAction* Constants::crossFade = 0;

string Constants::getFullMusicPath(string music, bool sfx) {
	string effectName = music + getMusicExtention(sfx, false);
	//Change to where you keep your music
	string result = "Sounds/" + getMusicExtention(sfx, true) + effectName;
	return result;
}

void Constants::playBackgroundMusic(BGMCouple couple) {
	//it's already playing so don't bother
	if (couple.id == playingBGM.id) {
		return;
	}
	//Could upgrade to use a stack to keep track of the previous music, I only need the last one
	previousBGM = playingBGM;
	playingBGM = couple;
	
	//Whether to repeat the A part or not
	bool repeat = !couple.hasIntro();
	
	//Get the music paths for the platform being played
	string musicA = getFullMusicPath(couple.partA, false);
	string musicB = getFullMusicPath(couple.partB, false);

	//Get the full music paths for the system
	musicA = FileUtils::getInstance()->fullPathForFilename(musicA);
	musicB = FileUtils::getInstance()->fullPathForFilename(musicB);

	int oldPlayingBGMID = playingBGMID;

	//If there's already a musicID for the A part, stop it
	if (audioIDList[musicA] > 0) {
		experimental::AudioEngine::stop(audioIDList[musicA]);
	}
	
	//Play the A part
	playingBGMID = experimental::AudioEngine::play2d(musicA, repeat, 0);
	audioIDList[musicA] = playingBGMID;

	//If we need to play the B part
	if (!repeat) {
		//Set the callback
		experimental::AudioEngine::setFinishCallback(playingBGMID,
				Constants::playRepeatBackgroundMusic);
		//If there's already a musicID for the B part, stop it
		if (audioIDList[musicB] > 0) {
			experimental::AudioEngine::stop(audioIDList[musicB]);
		} else {
			experimental::AudioEngine::preload(musicB);
		}
	}

	//If there's a crossFade action for the BGM already, stop it and reset it
	if (crossFade) {
		crossFade->stop();
		crossFade->release();
		crossFade = 0;
	}
	//Create the cross fade
	// Could upgrade method to pass the length of time to have the cross fade cover, and to use easing 
	// See here for more details http://www.cocos2d-x.org/wiki/Actions#Easing
	crossFade = CrossFadeAction::create(1, oldPlayingBGMID, playingBGMID);
	crossFade->retain();

	//Make sure the audio entity is created in the first scene, see definition above for details
	if (AudioEntity) {
		//Add the cross fade to the audio entity
		Director::getInstance()->getActionManager()->addAction(crossFade,
				Constants::AudioEntity, false);
	} else {
		//Don't use the cross fade
		experimental::AudioEngine::setVolume(playingBGMID,
				Constants::maxBGMVolume);
	}
}

void Constants::playRepeatBackgroundMusic(int val, string s) {
	audioIDList[s] = 0;
	if (val == playingBGMID) {
		//Similar to the method above, get the file paths and play the music on repeat
		string musicB = getFullMusicPath(playingBGM.partB, false);
		musicB = FileUtils::getInstance()->fullPathForFilename(musicB);
		playingBGMID = experimental::AudioEngine::play2d(musicB, true,
				experimental::AudioEngine::getVolume(val));
		audioIDList[musicB] = playingBGMID;
		crossFade->setPartBSoundID(playingBGMID);
	}
}

//For multiplatform purposes
string Constants::getMusicExtention(bool sfx, bool folder) {
	string result = "";
	string ogg = "ogg", wav = "wav", mp3 = "mp3";
	if (!folder) {
		result += ".";
	}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	result += mp3;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	result += mp3;
#else
	result += wav;
#endif
	if (folder) {
		result += "/";
	}
	return result;
}
