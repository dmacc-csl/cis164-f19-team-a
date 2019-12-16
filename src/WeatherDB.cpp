#include "WeatherDB.h"
WeatherDB::WeatherDB(string fileName) : fileName(fileName), session("SQLite", fileName) {
}

long WeatherDB::getLatestRowId() {
	long id;
	session << "SELECT last_insert_rowid()", into(id), now;
	return id;
}

void WeatherDB::printLocations() {
	cout << endl << "Locations" << endl;

	Location location;
	unique_ptr<Statement> statement = getLocations(location);
	while (!statement->done()) {
		statement->execute();
		cout << "Location " << location.getLocationID() << " " << location.getCity() << ", " << location.getCountry() << endl;
	}
}

void WeatherDB::printViews() {
	cout << endl << "Views" << endl;

	View view;
	unique_ptr<Statement> statement = getViews(view);
	while (!statement->done()) {
		statement->execute();
		cout << "View " << view.getViewID() << " " << view.getViewName() << " Description: " << view.getDescription() << endl;
	}
}

void WeatherDB::printDashboards() {
	cout << endl << "Dashboards" << endl;

	Dashboard dashboard;
	unique_ptr<Statement> statement = getDashboards(dashboard);
	while (!statement->done()) {
		statement->execute();
		cout << "Dashboard Name: " << dashboard.getDashName() << " Tile1Name: " << dashboard.getTile1Name() << " Tile2Name: " << dashboard.getTile2Name() << endl;
		cout << " Tile3Name: " << dashboard.getTile3Name() << " Tile4Name: " << dashboard.getTile4Name() << endl;
	}
}

void WeatherDB::printTiles(Tile& tile) {
	cout << endl << "Tiles" << endl;

	//Tile tile;
	unique_ptr<Statement> statement = getTiles(tile);
	while (!statement->done()) {
		
			statement->execute();
			cout << "Tile " << tile.getTileID() << " Location: " << tile.getLocation().getCity() << " View: " << tile.getView().getViewName() << endl;
		

	}
}

unique_ptr<Statement> WeatherDB::getLocations(Location& location) {
	auto selectPtr = unique_ptr<Statement>(new Statement(session));
	*selectPtr << "SELECT locationID, city, country FROM Location", into(location.locationID), into(location.city), into(location.country), range(0, 1);
	return selectPtr;
}

unique_ptr<Statement> WeatherDB::getViews(View& view) {
	auto selectPtr = unique_ptr<Statement>(new Statement(session));
	*selectPtr << "SELECT viewID, viewName, description FROM View", into(view.viewID), into(view.viewName), into(view.description), range(0, 1);
	return selectPtr;
}

unique_ptr<Statement> WeatherDB::getTiles(Tile& tile) {
	auto selectPtr = unique_ptr<Statement>(new Statement(session));
	*selectPtr << "SELECT tileID, location, view FROM Tile", into(tile.tileID), into(tile.getLocation().city), into(tile.getView().viewName), range(0, 1);
	return selectPtr;
}

unique_ptr<Statement> WeatherDB::getDashboards(Dashboard& dashboard) {
	auto selectPtr = unique_ptr<Statement>(new Statement(session));
	*selectPtr << "SELECT dashID, dashName, tile1Name, tile1ID, tile2Name, tile2ID, tile3Name, tile3ID, tile4Name, tile4ID FROM Dashboard", into(dashboard.dashID), into(dashboard.dashName), into(dashboard.tile1Name), into(dashboard.tile1ID), into(dashboard.tile2Name), into(dashboard.tile2ID), into(dashboard.tile3Name), into(dashboard.tile3ID), into(dashboard.tile4Name), into(dashboard.tile4ID), range(0, 1);
	return selectPtr;
}


void WeatherDB::insertLocation(Location& loc) {
	Statement insertLocation(session);
	insertLocation << "INSERT INTO Location (city, country) VALUES (?, ?)", use(loc.city), use(loc.country);
	insertLocation.execute();
	long locationID1 = getLatestRowId();
	loc.locationID = locationID1;
}

void WeatherDB::insertTile(Tile& tile) {
	Statement insertTile(session);
	insertTile << "INSERT INTO Tile (location, view) VALUES (?, ?)", use(tile.getLocation().city), use(tile.getView().viewName);
	insertTile.execute();
	long tileID1 = getLatestRowId();
	tile.tileID = tileID1;
}

void WeatherDB::insertDashboard(Dashboard& dashboard) {
	Statement insertDashboard(session);
	insertDashboard << "INSERT INTO Dashboard (dashName, tile1Name, tile1ID, tile2Name, tile2ID, tile3Name, tile3ID, tile4Name, tile4ID) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)", use(dashboard.dashName), use(dashboard.tile1Name), use(dashboard.tile1ID),use(dashboard.tile2Name), use(dashboard.tile2ID), use(dashboard.tile3Name), use(dashboard.tile3ID), use(dashboard.tile4Name), use(dashboard.tile4ID);
	insertDashboard.execute();
	long dashID1 = getLatestRowId();
	dashboard.dashID = dashID1;
}

void WeatherDB::rebuildWeatherDatabase() {
	//drop sample table, if it exists
	session << "DROP TABLE IF EXISTS Location", now;

	//recreate table
	session << "CREATE TABLE Location (locationID INTEGER PRIMARY KEY, city TEXT, country TEXT)", now;

	//drop view table
	session << "DROP TABLE IF EXISTS View", now;
	//create table for 3 Views
	session << "CREATE TABLE View (viewID INTEGER PRIMARY KEY, viewName TEXT, description TEXT)", now;
	
	View view("Current", "Current day weather information");
	Statement insertView(session);
	insertView << "INSERT INTO View (viewName, description) VALUES (?, ?)", use(view.viewName), use(view.description);
	insertView.execute();
	long viewID1 = getLatestRowId();
	view.viewID = viewID1;
	view.setViewName("5_Day");
	view.setDescription("Five day future forecast");
	insertView.execute();
	long viewID2 = getLatestRowId();
	view.viewID = viewID2;
	view.setViewName("High_Low_Temp");
	view.setDescription("High and low for the day");
	insertView.execute();
	long viewID3 = getLatestRowId();
	view.viewID = viewID3;

	//drop tile table
	session << "DROP TABLE IF EXISTS Tile", now;
	//create table for tiles
	session << "CREATE TABLE Tile (tileID INTEGER PRIMARY KEY, location TEXT, view TEXT)", now;

	/*Tile tile(location, view);
	Statement insertTile(session);
	insertTile << "INSERT INTO Tile (location, view) VALUES (?, ?)", use(tile.location), use(tile.view);
	insertTile.execute();
	long tileID1 = getLatestRowId();
	tile.tileID = tileID1;*/

	//drop Dashboard table
	session << "DROP TABLE IF EXISTS Dashboard", now;
	//create table for Dashboards
	session << "CREATE TABLE Dashboard (dashID INTEGER PRIMARY KEY, dashName TEXT, tile1Name TEXT, tile1ID INTEGER, tile2Name TEXT, tile2ID INTEGER, tile3Name TEXT, tile3ID INTEGER, tile4Name TEXT, tile4ID INTEGER)", now;
	
}