/*
 * TransportManager.h
 *
 *  Created on: 21 Dec 2022
 *      Author: tasneem
 */

#ifndef TRANSPORTMANAGER_H_
#define TRANSPORTMANAGER_H_

#include "ConnectionChanel.h"
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include </home/sewar/Downloads/rapidjson-master/include/rapidjson/istreamwrapper.h>
#include </home/sewar/Downloads/rapidjson-master/include/rapidjson/writer.h>
#include </home/sewar/Downloads/rapidjson-master/include/rapidjson/stringbuffer.h>
#include </home/sewar/Downloads/rapidjson-master/include/rapidjson/ostreamwrapper.h>
#include "/home/sewar/Downloads/rapidjson-master/include/rapidjson/document.h"     // rapidjson's DOM-style API
#include "/home/sewar/Downloads/rapidjson-master/include/rapidjson/prettywriter.h" // for stringify JSON
#include "MessageTransmission.h"
#include "MDSMessage.h"
using namespace rapidjson;

//listen to clients
class TransportManager {
public:
	TransportManager();
	//TransportManager(void (*func)(int));
	//void ReadPortsFromSetting();
	virtual ~TransportManager();
	void StartListening(); // this is the server
	MDSMessage HandleMessage(vector<char> message);
private:
	vector<int> ports_list; // list of the ports which we will connect with
	//ConnectionChanel chanel_1; // only for debugging
};

#endif /* TRANSPORTMANAGER_H_ */
