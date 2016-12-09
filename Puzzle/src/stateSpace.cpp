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
bool stateSpace::isValid(const state &tileState) {
	return true;
}

bool stateSpace::isGoal(const state &tileState) {
	bool aux = true;
	int cols, rows;

	cols = tileState.getCols();
	rows = tileState.getRows();

	TileMatrix messyArray = tileState.getTileArray();
	TileMatrix tileArray = _goalState.getTileArray();
	for (int q = 0; q < cols && aux; q++) {
		for (int s = 0; s < rows && aux; s++) {

					if (messyArray(q, s).getIdentifier()
							!= tileArray(q, s).getIdentifier()) {

						cout << "Not the goal state." << endl;
						aux = false;
					}
		}
	}

	if(aux)
		cout << "Goal archieved!" << endl;
	return aux;
}

state& stateSpace::getGoalState(){
	return _goalState;
}
list<Sucessor>* stateSpace::Successor(const state &pstate){

	list<Sucessor>* sucessors = new list<Sucessor>();

	list<bool>* possibleMovements = pstate.getTileArray().getMovements(pstate.getX(), pstate.getY(), pstate.getCols(), pstate.getRows());

	//Used just to create the new state.

	int i = 1;

	TileMatrix auxTileArray1(pstate.getCols(), pstate.getRows());
	TileMatrix auxTileArray2(pstate.getCols(), pstate.getRows());
	TileMatrix auxTileArray3(pstate.getCols(), pstate.getRows());
	TileMatrix auxTileArray4(pstate.getCols(), pstate.getRows());

	for (std::list<bool>::iterator it=possibleMovements->begin(); it != possibleMovements->end(); ++it){

		if(*it==true){

			//top
			if(i==1){

				auxTileArray1.makeEqual(pstate.getTileArray(), pstate.getRows(), pstate.getCols());

				//children.getTileArray()->swap(children.getX(), children.getY(), children.getX()-1, children.getY() );
				Tile aux1(pstate.getTileArray().get(pstate.getX(),pstate.getY()).getIdentifier(),
						pstate.getTileArray().get(pstate.getX(),pstate.getY()).getImage());
				//aux1 = auxTileArray1(pstate.getX(), pstate.getY());
				Tile aux2(pstate.getTileArray().get(pstate.getX(),pstate.getY()-1).getIdentifier(),
						pstate.getTileArray().get(pstate.getX(),pstate.getY()-1).getImage());
				//aux2 = auxTileArray1(pstate.getX()-1, pstate.getY());
				auxTileArray1(pstate.getX(), pstate.getY()) = aux2;
				auxTileArray1(pstate.getX(), pstate.getY()-1) = aux1;
				state children(auxTileArray1,pstate.getX(),pstate.getY(),pstate.getCols(),pstate.getRows());
				cout << "Changing " << children.getX() << children.getY()<< " for " << children.getX() << children.getY()-1 << endl;
				children.setY(children.getY()-1);

				Sucessor aux(children, 1, "top");
				sucessors->push_back(aux);


			//bot
			}else if(i==2){
				auxTileArray2.makeEqual(pstate.getTileArray(), pstate.getRows(), pstate.getCols());
				//children.getTileArray()->swap(children.getX(), children.getY(), children.getX()+1, children.getY() );
				Tile aux1(pstate.getTileArray().get(pstate.getX(),pstate.getY()).getIdentifier(),
						pstate.getTileArray().get(pstate.getX(),pstate.getY()).getImage());
				//aux1 = auxTileArray2(pstate.getX(), pstate.getY());
				Tile aux2(pstate.getTileArray().get(pstate.getX(),pstate.getY()+1).getIdentifier(),
						pstate.getTileArray().get(pstate.getX(),pstate.getY()+1).getImage());
				//aux2 = auxTileArray2(pstate.getX()+1, pstate.getY());
				auxTileArray2(pstate.getX(), pstate.getY()) = aux2;
				auxTileArray2(pstate.getX(), pstate.getY()+1) = aux1;
				state children(auxTileArray2,pstate.getX(),pstate.getY(),pstate.getCols(),pstate.getRows());
				cout << "Changing " << children.getX() << children.getY()<< " for " << children.getX() << children.getY()+1 << endl;
				children.setY(children.getY()+1);
				Sucessor aux(children, 1, "bot");
				sucessors->push_back(aux);

			//midLeft
			}else if(i==3){
				auxTileArray3.makeEqual(pstate.getTileArray(), pstate.getRows(), pstate.getCols());
				//children.getTileArray()->swap(children.getX(), children.getY(), children.getX() , children.getY()-1);
				Tile aux1(pstate.getTileArray().get(pstate.getX(),pstate.getY()).getIdentifier(),
						pstate.getTileArray().get(pstate.getX(),pstate.getY()).getImage());
				//aux1 = auxTileArray3(pstate.getX(), pstate.getY());
				Tile aux2(pstate.getTileArray().get(pstate.getX()-1,pstate.getY()).getIdentifier(),
						pstate.getTileArray().get(pstate.getX()-1,pstate.getY()).getImage());

				//aux2 = auxTileArray3(pstate.getX(), pstate.getY()-1);
				auxTileArray3(pstate.getX(), pstate.getY()) = aux2;
				auxTileArray3(pstate.getX()-1, pstate.getY()) = aux1;
				state children(auxTileArray3,pstate.getX(),pstate.getY(),pstate.getCols(),pstate.getRows());
				cout << "Changing " << children.getX() << children.getY()<< " for " << children.getX()-1 << children.getY() << endl;
				children.setX(children.getX()-1);
				//children.setY(children.getY()-1);
				Sucessor aux(children, 1, "midLeft");
				sucessors->push_back(aux);

			//midRight
			}else if(i==4){
				auxTileArray4.makeEqual(pstate.getTileArray(), pstate.getRows(), pstate.getCols());

				//children.getTileArray()->swap(children.getX(), children.getY(), children.getX() , children.getY()+1);
				Tile aux1(pstate.getTileArray().get(pstate.getX(),pstate.getY()).getIdentifier(),
						pstate.getTileArray().get(pstate.getX(),pstate.getY()).getImage());
				//aux1 = auxTileArray4(pstate.getX(), pstate.getY());
				Tile aux2(pstate.getTileArray().get(pstate.getX()+1,pstate.getY()).getIdentifier(),
						pstate.getTileArray().get(pstate.getX()+1,pstate.getY()).getImage());
				//aux2 = auxTileArray4(pstate.getX(), pstate.getY()+1);
				auxTileArray4(pstate.getX(), pstate.getY()) = aux2;
				auxTileArray4(pstate.getX()+1, pstate.getY()) = aux1;
				state children(auxTileArray4,pstate.getX(),pstate.getY(),pstate.getCols(),pstate.getRows());
				cout << "Changing " << children.getX() << children.getY() << " for " << children.getX()+1 << children.getY() << endl;
				children.setX(children.getX()+1);
				Sucessor aux(children, 1, "midRight");
				sucessors->push_back(aux);

			}

		}

		i++;
	}

	return sucessors;
}
