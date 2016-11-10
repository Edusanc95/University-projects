/*
 * Sucessor.cpp
 *
 *  Created on: Nov 10, 2016
 *      Author: edu
 */
#include "Sucessor.h"

Sucessor::Sucessor(string action, state state, int cost): _action(action), _state(state), _cost(cost){

}

Sucessor::~Sucessor(){

}

state Sucessor::getState(){
	return _state;
}
 int Sucessor::getCost(){
	 return _cost;
 }
