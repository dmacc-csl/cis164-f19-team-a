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
		cout << "View " << view.getViewID() << " " << view.getViewName() << endl;
	}
}

unique_ptr<Statement> WeatherDB::getLocations(Location& location) {
	auto selectPtr = unique_ptr<Statement>(new Statement(session));
	*selectPtr << "SELECT locationID, city, country FROM Location", into(location.locationID), into(location.city), into(location.country), range(0, 1);
	return selectPtr;
}

unique_ptr<Statement> WeatherDB::getViews(View& view) {
	auto selectPtr = unique_ptr<Statement>(new Statement(session));
	*selectPtr << "SELECT viewID, viewName FROM View", into(view.viewID), into(view.viewName), range(0, 1);
	return selectPtr;
}

void WeatherDB::rebuildWeatherDatabase() {
	//drop sample table, if it exists
	session << "DROP TABLE IF EXISTS Location", now;

	//recreate table
	session << "CREATE TABLE Location (locationID INTEGER PRIMARY KEY, city TEXT, country TEXT)", now;

	Location location("Des Moines", "United States");
	Statement insertLocation(session);
	insertLocation << "INSERT INTO Location (city, country) VALUES (?, ?)", use(location.city), use(location.country);
	insertLocation.execute();
	long locationID1 = getLatestRowId();
	location.locationID = locationID1;
	location.setCity("Valencia");
	location.setCountry("Spain");
	insertLocation.execute();
	long locationID2 = getLatestRowId();
	location.locationID = locationID2;
	location.setCity("London");
	location.setCountry("England");
	insertLocation.execute();
	long locationID3 = getLatestRowId();
	location.locationID = locationID3;
	location.setCity("Paris");
	location.setCountry("France");
	insertLocation.execute();
	long locationID4 = getLatestRowId();
	location.locationID = locationID4;

	//drop view table
	session << "DROP TABLE IF EXISTS View", now;
	//create table for 3 Views
	session << "CREATE TABLE View (viewID INTEGER PRIMARY KEY, viewName TEXT)", now;
	
	View view("Current");
	Statement insertView(session);
	insertView << "INSERT INTO View (viewName) VALUES (?)", use(view.viewName);
	insertView.execute();
	long viewID1 = getLatestRowId();
	view.viewID = viewID1;
	view.setViewName("5_Day");
	insertView.execute();
	long viewID2 = getLatestRowId();
	view.viewID = viewID2;
	view.setViewName("UV_Index");
	insertView.execute();
	long viewID3 = getLatestRowId();
	view.viewID = viewID3;
	
}