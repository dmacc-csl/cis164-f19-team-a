#ifndef TILE_H
#define TILE_H

#include "Location.h"
#include "View.h"

class Tile {
private:
	int tileID;
	Location& location;
	View& view;
	friend class WeatherDB;
public:
	//Tile();
	Tile(Location&, View&);
	

	int getTileID() { return tileID; }
	void setTileID(int);

	View& getView() const { return view; }
	
	void setView(View&);

	Location& getLocation() const {
		return location;
	}
	void setLocation(Location&);

};

#endif
