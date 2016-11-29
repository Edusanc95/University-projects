/*
 * Problem.cpp
 *
 *  Created on: Nov 25, 2016
 *      Author: edu
 */
#include "Problem.h"

Problem::Problem(state initialState, stateSpace aStateSpace): _initialState(initialState), _stateSpace(aStateSpace){

}

Problem::~Problem(){

}

//change list<>* for list<*>
bool Problem::boundedSearch(string strategy, int max_Depth){
	//Initialization process
	CImg<unsigned char> auxImage("puzzle.png");
	Frontier* pFrontier = new Frontier();
	node* n_actual;

	node* n_initial = new node(NULL, _initialState, 0, "nothing", 0, 0);
	pFrontier->insert(n_initial);
	bool isSolution = false;

	//Search loop
	//Remember to eliminate iterator and maxAux, and the _reconstructing_disp if needed.
	_reconstructing_disp.display(auxImage);

	while(!isSolution && !pFrontier->isEmpty() && !_reconstructing_disp.is_closed()){
		n_actual = pFrontier->removeFirst();

		if(n_actual->getParent() != NULL){
			_ImageManipulator.showIds(n_actual->getParent()->getState().getCols(), n_actual->getState().getRows(), n_actual->getParent()->getState().getTileArray());
			cout << n_actual->getAction()<< endl;
			_ImageManipulator.showIds(n_actual->getState().getCols(), n_actual->getState().getRows(), n_actual->getState().getTileArray());
		}
		//Representation of what's happening on screen, can be erased without problems.
		//_ImageManipulator.showTiles(n_actual->getState().getCols(),  n_actual->getState().getRows(), *(n_actual->getState().getTileArray()), &_reconstructing_disp);
		auxImage =_ImageManipulator.reconstructImage(n_actual->getState().getCols()
				   ,n_actual->getState().getRows()
				   ,auxImage.width() / n_actual->getState().getRows()
				   ,auxImage.height() / n_actual->getState().getCols()
				   ,auxImage
				   ,(n_actual->getState().getTileArray()));

		/*
		_ImageManipulator.equalImage(n_actual->getState().getCols(), n_actual->getState().getRows(), *_initialState.getTileArray(),
				*n_actual->getState().getTileArray());
		*/
		_reconstructing_disp.display(auxImage);
		sleep(1);

		if(_stateSpace.isGoal(n_actual->getState())){
			isSolution = true;
		}else{
			list<Sucessor>* sucessors = _stateSpace.Successor(n_actual->getState());
			list<node*> nodes;
			nodes = createListTreeNodes(sucessors, n_actual, max_Depth, strategy);
			for (std::list<node*>::iterator it=nodes.begin(); it != nodes.end(); ++it){
				pFrontier->insert(*it);
			}
		}
	}

	//Result
	//Placeholder
	if(isSolution){
		return true;
	}else{
		return false;
	}
}

bool Problem::Search(string strategy, int max_Depth, int inc){
	int actual_depth = inc;
	bool solution = false; //placeholder
	while(!solution && actual_depth<=max_Depth){
		solution = boundedSearch(strategy, actual_depth);
		actual_depth = actual_depth + inc;
	}
	return solution;
}
list<node*> Problem::createListTreeNodes(list<Sucessor>* sucessors, node* pNode, int max_Depth, string strategy){
	list<node*> nodes;
	if(pNode->getDepth()+1 > max_Depth){
		cout << "Maximum depth obtained, not adding the new nodes." << endl;
		//Do nothing because we got to the maximum depth
	}else{
		for (std::list<Sucessor>::iterator it=sucessors->begin(); it != sucessors->end(); ++it){
			int value = pNode->getValue()+1; //Placeholder
			node* auxNode = new node(pNode, it->getState(), it->getCost(), it->getAction(), pNode->getDepth()+1, value);
			nodes.push_back(auxNode);
		}
	}
	return nodes;
}

