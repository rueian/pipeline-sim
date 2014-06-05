//
// Created by RueianOneecom on 2014/6/3.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

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

void ITypeInstruction::IDStage() {
    _regs->plReg["ID/EX"] = {
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

    _regs->plReg["EX/MEM"] = {
            {"ReadData2", _regs->plReg["ID/EX"]["ReadData2"]},
            {"ALUout", to_string(ALUResult(readData1, sign_ext))},
            {"WriteData", _controlSginal.substr(6, 1)},
            {"Rt", _regs->plReg["ID/EX"]["Rt"]},
            {"Rd", ""},
            {"Control Signals", _controlSginal.substr(4, 5)}
    };
}

void ITypeInstruction::MEMStage() {
    _regs->plReg["MEM/WB"] = {
            {"ReadData", to_string(readDataMemory())},
            {"ALUout", _regs->plReg["EX/MEM"]["ALUout"]},
            {"Control Signals", _controlSginal.substr(7, 2)}
    };
}

void ITypeInstruction::WBStage() {

}
