#define CROW_MAIN
#include "crow.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <map>

#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "HelloDLL.h"

using namespace std;
using namespace nlohmann;

size_t WriteCallback(char *contents, size_t size, size_t nmemb, void *userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

int main()
{
	
	// initialize api instance
	crow::SimpleApp app;
	
	CROW_ROUTE(app, "/")([]() {
		// initialize connection instance
		CURL *curl = curl_easy_init();
		if (!curl) {
			fprintf(stderr, "init failed\n");
			return EXIT_FAILURE;
		}
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

		string base_url;
		string project_key;
		base_url = "https://rd-datalake-test.icp.infineon.com";
		project_key = "RDDLTST1";

		// set url
		string filter;
		string get_url;
		filter = "task%3AserverlessCpp";
		//url = "https://rd-datalake-test.icp.infineon.com/v1/projects/RDDLTST1/artifacts/metadata?filter=";
		get_url = base_url.append("/v1/projects/RDDLTST1/artifacts/metadata?filter=");
		get_url.append(filter); // <-- NOTE: see further below!
		get_url.append("&pageNumber=1&pageSize=25");
		cout << "url is:" << endl;
		cout << get_url << endl;
		curl_easy_setopt(curl, CURLOPT_URL, get_url.c_str());
		curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);

		// set headers 
		struct curl_slist *list = NULL;
		list = curl_slist_append(list, "Authorization: Bearer 0004TT4JyZDvec8XR396qzCSECCx");
		list = curl_slist_append(list, "accept: application/json");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);

		string readBuffer;
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

		CURLcode result = curl_easy_perform(curl);
		cout << "------1--------" << endl;
		classDLL helloDLL;
		InputParameter inputParameter;
		Event event;
		// 1.TODO: call init(struct Event *event)
		event.filter = "task%3AserverlessCpp";
		helloDLL.init(&event);

		json jsonReturn = json::parse(readBuffer);
		json jsonData = jsonReturn["data"];
		int count = 0;
		for (auto &item : jsonData) {
			// 2.TODO: call data_handler
			count += 1;
			cout << "Item No.:" << count << endl;
			cout << item["artifactID"] << endl;    // returns string
			cout << item["rawDataFile"]["fileName"] << endl;    // returns array
																//inputParameter["metadata"] = item;
			inputParameter.metadata = item;
			inputParameter.url = "this is a url";
			helloDLL.data_handler(&inputParameter);
		}
		// 3.TODO: call post_process()
		helloDLL.post_process();
		cout << "------1--------" << endl;

		if (result != CURLE_OK) {
			fprintf(stderr, "downlaod problem: %s \n", curl_easy_strerror(result));
		}
		curl_easy_cleanup(curl);

		//return "Hello World";
		return 1;
		//return EXIT_SUCCESS;
	});
	
	CROW_ROUTE(app, "/xing")([]() {
		return "Hello World From Xing";
	});

	app.port(8080).multithreaded().run();
	
	return 0;
}