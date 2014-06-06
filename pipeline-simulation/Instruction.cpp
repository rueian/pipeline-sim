//
// Created by RueianOneecom on 2014/6/2.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#include <iostream>
#include "Instruction.h"

typedef Instruction* (*Func)(string);
map<string, Func> Instruction::_instructionMap = map<string, Func>();

void Instruction::goNextStage() {
    if (_currentStage == "BEGIN") {
        IFStage();
        _currentStage = "IF";
    } else if (_currentStage == "IF") {
        _nop ? nopIDStage() : IDStage();
        _currentStage = "ID";
    } else if (_currentStage == "ID") {
        _nop ? nopEXStage() : EXStage();
        _currentStage = "EX";
    } else if (_currentStage == "EX") {
        _nop ? nopMEMStage() : MEMStage();
        _currentStage = "MEM";
    } else if (_currentStage == "MEM") {
        _nop ? nopWBStage() : WBStage();
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
}

Instruction::Instruction(string machineCode) {
    _nop = false;
    _currentStage = "BEGIN";
    _machineCode  = machineCode;
}

bool Instruction::isDone() {
    return _currentStage == "DONE";
}

bool Instruction::needStallPipeline() {
    return false;
}

Instruction* Instruction::becomeNop() {
    _nop = true;
    return this;
}

void Instruction::nopIDStage() {
    _regs->plRegNew["ID/EX"] = {
            {"ReadData1", to_string((int)_regs->reg[_rs])},
            {"ReadData2", to_string((int)_regs->reg[_rt])},
            {"sign_ext", "0"},
            {"Rs", to_string(_rs)},
            {"Rt", to_string(_rt)},
            {"Rd", to_string(_rd)},
            {"Control Signals", "000000000"}
    };
}

void Instruction::nopEXStage() {
    _regs->plRegNew["EX/MEM"] = {
            {"ALUout", "0"},
            {"WriteData", "0"},
            {"Rt", ""},
            {"Rd", _regs->plReg["ID/EX"]["Rd"]},
            {"Control Signals", "00000"}
    };
}

void Instruction::nopMEMStage() {
    _regs->plRegNew["MEM/WB"] = {
            {"ReadData", "0"},
            {"ALUout", "0"},
            {"Rd", _regs->plReg["EX/MEM"]["Rd"]},
            {"Control Signals", "00"}
    };
}

void Instruction::nopWBStage() {

}

void Instruction::formatInstruction() {
    _opcode    = _machineCode.substr(0, 6);
    _rs        = Instruction::bitStringConvert(_machineCode.substr(6, 5));
    _rt        = Instruction::bitStringConvert(_machineCode.substr(11, 5));
    _rd        = Instruction::bitStringConvert(_machineCode.substr(16, 5));
    _shamt     = Instruction::bitStringConvert(_machineCode.substr(21, 5));
    _immediate = Instruction::bitStringConvert(_machineCode.substr(16, 16));
    _target    = Instruction::bitStringConvert(_machineCode.substr(6, 26));
    _funct     = _machineCode.substr(26, 6);
}
