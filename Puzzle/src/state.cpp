/*
 * state.cpp
 *
 *  Created on: Nov 6, 2016
 *      Author: edu
 */
#include "state.h"

state::state(Matrix<Tile, 4, 4> tileArray, int x, int y, int cols, int rows):
_tileArray(tileArray), _x(x), _y(y), _cols(cols), _rows(rows){

}


state::~state(){

}

Matrix<Tile, 4, 4> state::getTileArray() const{
	return _tileArray;
}

int state::getX() const{
	return _x;
}

int state::getY() const{
	return _y;
}

void state::setX(int x){
	_x = x;
}

void state::setY(int y){
	_y = y;
}
int state::getCols() const{
	return _cols;
}

int state::getRows() const{
	return _rows;
}
