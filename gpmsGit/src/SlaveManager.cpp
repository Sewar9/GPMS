/*
 * SlaveManager.cpp
 *
 *  Created on: 18 Dec 2022
 *      Author: tasneem
 */

#include "SlaveManager.h"
//#include "MessageTransmission.h"

SlaveManager::SlaveManager() {
	//this->trans_manager = new TransportManager();
	this->coils_table = new CoilsRegisters();
	this->discrete_table = new DiscreteInput();
	this->holding_regs_table = new HoldingRegisters();
	this->input_regs_table = new InputRegisters();
}

SlaveManager::~SlaveManager() {
	// TODO Auto-generated destructor stub
}
void SlaveManager::HandleMessage(MDSMessage &msg){
	cout<<"this handle message x "<<endl;
	// SHOULD IMPLEMENT SWITCH CASE HERE !!

	switch(msg.getFunctionCode()){
	case 3:
			cout<<"TBD Function code 3" <<endl;
			uint8_t* data = msg.getData();
			cout << data[10] + '0';
			uint8_t a = data[9];
			uint8_t b = data[10];

			uint16_t starting_addr = (static_cast<uint16_t>(a) << 8) | b;
			cout << starting_addr + '0';

			uint8_t c = data[11];
			uint8_t d = data[12];

			uint16_t numOfRegs = (static_cast<uint16_t>(c) << 8) | d;
			cout << numOfRegs + '0';
			break;
	/*case 6:
			cout<<"TBD Function code 6" <<endl;
			break;
	case 10:
			cout<<"TBD Function code 10" <<endl;
	*/
	}
}

void SlaveManager::sendMessage(uint8_t funcCode, uint8_t* data, int index){
	MDSMessage mess;

	mess.setData(data);
	mess.setFunctionCode(funcCode);

	cout << "getMessage got called" << endl;
	HandleMessage(mess);
	return;
}


