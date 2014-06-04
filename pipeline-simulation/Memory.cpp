//
// Created by RueianOneecom on 2014/6/1.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//
#include <iostream>
#include <string>
#include <cmath>
#include "Memory.h"

#define INSTRUCTION_LENGTH 32

Memory::Memory(map<string, int> datas) {
    _dataMemory = datas;
}

Memory::~Memory() {
}

void Memory::loadMachineCode(string machineCode) {
    unsigned currentPostition = 0;
    while (currentPostition < machineCode.length()) {
        _instructionMemory.push_back(machineCode.substr(currentPostition, INSTRUCTION_LENGTH));
        currentPostition += INSTRUCTION_LENGTH;
    }
}

string Memory::getInstruction(int key) {
    return _instructionMemory[key];
}
int Memory::getDataMemory(string key) {
    return _dataMemory[key];
}
void Memory::setDataMemory(string key, int data) {
    _dataMemory[key] = data;
}

int Memory::getInstructionCount() {
    return (int)_instructionMemory.size();
}
