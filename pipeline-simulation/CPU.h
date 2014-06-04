//
// Created by RueianOneecom on 2014/5/31.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//
#include <vector>
#include "Memory.h"
#include "Instruction.h"
#include "Registers.h"
using namespace std;

#ifndef __CPU_H_
#define __CPU_H_


class CPU {
public:
    CPU(Registers&, Memory&);
    ~CPU();
    void execute();
    void printStatus();

private:
    int _programCounter;
    int _cycleCounter;
    Registers& _registers;
    Memory& _memory;
    vector<Instruction*> _pipeline;

    bool instructionFetchable();
    bool allInstructionDone();
    void instructionFetch();
};


#endif //__CPU_H_
