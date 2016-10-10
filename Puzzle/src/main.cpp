#include <Tile.h>
#include <iostream>
#include "CImg.h"
#include "matrix.h"
using namespace std;
using namespace cimg_library;


/*
 * 
 */

int main(int argc,char **argv) {

	CImg<unsigned char> ogImage("puzzle.png"), auxImage("puzzle.png");
	CImgDisplay main_disp(ogImage, "OG Image"), draw_disp(auxImage, "Cropped Image");

	const int cols = 3;
	const int rows = 3;
	int id = 1; //Identifier for the different images

	CImg<unsigned char> array[rows][cols];
	Matrix<Tile, cols, rows> tileArray; // size_x, size_y
	//Tile* tileArray[rows][cols];

	int x = cimg_option("-x",ogImage.width()/cols,"x crop"); //width
	int y = cimg_option("-y",ogImage.height()/rows,"y crop");//height

	for(int i = 0; i<cols; i++){
		for(int j = 0; j<rows; j++){

			//We create the tile related with the cropped image.
			Tile tile(id, ogImage.get_crop(x*i+x, y*j+y, x*i,y*j));

			array[j][i] = ogImage.get_crop(x*i+x, y*j+y, x*i,y*j);
			tileArray(j,i) = tile;
			id++;
		}
	}

	while (!main_disp.is_closed()) {
		main_disp.wait();
		if (main_disp.button() && main_disp.mouse_y() >= 0) {

			/*
			if(ogImage == auxImage){
				cout << "Same image" << endl;
			}else{
				cout << "Different image" << endl;
			}

			auxImage = array[0][0];
			draw_disp.display(auxImage);
			*/

			for(int z = 0; z < cols; z++){
				for(int w = 0; w < rows; w++){
					cout << w << " Row " << z << " Col " << endl;
					cout << "Identifier: " << tileArray(w,z).getIdentifier() << endl;
					auxImage = tileArray(w,z).getImage();
					draw_disp.display(auxImage);
					sleep(1);
				}
			}

		}
	}
	return 0;
}

