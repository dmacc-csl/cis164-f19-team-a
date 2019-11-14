#ifndef LOCATION_H
#define LOCATION_H
#include <string>
//#include "WeatherDB.h"
using namespace std;

class Location {
private:
	int locationID;
	string city;
	string country;
	friend class WeatherDB;
public:
	Location();
	Location(string, string);
	
	int getLocationID() { return locationID; }
	void setLocationID(int l) { locationID = l; }
	
	string getCity() { return city; }
	void setCity(string c) { city = c; }
	
	string getCountry() { return country; }
	void setCountry(string ctry) { country = ctry; }
};

#endif
