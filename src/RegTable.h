/*
 * RegTable.h
 *
 *  Created on: 30 Dec 2022
 *      Author: tasneem
 *
 *      this file contains five classes of registers table
 *      instead of using multiple file ..
 */

#ifndef REGTABLE_H_
#define REGTABLE_H_

#include <unordered_map>
#include <iostream>

using namespace std;

/************* ABSTRACT CLASS ************/
template<class K,class V>
class RegTable {
protected:
	unordered_map<K,V> map;
public:
    RegTable() = default;
    virtual ~RegTable() = default;

	// operation to handle the data structure - hash map
    virtual void addRegs(K key,V value){
        this->map.insert(make_pair(key,value));
    }
    virtual void updateRegs(K key,V value){
    	this->map[key]=value;
    }
    virtual V ReadReg(K key){
    	if(map.find(key)==map.end()){
    		//should not get here
    		return -1;
    	}
    	else{
    		return map[key];
    	}
    }

};

/************* DERIVED CLASSES  ************/

class HoldingRegisters : public RegTable<int,int>{
public:
        HoldingRegisters():RegTable<int, int>(){}
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
