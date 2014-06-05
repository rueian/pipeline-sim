//
// Created by RueianOneecom on 2014/6/3.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#include "LwInstruction.h"

LwInstruction::LwInstruction(string machineCode)
: ITypeInstruction(machineCode) {
    _controlSginal = "000101011";
}

void LwInstruction::IDStage() {
    _regs->plReg["ID/EX"]["Rs"] = to_string(_rs);
    _regs->plReg["ID/EX"]["Rt"] = to_string(_rt);
    _regs->plReg["ID/EX"]["sign_ext"] = to_string(_immediate);
    _regs->plReg["ID/EX"]["Control Signals"] = _controlSginal;

    _regs->plReg["ID/EX"]["ReadData1"] = to_string((int)_regs->reg[_rs]);
    _regs->plReg["ID/EX"]["ReadData2"] = to_string((int)_regs->reg[_rt]);
}

void LwInstruction::EXStage() {
    int readData1 = stoi(_regs->plReg["ID/EX"]["ReadData1"]);
    int sign_ext = stoi(_regs->plReg["ID/EX"]["sign_ext"]);
    _regs->plReg["EX/MEM"]["ALUout"] = to_string(readData1 + sign_ext);
    _regs->plReg["EX/MEM"]["Rt"] = _regs->plReg["ID/EX"]["Rt"];
    _regs->plReg["EX/MEM"]["Rd"] = "";
    _regs->plReg["EX/MEM"]["Control Signals"] = _controlSginal.substr(4, 5);
}

void LwInstruction::MEMStage() {
    _regs->plReg["MEM/WB"]["ReadData"] = to_string(_memory->getDataMemory(_regs->plReg["EX/MEM"]["ALUout"]));
    _regs->plReg["MEM/WB"]["ALUout"] = _regs->plReg["EX/MEM"]["ALUout"];
    _regs->plReg["MEM/WB"]["Control Signals"] = _controlSginal.substr(7, 2);
}

void LwInstruction::WBStage() {
    _regs->reg[_rt] = stoi(_regs->plReg["MEM/WB"]["ReadData"]);
}

REGISTER_INSTRUCTION(100011, LwInstruction)