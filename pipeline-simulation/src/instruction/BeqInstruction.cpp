//
// Created by RueianOneecom on 2014/6/6.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#include <iostream>
#include "BeqInstruction.h"

BeqInstruction::BeqInstruction(string machineCode)
: ITypeInstruction(machineCode) {
    _controlSignal = "001010000";
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

    _regs->plRegNew["ID/EX"] = {
            {"ReadData1", to_string(getALUsrc("Rs"))},
            {"ReadData2", to_string(getALUsrc("Rt"))},
            {"sign_ext", to_string(_immediate)},
            {"Rs", to_string(_rs)},
            {"Rt", to_string(_rt)},
            {"Rd", "0"},
            {"Control signals", _controlSignal}
    };
    if (needTakeBranch(getALUsrc("Rs"), getALUsrc("Rt")))
        *(_programCounter) = stoi(_regs->plReg["IF/ID"]["PC"])/4 + _immediate;
}

void BeqInstruction::EXStage() {
    _regs->plRegNew["EX/MEM"] = {
            {"ALUout", "0"},
            {"WriteData", "0"},
            {"Rt", "0"},
            {"Rd", ""},
            {"Control signals", "00000"}
    };
}

void BeqInstruction::MEMStage() {
    _regs->plRegNew["MEM/WB"] = {
            {"ReadData", "0"},
            {"ALUout", "0"},
            {"Rd", "0"},
            {"Control signals", "00"}
    };
}

bool BeqInstruction::IDStallPipeline() {
    return _regs->plReg["IF/ID"]["Rs"] == _regs->plReg["ID/EX"]["Rd"] ||
           _regs->plReg["IF/ID"]["Rt"] == _regs->plReg["ID/EX"]["Rd"];
}

bool BeqInstruction::needStallPipeline() {
    return _currentStage == "ID" && IDStallPipeline();
}

bool BeqInstruction::needTakeBranch() {
    return _currentStage == "ID" && needTakeBranch(getALUsrc("Rs"), getALUsrc("Rt"));
}

bool BeqInstruction::needTakeBranch(int data1, int data2) {
    return (bool)ALUResult(data1, data2);
}

bool BeqInstruction::hazardHappened(string reg, string src) {
    return _regs->plReg[reg]["Rd"] != "0" && _regs->plReg[reg]["Rd"] == _regs->plReg["IF/ID"][src];
}

int BeqInstruction::getALUsrc(string src) {
    if (hazardHappened("EX/MEM", src)) {
        cout << "Branch Hazard" << endl;
        return stoi(_regs->plReg["EX/MEM"]["ALUout"]);
    } else if (hazardHappened("MEM/WB", src)) {
        cout << "Branch Hazard" << endl;
        return stoi(_regs->plReg["MEM/WB"]["ALUout"]);
    }

    return  (int)(src == "Rs" ? _regs->reg[_rs] : _regs->reg[_rt]);
}

bool BeqInstruction::isDone() {
    return _currentStage == "MEM";
}

//REGISTER_INSTRUCTION(000100, BeqInstruction)

