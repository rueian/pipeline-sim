//
// Created by RueianOneecom on 2014/6/6.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#include "BeqInstruction.h"

BeqInstruction::BeqInstruction(string machineCode)
: ITypeInstruction(machineCode) {
    _controlSginal = "001010000";
}

int BeqInstruction::ALUResult(int data1, int data2) {
    return data1 && data2;
}

int BeqInstruction::readDataMemory() {
    return 0;
}

void BeqInstruction::IDStage() {
    ITypeInstruction::IDStage();

    if (needTakeBranch((int) _regs->reg[_rs], (int) _regs->reg[_rt]))
        _programCounter += _immediate;
}

bool BeqInstruction::needTakeBranch() {
    if (_currentStage == "ID")
        return needTakeBranch((int) _regs->reg[_rs], (int) _regs->reg[_rt]);
    return false;
}

bool BeqInstruction::needTakeBranch(int data1, int data2) {
    return (bool)ALUResult(data1, data2);
}

REGISTER_INSTRUCTION(000100, BeqInstruction)
