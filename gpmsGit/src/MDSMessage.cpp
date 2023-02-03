/*
 * MDSMessage.cpp
 *
 *  Created on: 28 Dec 2022
 *      Author: tasneem
 */

#include "MDSMessage.h"

/*MDSMessage::MDSMessage() {
	// TODO Auto-generated constructor stub
	this->function_code = 0;
	this->data = {0};
}*/

MDSMessage::~MDSMessage() {
	// TODO Auto-generated destructor stub
}
/*MDSMessage::MDSMessage(uint8_t Func_code, std::vector<uint8_t> & data){
	this->function_code = 0;
	this->data = {0};
}
*/
void MDSMessage::setData(uint8_t* data){
	this->data=data;
}
void MDSMessage::setFunctionCode(uint8_t func_code){
	this->function_code = func_code;
}

uint8_t MDSMessage::getFunctionCode(){
	return this->function_code;
}

uint8_t* MDSMessage::getData(){
	return this->data;
}

void MDSMessage::print(){
	cout << this->function_code << endl;
}
