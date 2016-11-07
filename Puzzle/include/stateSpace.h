/*
 * stateTemplate.h
 *
 *  Created on: Nov 6, 2016
 *      Author: edu
 */

#ifndef INCLUDE_STATESPACE_H_
#define INCLUDE_STATESPACE_H_
#include "state.h"

class stateSpace {
public:
	stateSpace(state &goalState);
	~stateSpace();

	bool isValid(state &tileState);
	bool isGoal(state &tileState);
	void Successor(state &tileState);

private:
	state &_goalState;

};



#endif /* INCLUDE_STATESPACE_H_ */
