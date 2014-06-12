//
// Created by RueianOneecom on 2014/6/4.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#include "Registers.h"

Registers::Registers(vector<int> regs) {
    reg = regs;
    plReg = Registers::newPipelineRegs();
    plRegNew = Registers::newPipelineRegs();

}

void Registers::updatePipeLineRegs() {
    plReg = plRegNew;
    plRegNew = Registers::newPipelineRegs();
}

map<string, map<string, string> > Registers::newPipelineRegs() {
    return {
            {"IF/ID", {
                    {"PC", ""},
                    {"Rs", ""},
                    {"Rt", ""},
                    {"Instruction", "00000000000000000000000000000000"}
            }},
            {"ID/EX", {
                    {"ReadData1", "0"},
                    {"ReadData2", "0"},
                    {"sign_ext", "0"},
                    {"Rs", "0"},
                    {"Rt", "0"},
                    {"Rd", "0"},
                    {"Control signals", "000000000"}
            }},
            {"EX/MEM", {
                    {"ALUout", "0"},
                    {"WriteData", "0"},
                    {"Rt", "0"},
                    {"Rd", ""},
                    {"Control signals", "00000"}
            }},
            {"MEM/WB", {
                    {"ReadData", "0"},
                    {"ALUout", "0"},
                    {"Rd", ""},
                    {"Control signals", "00"}
            }}
    };
}
