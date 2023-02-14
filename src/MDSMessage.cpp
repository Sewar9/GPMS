/*
 * MDSMessage.cpp
 *
 *  Created on: 28 Dec 2022
 *      Author: tasneem
 */

#include "MDSMessage.h"

MDSMessage::MDSMessage() {
	// TODO Auto-generated constructor stub
	this->data = NULL;

}

MDSMessage::~MDSMessage() {
	// TODO Auto-generated destructor stub
}
MDSMessage::MDSMessage(uint8_t fc,uint16_t first_,uint16_t sec_){
	this->data = NULL;
	this->function_code = fc;
	this->sec = sec_;
	this->first = first_;
}
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
uint16_t MDSMessage::getFirst2Bytes(){
	return this->first;
}
uint16_t MDSMessage::getSec2Bytes(){
	return this->sec;
}
