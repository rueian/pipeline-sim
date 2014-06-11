//
// Created by RueianOneecom on 2014/6/3.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#include <iostream>
#include "RTypeInstruction.h"

RTypeInstruction::RTypeInstruction(string machineCode)
: Instruction(machineCode) {
    _controlSignal = "110000010";
}

RTypeInstruction::~RTypeInstruction() {
}

void RTypeInstruction::IDStage() {
    _regs->plRegNew["ID/EX"] = {
            {"ReadData1", to_string((int)_regs->reg[_rs])},
            {"ReadData2", to_string((int)_regs->reg[_rt])},
            {"sign_ext", "0"},
            {"Rs", to_string(_rs)},
            {"Rt", to_string(_rt)},
            {"Rd", to_string(_rd)},
            {"Control signals", _controlSignal}
    };
}

void RTypeInstruction::EXStage() {
    _regs->plRegNew["EX/MEM"] = {
            {"ALUout", to_string(ALUResult(getALUSrc("Rs"), getALUSrc("Rt")))},
            {"WriteData", "0"},
            {"Rt", ""},
            {"Rd", _regs->plReg["ID/EX"]["Rd"]},
            {"Control signals", _controlSignal.substr(4, 5)}
    };
}

void RTypeInstruction::MEMStage() {
    _regs->plRegNew["MEM/WB"] = {
            {"ReadData", "0"},
            {"ALUout", _regs->plReg["EX/MEM"]["ALUout"]},
            {"Rd", _regs->plReg["EX/MEM"]["Rd"]},
            {"Control signals", _controlSignal.substr(7, 2)}
    };
}

void RTypeInstruction::WBStage() {
    _regs->reg[_rd] = stoi(_regs->plReg["MEM/WB"]["ALUout"]);
}

int RTypeInstruction::getALUSrc(string src) {
    if (hazardHappened("EX/MEM", src)) {
        cout << "Data Hazard" << endl;
        return stoi(_regs->plReg["EX/MEM"]["ALUout"]);
    } else if (lwHazardHappened(src)) {
        cout << "Lw   Hazard" << endl;
        return stoi(_regs->plReg["MEM/WB"]["ReadData"]);
    } else if (hazardHappened("MEM/WB", src)) {
        cout << "Data Hazard" << endl;
        return stoi(_regs->plReg["MEM/WB"]["ALUout"]);
    }

    string destination = (src == "Rs" ? "ReadData1" : "ReadData2");
    return stoi(_regs->plReg["ID/EX"][destination]);
}

bool RTypeInstruction::hazardHappened(string reg, string src) {
    return _regs->plReg[reg]["Rd"] != "0" && _regs->plReg[reg]["Rd"] == _regs->plReg["ID/EX"][src];
}

bool RTypeInstruction::lwHazardHappened(string src) {
    return _regs->plReg["MEM/WB"]["Rt"] != "0" && _regs->plReg["MEM/WB"]["Rt"] == _regs->plReg["ID/EX"][src];
}
