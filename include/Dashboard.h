#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <string>
#include <vector>
#include "Tile.h"

using namespace std;

class Dashboard {
private:
	int dashID;
	string dashName;
	string tile1Name;
	int tile1ID;
	string tile2Name;
	int tile2ID;
	string tile3Name;
	int tile3ID;
	string tile4Name;
	int tile4ID;
	friend class WeatherDB;
public:
	Dashboard();
	Dashboard(string, string, int, string, int, string, int, string, int);

	int getDashID() { return dashID; }
	string getDashName() { return dashName; }
	string getTile1Name() { return tile1Name; }
	string getTile2Name() { return tile2Name; }
	string getTile3Name() { return tile3Name; }
	string getTile4Name() { return tile4Name; }

	void setTile1(string, int);
	void setTile2(string, int);
	void setTile3(string, int);
	void setTile4(string, int);

};

#endif