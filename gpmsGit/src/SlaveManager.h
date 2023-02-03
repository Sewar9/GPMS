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
#include "MDSMessage.h"
//#include "HoldingRegisters.h"
//#include "DiscreteInput.h"
#include "RegTable.h"
//#include "CoilsRegisters.h"

class SlaveManager {
public:
	SlaveManager();
	virtual ~SlaveManager();
	static void HandleMessage(MDSMessage &msg);
	//int SendToLogic();
	static void sendMessage(uint8_t funcCode,  uint8_t* data, int index);
private:

	RegTable<uint8_t,uint8_t> *holding_regs_table;
	RegTable<int,int> *input_regs_table;
	RegTable<bool,int> *coils_table;
	RegTable<bool,int> *discrete_table;
	//TransportManager* trans_manager;

};

#endif /* SLAVEMANAGER_H_ */
