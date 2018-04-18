#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>

using namespace std;

void overWriteToFile (string fileName, string data) {

  ofstream myfile;
  myfile.open (fileName, ios::trunc);
  myfile << data << endl;
  myfile.close();

}

void overWriteVectorToFile (string fileName, std::vector<std::string> opArr) {

  ofstream myfile;
  myfile.open (fileName, ios::trunc);
  for(auto line : opArr){
	  myfile << line << endl;
  }
  myfile.close();

}

string readValueByKey (string fileName, string key){

	std::regex repat ("^"+key+":(.*)$");
	std::cmatch cm;
	string val = "";
	ifstream myfile (fileName);

	if (myfile.is_open())
	{
		std::string line;
		while ( getline (myfile,line) )
		{
			if(std::regex_match (line.c_str(),cm,repat)){
				val = cm[1];
				break;
			}
		}
		myfile.close();
	}else
		cout << "Unable to open file";

	return val;

}

void writeKeyValuePair (string fileName, string key, string value) {

	std::vector<std::string> opArr;
	std::regex repat ("^"+key+":.*$");
	bool isKeyFound = false;
	ifstream myfile (fileName);

	if (myfile.is_open())
	{
		std::string line;
		while ( getline (myfile,line) )
		{
			if(std::regex_match (line,repat)){
				opArr.push_back(key+":"+value);
				isKeyFound = true;
			}else{
				opArr.push_back(line);
			}
		}
		myfile.close();
		if(!isKeyFound){
			opArr.push_back(key+":"+value);
		}
		overWriteVectorToFile(fileName,opArr);
	}else
		cout << "Unable to open file";

}
