//============================================================================
// Name        : server.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <vector>
#include <fstream>
#include <cstring>
#include "Logic.h"
#include "ConnectionChanel.h"
#include "TransportManager.h"
#include "SlaveManager.h"
#include <unordered_map>
#include <fstream>
#include <cstdlib>
using namespace rapidjson;


int main() {
	SlaveManager man;
//	Logic logic;
//	uint16_t reg = 0x07;
//	uint16_t value = 0x20;
//	logic.applyOutsideChanges(reg, value);
    TransportManager trans;
    trans.StartListening();

}
