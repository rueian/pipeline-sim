//
// Created by RueianOneecom on 2014/6/3.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#include "LwInstruction.h"

LwInstruction::LwInstruction(string machineCode)
: ITypeInstruction(machineCode) {
    _controlSignal = "000101011";
}

void LwInstruction::WBStage() {
    _regs->reg[_rt] = stoi(_regs->plReg["MEM/WB"]["ReadData"]);
}

int LwInstruction::ALUResult(int data1, int data2) {
    return data1 + data2;
}

int LwInstruction::readDataMemory() {
    return _memory->getDataMemory(_regs->plReg["EX/MEM"]["ALUout"]);
}

bool LwInstruction::needStallPipeline() {
    if (_currentStage == "EX")
        return _regs->plReg["ID/EX"]["Rt"] == _regs->plReg["IF/ID"]["Rt"] ||
               _regs->plReg["ID/EX"]["Rt"] == _regs->plReg["IF/ID"]["Rs"];
    return false;
}

REGISTER_INSTRUCTION(100011, LwInstruction)
