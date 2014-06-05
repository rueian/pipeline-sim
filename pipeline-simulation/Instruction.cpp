//
// Created by RueianOneecom on 2014/6/2.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#include "Instruction.h"

typedef Instruction* (*Func)(string);
map<string, Func> Instruction::_instructionMap = map<string, Func>();

void Instruction::goNextStage() {
    if (_currentStage == "BEGIN") {
        IFStage();
        _currentStage = "IF";
    } else if (_currentStage == "IF") {
        IDStage();
        _currentStage = "ID";
    } else if (_currentStage == "ID") {
        EXStage();
        _currentStage = "EX";
    } else if (_currentStage == "EX") {
        MEMStage();
        _currentStage = "MEM";
    } else if (_currentStage == "MEM") {
        WBStage();
        _currentStage = "DONE";
    }
}

void Instruction::registerInstruction(string code, Func func) {
    _instructionMap[code] = func;
}

Instruction* Instruction::instructionDecode(string machineCode, Memory *memory, Registers *registers, int *programCounter) {
    string opcode = machineCode.substr(0, 6);
    string funct = machineCode.substr(26, 6);
    Instruction* instruction;
    if (_instructionMap.find(opcode) != _instructionMap.end())
        instruction = _instructionMap[opcode](machineCode);
    else
        instruction = _instructionMap[opcode + funct](machineCode);
    return instruction->setMemory(memory)->setRegisters(registers)->setProgramCounter(programCounter);
}

Instruction* Instruction::setMemory(Memory *memory) {
    _memory = memory;
    return this;
}

Instruction* Instruction::setRegisters(Registers *registers) {
    _regs = registers;
    return this;
}

Instruction* Instruction::setProgramCounter(int *programCounter) {
    _programCounter = programCounter;
    return this;
}

string Instruction::getCurrentStage() {
    return _currentStage;
}

int Instruction::bitStringConvert(string bitString) {
    int num = 0;
    for (char c : bitString)
        num = (num << 1) |  // Shift the current set of bits to the left one bit
                (c - '0');    // Add in the current bit via a bitwise-or
    return num;
}

void Instruction::IFStage() {
    formatInstruction();
    _regs->plRegNew["IF/ID"]["Instruction"] = _machineCode;
    _regs->plRegNew["IF/ID"]["PC"] = to_string(*_programCounter*4);
}

Instruction::Instruction(string machineCode) {
    _currentStage = "BEGIN";
    _machineCode  = machineCode;
}

bool Instruction::isDone() {
    return _currentStage == "DONE";
}
