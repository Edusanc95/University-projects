/*
 * matrix.h
 *
 *  Created on: Oct 10, 2016
 *      Author: edu
 */

#ifndef INCLUDE_MATRIX_H_
#define INCLUDE_MATRIX_H_
#include <array>
#include <list>
#include <iterator>
#include <ctime>

template<class T, size_t rows, size_t cols>
class Matrix {
	std::array<T, rows * cols> m_Data;

private:
	//It's the same method as the overload of the operator (), but separated for only private uses inside the matrix.
	T& get(size_t y, size_t x) {
		return m_Data[y * cols + x];
	}

public:
	T& operator()(size_t y, size_t x) {
		return m_Data[y * cols + x];
	}

	//This randomization method only works with arrays of type n x n
	//Will be fixed later
	void shuffle() {
		std::srand(time(NULL));
			//std::random_shuffle( &get(0,0), &get(0,0) + sizeof(m_Data)/sizeof(get(0,0)) );
		std::random_shuffle(std::begin(m_Data), std::end(m_Data));
	}

	std::list<T>* getAdjacents(int x, int y) {
		std::list<T>* result = new list<T>;

		T top, midLeft, midRight, bot;
		if(y-1>=0) {
			top = get(x, y - 1);

		}

		if(x-1>=0) {
			midLeft = get(x - 1, y);

		}

		if(x+1<cols) {
			midRight = get(x + 1, y);

		}

		if(y+1<rows) {
			bot = get(x, y + 1);

		}

		if(y-1>=0)
		result->push_back(top);

		if(y+1<rows)
		result->push_back(bot);

		if(x-1>=0)
		result->push_back(midLeft);

		if(x+1<cols)
		result->push_back(midRight);

		return result;
	}

	// more methods go here
}
;

#endif /* INCLUDE_MATRIX_H_ */
