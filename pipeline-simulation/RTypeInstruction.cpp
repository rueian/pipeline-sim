//
// Created by RueianOneecom on 2014/6/3.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#include "RTypeInstruction.h"

RTypeInstruction::RTypeInstruction(string machineCode)
: Instruction(machineCode) {
    _controlSginal = "110000010";
}

void RTypeInstruction::formatInstruction() {
    _opcode = _machineCode.substr(0, 6);
    _rs = Instruction::bitStringConvert(_machineCode.substr(6, 5));
    _rt = Instruction::bitStringConvert(_machineCode.substr(11, 5));
    _rd = Instruction::bitStringConvert(_machineCode.substr(16, 5));
    _shamt = Instruction::bitStringConvert(_machineCode.substr(21, 5));
    _funct = _machineCode.substr(26, 6);
}

RTypeInstruction::~RTypeInstruction() {
}

void RTypeInstruction::IDStage() {
    _regs->plReg["ID/EX"] = {
            {"ReadData1", to_string(_regs->reg[_rs])},
            {"ReadData2", to_string(_regs->reg[_rt])},
            {"sign_ext", "0"},
            {"Rs", to_string(_rs)},
            {"Rt", to_string(_rt)},
            {"Rd", to_string(_rd)},
            {"Control Signals", _controlSginal}
    };
}

void RTypeInstruction::EXStage() {
    int readData1 = stoi(_regs->plReg["ID/EX"]["ReadData1"]);
    int readData2 = stoi(_regs->plReg["ID/EX"]["ReadData2"]);

    _regs->plReg["EX/MEM"] = {
            {"ALUout", to_string(ALUResult(readData1, readData2))},
            {"WriteData", "0"},
            {"Rt", ""},
            {"Rd", _regs->plReg["ID/EX"]["Rd"]},
            {"Control Signals", _controlSginal.substr(4, 5)}
    };
}

void RTypeInstruction::MEMStage() {
    _regs->plReg["MEM/WB"] = {
            {"ReadData", "0"},
            {"ALUout", _regs->plReg["EX/MEM"]["ALUout"]},
            {"Rd", _regs->plReg["EX/MEM"]["Rd"]},
            {"Control Signals", _controlSginal.substr(7, 2)}
    };
}

void RTypeInstruction::WBStage() {
    _regs->reg[_rd] = stoi(_regs->plReg["MEM/WB"]["ALUout"]);
}
