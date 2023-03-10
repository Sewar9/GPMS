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

	// copy all the registers from the logic layer
	for(auto i : this->logic_layer.regs_){
		this->holding_regs_table_.addRegs(i.first,i.second);
	}
	for(auto i : this->logic_layer.oneBit_regs){
		this->coils_table_.addRegs(i.first,i.second);
	}

	this->ReadValidAddFromSetting();

}
//***********************************************************//
SlaveManager::~SlaveManager() {
	// TODO Auto-generated destructor stub
}
//***********************************************************//

vector<uint16_t>  SlaveManager::HandleMessage(MDSMessage &msg){
	vector<uint16_t> response;
	response.clear();
	response.push_back(msg.getFunctionCode());

	switch(msg.getFunctionCode()){

		case READ_HOLD_REGISTER:
			{
				cout<<"Function code 3" <<endl;
				uint16_t starting_addr = msg.getFirst2Bytes();
				uint16_t quantity = msg.getSec2Bytes();

				// if(!ValidAddr(starting_addr,quantity)){ cout << "starting addres is not valid/out of range"<endl;};

				response.push_back(2*quantity);
				// go over all the block of registers and add them to the response
				for (int i=0; i<quantity; i++){
					uint16_t value = holding_regs_table_.ReadReg(starting_addr); //value of the register
					response.push_back(value);
					starting_addr++;

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
					logic_layer.updateRegs(reg,off); //update logic if it's relevant reg
				}

				cout<<"slave manager : reg "<< static_cast<unsigned int>(reg) <<" have been updated to : "<< static_cast<bool>(value)<<endl;
				break;

			}


		case READ_COIL :
			{
				cout<<" Function code 1" <<endl;
				uint16_t starting_addr = msg.getFirst2Bytes();
				uint16_t quantity = msg.getSec2Bytes();
				response.push_back(quantity);
				// go over all the block of registers and add them to the response
				for (int i=0; i<quantity; i++){
					bool value = coils_table_.ReadReg(starting_addr); //value of the register
					response.push_back(value);
					starting_addr++;
				}
				break;

			}
		case READ_INPUT_REGISTER:
		{
			cout<<"Function code 4" <<endl;
			uint16_t starting_addr = msg.getFirst2Bytes();
			uint16_t quantity = msg.getSec2Bytes();

			response.push_back(2*quantity);
			// go over all the block of registers and add them to the response
			for (int i=0; i<quantity; i++){
			uint16_t value = holding_regs_table_.ReadReg(starting_addr); //value of the register
			response.push_back(value);
			starting_addr++;

			}
			break;
		}

		default:
			cout<<"there is no handle to this function code yet!" <<endl;

	}

	cout<<"response is: ";
	for (auto i: response)
		cout << static_cast<unsigned int>(i)<<" ";
	cout<<endl;
	return response;
}
//***********************************************************//
// this function decodes the received message
uint8_t*  SlaveManager::sendMessage(uint8_t func_code, uint8_t* data){
// 1 Bytes = function_code--- 2 Bytes = starting_address/register--- 2 Bytes = quantity/value

	uint8_t high_first = data[8],low_first = data[9];
	uint8_t high_sec = data[10], low_sec = data[11];
	uint16_t left_two_bytes= (high_first << 8) | low_first;
	uint16_t right_two_bytes = (high_sec << 8) | low_sec;

	MDSMessage mess(func_code,left_two_bytes,right_two_bytes );

	vector<uint16_t> response = HandleMessage(mess);

//------------------------- handle response -------------------------

//copy the information bytes (data) - all the bytes before function code
	 uint8_t *resp = new uint8_t[4096];
	 for(int i=0 ; i< 256 ; i++){
		 resp[i] = data[i];
	 }


	int index = 8; // start to fill the response one byte after function code..
	for(unsigned int i = 1; i < response.size(); i++ ){
		uint16_t value = response[i];
		uint8_t partA = static_cast<uint8_t>((value & 0xFF00) >> 8);
		uint8_t partB = static_cast<uint8_t>(value & 0x00FF);
		if(i==1){
			//quantity should be saved in 1 byte
			resp[index] = partB;
			index+=1;
		}
		else{
			//the rest of fields should be saved in 2-Bytes (in holding/Input tables)
			resp[index] = partA;
			resp[index + 1] = partB;
			index+=2;
		}
	  }


	return resp;
}
//************************************************************//
void SlaveManager::updateHoldingReg(uint16_t reg,uint16_t value){
	holding_regs_table_.updateRegs(reg, value);
}
//************************************************************//
void SlaveManager::updateCoils(uint16_t reg,bool value){
	coils_table_.updateRegs(reg, value);
}
//***********************************************************//
void SlaveManager::ReadValidAddFromSetting(){
   std::ifstream ifs { R"(/home/tasneem/eclipse-workspace/server/src/setting.json)" };
    if ( !ifs.is_open() )
    {
        std::cerr << "Could not open file for reading!\n";
        return;
    }

    IStreamWrapper isw { ifs };

    Document doc {};
    doc.ParseStream( isw );
    assert(doc.IsObject());
    assert(doc.HasMember("Key"));
    assert(doc["Key"].IsString());
    const Value& a = doc["ranges"]["tables"];
    assert(a.IsArray());
    for (SizeType i = 0; i < a.Size(); i++) {
    	string table_name = a[i]["name"].GetString();
    	if(table_name.compare("holding") == 0 ){
            valid_range_holding[0] = a[i]["start"].GetInt();
            valid_range_holding[1] = a[i]["end"].GetInt();
    	}
    	else if(table_name.compare("coils") == 0 ){
            valid_range_coils[0] = a[i]["start"].GetInt();
            valid_range_coils[1] = a[i]["end"].GetInt();
    	}
    }
    StringBuffer buffer {};
    Writer<StringBuffer> writer { buffer };
    doc.Accept( writer );

    if ( doc.HasParseError() )
    {
        std::cout << "Error  : " << doc.GetParseError()  << '\n'
                  << "Offset : " << doc.GetErrorOffset() << '\n';
        return;
    }

}
//---------------------------------------------------
//uint8_t* SlaveManager::fixResponse(vector<uint8_t> old_resp,uint8_t* new_resp){
//	// this function is used only if function code = readCoils
//	uint8_t curr = 0,one_bit = 1;
//	uint8_t quan = old_resp[8],quan_in_bits;
//	int counter = 1;

//	if( quan % 8 == 0 ){
//		quan_in_bits = quan / 8;
//	}
//	else{
//		quan_in_bits = (quan / 8) + 1;
//	}
//
//}
//------------------------------------------------
