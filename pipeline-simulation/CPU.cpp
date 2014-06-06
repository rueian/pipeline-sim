//
// Created by RueianOneecom on 2014/5/31.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#include <iostream>
#import <iomanip>
#include "CPU.h"

using namespace std;

CPU::CPU(Registers& regs, Memory& ram)
: _registers(regs), _programCounter(0), _cycleCounter(1), _memory(ram) {
}

CPU::~CPU() {
}

void CPU::execute() {
    while ( ! allInstructionDone()) {
        if (instructionFetchable())
            instructionFetch();

        _programCounter++;
        _registers.plRegNew["IF/ID"]["PC"] = to_string(_programCounter*4);

        for(int i = 0; i < _pipeline.size(); i++) {
            _pipeline[i]->goNextStage();
            if (_pipeline[i]->needStallPipeline()) {
                _pipeline[i+1]->becomeNop();
                stallPipeline();
            }
        }

        _registers.updatePipeLineRegs();
        printStatus();
        _cycleCounter++;
    }
}

// Instruction* CPU::instructionDecode(string machineCode) {
//    string opcode = machineCode.substr(0, 6);
//
//    if (opcode == "100011") { // lw
//        cout << "lw" << endl;
//    } else if (opcode == "001000") { // sw
//        cout << "sw" << endl;
//    } else if (opcode == "000100") { // beq
//        cout << "beq" << endl;
//    } else if (opcode == "000000") { // R
//        string funct = machineCode.substr(26, 6);
//        if (funct == "100000") {
//            cout << "add" << endl;
//        } else if (funct == "100010") {
//            cout << "sub" << endl;
//        } else if (funct == "100100") {
//            cout << "and" << endl;
//        } else if (funct == "100101") {
//            cout << "or" << endl;
//        }
//    }
// }
void CPU::printStatus() {
    cout << "CC " << _cycleCounter << ":" << endl << endl;
    cout << "Registers:" << endl;
    for (int i = 0 ; i < _registers.reg.size(); i++) {
        cout << "$" << i << ": " << setw(4) << left << _registers.reg[i];
        if (i != 0 && (i+1) % 3 == 0) cout << endl;
    }
    cout << endl;
    cout << "Data Memory:" << endl;
    for (auto v : {"0","4","8","12","16"})
        cout << setfill('0') << setw(2) << v << ":" << setfill(' ') << setw(6) << right << _memory.getDataMemory(v) << endl;
    cout << endl;
    map<string, vector<string>> pipelineRegistersIndex = {{"IF/ID", {"PC", "Instruction"}},{"ID/EX", {"ReadData1","ReadData2","sign_ext","Rs","Rt","Rd","Control Signals"}},{"EX/MEM", {"ALUout","WriteData","Rt","Rd","Control Signals"}},{"MEM/WB", {"ReadData","ALUout","Control Signals"}}};
    for (auto k : {"IF/ID","ID/EX","EX/MEM","MEM/WB"}) {
        cout << k << ":" << endl;
        for (auto v : pipelineRegistersIndex[k]) {
            if (!(strcmp(k, "EX/MEM") == 0 && v == "Rt" && _registers.plReg[k][v] == "") && !(strcmp(k, "EX/MEM") == 0 && v == "Rd" && _registers.plReg[k][v] == ""))
                cout << setw(17) << left << v << _registers.plReg[k][v] << endl;
        }
        cout << endl;
    }
    cout << "=================================================================" << endl;
}

bool CPU::instructionFetchable() {
    return _programCounter < _memory.getInstructionCount();
}

bool CPU::allInstructionDone() {
    return !_pipeline.empty() && _pipeline.back()->isDone();
}

void CPU::instructionFetch(int pc) {
    Instruction* instruction = Instruction::instructionDecode(_memory.getInstruction(pc), &_memory, &_registers, &_programCounter);
    _pipeline.push_back(instruction);
}

void CPU::instructionFetch() {
    instructionFetch(_programCounter);
}

void CPU::stallPipeline() {
    _pipeline.pop_back();
    _registers.plRegNew["IF/ID"] = _registers.plReg["IF/ID"];
    _programCounter --;
    instructionFetch(_programCounter-1);
}

