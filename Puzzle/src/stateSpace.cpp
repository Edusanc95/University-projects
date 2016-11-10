/*
 * stateSpace.cpp
 *
 *  Created on: Nov 10, 2016
 *      Author: edu
 */
#include "stateSpace.h"

stateSpace::stateSpace(state &goalState) :
		_goalState(goalState) {

}

stateSpace::~stateSpace() {

}

//Ask what we need to do here
bool stateSpace::isValid(state &tileState) {
	return true;
}

bool stateSpace::isGoal(state &tileState) {
	bool aux = true;
	int cols, rows;

	cols = tileState.getCols();
	rows = tileState.getRows();

	Matrix<Tile, 10, 10> messyArray = tileState.getTileArray();
	Matrix<Tile, 10, 10> tileArray = _goalState.getTileArray();
	for (int q = 0; q < cols; q++) {
		for (int s = 0; s < rows; s++) {


			for (int i = 0; i < cols && aux; i++) {
				for (int j = 0; j < rows && aux; j++) {
					if (messyArray(q, s).getImage()
							!= tileArray(i, j).getImage()) {

						cout << "Not the same" << endl;
						aux = false;
					}
				}
			}

		}
	}
	return aux;
}

list<node>* stateSpace::Successor(node &pnode){

	list<node>* nodes = new list<node>();

	list<bool>* possibleMovements = pnode.getState().getTileArray().getMovements(pnode.getState().getX(), pnode.getState().getY());

	node* aux;
	Matrix<Tile, 10, 10> auxTileArray;
	state children(auxTileArray,0,0,0,0);
	int i = 1;
	for (std::list<bool>::iterator it=possibleMovements->begin(); it != possibleMovements->end(); ++it){

		if(*it==true){
			switch(i){
			//top
			case 1 :
				children = pnode.getState();
				children.getTileArray().swap(children.getX(), children.getY(), children.getX(), children.getY() - 1);
				aux = new node(&pnode, children, pnode.getCost(), "top", pnode.getDepth()+1, 0);
				break;
			//bot
			case 2 :
				children = pnode.getState();
				children.getTileArray().swap(children.getX(), children.getY(), children.getX(), children.getY() + 1);
				aux = new node(&pnode, children, pnode.getCost(), "bot", pnode.getDepth()+1, 0);
				break;
			//midLeft
			case 3 :
				children = pnode.getState();
				children.getTileArray().swap(children.getX(), children.getY(), children.getX() - 1, children.getY() - 1);
				aux = new node(&pnode, children, pnode.getCost(), "midLeft", pnode.getDepth()+1, 0);
				break;
			//midRight
			case 4 :
				children = pnode.getState();
				children.getTileArray().swap(children.getX(), children.getY(), children.getX() + 1, children.getY() - 1);
				aux = new node(&pnode, children, pnode.getCost(), "midRight",  pnode.getDepth()+1, 0);
				break;
			default :
				break;
			}
			nodes->push_back(*aux);
		}

		i++;
	}

	return nodes;
}
