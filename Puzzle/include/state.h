/*
 * state.h
 *
 *  Created on: Nov 6, 2016
 *      Author: edu
 */

#ifndef INCLUDE_STATE_H_
#define INCLUDE_STATE_H_
#include "TileMatrix.h"
#include "Tile.h"

class state{
public:
	state(TileMatrix tileArray, int x, int y, int cols, int rows);
	~state();

	TileMatrix getTileArray() const;
	int getX() const;
	int getY() const;
	void setX(int x);
	void setY(int y);
	int getCols() const;
	int getRows() const;

private:
	TileMatrix _tileArray;

	//Position of the black tile
	int _x, _y;

	int _cols, _rows;
};


#endif /* INCLUDE_STATE_H_ */
