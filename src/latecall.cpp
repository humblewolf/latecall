//============================================================================
// Name        : latecall.cpp
// Author      : humble_wolf
// Version     :
// Copyright   : All rights reserved by humble_wolf
// Description : C++, Ansi-style
//============================================================================

#include <iostream>
#include <chrono>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <mutex>
#include "lcFileWork.h"
#include "SingletonProcess.cpp"
#define CONFIGFILE "/usr/local/etc/latecall.ini"//replace this with some hardcoded system path like /etc/latecall

using namespace std;

mutex mtx;

void shutdownLateCall(){
	//first stop latecall service.....
	string cmd = "systemctl stop latecall.service;systemctl disable latecall.service";
	system(cmd.c_str());
	exit(0);
}

string readFromInfStr(string file, string key){
	return readValueByKey(file,key);
}

void writeToInfStr(string file, string key, string value){
	writeKeyValuePair(file, key, value);
}

void getLateCallStatus(){
	int hrs_rem = stoi(readFromInfStr(CONFIGFILE,"time"));
	cout << "Hours remaining till latecall - " << to_string(hrs_rem) << endl;
}

void runScript(){

	string scriptn = readFromInfStr(CONFIGFILE,"script");
	//string cmd = "echo "+pass+" | sudo -S ./"+scriptn;
	string cmd = "bash ./"+scriptn;
	system(cmd.c_str());
	mtx.unlock();//first release the mutex
	shutdownLateCall();

}

void runPreScript(){

	string scriptn = readFromInfStr(CONFIGFILE,"preScript");
	//string cmd = "echo "+pass+" | sudo -S ./"+scriptn;
	string cmd = "bash ./"+scriptn;
	system(cmd.c_str());

}

void waitCheck(){

	int hrs_rem = stoi(readFromInfStr(CONFIGFILE,"time"));
	int gap_hrs = stoi(readFromInfStr(CONFIGFILE,"gap"));
	cout << "Hours remaining till latecall - " << to_string(hrs_rem) << endl;
	if(hrs_rem == 0){
		cout << "Latecall will be executed." << endl;
		runScript();
	}else if(hrs_rem == gap_hrs){
		cout << "Pre Latecall will be executed." << endl;
		runPreScript();
	}


	//std::this_thread::sleep_for(std::chrono::milliseconds(4000));//sleep for 1 hr
	std::this_thread::sleep_for(std::chrono::hours(1));//sleep for 1 hr

	hrs_rem--;
	writeToInfStr(CONFIGFILE,"time",to_string(hrs_rem));

	waitCheck();

}

void writePropToFileAndWait(int ghours, int hours, string preScriptn, string scriptn){

	//cout << "Going to write prop files" << to_string(hours) << scriptn << to_string(isOn) << endl;
	writeToInfStr(CONFIGFILE,"gap",to_string(ghours));
	writeToInfStr(CONFIGFILE,"time",to_string(hours));
	writeToInfStr(CONFIGFILE,"preScript",preScriptn);
	writeToInfStr(CONFIGFILE,"script",scriptn);

	waitCheck();

}


int startApp(int argc, char** argv){

	//---------------------POSSIBLE EXECUTIONS---------------------------------------
		//normal execution :5 latecall --run <time-unit> <time-as-per-units> <gap-time-asper-timeunit> <pre-script-path> <main-script-path> [timeunit can be -h(hours) or -d(days) ]
		//revival execution:2 latecall --revive
		//status of execution:2 latecall --status

		//first line of defence.....
		switch (argc) {
			case 2: case 7:
				//cout << "valid no of args" << endl;
				break;
			default:
				cout << "Invalid no of arguments" << endl;
				return 0;

		}

		//now parse correct no of args....
		string flag = argv[1];
		if(flag.compare("--revive")==0){
			waitCheck();
			return 0;
		}else if (flag.compare("--status")==0) {
			getLateCallStatus();
			return 0;
		}else if (flag.compare("--run")==0 && argc==7) {

			string tunit,preScriptn,scriptn;
			int timei, gtimei;

			tunit = argv[2];
			preScriptn = argv[5];
			scriptn = argv[6];

			try
			{
				gtimei = stoi(argv[3]);
				timei = stoi(argv[4]);
			}
			catch (std::invalid_argument&)
			{
				cout << "Time can be only be an integer. " << endl ;
				return 0;
			}

			if(tunit.compare("-d") == 0){
				gtimei = gtimei*24;
				timei = timei*24;
			}else if (tunit.compare("-h") != 0) {
				cout << "Time unit can be only -h(hours) and -d(days)" << endl ;
				return 0;
			}

			cout << "Starting latecall" << endl;
			writePropToFileAndWait(gtimei,timei,preScriptn,scriptn);
			cout << "Stopping latecall" << endl;
			return 0;

		}else{
			cout << "Invalid arguments" << endl;
			return 0;
		}

}

int main(int argc, char** argv) {

	SingletonProcess singleton(5505);//latecall will acquire port 5505
	if (!singleton()){

		cout << "Latecall already running" << endl;
		return 0;

	}
	return startApp(argc, argv);

}

//reserved code --


/*bool tryMutexLock(){//this a more reliable yet complicated way of taking lock

	cout << "Trying for mutex lock" << endl;
	int i = 1;
	whilWWWWWe(i<50){//because taking a mutex lock can fail without any reason even if no thread thread owns mutex....

		if(mtx.try_lock()){//it means we got lock of mutex
			return true;
		}
		i++;

	}
	cout << "Latecall already running" << endl;
	shutdownLateCall();

}*/

/*bool tryMutexLock(){

	cout << "Trying for latecall lock" << endl;
	if(mtx.try_lock()){//it means we got lock of mutex
		cout << "Latecall lock taken successfully" << endl;
		return true;
	}else{
		cout << "Unable to take lock, this may be because latecall is already running, if you think this is not the case please try again." << endl;
		shutdownLateCall();
		return false;
	}

}*/
