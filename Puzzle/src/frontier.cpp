/*
 * frontier.cpp
 *
 *  Created on: Nov 7, 2016
 *      Author: edu
 */
#include "frontier.h"

static bool compareNode(node* i, node* j){
	return (i->getValue() < j->getValue());
}

//The data structure should be empty at the beginning
Frontier::Frontier(){

}

Frontier::~Frontier(){

}

void Frontier::insert(node *auxiliar){
	_frontier.push(auxiliar);
	//Very important to order the values correctly in the frontier
	//std::sort(_frontier.begin(), _frontier.end(), compareNode);
	//_frontier.sort(compareNode);
}

//Remove AND get first
node* Frontier::removeFirst(){
	node* aux = _frontier.top();
	_frontier.pop();
	return aux;
}

bool Frontier::isEmpty(){
	return _frontier.empty();
}

int Frontier::size(){
	return _frontier.size();
}
