/*
 * Logic.h
 *
 *  Created on: 18 Dec 2022
 *      Author: tasneem
 */

#ifndef LOGIC_H_
#define LOGIC_H_
#include "stdlib.h"
#include "SlaveManager.h"
#include <unordered_map>
#include <iostream>
using namespace std;

//**********************************************************/
//class Logic;
/******************** Defines And Enums *********************/

enum TEMPRETURE : uint16_t {
	ROOM_TEMPRETURE 	  = 0x19 //25 in decimal
};
enum RegistersNumber : uint16_t {
  MODE_REG            = 0x0007,
  POWER_REG           = 0x0030,
  SET_TEMPRETURE_REG  = 0x0009,
  TEMPRETURE_REG      = 0x0000,
  FAN_SPEED_REG       = 0x0008,
};

enum ModeVal : uint16_t {
  COOL  = 0x01,
  HEAT  = 0x02,
  COLD  = 0x03,

};
enum FanVal : uint16_t {
  ONE   = 0x01,
  TWO   = 0x02,
  THREE = 0x03,
  AUTO  = 0x04

};
enum PowerVal : bool {
  ON  = 1,
  OFF = 0,
};

class Logic;

//*****************************************************************//

class Logic {
public:
	Logic();
	virtual ~Logic();
	void updateRegs(uint16_t reg,uint16_t value);
	void updateOneBitRegs(uint16_t reg,bool value);
	void updateRegsInCoils(uint16_t reg,bool value); 	//slave --> logic
	static void applyOutsideChanges(uint16_t reg,uint16_t value);  // logic-->slave
	static void applyOutsideChanges_v2(uint16_t reg,bool value);  // logic-->slave

	static unordered_map<uint16_t,uint16_t> regs_;
	static unordered_map<uint16_t,bool> oneBit_regs;
};

#endif /* LOGIC_H_ */
