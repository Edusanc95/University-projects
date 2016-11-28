#include <Tile.h>
#include <iostream>
#include "CImg.h"
#include "matrix.h"
#include "Problem.h"
#include "ImageManipulation.h"
#include <list>
#include <vector>
#include <sstream>

using namespace std;
using namespace cimg_library;

template<typename T>
T cinitialize(std::istream & is) noexcept
{
	T x;
	return (is && is >> x) ? x : T();
}

int main(int argc, char **argv) {

	int cols, rows;
	string puzzle;

	ImageManipulation ImageManipulator;
	cout << "Introduce number of columns:" << endl;
	cin >> cols;
	cout << "Introduce number of rows:" << endl;
	cin >> rows;

	CImg<unsigned char> ogImage("puzzle.png");
	CImg<unsigned char> messyImage("messyPuzzle.png");

	CImgDisplay main_disp(ogImage, "OG Image"), draw_disp(messyImage,
			"Cropped Image");

	//ogImage
	Matrix<Tile, 4, 4> tileArray; // size_x, size_y

	//Image that's not in order
	Matrix<Tile, 4, 4> messyArray; // size_x, size_y

	int x = ogImage.width() / rows; //width
	int y = ogImage.height() / cols; //height

	ImageManipulator.cropImage(cols, rows, x, y, ogImage, tileArray);
	ImageManipulator.cropImage(cols, rows, x, y, messyImage, messyArray);

	while (!main_disp.is_closed()) {
		main_disp.wait();
		if (main_disp.button() && main_disp.mouse_y() >= 0) {

			//Showing the tiles and their adyacents one by one
			//showTiles(cols, rows, tileArray, &draw_disp);

			//Shuffle randomly the matrix of tiles.
			//tileArray.shuffle();

			//reconstructImage(cols, rows, x, y, ogImage, tileArray).save("messyPuzzle.png");

			//Reconstruction of the image.
			ImageManipulator.solvePuzzle(cols, rows, tileArray, messyArray);

			main_disp.display(
					ImageManipulator.reconstructImage(cols, rows, x, y, ogImage, tileArray));
			draw_disp.display(
					ImageManipulator.reconstructImage(cols, rows, x, y, messyImage, messyArray));

			//To select where is the black tile.
			int posx, posy, posxx, posyy;
			for (int i = 0; i < cols; i++) {
					for (int j = 0; j < rows; j++) {
						if(tileArray(i,j).getIdentifier()==1){
							posx = i;
							posy = j;
						}
						if(messyArray(i,j).getIdentifier()==1){
							posxx = i;
							posyy = j;
						}
					}
			}
			state initialState(&messyArray, posxx, posyy, cols, rows);
			state goalState(&tileArray, posx, posy, cols, rows);

			stateSpace problemStateSpace(goalState);
			Problem puzzleProblem(initialState, problemStateSpace);
			puzzleProblem.boundedSearch("BFS", 1000);
		}
	}
	return 0;
}
