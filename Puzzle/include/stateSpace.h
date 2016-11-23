/*
 * stateTemplate.h
 *
 *  Created on: Nov 6, 2016
 *      Author: edu
 */

#ifndef INCLUDE_STATESPACE_H_
#define INCLUDE_STATESPACE_H_
#include "state.h"
#include "Sucessor.h"
#include "node.h"
#include "matrix.h"
#include <list>
#include <iostream>

class stateSpace {
public:
	stateSpace(state &goalState);
	~stateSpace();

	bool isValid(state &tileState);
	bool isGoal(state &tileState);
	list<Sucessor>* Successor(state &pstate);

private:
	state &_goalState;

};



#endif /* INCLUDE_STATESPACE_H_ */
