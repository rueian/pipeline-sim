//
// Created by RueianOneecom on 2014/5/31.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#include <iomanip>
#include <iostream>
#include "CPU.h"

using namespace std;

CPU::CPU(Registers& regs, Memory& ram)
: _registers(regs), _programCounter(0), _cycleCounter(1), _memory(ram) {
}

CPU::~CPU() {
}

void CPU::execute(string outFile) {
    ofstream fout;
    fout.open(outFile);
    while ( ! allInstructionDone()) {
        if (instructionFetchable())
            instructionFetch(_programCounter);

        _programCounter++;
        _registers.plRegNew["IF/ID"]["PC"] = to_string(_programCounter*4);

        for(int i = 0; i < _pipeline.size(); i++) {
            _pipeline[i]->goNextStage();
            if (_pipeline[i]->needStallPipeline())
                stallPipeline(i);
            else if (_pipeline[i]->needTakeBranch())
                flushInstruction(i);
        }

        _registers.updatePipeLineRegs();
        printStatus(fout);
        _cycleCounter++;
    }
    fout.close();
}

void CPU::printStatus(ofstream& fout) {
    fout << "CC " << _cycleCounter << ":" << endl << endl;
    fout << "Registers:" << endl;
    for (int i = 0 ; i < _registers.reg.size(); i++) {
        fout << "$" << i << ": " << setw(4) << left << _registers.reg[i];
        if (i != 0 && (i+1) % 3 == 0) fout << endl;
    }
    fout << endl;
    fout << "Data Memory:" << endl;
    for (auto v : {"0","4","8","12","16"})
        fout << setfill('0') << setw(2) << v << ":" << setfill(' ') << setw(6) << right << _memory.getDataMemory(v) << endl;
    fout << endl;
    map<string, vector<string>> pipelineRegistersIndex = {{"IF/ID", {"PC", "Instruction"}},{"ID/EX", {"ReadData1","ReadData2","sign_ext","Rs","Rt","Rd","Control signals"}},{"EX/MEM", {"ALUout","WriteData","Rt","Rd","Control signals"}},{"MEM/WB", {"ReadData","ALUout","Control signals"}}};
    for (string k : {"IF/ID","ID/EX","EX/MEM","MEM/WB"}) {
        fout << k << ":" << endl;
        for (auto v : pipelineRegistersIndex[k]) {
            if (!(k.compare("EX/MEM") == 0 && v == "Rt" && _registers.plReg[k][v] == "") && !(k.compare("EX/MEM") == 0 && v == "Rd" && _registers.plReg[k][v] == ""))
                fout << setw(17) << left << v << _registers.plReg[k][v] << endl;
        }
        if (k != "MEM/WB") fout << endl;
    }
    fout << "=================================================================" << endl;
}

bool CPU::instructionFetchable() {
    return _programCounter < _memory.getInstructionCount();
}

bool CPU::allInstructionDone() {
    return (!_pipeline.empty() && _pipeline.back()->isDone()) || _memory.getInstructionCount() == 0;
}

void CPU::instructionFetch(int pc) {
    Instruction* instruction = Instruction::instructionDecode(_memory.getInstruction(pc), &_memory, &_registers, &_programCounter);
    _pipeline.push_back(instruction);
}

void CPU::stallPipeline(int i) {
    if (_pipeline[i]->getCurrentStage() != "ID")
        i++;
    if (i >= _pipeline.size()) return;
    _pipeline[i]->becomeNop();
    _pipeline.pop_back();
    _registers.plRegNew["IF/ID"] = _registers.plReg["IF/ID"];
    _programCounter --;
    instructionFetch(_programCounter-1);
    cout << "Stall Pipeline" << endl;
}

void CPU::flushInstruction(int instructionIndex) {
    if (instructionIndex+1 >= _pipeline.size()) return;
    _pipeline[instructionIndex+1]->becomeNop();
    cout << "Flush Instruction" << endl;
}
