/*
 * MDSMessage.h
 *
 *  Created on: 28 Dec 2022
 *      Author: tasneem
 */

#ifndef MDSMESSAGE_H_
#define MDSMESSAGE_H_
#include <vector>
#include <iostream>
using namespace std;

class MDSMessage {
public:
	//MDSMessage();
	//MDSMessage(uint8_t Func_code, std::vector<uint8_t> & data);
	virtual ~MDSMessage();
	uint8_t getFunctionCode();
	uint8_t* getData();
	void print();
	void setData(uint8_t* data);
	void setFunctionCode(uint8_t Func_code);
private:
	uint8_t function_code; //unit
	uint8_t* data;

};

#endif /* MDSMESSAGE_H_ */
