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
#include "ConnectionChanel.h"
#include "TransportManager.h"
#include "SlaveManager.h"
#include <unordered_map>
#include <fstream>
#include <cstdlib>
using namespace rapidjson;


int main() {
	SlaveManager man;
    TransportManager trans;
    trans.StartListening();

}
