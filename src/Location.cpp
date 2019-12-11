#include "Location.h"
Location::Location() { locationID = 0; }
Location::Location(string city, string country) : city(city), country(country) {}