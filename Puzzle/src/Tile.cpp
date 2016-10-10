#include <iostream>

#include "Tile.h"
using namespace std;

Tile::Tile(int identifier, CImg<unsigned char> _image) {
  cout << "[!] Creating new tile [!]" << endl;
}
Tile::~Tile () {
  cout << "[X] Destroying tile [X]" << endl;
}


