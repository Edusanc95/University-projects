#include <Tile.h>
#include <iostream>
#include "CImg.h"
#include "matrix.h"
#include <list>
using namespace std;
using namespace cimg_library;

//This method crops the Image and stores it in a custom object of type Matrix, which simulates an array, called tileArray.
void cropImage(int cols, int rows, int x, int y, CImg<unsigned char> ogImage,
		auto &tileArray) {
	int id = 1; //Identifier for the different images
	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {

			//We create the tile related with the cropped image.
			Tile tile(id, ogImage.get_crop(x * i + x, y * j + y, x * i, y * j));

			tileArray(j, i) = tile;
			id++;
		}
	}
}

//This method shows in a window the different tiles of the image, with the corresponding adjacent tiles in the standard output
void showTiles(int cols, int rows, auto tileArray, CImgDisplay *draw_disp) {
	std::list<Tile>* ady = new list<Tile>(4); //To store the adyacents
	CImg<unsigned char> auxImage("puzzle.png");
	for (int z = 0; z < cols; z++) {
		for (int w = 0; w < rows; w++) {
			cout << w << " Row " << z << " Col " << endl;
			cout << "Identifier: " << tileArray(w, z).getIdentifier() << endl;
			auxImage = tileArray(w, z).getImage();
			draw_disp->display(auxImage);
			ady = tileArray.getAdjacents(w, z); //test
			for (std::list<Tile>::iterator it = ady->begin(), end = ady->end();
					it != end; ++it) {
				cout << "Adyacent with: " << (*it).getIdentifier() << endl;
			}
			sleep(1);
		}
	}
}

//This method reconstructs the Image from the Matrix of Tiles given and returns it.
CImg<unsigned char> reconstructImage(int cols, int rows, int x, int y, CImg<unsigned char> ogImage, auto tileArray) {
	for (int q = 0; q < cols; q++) {
		for (int s = 0; s < rows; s++) {
			ogImage.draw_image(s * x, q * y, tileArray(q, s).getImage());
		}
	}

	return ogImage;
}

int main(int argc, char **argv) {

	CImg<unsigned char> ogImage("puzzle.png");
	CImgDisplay main_disp(ogImage, "OG Image"), draw_disp(ogImage,
			"Cropped Image");

	const int cols = 5;
	const int rows = 5;

	Matrix<Tile, cols, rows> tileArray; // size_x, size_y

	//Tile* tileArray[rows][cols];

	int x = cimg_option("-x", ogImage.width() / cols, "x crop"); //width
	int y = cimg_option("-y", ogImage.height() / rows, "y crop"); //height

	cropImage(cols, rows, x, y, ogImage, tileArray);

	while (!main_disp.is_closed()) {
		main_disp.wait();
		if (main_disp.button() && main_disp.mouse_y() >= 0) {

			//Showing the tiles and their adyacents one by one
			showTiles(cols, rows, tileArray, &draw_disp);

			//Shuffle randomly the matrix of tiles.
			tileArray.shuffle();

			//Reconstruction of the image.
			main_disp.display(reconstructImage(cols, rows, x, y, ogImage, tileArray));
			ogImage.save("messyPuzzle.png");

		}
	}
	return 0;
}
