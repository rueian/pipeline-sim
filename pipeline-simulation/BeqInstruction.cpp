//
// Created by RueianOneecom on 2014/6/6.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#include <iostream>
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
    if (IDStallPipeline())
        return Instruction::nopIDStage();

    ITypeInstruction::IDStage();
    if (needTakeBranch(getALUsrc("Rs"), getALUsrc("Rt")))
        *(_programCounter) = stoi(_regs->plReg["IF/ID"]["PC"])/4 + _immediate;
}

void BeqInstruction::EXStage() {
    Instruction::nopEXStage();
}

void BeqInstruction::MEMStage() {
    Instruction::nopMEMStage();
}

bool BeqInstruction::IDStallPipeline() {
    return _regs->plReg["IF/ID"]["Rs"] == _regs->plReg["ID/EX"]["Rd"] ||
           _regs->plReg["IF/ID"]["Rt"] == _regs->plReg["ID/EX"]["Rd"];
}

bool BeqInstruction::needStallPipeline() {
    return _currentStage == "ID" && IDStallPipeline();
}

bool BeqInstruction::needTakeBranch() {
    if (_currentStage == "ID")
        return needTakeBranch(getALUsrc("Rs"), getALUsrc("Rt"));
    return false;
}

bool BeqInstruction::needTakeBranch(int data1, int data2) {
    return (bool)ALUResult(data1, data2);
}

bool BeqInstruction::hazardHappened(string reg, string src) {
    return _regs->plReg[reg]["Rd"] != "0" && _regs->plReg[reg]["Rd"] == _regs->plReg["IF/ID"][src];
}

int BeqInstruction::getALUsrc(string src) {
    if (hazardHappened("EX/MEM", src))
        return stoi(_regs->plReg["EX/MEM"]["ALUout"]);
    else if (hazardHappened("MEM/WB", src))
        return stoi(_regs->plReg["MEM/WB"]["ALUout"]);
    return  (int)(src == "Rs" ? _regs->reg[_rs] : _regs->reg[_rt]);
}

bool BeqInstruction::isDone() {
    return _currentStage == "MEM";
}

REGISTER_INSTRUCTION(000100, BeqInstruction)

