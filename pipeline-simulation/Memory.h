//
// Created by RueianOneecom on 2014/6/1.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//
#include <vector>
#include <string>
#import <map>

using namespace std;

#ifndef __Memory_H_
#define __Memory_H_


class Memory {
public:
    Memory(map<string,int>);
    ~Memory();

    void loadMachineCode(string);
    string getInstruction(int);
    int getInstructionCount();
    int getDataMemory(string);
    void setDataMemory(string, int);

private:
    vector<string> _instructionMemory;
    map<string, int> _dataMemory;
};


#endif //__Memory_H_
