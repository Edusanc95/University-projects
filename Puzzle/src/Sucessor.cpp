/*
 * Sucessor.cpp
 *
 *  Created on: Nov 10, 2016
 *      Author: edu
 */
#include "Sucessor.h"

Sucessor::Sucessor(state state, int cost, string action): _action(action), _state(state), _cost(cost){

}

Sucessor::~Sucessor(){

}

state Sucessor::getState(){
	return _state;
}

int Sucessor::getCost(){
	 return _cost;
}

string Sucessor::getAction(){
	return _action;
}
