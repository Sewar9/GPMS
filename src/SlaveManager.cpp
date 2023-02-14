/*
 * SlaveManager.cpp
 *
 *  Created on: 18 Dec 2022
 *      Author: tasneem
 */

#include "SlaveManager.h"

RegTable<uint16_t,uint16_t> SlaveManager::holding_regs_table_;
RegTable<uint16_t,uint16_t> SlaveManager::input_regs_table_;
RegTable<uint16_t,bool> 	SlaveManager::coils_table_;
RegTable<uint16_t,bool> 	SlaveManager::discrete_table_;
Logic SlaveManager::logic_layer;



SlaveManager::SlaveManager() {
	// initialize the tables which we will use in Logic
	this->holding_regs_table_.addRegs(MODE_REG,COOL);
	this->holding_regs_table_.addRegs(SET_TEMPRETURE_REG,ROOM_TEMPRETURE);
	this->holding_regs_table_.addRegs(TEMPRETURE_REG,ROOM_TEMPRETURE);
	this->holding_regs_table_.addRegs(FAN_SPEED_REG,AUTO);
	this->coils_table_.addRegs(POWER_REG, OFF);

}
//***********************************************************//
SlaveManager::~SlaveManager() {
	// TODO Auto-generated destructor stub
}
//***********************************************************//

void SlaveManager::HandleMessage(MDSMessage &msg){
	vector<uint16_t> response;
	response.clear();
	response.push_back(msg.getFunctionCode());

	switch(msg.getFunctionCode()){

		case READ_HOLD_REGISTER:
			{
				cout<<"Function code 3" <<endl;
				uint16_t starting_addr = msg.getFirst2Bytes();
				uint16_t quantity = msg.getSec2Bytes();

				// go over all the block of registers and add them to the response
				for (int i=0; i<quantity; i++){
					uint16_t value = holding_regs_table_.ReadReg(starting_addr); //value of the register
					response.push_back(value);
					starting_addr++;
//					uint8_t partA = static_cast<uint8_t>((value & 0xFF00) >> 8);
//					uint8_t partB = static_cast<uint8_t>(value & 0x00FF);
//					response.push_back(partA);
//					response.push_back(partB);
				}
				break;
			}

		case WRITE_HOLD_REGISTER :
			{
				cout<<"Function code 6" <<endl;
				uint16_t reg = msg.getFirst2Bytes();
				uint16_t value = msg.getSec2Bytes();
				response.push_back(reg);
				response.push_back(value);

				holding_regs_table_.updateRegs(reg, value);
				logic_layer.updateRegs(reg,value); //update logic if it's relevant reg

				cout<<"slave manager : reg "<< static_cast<unsigned int>(reg) <<" have been updated to : "<< static_cast<unsigned int>(value)<<endl;
				break;

			}
		case WRITE_COIL :
			{
				cout<<"Function code 5" <<endl;
				uint16_t reg = msg.getFirst2Bytes();
				uint16_t value = msg.getSec2Bytes();
				response.push_back(reg);

				uint16_t on = 0xff00;
				uint16_t off = 0x0000;

				if(value == on){
					coils_table_.updateRegs(reg, 1);
					response.push_back(on);
					logic_layer.updateRegs(reg,on); //update logic if it's relevant reg --- CHECK!!!!!!!
				}
				else if(value == off){
					coils_table_.updateRegs(reg, 0);
					response.push_back(off);
					logic_layer.updateRegs(reg,off); //update logic if it's relevant reg --- CHECK!!!!!!!
				}

				cout<<"slave manager : reg "<< static_cast<unsigned int>(reg) <<" have been updated to : "<< static_cast<bool>(value)<<endl;
				break;

			}


		case READ_COIL :
			{
				cout<<" Function code 1" <<endl;
				uint16_t starting_addr = msg.getFirst2Bytes();
				uint16_t quantity = msg.getSec2Bytes();

				// go over all the block of registers and add them to the response
				for (int i=0; i<quantity; i++){
					bool value = coils_table_.ReadReg(starting_addr); //value of the register
					response.push_back(value);
					starting_addr++;
				}
				break;

			}
			// add case to read input
		default:
			cout<<"there is no handle to this function code yet!" <<endl;

	}

	cout<<"response is: ";
	for (auto i: response)
		cout << static_cast<unsigned int>(i)<<" ";
	cout<<endl;
}
//***********************************************************//
// this function decodes the received message
void SlaveManager::sendMessage(uint8_t func_code, uint8_t* data){
// 1 Bytes = function_code--- 2 Bytes = starting_address/register--- 2 Bytes = quantity/value

	uint8_t high_first = data[8],low_first = data[9];
	uint8_t high_sec = data[10], low_sec = data[11];
	uint16_t left_two_bytes= (high_first << 8) | low_first;
	uint16_t right_two_bytes = (high_sec << 8) | low_sec;

	MDSMessage mess(func_code,left_two_bytes,right_two_bytes );

	HandleMessage(mess);
}
//************************************************************//
void SlaveManager::updateHoldingReg(uint16_t reg,uint16_t value){
	holding_regs_table_.updateRegs(reg, value);
}
//************************************************************//
void SlaveManager::updateCoils(uint16_t reg,bool value){
	coils_table_.updateRegs(reg, value);
}
