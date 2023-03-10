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
#include "rapidjson/istreamwrapper.h"
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include "rapidjson/ostreamwrapper.h"
#include "rapidjson/document.h"     // rapidjson's DOM-style API
#include "rapidjson/prettywriter.h" // for stringify JSON
#include "MDSMessage.h"
#include "Logic.h"
using namespace rapidjson;

//listen to clients
class TransportManager {
public:
	TransportManager();
	void ReadPortsFromSetting();
	virtual ~TransportManager();
	void StartListening(); // this is the server
	MDSMessage HandleMessage(vector<char> message);
private:
	vector<int> ports_list; // list of the ports which we will connect with
};

#endif /* TRANSPORTMANAGER_H_ */
