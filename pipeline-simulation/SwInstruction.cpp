//
// Created by RueianOneecom on 2014/6/5.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#include "SwInstruction.h"

SwInstruction::SwInstruction(string machineCode)
:ITypeInstruction(machineCode) {
    _controlSginal = "000100100";
}

int SwInstruction::ALUResult(int data1, int data2) {
    return data1 + data2;
}

int SwInstruction::readDataMemory() {
    return 0;
}

void SwInstruction::MEMStage() {
    ITypeInstruction::MEMStage();

    _memory->setDataMemory(_regs->plReg["EX/MEM"]["ALUout"], stoi(_regs->plReg["EX/MEM"]["ReadData2"]));
}

//REGISTER_INSTRUCTION(001000, SwInstruction)