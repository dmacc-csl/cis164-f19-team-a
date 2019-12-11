#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/Path.h>
#include <Poco/URI.h>
#include <Poco/Exception.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include "Poco/Dynamic/Var.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace Poco::Net;
using namespace Poco::JSON;
using namespace Poco;
using namespace Dynamic;
using namespace std;

string findCurrentValue(string location);
double findTemperature(string location);
double findMaxTemperature(string location);
double findMinTemperature(string location);
double findHumidity(string location);
double findPressure(string location);
double *findFiveDay(string location);

std::string to_string(std::istream& in)
{
	std::string ret;
	char buffer[4096];
	while (in.read(buffer, sizeof(buffer)))
	{
		ret.append(buffer, sizeof(buffer));
	}
	ret.append(buffer, in.gcount());
	return ret;
}

string makeRequest(string url) {
	try {
		// prepare session
		URI uri(url);
		HTTPClientSession session(uri.getHost(), uri.getPort());

		// prepare path
		string path(uri.getPathAndQuery());
		//if (path.empty()) path = "/comments/" + to_string(postId);

		// send request
		HTTPRequest req(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
		session.sendRequest(req);

		// get response
		HTTPResponse res;
		

		// print response
		istream& is = session.receiveResponse(res);

		string response = to_string(is);

		return response;

		//post = parseJson(is);
	}
	catch (Exception & ex) {
		cerr << ex.displayText() << endl;
	}
}

double* findFiveDay(string location) {
	ifstream input;
	string line;
	string search = "12:00:00";
	string tempSearch = "temp";
	string finalValue;

	const int SIZE = 5;
	double temperatures[SIZE] = { 0 };

	int comma = location.find(",");
	string city = location.substr(0, comma);

	string country = location.substr(comma + 2);

	string url = "http://api.openweathermap.org/data/2.5/forecast?q=" +city+ "," +country+ "&APPID=8a8970ef05558bcb0c0598d8b0b610ad";
	line = makeRequest(url);
			for (int index = 0; index < SIZE; index++) {
				size_t found = line.find(search);
				if (found != string::npos) {
					//cout << found << endl;
					string helper = line.substr(found, string::npos);
					size_t foundTemp = helper.find(tempSearch);
					if (foundTemp != string::npos) {
						//cout << foundTemp << endl;
						string temporaryTemp = helper.substr(foundTemp, string::npos);
						int position2 = temporaryTemp.find(":");
						int position3 = temporaryTemp.find(",");
						position3 = position3 - position2;
						string value = temporaryTemp.substr(position2, position3);
						//cout << "Value: " << value << endl;
						for (int index = 0; index < value.length(); index++) {
							char c = value.at(index);
							if (c == ' ' || c == ':') {
								finalValue = value.substr(index + 1, position3);
							}
						}

						double tempFahrenheit = stod(finalValue) * 9 / 5 - 459.67;
						temperatures[index] = truncf(tempFahrenheit * 10) / 10;

						line = temporaryTemp;
					}
				}
			}

			for (int pos = 0; pos < SIZE; pos++) {
				cout << "Temperature " << pos << ": " << temperatures[pos] << endl;
			}
		
			return temperatures;
}

double findTemperature(string location) {
	ifstream input;
	string temperature;
	string line;
	string search = "temp";
	string finalValue;

	int comma = location.find(",");
	string city = location.substr(0, comma);

	string country = location.substr(comma + 2);

	string url = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "," + country + "&APPID=8a8970ef05558bcb0c0598d8b0b610ad";
	line = makeRequest(url);

			size_t found = line.find(search);
			if (found != string::npos) {
				//cout << found << endl;
				string helper = line.substr(found, string::npos);
				int position2 = helper.find(":");
				int position3 = helper.find(",");
				position3 = position3 - position2;
				string value = helper.substr(position2, position3);

				for (int index = 0; index < value.length(); index++) {
					char c = value.at(index);
					if (c == ' ' || c == ':') {
						finalValue = value.substr(index + 1, position3);
					}
				}

				double tempFahrenheit = stod(finalValue) * 9 / 5 - 459.67;

				return truncf(tempFahrenheit * 10) / 10;
			}

	
}

double findMaxTemperature(string location) {
	ifstream input;
	string temperature;
	string line;
	string search = "temp_max";
	string finalValue;

	int comma = location.find(",");
	string city = location.substr(0, comma);

	string country = location.substr(comma + 2);

	string url = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "," + country + "&APPID=8a8970ef05558bcb0c0598d8b0b610ad";
	line = makeRequest(url);

	size_t found = line.find(search);
	if (found != string::npos) {
		//cout << found << endl;
		string helper = line.substr(found, string::npos);
		int position2 = helper.find(":");
		int position3 = helper.find(",");
		position3 = position3 - position2;
		string value = helper.substr(position2, position3);

		for (int index = 0; index < value.length(); index++) {
			char c = value.at(index);
			if (c == ' ' || c == ':') {
				finalValue = value.substr(index + 1, position3);
			}
		}

		double tempFahrenheit = stod(finalValue) * 9 / 5 - 459.67;

		return truncf(tempFahrenheit * 10) / 10;
	}


}

double findMinTemperature(string location) {
	ifstream input;
	string temperature;
	string line;
	string search = "temp_min";
	string finalValue;

	int comma = location.find(",");
	string city = location.substr(0, comma);

	string country = location.substr(comma + 2);

	string url = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "," + country + "&APPID=8a8970ef05558bcb0c0598d8b0b610ad";
	line = makeRequest(url);

	size_t found = line.find(search);
	if (found != string::npos) {
		//cout << found << endl;
		string helper = line.substr(found, string::npos);
		int position2 = helper.find(":");
		int position3 = helper.find(",");
		position3 = position3 - position2;
		string value = helper.substr(position2, position3);

		for (int index = 0; index < value.length(); index++) {
			char c = value.at(index);
			if (c == ' ' || c == ':') {
				finalValue = value.substr(index + 1, position3);
			}
		}

		double tempFahrenheit = stod(finalValue) * 9 / 5 - 459.67;

		return truncf(tempFahrenheit * 10) / 10;
	}


}

double findPressure(string location) {
	ifstream input;
	string pressure;
	string line;
	string search = "pressure";
	string finalValue;
	int comma = location.find(",");
	string city = location.substr(0, comma);

	string country = location.substr(comma + 2);

	string url = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "," + country + "&APPID=8a8970ef05558bcb0c0598d8b0b610ad";
	line = makeRequest(url);

			size_t found = line.find(search);
			if (found != string::npos) {
				//cout << found << endl;
				string helper = line.substr(found, string::npos);
				int position2 = helper.find(":");
				int position3 = helper.find(",");
				position3 = position3 - position2;
				string value = helper.substr(position2, position3);
				//cout << "Value: " << value << endl;
				for (int index = 0; index < value.length(); index++) {
					char c = value.at(index);
					if (c == ' ' || c == ':') {
						finalValue = value.substr(index + 1, position3);
					}
				}
				

				return stod(finalValue);
			}

		
	
}

double findHumidity(string location) {
	ifstream input;
	string humidity;
	string line;
	string search = "humidity";
	string finalValue;
	int comma = location.find(",");
	string city = location.substr(0, comma);

	string country = location.substr(comma + 2);

	string url = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "," + country + "&APPID=8a8970ef05558bcb0c0598d8b0b610ad";
	line = makeRequest(url);

			size_t found = line.find(search);
			if (found != string::npos) {
				//cout << found << endl;
				string helper = line.substr(found, string::npos);
				int position2 = helper.find(":");
				int position3 = helper.find(",");
				position3 = position3 - position2;
				string value = helper.substr(position2, position3);
				//cout << "Value: " << value << endl;
				for (int index = 0; index < value.length(); index++) {
					char c = value.at(index);
					if (c == ' ' || c == ':') {
						finalValue = value.substr(index + 1, position3);
					}
				}


				return stod(finalValue);
			}

}

string findCurrentValue(string location) {
	ifstream input;

	int comma = location.find(",");
	string city = location.substr(0, comma);

	string country = location.substr(comma + 2);

	string url = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "," + country + "&APPID=8a8970ef05558bcb0c0598d8b0b610ad";
	
		string uv;
		string line;
		string search = "description";
		string finalValue;
		line = makeRequest(url);

			size_t found = line.find(search);
			if (found != string::npos) {
				//cout << "found: "<< found <<endl;
				string helper = line.substr(found, string::npos);
				//cout << "Helper" << helper << endl;
				int position2 = helper.find(":") + 1;
				int position3 = helper.find(",");
				position3 = position3 - position2;
				string finalValue = helper.substr(position2, position3);

				int first = finalValue.find("\"") + 1;

				string finalValue1 = finalValue.substr(first, position3);

				int second = finalValue1.find("\"");

				string actualFinal = finalValue1.substr(0, second);

				return actualFinal;
			}

}
