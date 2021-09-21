#include "HelloDLL.h"
#include <iostream>

using namespace std;


void classDLL::hello()
{
	cout << "Hello World of DLL" << endl;
}

void classDLL::hello_static()
{
	cout << "Hello World of DLL static" << endl;
}

int classDLL::init(struct Event *event) {
	cout << "init" << endl;
	return 0;
}

int classDLL::data_handler(struct InputParameter *inputParameter) {
	cout << "main" << endl;
	cout << inputParameter->url << endl;
	return 0;
}

int classDLL::post_process() {
	cout << "post process" << endl;
	return 0;
}