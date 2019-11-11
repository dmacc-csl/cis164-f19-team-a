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
			URI uri(req.getURI());
			uri.getPathSegments(segments);

			ostream& out = resp.send();
			if (segments.size() == 0) {
				out << "<h1>Team A UI Tests</h1>"
					<< "<p>To view an account balance visit http://localhost:" << TEST_SERVER_PORT << "/tests/x where x is the test number.</p>";
			}
			else if (segments.size() == 2 && segments[0] == "tests") {
				int testId = stoi(segments[1]);
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
					out << "<script>function showText(){var inputText = document.getElementById('inputText').value;outputText.innerHTML = inputText;}</script>";
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