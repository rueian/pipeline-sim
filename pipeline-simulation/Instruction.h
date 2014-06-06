//
// Created by RueianOneecom on 2014/6/2.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#define REGISTER_INSTRUCTION(code, class)\
__attribute__((constructor)) void register##class() { \
    Instruction::registerInstruction(#code, [](string machineCode){ \
        return (Instruction*)new class(machineCode); \
    }); \
}

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
    bool isDone();
    virtual bool needStallPipeline();
    Instruction* becomeNop();
    Instruction* setMemory(Memory*);
    Instruction* setRegisters(Registers*);
    Instruction* setProgramCounter(int*);

    static void registerInstruction(string, Func);
    static int bitStringConvert(string);
    static Instruction* instructionDecode(string, Memory*, Registers*, int*);

protected:
    string _opcode;
    int _rs;
    int _rt;
    int _rd;
    int _shamt;
    int _immediate;
    int _target;
    string _funct;

    virtual void IFStage();
    virtual void formatInstruction();
    virtual void IDStage() = 0;
    virtual void EXStage() = 0;
    virtual void MEMStage() = 0;
    virtual void WBStage() = 0;
    virtual int ALUResult(int, int) = 0;

    void nopIDStage();
    void nopEXStage();
    void nopMEMStage();
    void nopWBStage();

    Memory *_memory;
    Registers *_regs;
    int *_programCounter;
    string _currentStage;
    string _machineCode;
    string _controlSginal;
    bool _nop;

private:
    static map<string, Func> _instructionMap;

};


#endif //__Instruction_H_
