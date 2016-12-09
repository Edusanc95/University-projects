/*
 * Problem.h
 *
 *  Created on: Nov 25, 2016
 *      Author: edu
 */

#ifndef INCLUDE_PROBLEM_H_
#define INCLUDE_PROBLEM_H_
#include "state.h"
#include "stateSpace.h"
#include "node.h"
#include "frontier.h"
#include "Sucessor.h"
#include "CImg.h"
#include "ImageManipulation.h"
#include <fstream>
class Problem{
public:
	Problem(state initialState, stateSpace aStateSpace);
	~Problem();

	bool boundedSearch(string strategy, int max_Depth);
	bool Search(string strategy, int max_Depth, int inc);
	void showSolution(string strategy, double time);
	int h(state x);
private:
	state _initialState;
	stateSpace _stateSpace;

	list<node*> createListTreeNodes(list<Sucessor>* sucessors, node* pNode, int max_Depth, string strategy);

	//For graphical representation of what's happening

	ImageManipulation _ImageManipulator;
	CImgDisplay _reconstructing_disp;
	node* _solution; //This is the last node we got, and may be the solution.
};


#endif /* INCLUDE_PROBLEM_H_ */
