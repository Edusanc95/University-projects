/*
 * frontier.h
 *
 *  Created on: Nov 7, 2016
 *      Author: edu
 */

#ifndef INCLUDE_FRONTIER_H_
#define INCLUDE_FRONTIER_H_
#include <list>
#include <queue>
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

	struct Comparation {
	    bool operator()(node* p1, node* p2) {
	        // return "true" if "p1" is ordered before "p2", for example:
	        return (p1->getValue() > p2->getValue());
	    }
	};

	typedef std::vector<node*> Nodes;
	typedef std::priority_queue<node*, Nodes, Comparation> NodeQueue;
	NodeQueue _frontier;
};



#endif /* INCLUDE_FRONTIER_H_ */
