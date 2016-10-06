#include <iostream>
#include "Entity3D.h"

#include "../include/Tile.h"
using namespace std;

Entity3D::Entity3D(){
    cout << "[!] Creating new Entity3D [!]" << endl;
}

Entity3D::~Entity3D() {
    cout << "[X] Destroying Entity3D [X]" << endl;
}
