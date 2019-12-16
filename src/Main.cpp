/*Alex Rooney CIS 164 Final Project*/
#include <iostream>
#include "WeatherDB.h"

#pragma comment(lib, "ws2_32.lib") // for Visual Studio, pulls in a Windows library
#pragma comment(lib, "IPHLPAPI.lib") // for Visual Studio, pulls in a Windows library
using namespace std;


int main() {
	
		// register SQLite connector
		Poco::Data::SQLite::Connector::registerConnector();
		WeatherDB wdb("weather.sqlite");
		
		//Build the database tables
		wdb.rebuildWeatherDatabase();

		//Create locations and push to 'Location' table
		Location loc1("New York City", "United States");
		wdb.insertLocation(loc1);
		Location loc2("Madrid", "Spain");
		wdb.insertLocation(loc2);
		Location loc3("Amsterdam", "Netherlands");
		wdb.insertLocation(loc3);
		Location loc4("London", "England");
		wdb.insertLocation(loc4);
		
		//Create view options from weather UI
		View view1("5_Day", "Five day future cast");
		View view2("Current", "Current day weather information");
		View view3("High_Low_Temp", "High and low for the day");
		
		//Create tiles. Location + View
		//Push to 'Tile'table
		Tile tile1(loc1, view1);
		wdb.insertTile(tile1);
		Tile tile2(loc2, view1);
		wdb.insertTile(tile2);
		Tile tile3(loc3, view2);
		wdb.insertTile(tile3);
		Tile tile4(loc4, view3);
		wdb.insertTile(tile4);

		//Create dashboard to hold all 4 tiles
		Dashboard dash1("Major World Cities", tile1.getLocation().getCity(), tile1.getTileID(), tile2.getLocation().getCity(), tile2.getTileID(),
			tile3.getLocation().getCity(), tile3.getTileID(), tile4.getLocation().getCity(), tile4.getTileID());
	
		//push to 'Dashboard' table
		wdb.insertDashboard(dash1);
		
		//Print out values to verify object pushed to database tables
		wdb.printLocations();
		wdb.printViews();
		wdb.printTiles(tile1);
		wdb.printDashboards();
	
	return 0;
}

