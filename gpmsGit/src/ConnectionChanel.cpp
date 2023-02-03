
/*
 * ConnectionChanel.cpp
 *
 *  Created on: 20 Dec 2022
 *      Author: tasneem
 */

#include "ConnectionChanel.h"
#define START_PTNO 8080
int ConnectionChanel::next_id=0;

ConnectionChanel::ConnectionChanel() {
	// TODO Auto-generated constructor stub
	this->id=START_PTNO + next_id++; //generate port number and update the next id number

}
ConnectionChanel::ConnectionChanel(int port_number){
	this->id=port_number;
}
ConnectionChanel::~ConnectionChanel() {
	// TODO Auto-generated destructor stub
}
int ConnectionChanel::GetPortNumber(){
	return this->id;
}
