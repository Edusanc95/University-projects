/*
 * frontier.h
 *
 *  Created on: Nov 7, 2016
 *      Author: edu
 */

#ifndef INCLUDE_FRONTIER_H_
#define INCLUDE_FRONTIER_H_
#include <list>
#include "node.h"
//REMEMBER WE NEED TO ORDER THE FRONTIER
class Frontier{

public:
	Frontier();
	~Frontier();
	void insert(node *auxiliar);
	node* removeFirst();
	bool isEmpty();

private:
	std::vector<node*>_frontier;
};



#endif /* INCLUDE_FRONTIER_H_ */
