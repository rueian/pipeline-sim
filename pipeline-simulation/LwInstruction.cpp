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
    _regs->plReg["ID/EX"] = {
            {"ReadData1", to_string(_regs->reg[_rs])},
            {"ReadData2", to_string(_regs->reg[_rt])},
            {"sign_ext", to_string(_immediate)},
            {"Rs", to_string(_rs)},
            {"Rt", to_string(_rt)},
            {"Rd", "0"},
            {"Control Signals", _controlSginal}
    };
}

void LwInstruction::EXStage() {
    int readData1 = stoi(_regs->plReg["ID/EX"]["ReadData1"]);
    int sign_ext = stoi(_regs->plReg["ID/EX"]["sign_ext"]);

    _regs->plReg["EX/MEM"] = {
            {"ALUout", to_string(readData1 + sign_ext)},
            {"WriteData", "0"},
            {"Rt", _regs->plReg["ID/EX"]["Rt"]},
            {"Rd", ""},
            {"Control Signals", _controlSginal.substr(4, 5)}
    };
}

void LwInstruction::MEMStage() {
    _regs->plReg["MEM/WB"] = {
            {"ReadData", to_string(_memory->getDataMemory(_regs->plReg["EX/MEM"]["ALUout"]))},
            {"ALUout", _regs->plReg["EX/MEM"]["ALUout"]},
            {"Control Signals", _controlSginal.substr(7, 2)}
    };
}

void LwInstruction::WBStage() {
    _regs->reg[_rt] = stoi(_regs->plReg["MEM/WB"]["ReadData"]);
}

REGISTER_INSTRUCTION(100011, LwInstruction)