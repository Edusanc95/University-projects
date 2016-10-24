#include <iostream>

#include "Tile.h"
using namespace std;

Tile::Tile() {
  //cout << "[!] New tile created [!]" << endl;

}

Tile::Tile(int identifier, CImg<unsigned char> image) {

  _identifier = identifier;
  _image = image;

  //cout << "[!] New tile created with identifier " << _identifier << " [!]" << endl;

}

Tile::~Tile () {

  //cout << "[X] Tile destroyed with identifier "<< _identifier << " [X]" << endl;

}

const int Tile::getIdentifier(){
	return _identifier;
}

const CImg<unsigned char> Tile::getImage(){
	return _image;
}

void Tile::setIdentifier(int identifier){
	_identifier = identifier;
}

