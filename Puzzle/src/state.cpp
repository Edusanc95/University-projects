/*
 * state.cpp
 *
 *  Created on: Nov 6, 2016
 *      Author: edu
 */
#include "state.h"

state::state(Matrix<Tile, 10, 10> tileArray, int x, int y, int cols, int rows):
_tileArray(tileArray), _x(x), _y(y), _cols(cols), _rows(rows){

}


state::~state(){

}

Matrix<Tile, 10, 10> state::getTileArray(){
	return _tileArray;
}

int state::getX(){
	return _x;
}

int state::getY(){
	return _y;
}

int state::getCols(){
	return _cols;
}

int state::getRows(){
	return _rows;
}
