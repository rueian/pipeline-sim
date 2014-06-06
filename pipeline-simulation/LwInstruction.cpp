//
// Created by RueianOneecom on 2014/6/3.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#include <iostream>
#include "LwInstruction.h"

LwInstruction::LwInstruction(string machineCode)
: ITypeInstruction(machineCode) {
    _controlSginal = "000101011";
    _stallFlag = false;
}

void LwInstruction::WBStage() {
    _regs->reg[_rt] = stoi(_regs->plReg["MEM/WB"]["ReadData"]);
}

void LwInstruction::EXStage() {
    ITypeInstruction::EXStage();
    cout << "ID/EX Rt: " << _regs->plReg["ID/EX"]["Rt"] << endl;
    cout << "IF/ID Rt: " << _regs->plReg["IF/ID"]["Rt"] << endl;
    cout << "IF/ID Rs: " << _regs->plReg["IF/ID"]["Rs"] << endl;
    _stallFlag = (_regs->plReg["ID/EX"]["Rt"] == _regs->plReg["IF/ID"]["Rt"] ||
                  _regs->plReg["ID/EX"]["Rt"] == _regs->plReg["IF/ID"]["Rs"]);
}

void LwInstruction::MEMStage() {
    ITypeInstruction::MEMStage();
    _stallFlag = false;
}

int LwInstruction::ALUResult(int data1, int data2) {
    return data1 + data2;
}

int LwInstruction::readDataMemory() {
    return _memory->getDataMemory(_regs->plReg["EX/MEM"]["ALUout"]);
}

bool LwInstruction::needStallPipeline() {
    return _stallFlag;
}

REGISTER_INSTRUCTION(100011, LwInstruction)
