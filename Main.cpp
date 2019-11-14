#include <iostream>
#include "WeatherDB.h"

#pragma comment(lib, "ws2_32.lib") // for Visual Studio, pulls in a Windows library
#pragma comment(lib, "IPHLPAPI.lib") // for Visual Studio, pulls in a Windows library
using namespace std;

void testSetCity(Location& location) {
	if (location.getCity() !="") {
		cout << "testLocationCity() has passed" << endl;
	}
	else {
		cout << "testLocationCity() has failed" << endl;
	}
}

void testSetCountry(Location& location) {
	if (location.getCountry() != "") {
		cout << "testLocationCountry() has passed" << endl;
	}
	else {
		cout << "testLocationCountry() has failed" << endl;
	}
}

void testSetViewName(View& view) {
	if (view.getViewName() != "") {
		cout << "testViewName() has passed" << endl;
	}
	else {
		cout << "testViewName)_ has failed" << endl;
	}
}

void testCheckCity(Tile& tile) {
	if (tile.checkCity() != "") {
		cout << "testCheckCity() has passed" << endl;
	}
	else {
		cout << "testCheckCity() has failed" << endl;
	}
}

void testCheckViewName(Tile& tile) {
	if (tile.checkViewName() != "") {
		cout << "testCheckViewName() has passed" << endl;
	}
	else {
		cout << "testCheckViewName() has failed" << endl;
	}
}

int main() {

	// register SQLite connector
	Poco::Data::SQLite::Connector::registerConnector();
	WeatherDB wdb("weather.sqlite");
	wdb.rebuildWeatherDatabase();
	
	//Test setCity and setCountry for Location.cpp
	Location location;
	location.setCity("Des Moines");
	testSetCity(location);
	testSetCountry(location);

	//Test setViewName
	View view;
	view.setViewName("5 Day");
	testSetViewName(view);

	//Test Tile
	Tile tile(location, view);
	testCheckCity(tile);
	testCheckViewName(tile);
	


}

