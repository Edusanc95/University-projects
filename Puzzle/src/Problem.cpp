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
	CImg<unsigned char>* auxImage = new CImg<unsigned char>("puzzle.png");
	Frontier* pFrontier = new Frontier();
	node* n_actual;

	node* n_initial = new node(NULL, _initialState, 0, "nothing", 0, 0);
	pFrontier->insert(n_initial);
	bool isSolution = false;

	//Search loop
	//Remember to eliminate iterator and maxAux, and the _reconstructing_disp if needed.
	_reconstructing_disp.display(*auxImage);

	while(!isSolution && !pFrontier->isEmpty() && !_reconstructing_disp.is_closed()){
		n_actual = pFrontier->removeFirst();
		_solution = n_actual;
		cout << "Depth: " << n_actual->getDepth() << endl;
		cout << "Value: " << n_actual->getValue() << endl;
		if(n_actual->getParent() != NULL){
			_ImageManipulator.showIds(n_actual->getParent()->getState().getCols(), n_actual->getState().getRows(), n_actual->getParent()->getState().getTileArray());
			cout << n_actual->getAction()<< endl;
			_ImageManipulator.showIds(n_actual->getState().getCols(), n_actual->getState().getRows(), n_actual->getState().getTileArray());
		}
		//Representation of what's happening on screen, can be erased without problems.
		//_ImageManipulator.showTiles(n_actual->getState().getCols(),  n_actual->getState().getRows(), *(n_actual->getState().getTileArray()), &_reconstructing_disp);

		/*
		auxImage =_ImageManipulator.reconstructImage(n_actual->getState().getCols()
				   ,n_actual->getState().getRows()
				   ,auxImage->width() / n_actual->getState().getRows()
				   ,auxImage->height() / n_actual->getState().getCols()
				   ,auxImage
				   ,(n_actual->getState().getTileArray()));

		_reconstructing_disp.display(*auxImage);
		sleep(1);
		 */

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

void Problem::showSolution(string strategy, int inc, int time){
	CImg<unsigned char>* auxImage = new CImg<unsigned char>("puzzle.png");
	_reconstructing_disp.display(*(_ImageManipulator.reconstructImage(_solution->getState().getCols()
			   ,_solution->getState().getRows()
			   ,auxImage->width() / _solution->getState().getRows()
			   ,auxImage->height() / _solution->getState().getCols()
			   ,auxImage
			   ,(_solution->getState().getTileArray()))));
	sleep(1);
	string incremental;
	if(inc == 1){
		incremental = " incremental";
	}else if(inc == 2){
		incremental = " no incremental";
	}
	ofstream myfile;
	myfile.open ("result.txt");
	myfile << "Done with "<< strategy << incremental <<"\n";
	myfile << "In depth " << _solution->getDepth() << "\n";
	myfile << _solution->getAction() <<"\n";

	while(_solution->getParent()!=NULL){
		_solution = _solution->getParent();
		_reconstructing_disp.display(*(_ImageManipulator.reconstructImage(_solution->getState().getCols()
		,_solution->getState().getRows()
		,auxImage->width() / _solution->getState().getRows()
		,auxImage->height() / _solution->getState().getCols()
		,auxImage
		,(_solution->getState().getTileArray()))));
		sleep(1);
		myfile << "In depth " << _solution->getDepth() <<"\n";
		myfile << _solution->getAction() <<"\n";
	}
	myfile << "Time consumed: " << time << "\n";
	myfile.close();
}

list<node*> Problem::createListTreeNodes(list<Sucessor>* sucessors, node* pNode, int max_Depth, string strategy){
	list<node*> nodes;
	int value;
	if(pNode->getDepth()+1 > max_Depth){
		cout << "Maximum depth obtained, not adding the new nodes." << endl;
		//Do nothing because we got to the maximum depth
	}else{
		for (std::list<Sucessor>::iterator it=sucessors->begin(); it != sucessors->end(); ++it){
			if(strategy=="BFS"){
				value = pNode->getDepth()+1;
			}else if(strategy=="DFS"){
				value = (-1)*(pNode->getDepth()+1);
			}else if(strategy=="UCS"){
				value = pNode->getValue()+1;
			}
			node* auxNode = new node(pNode, it->getState(), it->getCost(), it->getAction(), pNode->getDepth()+1, value);
			nodes.push_back(auxNode);
		}
	}
	return nodes;
}

