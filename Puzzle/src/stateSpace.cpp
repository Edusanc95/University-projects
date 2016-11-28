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

	Matrix<Tile, 4, 4> messyArray = *tileState.getTileArray();
	Matrix<Tile, 4, 4> tileArray = *_goalState.getTileArray();
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

list<Sucessor>* stateSpace::Successor(const state &pstate){

	list<Sucessor>* sucessors = new list<Sucessor>();

	list<bool>* possibleMovements = pstate.getTileArray()->getMovements(pstate.getX(), pstate.getY(), pstate.getRows(), pstate.getCols());

	//Used just to create the new state.

	int i = 1;

	Matrix<Tile, 4, 4> auxTileArray1;
	Matrix<Tile, 4, 4> auxTileArray2;
	Matrix<Tile, 4, 4> auxTileArray3;
	Matrix<Tile, 4, 4> auxTileArray4;

	for (std::list<bool>::iterator it=possibleMovements->begin(); it != possibleMovements->end(); ++it){

		if(*it==true){

			//top
			if(i==1){

				auxTileArray1.makeEqual(*pstate.getTileArray(), pstate.getRows(), pstate.getCols());

				//children.getTileArray()->swap(children.getX(), children.getY(), children.getX()-1, children.getY() );
				Tile aux1(pstate.getTileArray()->get(pstate.getX(),pstate.getY()).getIdentifier(),
						pstate.getTileArray()->get(pstate.getX(),pstate.getY()).getImage());
				//aux1 = auxTileArray1(pstate.getX(), pstate.getY());
				Tile aux2(pstate.getTileArray()->get(pstate.getX()-1,pstate.getY()).getIdentifier(),
						pstate.getTileArray()->get(pstate.getX()-1,pstate.getY()).getImage());
				//aux2 = auxTileArray1(pstate.getX()-1, pstate.getY());
				auxTileArray1(pstate.getX(), pstate.getY()) = aux2;
				auxTileArray1(pstate.getX()-1, pstate.getY()) = aux1;
				state children(&auxTileArray1,pstate.getX(),pstate.getY(),pstate.getCols(),pstate.getRows());
				cout << "Changing " << children.getX() << children.getY()<< " for " << children.getX()-1 << children.getY() << endl;
				children.setX(children.getX()-1);

				Sucessor aux(children, 1, "top");
				sucessors->push_back(aux);


			//bot
			}else if(i==2){
				auxTileArray2.makeEqual(*pstate.getTileArray(), pstate.getRows(), pstate.getCols());
				//children.getTileArray()->swap(children.getX(), children.getY(), children.getX()+1, children.getY() );
				Tile aux1(pstate.getTileArray()->get(pstate.getX(),pstate.getY()).getIdentifier(),
						pstate.getTileArray()->get(pstate.getX(),pstate.getY()).getImage());
				//aux1 = auxTileArray2(pstate.getX(), pstate.getY());
				Tile aux2(pstate.getTileArray()->get(pstate.getX()+1,pstate.getY()).getIdentifier(),
						pstate.getTileArray()->get(pstate.getX()+1,pstate.getY()).getImage());
				//aux2 = auxTileArray2(pstate.getX()+1, pstate.getY());
				auxTileArray2(pstate.getX(), pstate.getY()) = aux2;
				auxTileArray2(pstate.getX()+1, pstate.getY()) = aux1;
				state children(&auxTileArray2,pstate.getX(),pstate.getY(),pstate.getCols(),pstate.getRows());
				cout << "Changing " << children.getX() << children.getY()<< " for " << children.getX()+1 << children.getY() << endl;
				children.setX(children.getX()+1);
				Sucessor aux(children, 1, "bot");
				sucessors->push_back(aux);

			//midLeft
			}else if(i==3){
				auxTileArray3.makeEqual(*pstate.getTileArray(), pstate.getRows(), pstate.getCols());
				//children.getTileArray()->swap(children.getX(), children.getY(), children.getX() , children.getY()-1);
				Tile aux1(pstate.getTileArray()->get(pstate.getX(),pstate.getY()).getIdentifier(),
						pstate.getTileArray()->get(pstate.getX(),pstate.getY()).getImage());
				//aux1 = auxTileArray3(pstate.getX(), pstate.getY());
				Tile aux2(pstate.getTileArray()->get(pstate.getX(),pstate.getY()-1).getIdentifier(),
						pstate.getTileArray()->get(pstate.getX(),pstate.getY()-1).getImage());

				//aux2 = auxTileArray3(pstate.getX(), pstate.getY()-1);
				auxTileArray3(pstate.getX(), pstate.getY()) = aux2;
				auxTileArray3(pstate.getX(), pstate.getY()-1) = aux1;
				state children(&auxTileArray3,pstate.getX(),pstate.getY(),pstate.getCols(),pstate.getRows());
				cout << "Changing " << children.getX() << children.getY()<< " for " << children.getX() << children.getY()-1 << endl;
				children.setY(children.getY()-1);
				//children.setY(children.getY()-1);
				Sucessor aux(children, 1, "midLeft");
				sucessors->push_back(aux);

			//midRight
			}else if(i==4){
				auxTileArray4.makeEqual(*pstate.getTileArray(), pstate.getRows(), pstate.getCols());

				//children.getTileArray()->swap(children.getX(), children.getY(), children.getX() , children.getY()+1);
				Tile aux1(pstate.getTileArray()->get(pstate.getX(),pstate.getY()).getIdentifier(),
						pstate.getTileArray()->get(pstate.getX(),pstate.getY()).getImage());
				//aux1 = auxTileArray4(pstate.getX(), pstate.getY());
				Tile aux2(pstate.getTileArray()->get(pstate.getX(),pstate.getY()+1).getIdentifier(),
						pstate.getTileArray()->get(pstate.getX(),pstate.getY()+1).getImage());
				//aux2 = auxTileArray4(pstate.getX(), pstate.getY()+1);
				auxTileArray4(pstate.getX(), pstate.getY()) = aux2;
				auxTileArray4(pstate.getX(), pstate.getY()+1) = aux1;
				state children(&auxTileArray4,pstate.getX(),pstate.getY(),pstate.getCols(),pstate.getRows());
				cout << "Changing " << children.getX() << children.getY() << " for " << children.getX() << children.getY()+1 << endl;
				children.setY(children.getY()+1);
				Sucessor aux(children, 1, "midRight");
				sucessors->push_back(aux);

			}

		}

		i++;
	}

	return sucessors;
}
