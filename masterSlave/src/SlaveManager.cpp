/*
 * SlaveManager.cpp
 *
 *  Created on: 18 Dec 2022
 *      Author: tasneem
 */

#include "SlaveManager.h"
//#include "MessageTransmission.h"
std::map<uint8_t, uint8_t> SlaveManager::holding_regs_table;
std::map<uint8_t, uint8_t> SlaveManager::input_regs_table;
std::map<bool, uint8_t> SlaveManager::coils_table;
std::map<bool, uint8_t> SlaveManager::discrete_table;

SlaveManager::SlaveManager() {
	//this->trans_manager = new TransportManager();

}

SlaveManager::~SlaveManager() {
	// TODO Auto-generated destructor stub
}
template <typename KeyType, typename ValueType>
void SlaveManager::updateMap(KeyType key, ValueType val, int mapNum){
	if (mapNum == 3){
		if (holding_regs_table.find(key) == holding_regs_table.end()) {
			holding_regs_table[key] = val;
			cout << static_cast<unsigned int>(key) << std::endl;
			cout << static_cast<unsigned int>(val) << std::endl;
		}
		else{
			uint8_t value = holding_regs_table[key];
			cout << static_cast<unsigned int>(value) << std::endl;
		}
	}
	if (mapNum == 4){
		if (input_regs_table.find(key) == input_regs_table.end()) {
			input_regs_table[key] = val;
			cout << key << std::endl;
			cout <<  val << std::endl;
			cout << static_cast<unsigned int>(key) << std::endl;
			cout << static_cast<unsigned int>(val) << std::endl;
		}
	}
	if (mapNum == 1){
		if (coils_table.find(key) == coils_table.end()) {
			coils_table[key] = val;
			cout << key << std::endl;
			cout <<  val << std::endl;
			cout << static_cast<unsigned int>(key) << std::endl;
			cout << static_cast<unsigned int>(val) << std::endl;
		}
	}
	if (mapNum == 2){
			if (discrete_table.find(key) == discrete_table.end()) {
				discrete_table[key] = val;
				cout << static_cast<unsigned int>(key) << std::endl;
				cout << static_cast<unsigned int>(val) << std::endl;
			}
			else{
				uint8_t value = discrete_table[key];
				cout << static_cast<unsigned int>(value) << std::endl;
			}
	}

}

void SlaveManager::HandleMessage(MDSMessage &msg){
	cout<<"this handle message x "<<endl;
	// SHOULD IMPLEMENT SWITCH CASE HERE !!
	uint8_t* data = msg.getData();
	uint8_t starting_addr = data[9];
	uint8_t numOfRegs = data[11];
	switch(msg.getFunctionCode()){
	case 3:
			cout<<"TBD Function code 3" <<endl;


			cout << static_cast<unsigned int>(starting_addr) << std::endl;

			for (int i=0; i<numOfRegs; i++){
				updateMap(starting_addr,0,3);
				starting_addr++;
			}

			cout << static_cast<unsigned int>(numOfRegs) << std::endl;

			break;
	case 4:
		cout<<"TBD Function code 4" <<endl;


		for (int i=0; i<numOfRegs; i++){
			updateMap(starting_addr,0,4);
			starting_addr++;
		}


		break;
	case 1:
		cout<<"TBD Function code 1" <<endl;


		for (int i=0; i<numOfRegs; i++){
			updateMap(starting_addr,0,1);
			starting_addr++;
		}
		break;
	case 2:
		cout<<"TBD Function code 2" <<endl;


		for (int i=0; i<numOfRegs; i++){
			updateMap(starting_addr,0,2);
			starting_addr++;
		}
		break;

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


