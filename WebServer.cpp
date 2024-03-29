#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Util/ServerApplication.h>
#include <iostream>
#include <string>
#include <vector>
#include <Poco\URI.h>

using namespace Poco::Net;
using namespace Poco::Util;
using namespace std;
using Poco::URI;

const int TEST_SERVER_PORT = 9090;
class MyRequestHandler : public HTTPRequestHandler
{
public:
	virtual void handleRequest(HTTPServerRequest& req, HTTPServerResponse& resp)
	{
			resp.setStatus(HTTPResponse::HTTP_OK);
			resp.setContentType("text/html");

			std::vector<string> segments;
			try {
				URI uri(req.getURI());
			
			uri.getPathSegments(segments);
			}
			catch (exception e) { throw new exception("Could not get URI and/or segment the path"); };

			ostream& out = resp.send();
			if (segments.size() == 0) {
				out << "<h1>Team A UI Tests</h1>"
					<< "<p>To view a test visit http://localhost:" << TEST_SERVER_PORT << "/tests/x where x is the test number.</p>"
					<<"<p>To view the project's UI visit http://localhost:" << TEST_SERVER_PORT << "/cis164</p>" ;
			}
			else if (segments.size() == 2 && segments[0] == "tests") {
				int testId = 0;
				try {
					testId = stoi(segments[1]);
					if (testId > 6 || testId < 1 || testId == NAN) { throw "ERROR, invalid URL (invalid test number)"; }
				}
				catch (exception e) { throw new exception("Not a valid test parameter or URL"); }

				
				if (testId == 1) {
					out << "<h2> TEST " << testId << "</h2>";
					out << "<p>This is to test the local HTTPServer functions;  if you're reading this the test passed!  </p>";
				}
				else if (testId == 2) {
					out << "<h2> TEST " << testId << "</h2>";
					out << "<p> This is to test the dropdown list  </p>";
					out << "<select><option value = '1'>If you</option><option value = '2'>see these</option><option value = '3'>options</option><option value = '4'>it worked!</option></select>";
				}
				else if (testId == 3) {
					out << "<script>function buttonTest(){alert('If you see this, it worked!');}</script>";
					out << "<h2> TEST " << testId << "</h2>";
					out << "<p> This is to test a JavaScript function call </p>";
					out << "<p>Press this button to test it:  </p> ";
					out << "<button type = 'button' onclick = 'buttonTest()'>Click me!</button>";
				}
				else if (testId == 4) {
					out << "<script>function showText(){var inputText = document.getElementById('inputText').value;if(inputText == ''){alert('Error, check the console');throw new Error('invalid input');outputText.innerHTML = inputText;}</script>";
					out << "<h2> TEST " << testId << "</h2>";
					out << "<p> This is to test receiving and displaying text from the user </p>";
					out << "<p>Type here and press the button to test it:  </p> ";
					out << "<input id = 'inputText' type = 'text'>";
					out << "<button type = 'button' onclick = 'showText()'>Click me!</button>";
					out << "<p>You typed: <span id = 'outputText'></span></p>";
				}
				else if (testId == 5) {
					out << "<style>body{text-align:right;}</style>";
					out << "<body>";
					out << "<h2> TEST " << testId << "</h2>";
					out << "<p>This is to test CSS being applied to the page;  if this is on the right side of the page, it passed!  </p>";
					out << "</body>";
				}
				else if (testId == 6) {
					out << "<script>function showText(){var inputText = document.getElementById('inputText').value; if(inputText == ''){alert('Error, check the console');throw new Error('invalid input');}outputText.innerHTML = inputText;}</script>";
					out << "<body>";
					out << "<h2> TEST " << testId << "</h2>";
					out << "<p> This is to test receiving and displaying text from the user </p>";
					out << "<p>Type here and press the button to test it:  </p> ";
					out << "<input id = 'inputText' type = 'text'>";
					out << "<button type = 'button' onclick = 'showText()'>Click me!</button>";
					out << "</body>";
					out << "<p>{ 'name': '<span id = 'outputText'></span>' , 'age':30, 'city':'New York'}<p>";

				}
				
			}
			else if (segments[0] == "cis164") {
				string location = "";
				string testId = (segments[0]);
				out << "<script>var dashes = ['dash1', 'dash2', 'dash3', 'dash4'];</script>";
				out << "<script>function addTile(){if(document.getElementById('inputText').value == ''){alert('ERROR: Name field blank');throw new Error('invalid input'); } if(dashes.includes(document.getElementById('inputText').value)){alert('ERROR: Name already exists');throw new Error('invalid input, dashboard already exists with that name');};  let inText = document.getElementById('inputText').value;  }</script>";
				out << "<script>function changeDash(){var e = document.getElementById('selectDash');var dashText = e.options[e.selectedIndex].text;  return 'http://localhost:9090/cis164/'+dashText;}</script>";
				out << "<script>function changeTile(tileText, tileNum){if(tileText == ''){alert('ERROR: Location field blank');throw new Error('invalid location'); }else{     var e = document.getElementById('tileSelect'+tileNum);var tileText = e.options[e.selectedIndex].text; document.getElementById('tile'+tileNum).innerHTML = tileText+' '+document.getElementById('tileText'+tileNum).value; getUrl(tileText+' '+document.getElementById('tileText'+tileNum).value); }}</script>";
				out << "<script>function getUrl(inText){ return 'http://localhost:9090/cis164/'+inText;}</script>";
				
				
				if (segments.size() == 2) {
					location = (segments[1]);
				}
				else {
					location = "";
				}
				out << "<style>.tile{display:flex;border-style:solid;width:10%;float:left; padding:100px;  margin:50px;margin-left:15%;margin-bottom:10px;} .top{text-align:center;}</style>";
				out << "<body>";
				out << "<h2 style = 'text-align:center;'> Dashboard " << location << "</h2>";
				out << "<p class = 'top'>Select dashboard: <select id = 'selectDash' onmouseout = 'document.location.href = changeDash();'><script>var len = dashes.length; var i = 0; while(len > 0){document.write('<option value = '+dashes[i]+'>'+dashes[i]+'</option>'); len=len-1; i++; };</script></select></p>";
				out << "<p class = 'top'>New dashbaord: <input id = 'inputText' type = 'text'><button type = 'button' onclick = 'document.location.href = getUrl(inputText.value); addTile()'>Add</button>";
				out << "<div class='tile' id = 'tile1'>tile1</div>";
				out << "<div class='tile' id = 'tile2'>tile2</div>";
				out << "<div style = 'display:block;'>";

				out << "<p style = 'margin-left:15%; float:left;'>Location: <input id = 'tileText1' type = 'text'> </p>";
				out << "<p style = 'margin-left:27%; float:left;'>Location: <input id = 'tileText2' type = 'text'> </p>";
				out << "<p style = 'margin-left:15%; float:left;'>View: <select id = 'tileSelect1' onclick = 'changeTile(tileText1.value, 1);'><option value = '1'>Tempurature</option><option value = '2'>High/Low</option><option value = '3'>Pressure</option><option value = '4'>Humidity</option><option value = '1'>5 Day</option></select></p>";
				out << "<p style = 'margin-left:37%; float:left;'>View: <select id = 'tileSelect2'  onclick = 'changeTile(tileText2.value, 2)'><option value = '1'>Tempurature</option><option value = '2'>High/Low</option><option value = '3'>Pressure</option><option value = '4'>Humidity</option><option value = '1'>5 Day</option></select></p>";
				out << "<div class='tile' id = 'tile3'>tile3</div>";
				out << "<div class='tile' id = 'tile4'>tile4</div>";
				out << "<div style = 'display:block;'>";
				out << "<p style = 'margin-left:15%; float:left;'>Location: <input id = 'tileText3' type = 'text'> </p>";
				out << "<p style = 'margin-left:27%; float:left;'>Location: <input id = 'tileText4' type = 'text'> </p>";
				out << "<p style = 'margin-left:15%; float:left;'>View: <select id = 'tileSelect3'  onclick = 'changeTile(tileText3.value, 3)'><option value = '1'>Tempurature</option><option value = '2'>High/Low</option><option value = '3'>Pressure</option><option value = '4'>Humidity</option><option value = '1'>5 Day</option></select></p>";
				out << "<p style = 'margin-left:37%; float:left;'>View: <select id = 'tileSelect4'  onclick = 'changeTile(tileText4.value, 4)'><option value = '1'>Tempurature</option><option value = '2'>High/Low</option><option value = '3'>Pressure</option><option value = '4'>Humidity</option><option value = '1'>5 Day</option></select></p>";
			    
				out << "</body>";

			}
			else {
				out << "<h1>This is not the page you are looking for, move along.</h1>"
					<< "<p>Host: " << req.getHost() << "</p>"
					<< "<p>Method: " << req.getMethod() << "</p>"
					<< "<p>URI: " << req.getURI() << "</p>";
			}
			
			out.flush();

			cout << endl << "Response sent for URI " << req.getURI() << endl;
		}
	};


class MyRequestHandlerFactory : public HTTPRequestHandlerFactory
{
public:
	virtual HTTPRequestHandler* createRequestHandler(const HTTPServerRequest&)
	{
		return new MyRequestHandler;
	}
};

class MyServerApp : public ServerApplication
{
protected:
	int main(const vector<string>&)
	{
		HTTPServer s(new MyRequestHandlerFactory, ServerSocket(9090), new HTTPServerParams);

		s.start();
		cout << endl << "Visit localhost:9090" << endl;

		waitForTerminationRequest();  // wait for CTRL-C or kill

		cout << endl << "Shutting down..." << endl;
		s.stop();

		return Application::EXIT_OK;
	}
};

int main(int argc, char** argv)
{
	MyServerApp app;
	return app.run(argc, argv);
}
