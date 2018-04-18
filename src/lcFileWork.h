/*
 * lcFileWork.h
 *
 *  Created on: 09-Feb-2018
 *      Author: humble_wolf
 */
#include <string>
#include <vector>

#ifndef LCFILEWORK_H_
#define LCFILEWORK_H_

void overWriteToFile (std::string , std::string);
void writeKeyValuePair (std::string, std::string, std::string);
void overWriteVectorToFile (std::string, std::vector<std::string>);
std::string readValueByKey (std::string, std::string);

#endif /* LCFILEWORK_H_ */
