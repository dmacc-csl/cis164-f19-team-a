#include "Dashboard.h"
Dashboard::Dashboard() {}

Dashboard::Dashboard(string dashName, string tile1Name, int tile1ID, string tile2Name, int tile2ID, string tile3Name, int tile3ID,
	string tile4Name, int tile4ID) : dashName(dashName), tile1Name(tile1Name), tile1ID(tile1ID), tile2Name(tile2Name), tile2ID(tile2ID),
	tile3Name(tile3Name), tile3ID(tile3ID), tile4Name(tile4Name), tile4ID(tile4ID) {
	this->dashID = 0;
}

void Dashboard::setTile1(string name, int ID) {
	this->tile1Name = name;
	this->tile1ID = ID;
}

void Dashboard::setTile2(string name, int ID) {
	this->tile2Name = name;
	this->tile2ID = ID;
}

void Dashboard::setTile3(string name, int ID) {
	this->tile3Name = name;
	this->tile3ID = ID;
}

void Dashboard::setTile4(string name, int ID) {
	this->tile4Name = name;
	this->tile4ID = ID;
}

