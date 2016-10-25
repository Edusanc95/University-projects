#include <Tile.h>
#include <iostream>
#include "CImg.h"
#include "matrix.h"
#include <list>
#include <vector>
#include <sstream>
using namespace std;
using namespace cimg_library;

//This is the comparation function needed for sort() for vectors
bool compareFunction(Tile i, Tile j) {
	return (i.getIdentifier() < j.getIdentifier());
}

//This method crops the Image and stores it in a custom object of type Matrix, which simulates an array, called tileArray.
void cropImage(int cols, int rows, int x, int y, CImg<unsigned char> ogImage,
		Matrix<Tile, 10, 10> &tileArray) {

	int id = 1; //Identifier for the different images
	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {

			//We create the tile related with the cropped image.
			//Tile tile(id, ogImage.get_crop(x * j + x, y * i + y, x * j, y * i));
			/*if(id=1){
			 CImg<unsigned char> aux (x, y, 1, 3, 0);
			 Tile tile(id, aux);
			 tileArray(i, j) = tile;
			 id++;
			 }else{*/
			Tile tile(id,
					ogImage.get_crop(((x * j + x) - 1), ((y * i + y) - 1),
							x * j, y * i));
			tileArray(i, j) = tile;
			id++;
			//}
		}
	}
}

//This method shows in a window the different tiles of the image, with the corresponding adjacent tiles in the standard output
void showTiles(int cols, int rows, Matrix<Tile, 10, 10> tileArray,
		CImgDisplay *draw_disp) {
	std::list<Tile>* ady = new list<Tile>(4); //To store the adyacents
	CImg<unsigned char> auxImage("puzzle.png");
	for (int z = 0; z < cols; z++) {
		for (int w = 0; w < rows; w++) {
			cout << z << " Row " << w << " Col " << endl;
			cout << "Identifier: " << tileArray(z, w).getIdentifier() << endl;
			auxImage = tileArray(z, w).getImage();
			draw_disp->display(auxImage);
			ady = tileArray.getAdjacents(z, w);
			for (std::list<Tile>::iterator it = ady->begin(), end = ady->end();
					it != end; ++it) {
				cout << "Adyacent with: " << (*it).getIdentifier() << endl;
			}
			sleep(1);
		}
	}
}

//This method reconstructs the Image from the Matrix of Tiles given and returns it.
CImg<unsigned char> reconstructImage(int cols, int rows, int x, int y,
		CImg<unsigned char> ogImage, Matrix<Tile, 10, 10> tileArray) {
	ogImage.fill(255, 0, 0);
	for (int q = 0; q < cols; q++) {
		for (int s = 0; s < rows; s++) {
			//This is used when we don't have an initial black tile
			if (tileArray(q, s).getIdentifier() == 1) {
				CImg<unsigned char> aux(tileArray(q, s).getImage().width(),
						tileArray(q, s).getImage().height(), 1, 3, 0);
				ogImage.draw_image(s * x, q * y, aux);
			} else {
				ogImage.draw_image(s * x, q * y, tileArray(q, s).getImage());
			}
			//ogImage.draw_image(s * x, q * y, tileArray(q, s).getImage());
		}
	}

	return ogImage;
}

//This method changes the identifiers of the tiles of the messy array to the ones of the og image so we can reconstruct it.
void solvePuzzle(int cols, int rows, Matrix<Tile, 10, 10> &tileArray,
		Matrix<Tile, 10, 10> &messyArray) {
	for (int q = 0; q < cols; q++) {
		for (int s = 0; s < rows; s++) {

			for (int i = 0; i < cols; i++) {
				for (int j = 0; j < rows; j++) {
					if (messyArray(q, s).getImage()
							== tileArray(i, j).getImage()) {
						messyArray(q, s).setIdentifier(
								tileArray(i, j).getIdentifier());

					}
				}
			}

		}
	}

	//Now we get all the data from the matrix into a vector.
	std::vector<Tile> vect;
	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {
			vect.push_back(tileArray(i, j));
		}
	}

	//and sort the vector using standart sort() function
	std::sort(vect.begin(), vect.end(), compareFunction);


	std::cout << "myvector contains:";
	for (std::vector<Tile>::iterator it = vect.begin(); it != vect.end();
			++it)
		std::cout << ' ' << it->getIdentifier();
	std::cout << '\n';

	//Finally, we put the data back into the matrix
	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {
			messyArray(i, j) = vect.at(i * rows + j);
		}
	}
}

template<typename T>
T cinitialize(std::istream & is) noexcept
{
	T x;
	return (is && is >> x) ? x : T();
}

int main(int argc, char **argv) {

	int cols, rows;
	string puzzle;

	cout << "Introduce number of columns:" << endl;
	cin >> cols;
	cout << "Introduce number of rows:" << endl;
	cin >> rows;

	CImg<unsigned char> ogImage("puzzle.png");
	CImg<unsigned char> messyImage("messyPuzzle.png");

	CImgDisplay main_disp(ogImage, "OG Image"), draw_disp(messyImage,
			"Cropped Image");

	//ogImage
	Matrix<Tile, 10, 10> tileArray; // size_x, size_y

	//Image that's not in order
	Matrix<Tile, 10, 10> messyArray; // size_x, size_y

	int x = ogImage.width() / cols; //width
	int y = ogImage.height() / rows; //height

	cropImage(cols, rows, x, y, ogImage, tileArray);
	cropImage(cols, rows, x, y, messyImage, messyArray);

	while (!main_disp.is_closed()) {
		main_disp.wait();
		if (main_disp.button() && main_disp.mouse_y() >= 0) {

			//Showing the tiles and their adyacents one by one
			//showTiles(cols, rows, tileArray, &draw_disp);

			//Shuffle randomly the matrix of tiles.
			//tileArray.shuffle();

			//reconstructImage(cols, rows, x, y, ogImage, tileArray).save("messyPuzzle.png");

			//Reconstruction of the image.
			solvePuzzle(cols, rows, tileArray, messyArray);

			main_disp.display(
					reconstructImage(cols, rows, x, y, ogImage, tileArray));
			draw_disp.display(
					reconstructImage(cols, rows, x, y, messyImage, messyArray));

		}
	}
	return 0;
}
