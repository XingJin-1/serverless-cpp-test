#pragma once

#include <nlohmann/json.hpp>
using namespace std;
using namespace nlohmann;


struct InputParameter {
	json metadata;
	string endpoint;
	string url;
	string path;
	json args;
};

struct Event {
	string projectKey;
	string filter;
	int pageNumber;
	int pageSize;
	string authorization;
	string jobId;
	string apiKey;
	// TODO: any type of values in map
	map<string, string> args;
};

class classDLL
{
public:
	classDLL(void){};
	~classDLL(void){};

	void hello();
	static void hello_static();

	int init(struct Event *event);
	int data_handler(struct InputParameter *inputParameter);
	int post_process();

}; 
