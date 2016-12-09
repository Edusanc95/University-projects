/*
 * TileMatrix.h
 *
 *  Created on: Nov 29, 2016
 *      Author: edu
 */

#ifndef INCLUDE_TILEMATRIX_H_
#define INCLUDE_TILEMATRIX_H_
#include <vector>
#include <list>
#include <algorithm> // For random_shuffle
#include <iterator>  // For the iterators
#include <ctime>
#include "Tile.h"

class TileMatrix {

private:
	size_t _rows;
	size_t _cols;
	std::vector<Tile> m_Data;

public:
	//It's the same method as the overload of the operator ()
	TileMatrix(size_t rows, size_t cols){
		_rows = rows;
		_cols = cols;
		m_Data.resize(_cols*_rows);
	}

	Tile& get(size_t y, size_t x) {
			return m_Data[y * _cols + x];
	}

	std::vector<Tile>& getMData(){
		return m_Data;
	}

	Tile& operator()(size_t y, size_t x) {
		return m_Data[y * _cols + x];
	}

	//This randomization method only works with arrays of type n x n
	//Will be fixed later
	void shuffle() {
		std::srand(time(NULL));
		//std::random_shuffle( &get(0,0), &get(0,0) + sizeof(m_Data)/sizeof(get(0,0)) );
		std::random_shuffle(std::begin(m_Data), std::end(m_Data));
	}

	std::list<Tile>* getAdjacents(int x, int y) {
		std::list<Tile>* result = new std::list<Tile>;

		Tile top, midLeft, midRight, bot;
		if (y - 1 >= 0) {
			top = get(x, y - 1);

		}

		if (x - 1 >= 0) {
			midLeft = get(x - 1, y);

		}

		if (x + 1 < 4) {
			midRight = get(x + 1, y);

		}

		if (y + 1 < 4) {
			bot = get(x, y + 1);

		}

		if (y - 1 >= 0)
			result->push_back(top);

		if (y + 1 < 4)
			result->push_back(bot);

		if (x - 1 >= 0)
			result->push_back(midLeft);

		if (x + 1 < 4)
			result->push_back(midRight);

		return result;
	}

	// Returns possible movements based on the specified position, the returning list has 4 booleans ordered like:
	// 1st: Top 2nd: Bot 3rd: MidLeft 4th: MidRight

	std::list<bool>* getMovements(int y, int x, int xx, int yy) {
		std::list<bool>* movements = new std::list<bool>;
		bool top = false, midLeft = false, midRight = false, bot = false;

		if (x - 1 >= 0) {
			top = true;
		}

		if (y - 1 >= 0) {
			midLeft = true;

		}

		if (y + 1 < yy) {
			midRight = true;

		}

		if (x + 1 < xx) {
			bot = true;

		}

		movements->push_back(top);
		movements->push_back(bot);
		movements->push_back(midLeft);
		movements->push_back(midRight);

		return movements;
	}

	//We change the position of 2 objects.
	void swap(int x1, int y1, int x2, int y2){
		Tile& aux1 = get(x1, y1);
		Tile& aux2 = get(x2, y2);

		get(x2, y2) = aux1;
		get(x1, y1) = aux2;
	}

	//Method to make equal another matrix
	//Important, they have to be the same size
	// x and y is the maximum number of rows and cols.
	void makeEqual(TileMatrix aux, int x, int y){
		/*for(int i = 0; i<x; i++){
			for(int j = 0; j<y; j++){
				this->get(i,j) = aux.get(i,j);
			}
		}*/
		m_Data = aux.getMData();
	}
	// more methods go here
};


#endif /* INCLUDE_TILEMATRIX_H_ */
