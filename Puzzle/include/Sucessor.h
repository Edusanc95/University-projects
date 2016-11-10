/*
 * Sucessor.h
 *
 *  Created on: Nov 10, 2016
 *      Author: edu
 */

#ifndef INCLUDE_SUCESSOR_H_
#define INCLUDE_SUCESSOR_H_

#include "state.h"

class Sucessor {
public:
	Sucessor(string action, state state, int cost);
	~Sucessor();
	state getState();
	int getCost();
private:
	string _action;
	state _state;
	int _cost;

};



#endif /* INCLUDE_SUCESSOR_H_ */
