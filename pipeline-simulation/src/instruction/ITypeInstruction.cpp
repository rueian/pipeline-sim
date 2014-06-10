//
// Created by RueianOneecom on 2014/6/3.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#include "ITypeInstruction.h"

ITypeInstruction::ITypeInstruction(string machineCode)
: Instruction(machineCode) {
}

ITypeInstruction::~ITypeInstruction() {

}

void ITypeInstruction::IFStage() {
    Instruction::IFStage();
    _regs->plRegNew["IF/ID"]["Rs"] = to_string(_rs);
    _regs->plRegNew["IF/ID"]["Rt"] = to_string(_rt);
}

void ITypeInstruction::IDStage() {
    _regs->plRegNew["ID/EX"] = {
            {"ReadData1", to_string((int)_regs->reg[_rs])},
            {"ReadData2", to_string((int)_regs->reg[_rt])},
            {"sign_ext", to_string(_immediate)},
            {"Rs", to_string(_rs)},
            {"Rt", to_string(_rt)},
            {"Rd", "0"},
            {"Control Signals", _controlSginal}
    };
}

void ITypeInstruction::EXStage() {
    int readData1 = stoi(_regs->plReg["ID/EX"]["ReadData1"]);
    int sign_ext = stoi(_regs->plReg["ID/EX"]["sign_ext"]);

    _regs->plRegNew["EX/MEM"] = {
            {"ReadData2", _regs->plReg["ID/EX"]["ReadData2"]},
            {"ALUout", to_string(ALUResult(readData1, sign_ext))},
            {"WriteData", _controlSginal.substr(6, 1)},
            {"Rt", _regs->plReg["ID/EX"]["Rt"]},
            {"Rd", ""},
            {"Control Signals", _controlSginal.substr(4, 5)}
    };
}

void ITypeInstruction::MEMStage() {
    _regs->plRegNew["MEM/WB"] = {
            {"ReadData", to_string(readDataMemory())},
            {"ALUout", _regs->plReg["EX/MEM"]["ALUout"]},
            {"Rd", ""},
            {"Control Signals", _controlSginal.substr(7, 2)}
    };
}

void ITypeInstruction::WBStage() {

}
