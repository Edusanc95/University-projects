#ifndef TILE_H
#define TILE_H
#include "CImg.h"
using namespace std;
using namespace cimg_library;

class Tile {
public:
	Tile(int identifier, CImg<unsigned char> _image);
	Tile();
	~Tile();

	const int getIdentifier();
	const CImg<unsigned char> getImage();
	void setIdentifier(int identifier);

private:
	int _identifier;
	CImg<unsigned char> _image;
};

#endif
