/*
 * ConnectionChanel.h
 *
 *  Created on: 20 Dec 2022
 *      Author: tasneem
 */

#ifndef CONNECTIONCHANEL_H_
#define CONNECTIONCHANEL_H_
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <vector>
using namespace std;

class ConnectionChanel {
public:
	ConnectionChanel();
	ConnectionChanel(int port_number);
	virtual ~ConnectionChanel();
	int GetPortNumber();
	static int next_id;

private:
	int id; //to determine port number
};

#endif /* CONNECTIONCHANEL_H_ */
