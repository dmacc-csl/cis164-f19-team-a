#ifndef WEATHERDB_H
#define WEATHERDB_H

#include <iostream>
#include <string>
#include <vector>
#include "Poco/Data/Session.h"
#include "Poco/Data/SQLite/Connector.h"
#include "Location.h"
#include "View.h"
#include "Tile.h"
using namespace std;
using namespace Poco::Data::Keywords;
using Poco::Data::Session;
using Poco::Data::Statement;

class WeatherDB {
private:
	string fileName;
	Session session;
	long getLatestRowId();

public:
	WeatherDB(string fileName);
	string getFileName() { return fileName; }

	void printLocations();
	unique_ptr<Statement> getLocations(Location& location);

	void printViews();
	unique_ptr<Statement> getViews(View& view);

	void rebuildWeatherDatabase();
};

#endif // WEATHERDB_H
