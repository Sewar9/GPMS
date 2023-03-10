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
	MDSMessage();
	MDSMessage(uint8_t fc,uint16_t start_addr,uint16_t quant);
	virtual ~MDSMessage();
	uint8_t getFunctionCode();
	uint8_t* getData();
	void print();
	uint16_t getFirst2Bytes();
	uint16_t getSec2Bytes();
	void setData(uint8_t* data);
	void setFunctionCode(uint8_t Func_code);
private:
	uint8_t function_code = 0;
	uint16_t first = 0;
	uint16_t sec = 0;
	uint8_t* data;

};

#endif /* MDSMESSAGE_H_ */
