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

					if (messyArray(q, s).getImage()
							!= tileArray(q, s).getImage()) {

						cout << "Not the same" << endl;
						aux = false;
					}


		}
	}
	return aux;
}

list<Sucessor>* stateSpace::Successor(state &pstate){

	list<Sucessor>* sucessors = new list<Sucessor>();

	list<bool>* possibleMovements = pstate.getTileArray().getMovements(pstate.getX(), pstate.getY());

	Sucessor* aux;
	Matrix<Tile, 10, 10> auxTileArray;
	state children(auxTileArray,0,0,0,0);
	int i = 1;
	for (std::list<bool>::iterator it=possibleMovements->begin(); it != possibleMovements->end(); ++it){

		if(*it==true){
			switch(i){
			//top
			case 1 :
				children = pstate;
				children.getTileArray().swap(children.getX(), children.getY(), children.getX(), children.getY() - 1);
				aux = new Sucessor(children, 1, "top");
				break;
			//bot
			case 2 :
				children = pstate;
				children.getTileArray().swap(children.getX(), children.getY(), children.getX(), children.getY() + 1);
				aux = new Sucessor(children, 1, "bot");
				break;
			//midLeft
			case 3 :
				children = pstate;
				children.getTileArray().swap(children.getX(), children.getY(), children.getX() - 1, children.getY() - 1);
				aux = new Sucessor(children, 1, "midLeft");
				break;
			//midRight
			case 4 :
				children = pstate;
				children.getTileArray().swap(children.getX(), children.getY(), children.getX() + 1, children.getY() - 1);
				aux = new Sucessor(children, 1, "midRight");
				break;
			default :
				break;
			}
			sucessors->push_back(*aux);
		}

		i++;
	}

	return sucessors;
}
