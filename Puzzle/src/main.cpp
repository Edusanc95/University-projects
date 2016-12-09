#include <Tile.h>
#include <iostream>
#include "CImg.h"
#include "matrix.h"
#include "Problem.h"
#include "ImageManipulation.h"
#include <list>
#include <vector>
#include <sstream>
#include <time.h>
#include "TileMatrix.h"

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
	int newPuzzle; //Used to know which part of the program we need to execute
	string puzzle;
	ImageManipulation ImageManipulator;

	cout << "1.- Create new puzzle" << endl;
	cout << "2.- Resolve puzzle" << endl;

	cin >> newPuzzle;
	cout << "Introduce number of columns:" << endl;
	cin >> cols;
	cout << "Introduce number of rows:" << endl;
	cin >> rows;

	CImg<unsigned char>* ogImage = new CImg<unsigned char>("puzzle.png");
	CImg<unsigned char>* messyImage = new CImg<unsigned char>("messyPuzzle.png");

	//ogImage
	TileMatrix tileArray(cols,rows); // size_x, size_y

	//Image that's not in order
	TileMatrix messyArray(cols, rows); // size_x, size_y

	int x = ogImage->width() / cols; //width
	int y = ogImage->height() / rows; //height

	ImageManipulator.cropImage(cols, rows, x, y, ogImage, tileArray, true);
	ImageManipulator.cropImage(cols, rows, x, y, messyImage, messyArray, false);

	ogImage->load("puzzle.png");
	if (newPuzzle == 1) {

		tileArray.shuffle();
		ogImage = ImageManipulator.reconstructImage(cols, rows, x, y, ogImage, tileArray);
		ogImage->save("messyPuzzle.png");
	} else if (newPuzzle == 2) {

		int depth;
		string strategy;
		int option;
		cout << "Introduce strategy:" << endl;
		cin >> strategy;
		if(strategy == "DLS" || strategy == "BLS"){
			cout << "Introduce depth:" << endl;
			cin >> depth;
		}else{
			depth = 12; // Maximum depth that most computers can handle.
		}
		if(strategy == "IDS"){
			option = 2;
		}else{
			option = 1;
		}
		if((strategy == "DFS" || strategy == "BFS" || strategy == "UCS" || strategy == "IDS" || strategy == "A*" || strategy == "BLS" || strategy == "DLS")&&(depth>0)&&(option == 1 || option == 2)){
		CImgDisplay main_disp(*ogImage, "OG Image"), draw_disp(*messyImage, "Cropped Image");
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
						*ImageManipulator.reconstructImage(cols, rows, x, y,
								ogImage, tileArray));
				draw_disp.display(
						*ImageManipulator.reconstructImage(cols, rows, x, y,
								messyImage, messyArray));

				//ImageManipulator.showTiles(cols, rows, messyArray, &draw_disp);
				//To select where is the black tile.
				int posx, posy, posxx, posyy;
				for (int i = 0; i < cols; i++) {
					for (int j = 0; j < rows; j++) {
						if (tileArray(i, j).getIdentifier() == 1) {
							posx = i;
							posy = j;
						}
						if (messyArray(i, j).getIdentifier() == 1) {
							posxx = i;
							posyy = j;
						}
					}
				}
				state initialState(messyArray, posxx, posyy, cols, rows);
				state goalState(tileArray, posx, posy, cols, rows);

				stateSpace problemStateSpace(goalState);
				Problem puzzleProblem(initialState, problemStateSpace);
				if(option == 1){
					clock_t tStart = clock();
					if(puzzleProblem.Search(strategy, depth, 1)){
						double time = (double)(clock() - tStart)/CLOCKS_PER_SEC;
						puzzleProblem.showSolution(strategy, time);
					}
				}else if(option == 2){
					clock_t tStart = clock();
					if(puzzleProblem.boundedSearch(strategy, depth)){
						double time = (double)(clock() - tStart)/CLOCKS_PER_SEC;
						puzzleProblem.showSolution(strategy, time);
					}
				}
			}
		}
	}
	}
	return 0;
}
