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

#ifndef CONSTANTS_H_
#define CONSTANTS_H_


#include <string>
#include <deque>
#include "cocos2d.h"
#include "BGMCouple.h"
#include "CrossFadeAction.h"

using namespace cocos2d;
using namespace std;

class Constants {

private:

	static string getMusicExtention(bool sfx, bool folder);
	static BGMCouple playingBGM;
	static BGMCouple previousBGM;
	static int partBID;
	static map<string, int> audioIDList;
	static CrossFadeAction* crossFade;

public:
	static int playingBGMID;
	static Node* AudioEntity;
	static float maxBGMVolume;

	static string getFullMusicPath(string music, bool sfx);
	static void playBackgroundMusic(BGMCouple couple);
	static void playRepeatBackgroundMusic(int val, string s);

};
#endif /* CONSTANTS_H_ */
