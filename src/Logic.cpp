/*
 * Logic.cpp
 *
 *  Created on: 18 Dec 2022
 *      Author: tasneem
 */

#include "Logic.h"
#include "SlaveManager.h"

unordered_map<uint16_t,uint16_t> Logic::logic_regs;


Logic::Logic() {
	// TODO Auto-generated constructor stub
	// init the registers in the logic layer

	this->logic_regs[MODE_REG] = 0x07;
	this->logic_regs[SET_TEMPRETURE_REG] = 0x19;
	this->logic_regs[TEMPRETURE_REG] = 0x19;
	this->logic_regs[FAN_SPEED_REG] = 0x04;
	this->logic_regs[POWER_REG] = 0x0000; //off
}
//-------------------------------------------
Logic::~Logic() {
	// TODO Auto-generated destructor stub
}
//-------------------------------------------
void Logic::updateRegs(uint16_t reg,uint16_t value){
	if(logic_regs.find(reg) != logic_regs.end()){
		//if this register does'nt affect the registers in  the logic layer --> do nothing
		this->logic_regs[reg] = value;
		switch(reg){
		case MODE_REG:
			cout<<"logic layer - mode is changed to : "<<value<<endl;
			break;
		case SET_TEMPRETURE_REG:
			cout<<"logic layer - tempreture is changed to : "<<value<<endl;
			break;

		case TEMPRETURE_REG:
			cout<<"logic layer - room tempreture is changed to : "<<value<<endl;
			break;
		case FAN_SPEED_REG:
			cout<<"logic layer - fan speed is changed to : "<<value<<endl;
			break;
		case POWER_REG:
			cout<<"logic layer - power click is changed to : "<<value<<endl;
			break;
		}

	}

}
//---------------------------------------------
void Logic::applyOutsideChanges(uint16_t reg,uint16_t value){
	// here we assume that someone's applies changes on the physical device
	// these changes affect register reg and changes it's value...

	if(logic_regs.find(reg) != logic_regs.end()){
		logic_regs[reg] = value;  //set changes on hardware

	}
	else{
		cout<<"Attention! the register you have entered is not in use !" <<endl;
	}

}




