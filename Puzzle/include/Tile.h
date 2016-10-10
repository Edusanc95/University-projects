#ifndef TILE_H
#define TILE_H
#include "CImg.h"
using namespace std;
using namespace cimg_library;

class Tile {
public:
	Tile(int identifier, CImg<unsigned char> _image);
	~Tile();

private:
	int _identifier;
	CImg<unsigned char> _image;
};

#endif
