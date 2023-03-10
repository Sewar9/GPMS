/*
 * Logic.cpp
 *
 *  Created on: 18 Dec 2022
 *      Author: tasneem
 */

#include "Logic.h"
#include "SlaveManager.h"

unordered_map<uint16_t,uint16_t> Logic::regs_;
unordered_map<uint16_t,bool> Logic::oneBit_regs;


Logic::Logic() {
	// TODO Auto-generated constructor stub
	// init the registers in the logic layer

	this->regs_[MODE_REG] = COOL;
	this->regs_[SET_TEMPRETURE_REG] = ROOM_TEMPRETURE;
	this->regs_[TEMPRETURE_REG] = ROOM_TEMPRETURE;
	this->regs_[FAN_SPEED_REG] = AUTO;

	this->oneBit_regs[POWER_REG] = OFF; //off
}
//-------------------------------------------
Logic::~Logic() {
	// TODO Auto-generated destructor stub
}
//-------------------------------------------
void Logic::updateRegs(uint16_t reg,uint16_t value){
	if(regs_.find(reg) != regs_.end()){
		//if this register does'nt affect the registers in  the logic layer --> do nothing

		this->regs_[reg] = value;
		switch(reg){
		case MODE_REG:
			cout<<"logic layer - mode is changed to : "<<value<<endl;
			break;
		case SET_TEMPRETURE_REG:
			cout<<"logic layer - temperature is changed to : "<<value<<endl;
			break;

		case TEMPRETURE_REG:
			cout<<"logic layer - room temperature is changed to : "<<value<<endl;
			break;
		case FAN_SPEED_REG:
			cout<<"logic layer - fan speed is changed to : "<<value<<endl;
			break;
		}

	}

}
//---------------------------------------------------------
void Logic::updateOneBitRegs(uint16_t reg,bool value){
	if(oneBit_regs.find(reg) != oneBit_regs.end()){
		switch(reg){
		case POWER_REG:
			cout<<"logic layer - power click is changed to : "<<value<<endl;
			break;
		}
		// it may be other cases in the future...
	}
}
//---------------------------------------------
void Logic::applyOutsideChanges(uint16_t reg,uint16_t value){
	// here we assume that someone's applies changes on the physical device
	// these changes affect register reg and changes it's value...

	// here someone changes the hardware/physical register to a new value:-
	// he changed register number "reg" to be the value "value"
	regs_[reg] = value;
	SlaveManager::updateHoldingReg(reg, value);
}
//-------------------------------------------------------
void Logic::applyOutsideChanges_v2(uint16_t reg,bool value){

	// here someone changes the hardware/physical register to a new value:-
	// he changed register number "reg" to be the value "value"
	oneBit_regs[reg] = value;
	SlaveManager::updateCoils(reg, value);
}




