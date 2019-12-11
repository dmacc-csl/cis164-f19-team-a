#include "Tile.h"
/*Tile::Tile() {
	this->tileID = 0;
	//not fixed
}*/

Tile::Tile(Location& location, View& view) : location(location), view(view) {
	this->tileID = -111;
}

void Tile::setTileID(int id) {
	this->tileID = id;
}

void Tile::setLocation(Location& loc) {
	this->location = loc;
}

void Tile::setView(View& v) {
	this->view = v;
}