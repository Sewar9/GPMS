/*
 * RegTable.h
 *
 *  Created on: 30 Dec 2022
 *      Author: tasneem
 */

#ifndef REGTABLE_H_
#define REGTABLE_H_

#include <unordered_map>
#include <iostream>

using namespace std;

 /////////////////////////////////*ABSTRACT CLASS *///////////////////////////////

template<class K,class V>
class RegTable {
protected:
	unordered_map<K,V> map;
public:
    RegTable() = default;
    virtual ~RegTable() = default;

	// operation to handle the data structure - hash map
    virtual void addPair(K key,V value){
        this->map.insert(make_pair(key,value));
    }
    virtual void updateValue(K key,V value){
    	this->map[key]=value;
    }
	virtual void erasePair(K key){
		this->map.erase(key);
	}


};
class HoldingRegisters : public RegTable<uint8_t,uint8_t>{
public:
        HoldingRegisters():RegTable<uint8_t, uint8_t>(){}
        ~HoldingRegisters() = default;

};
class CoilsRegisters : public RegTable<bool,int>{
public:
        CoilsRegisters():RegTable<bool, int>(){}
        ~CoilsRegisters() = default;

};

class DiscreteInput : public RegTable<bool,int>{
public:
	DiscreteInput():RegTable<bool, int>(){}
        ~DiscreteInput() = default;

};
class InputRegisters : public RegTable<int,int>{
public:
	InputRegisters():RegTable<int, int>(){}
        ~InputRegisters() = default;

};
#endif /* REGTABLE_H_ */
