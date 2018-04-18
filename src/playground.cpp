#include <iostream>
#include <chrono>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <regex>
#include "lcFileWork.h"

using namespace std;

/*int main() {
	void playHere();
	playHere();
	return 0;
}*/

void playHere(){

	//overWriteToFile("tf.txt","test data_2");
	//writeKeyValuePair("tf.txt","c4","ajaz");
	//cout << readValueByKey("tf.txt","c4");
	cout << "done donna";

}

// write server fail-safe logic too ------- create a file - write no of hours in it - at every hour dec count by one and save file - when count is 0 run script

//reserved code.....

	/*std::string key = "msg";
	std::string nval = "be happy";

	std::string s = "msg:hello there";
	std::regex e ("^"+key+":.*$");

	std::string finals = std::regex_replace (s,e,key+":"+nval);
	std::cout << finals;*/

/*string pass,scriptn,cmd;

	cout << "Enter full script path" << endl ;
	cin >> scriptn;

	cout << "Enter sudo password" << endl ;
	cin >> pass;

	scriptn = argv[1];
	pass = argv[2];

	std::this_thread::sleep_for(std::chrono::milliseconds(4000));

	cmd = "echo "+pass+" | sudo -S "+scriptn;
	cout << "Sleep ended, now executing command - "+cmd << endl ;

	system(cmd.c_str());*/
