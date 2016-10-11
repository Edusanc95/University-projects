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

	std::list<T>* getAdjacents(int x, int y) {
		std::list<T>* result = new list<T>;
		/*
		 for (int dx = -1; dx <= 1; ++dx) {
		 for (int dy = -1; dy <= 1; ++dy) {
		 if (dx != 0 || dy != 0) {
		 result->push_back(m_Data[(x + dx) + (y + dy)]);
		 }
		 }
		 }*/

		T top, midLeft, midRight, bot;
		if(y-1>=0){
		top = get(x, y - 1);

		}

		if(x-1>=0){
		midLeft = get(x - 1, y);

		}

		if(x+1<cols){
		midRight = get(x + 1, y);

		}


		if(y+1<rows){
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
};

#endif /* INCLUDE_MATRIX_H_ */
