#ifndef VIEW_H
#define VIEW_H

#include <string>
using namespace std;

class View {
private:
	long viewID;
	string viewName;
	string description;
	friend class WeatherDB;
public: 
	View();
	View(string, string);

	long getViewID() { return viewID; }
	string getViewName() { return viewName; }
	string getDescription() { return description; }
	void setViewName(string vName) { viewName = vName; }
	void setDescription(string desc) { description = desc; }
};

#endif
