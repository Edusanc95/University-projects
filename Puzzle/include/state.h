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
	state(Matrix<Tile, 4, 4> tileArray, int x, int y, int cols, int rows);
	~state();

	Matrix<Tile, 4, 4> getTileArray() const;
	int getX() const;
	int getY() const;
	void setX(int x);
	void setY(int y);
	int getCols() const;
	int getRows() const;

private:
	Matrix<Tile, 4, 4> _tileArray;

	//Position of the black tile
	int _x, _y;

	int _cols, _rows;
};


#endif /* INCLUDE_STATE_H_ */
