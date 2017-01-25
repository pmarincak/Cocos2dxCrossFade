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
* The audio coupling structure used for cross fades and playing music
*/

#ifndef BGMCOUPLE_H_
#define BGMCOUPLE_H_

#include <string>
#include <deque>

using namespace std;

struct BGMCouple {
	
	//Local strings
	//Could upgrade this to use a list/deque of strings for more parts; I only need 2
	string partA;
	string partB;
	
	//The music ID
	int id;
	
	//The next music ID to be set
	static int index;

	//Generic Creation Method
	BGMCouple() :
			partA(""), partB(""), id(-1) {

	}

	//Standard Creation Method
	BGMCouple(string A, string B = "") :
			partA(A), partB(B) {
		id = index;
		index++;
	}

	//Whether there is an intro or not
	bool hasIntro() {
		return partB != "";
	}

};

#endif /* BGMCOUPLE_H_ */
