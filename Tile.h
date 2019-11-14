#ifndef TILE_H
#define TILE_H

#include "Location.h"
#include "View.h"

class Tile {
private:
	int tileID;
	Location location;
	View view;

public:
	Tile(Location, View);

	string checkCity() {
		return "";
	}

	string checkViewName() {
		return "";
	}
};

#endif
