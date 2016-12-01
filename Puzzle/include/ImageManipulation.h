/*
 * ImageManipulation.h
 *
 *  Created on: Nov 27, 2016
 *      Author: edu
 */

#ifndef INCLUDE_IMAGEMANIPULATION_H_
#define INCLUDE_IMAGEMANIPULATION_H_

#include "CImg.h"
#include "TileMatrix.h"
#include "matrix.h"
#include <vector>
using namespace cimg_library;
/* A generic class that uses CImg to manipulate images. */
/* It uses a class matrix for most of the operations, to store there the images with an identifier. */
class ImageManipulation {
public:

	ImageManipulation() {
	}
	~ImageManipulation() {
	}

	/*This method crops the Image and stores it in a custom object of type Matrix, which simulates an array, called tileArray.*/
	void cropImage(int cols, int rows, int x, int y,
			CImg<unsigned char> *ogImage, TileMatrix &tileArray) {

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
				CImg<unsigned char>* aux = new CImg<unsigned char>("puzzle.png");
				*aux = ogImage->get_crop(((x * j + x) - 1), ((y * i + y) - 1),x * j, y * i);
				Tile tile(id,aux);
				tileArray(i, j) = tile;
				/*if(id=1){
				 CImg<unsigned char> aux(tileArray(i, j).getImage().width(),
				 tileArray(i, j).getImage().height(), 1, 3, 0);
				 ogImage.draw_image(j * x, i * y, aux);
				 }*/
				id++;
				//}
			}
		}
	}

	//This method shows in a window the different tiles of the image, with the corresponding adjacent tiles in the standard output
	void showTiles(int cols, int rows, TileMatrix tileArray,
			CImgDisplay *draw_disp) {
		std::list<Tile>* ady = new list<Tile>(4); //To store the adyacents
		CImg<unsigned char> auxImage("puzzle.png");
		for (int z = 0; z < cols; z++) {
			for (int w = 0; w < rows; w++) {
				cout << z << " Row " << w << " Col " << endl;
				cout << "Identifier: " << tileArray(z, w).getIdentifier()
						<< endl;
				auxImage = *(tileArray(z, w).getImage());
				draw_disp->display(auxImage);
				ady = tileArray.getAdjacents(z, w);
				for (std::list<Tile>::iterator it = ady->begin(), end =
						ady->end(); it != end; ++it) {
					cout << "Adyacent with: " << (*it).getIdentifier() << endl;
				}
				sleep(1);
			}
		}
	}

	/*This method reconstructs the Image from the Matrix of Tiles given and returns it.*/
	CImg<unsigned char>* reconstructImage(int cols, int rows, int x, int y,
			CImg<unsigned char>* ogImage, TileMatrix tileArray) {
		ogImage->fill(255, 255, 255);
		for (int q = 0; q < cols; q++) {
			for (int s = 0; s < rows; s++) {

				//This is used when we don't have an initial black tile
				/*if (tileArray(q, s).getIdentifier() == 1) {
				 CImg<unsigned char> aux(tileArray(q, s).getImage().width(),
				 tileArray(q, s).getImage().height(), 1, 3, 0);
				 ogImage.draw_image(s * x, q * y, aux);
				 } else {*/
				ogImage->draw_image(s * x, q * y, *(tileArray(q, s).getImage()));
				//}
				//ogImage.draw_image(s * x, q * y, tileArray(q, s).getImage());
			}
		}
		return ogImage;
	}

	/*This is the comparation function needed for sort() for vectors*/
	static bool compareFunction(Tile i, Tile j) {
		return (i.getIdentifier() < j.getIdentifier());
	}

	/*This method changes the identifiers of the tiles of the messy array to the ones of the og image so we can reconstruct it.*/
	void solvePuzzle(int cols, int rows, TileMatrix &tileArray,
			TileMatrix &messyArray) {

		for (int q = 0; q < cols; q++) {
			for (int s = 0; s < rows; s++) {

				bool sorted = false;
				for (int i = 0; i < cols && !sorted; i++) {
					for (int j = 0; j < rows && !sorted; j++) {
						if (*(messyArray(q, s).getImage())
								== *(tileArray(i, j).getImage())) {
							sorted = true;
							cout << "sorting "
									<< tileArray(i, j).getIdentifier()
									<< " with "
									<< messyArray(q, s).getIdentifier() << endl;

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
				vect.push_back(messyArray(i, j));
			}
		}

		std::cout << "Presorted vector contains:";
		for (std::vector<Tile>::iterator it = vect.begin(); it != vect.end();
				++it)
			std::cout << ' ' << it->getIdentifier();
		std::cout << '\n';

		//and sort the vector using standart sort() function
		std::sort(vect.begin(), vect.end(), compareFunction);

		/*
		 std::cout << "Sorted vector contains:";
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
		 */
	}

	/*This method shows in standard output the current ids and their position*/
	void showIds(int cols, int rows, TileMatrix tileArray) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				cout << tileArray(i, j).getIdentifier() << " ";
			}
			cout << endl;
		}

	}

	void equalImage(int cols, int rows, TileMatrix &tileArray,
			Matrix<Tile, 4, 4> &messyArray) {
		for (int q = 0; q < cols; q++) {
			for (int s = 0; s < rows; s++) {

				bool sorted = false;
				for (int i = 0; i < cols && !sorted; i++) {
					for (int j = 0; j < rows && !sorted; j++) {
						if (messyArray(q, s).getIdentifier()
								== tileArray(i, j).getIdentifier()) {
							sorted = true;

							messyArray(q, s).setImage(tileArray(i, j).getImage());

						}
					}
				}

			}
		}
	}

private:

};

#endif /* INCLUDE_IMAGEMANIPULATION_H_ */
