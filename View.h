#ifndef VIEW_H
#define VIEW_H

#include <string>
using namespace std;

class View {
private:
	long viewID;
	string viewName;
	friend class WeatherDB;
public: 
	View();
	View(string);

	long getViewID() { return viewID; }
	string getViewName() { return viewName; }
	void setViewName(string vName) { viewName = vName; }
};

#endif
