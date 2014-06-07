//
//  main.cpp
//  pipeline-simulation
//
//  Created by RueianOneecom on 2014/5/30.
//  Copyright (c) 2014 RueianOneecom. All rights reserved.
//

#include "CPU.h"

using namespace std;

int main(int argc, const char * argv[])
{
    map< string, string > IO = {
            {"General.txt", "genResult.txt"},
            {"Datahazard.txt", "dataResult.txt"},
            {"Lwhazard.txt", "loadResult.txt"},
            {"Branchazard.txt", "branchResult.txt"},
            {"Branchbonus.txt", "bonusResult.txt"},
    };
    for(auto& file : IO) {
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
