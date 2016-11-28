#ifndef TILE_H
#define TILE_H
#include "CImg.h"
#include <memory>
#include <algorithm>
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
	void setImage(CImg<unsigned char> image);
private:
	int _identifier;
	CImg<unsigned char> _image;
};

#endif
