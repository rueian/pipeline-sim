//
// Created by RueianOneecom on 2014/6/3.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#include <iostream>
#include "ITypeInstruction.h"

ITypeInstruction::ITypeInstruction(string machineCode)
: Instruction(machineCode) {
}

void ITypeInstruction::formatInstruction() {
    _opcode = _machineCode.substr(0, 6);
    _rs = Instruction::bitStringConvert(_machineCode.substr(6, 5));
    _rt = Instruction::bitStringConvert(_machineCode.substr(11, 5));
    _immediate = Instruction::bitStringConvert(_machineCode.substr(16, 16));
}

ITypeInstruction::~ITypeInstruction() {

}
