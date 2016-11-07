/*
 * node.cpp
 *
 *  Created on: Nov 7, 2016
 *      Author: edu
 */
#include "node.h"

node::node(node &parent, state state, int cost, string action, int depth, int value):
_parent(parent), _state(state), _cost(cost), _action(action), _depth(depth), _value(value){

}

int node::getValue(){
	return _value;
}
