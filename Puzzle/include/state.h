/*
 * state.h
 *
 *  Created on: Nov 6, 2016
 *      Author: edu
 */

#ifndef INCLUDE_STATE_H_
#define INCLUDE_STATE_H_
#include "matrix.h"
#include "Tile.h"

class state{
public:
	state(Matrix<Tile, 10, 10> tileArray, int x, int y, int cols, int rows);
	~state();

	Matrix<Tile, 10, 10> getTileArray();
	int getX();
	int getY();
	int getCols();
	int getRows();

private:
	Matrix<Tile, 10, 10> _tileArray;

	//Position of the black tile
	int _x, _y;

	int _cols, _rows;
};


#endif /* INCLUDE_STATE_H_ */
