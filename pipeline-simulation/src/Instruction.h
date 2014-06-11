//
// Created by RueianOneecom on 2014/6/2.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

//#define REGISTER_INSTRUCTION(code, class)\
//__attribute__((constructor(103))) void register##class() { \
//    Instruction::registerInstruction(#code, [](string machineCode){ \
//        return (Instruction*)new class(machineCode); \
//    }); \
//}

#include <string>
#include <map>
#include "Memory.h"
#include "Registers.h"

using namespace std;

#ifndef __Instruction_H_
#define __Instruction_H_

class Instruction {
    typedef Instruction* (*Func)(string);
public:
    Instruction(string);

    string getCurrentStage();
    void goNextStage();
    virtual bool isDone();
    virtual bool needStallPipeline();
    virtual bool needTakeBranch();
    Instruction* becomeNop();
    Instruction* setMemory(Memory*);
    Instruction* setRegisters(Registers*);
    Instruction* setProgramCounter(int*);

    static int bitStringConvert(string);
    static void registerInstruction(string, Func);
    static Instruction* instructionDecode(string, Memory*, Registers*, int*);

protected:
    int _rs;
    int _rt;
    int _rd;
    int _shamt;
    int _immediate;

    bool _nop;
    int *_programCounter;
    Memory *_memory;
    Registers *_regs;
    string _currentStage;
    string _machineCode;
    string _controlSignal;

    virtual void IFStage();
    virtual void IDStage() = 0;
    virtual void EXStage() = 0;
    virtual void MEMStage() = 0;
    virtual void WBStage() = 0;
    virtual void formatInstruction();
    virtual int ALUResult(int, int) = 0;

    void nopIFStage();
    void nopIDStage();
    void nopEXStage();
    void nopMEMStage();
    void nopWBStage();

private:
    static map<string, Func> _instructionMap;

};


#endif //__Instruction_H_
