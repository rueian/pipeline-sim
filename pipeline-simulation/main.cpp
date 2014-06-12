//
//  main.cpp
//  pipeline-simulation
//
//  Created by RueianOneecom on 2014/5/30.
//  Copyright (c) 2014 RueianOneecom. All rights reserved.
//

#define REGISTER_INSTRUCTION(code, class)\
    Instruction::registerInstruction(#code, [](string machineCode){ \
        return (Instruction*)new class(machineCode); \
    });

#include <iostream>
#include "CPU.h"
#include "AddInstruction.h"
#include "AndInstruction.h"
#include "BeqInstruction.h"
#include "BneInstruction.h"
#include "LwInstruction.h"
#include "OrInstruction.h"
#include "SubInstruction.h"
#include "SwInstruction.h"

using namespace std;

int main(int argc, const char * argv[])
{
    REGISTER_INSTRUCTION(000000100000, AddInstruction)
    REGISTER_INSTRUCTION(000000100100, AndInstruction)
    REGISTER_INSTRUCTION(000100, BeqInstruction)
    REGISTER_INSTRUCTION(000101, BneInstruction)
    REGISTER_INSTRUCTION(100011, LwInstruction)
    REGISTER_INSTRUCTION(000000100101, OrInstruction)
    REGISTER_INSTRUCTION(000000100010, SubInstruction)
    REGISTER_INSTRUCTION(001000, SwInstruction)

    map< string, string > IO = {
            {"General.txt", "genResult.txt"},
            {"Datahazard.txt", "dataResult.txt"},
            {"Lwhazard.txt", "loadResult.txt"},
            {"Branchazard.txt", "branchResult.txt"},
            {"Branchbonus.txt", "bonusResult.txt"},
    };
    for(auto& file : IO) {
        cout << file.first << ":" << endl;
        Memory ram({{"0", 1}, {"4", 2}, {"8", 3}, {"12", 4}, {"16", 5}});
        Registers registers({0, 1, 2, 3, 4, 1, 6, 7, 8});
        CPU cpu(registers, ram);

        // load from standard input
        string buffer, machineCode = "";
        ifstream fin(file.first);
        while(getline(fin, buffer)) {
            machineCode += buffer;
        }

        ram.loadMachineCode(machineCode);

        cpu.execute(file.second);
    }
    return 0;
}
