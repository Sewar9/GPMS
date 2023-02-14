/*
 * SlaveManager.h
 *
 *  Created on: 18 Dec 2022
 *      Author: tasneem
 */

#ifndef SLAVEMANAGER_H_
#define SLAVEMANAGER_H_

#include <vector>
#include <unordered_map>
#include "ConnectionChanel.h"
#include "TransportManager.h"
#include "Logic.h"
#include "MDSMessage.h"
#include "RegTable.h"

/******************** Defines And Enums *********************/
enum TEMPRETURE : uint16_t {
	ROOM_TEMPRETURE 	  = 0x19 //25 in decimal
};

enum FunctionCode : uint8_t {
  ANY_FUNCTION_CODE       = 0x00,
  READ_COIL               = 0x01,
  READ_DISCR_INPUT        = 0x02,
  READ_HOLD_REGISTER      = 0x03,
  READ_INPUT_REGISTER     = 0x04,
  WRITE_COIL              = 0x05,
  WRITE_HOLD_REGISTER     = 0x06,
  READ_EXCEPTION_SERIAL   = 0x07,
  DIAGNOSTICS_SERIAL      = 0x08,
  READ_COMM_CNT_SERIAL    = 0x0B,
  READ_COMM_LOG_SERIAL    = 0x0C,
  WRITE_MULT_COILS        = 0x0F,
  WRITE_MULT_REGISTERS    = 0x10,
  REPORT_SERVER_ID_SERIAL = 0x11,
  READ_FILE_RECORD        = 0x14,
  WRITE_FILE_RECORD       = 0x15,
  MASK_WRITE_REGISTER     = 0x16,
  R_W_MULT_REGISTERS      = 0x17,
  READ_FIFO_QUEUE         = 0x18,
  ENCAPSULATED_INTERFACE  = 0x2B,
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
/********************************************************************/
class Logic {
public:
	Logic();
	virtual ~Logic();
	void updateRegs(uint16_t reg,uint16_t value);
	void updateRegsInCoils(uint16_t reg,bool value); 	//slave --> logic
	static void applyOutsideChanges(uint16_t reg,uint16_t value);  // logic-->slave

	static unordered_map<uint16_t,uint16_t> logic_regs;
	//static bool Power_click;
};

//*****************************************************************//
class SlaveManager {

public:
	SlaveManager();
	virtual ~SlaveManager();
	static void HandleMessage(MDSMessage &msg);
	static void sendMessage(uint8_t funcCode,  uint8_t* data);
	static void initMaps(); //this is a pre-processed  initialization
	static void updateHoldingReg(uint16_t reg,uint16_t value); //this is a pre-processed  initialization
	static void updateCoils(uint16_t reg,bool value); //this is a pre-processed  initialization

private:
	static RegTable<uint16_t,uint16_t> holding_regs_table_;
	static RegTable<uint16_t,uint16_t> input_regs_table_;
	static RegTable<uint16_t,bool> coils_table_;
	static RegTable<uint16_t,bool> discrete_table_;
	static Logic logic_layer;

};
/********************************************************************/

#endif /* SLAVEMANAGER_H_ */
