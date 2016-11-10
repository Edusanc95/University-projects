/*
 * node.h
 *
 *  Created on: Nov 7, 2016
 *      Author: edu
 */

#ifndef INCLUDE_NODE_H_
#define INCLUDE_NODE_H_
#include "state.h"

class node{
public:
	node(node* parent, state state, int cost, string action, int depth, int value);
	~node();

	int getValue();
	state getState();
	int getCost();
	int getDepth();

private:
	//Node information
	node* _parent;

	//Domain information
	state _state; //The arragement of tiles in this node
	int _cost; //Cost from the initial node to here
	string _action; //Movement that we made from the parent
	int _depth; //From the initial node to here
	int _value;
};



#endif /* INCLUDE_NODE_H_ */
