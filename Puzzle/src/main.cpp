#include <Tile.h>
#include <iostream>
#include "CImg.h"
using namespace std;
using namespace cimg_library;


/*
 * 
 */

int main(int argc,char **argv) {

	CImg<unsigned char> ogImage("puzzle.png"), auxImage("puzzle.png");
	CImgDisplay main_disp(ogImage, "OG Image"), draw_disp(auxImage, "Cropped Image");

	int cols = 3;
	int rows = 3;
	CImg<unsigned char> array[rows][cols];

	int x = cimg_option("-x",ogImage.width()/cols,"x crop"); //width
	int y = cimg_option("-y",ogImage.height()/rows,"y crop");//height

	for(int i = 0; i<cols; i++){
		for(int j = 0; j<rows; j++){
			array[j][i] = ogImage.get_crop(x*i+x, y*j+y, x*i,y*j);
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
					auxImage = array[w][z];
					draw_disp.display(auxImage);
					sleep(1);
				}
			}

		}
	}
	return 0;
}

