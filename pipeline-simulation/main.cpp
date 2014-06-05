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
    Memory ram({{"0", 1}, {"2", 2}, {"4", 3}, {"8", 4}, {"16", 5}});
    Registers registers({0, 1, 2, 3, 4, 1, 6, 7, 8});
    CPU cpu(registers, ram);
//    load from standard input
//    std::string machineCode = "";
//    std::string buffer;
//    while(getline(cin, buffer)) {
//        machineCode += buffer;
//    }

// general.txt
//    string machineCode =
//            "10001101000000010000000000001000"
//            "00000000110001110001000000100010"
//            "00000000101001000001100000100100";

    string machineCode =
            "00000000001000110001000000100010"
            "00000000010001010010000000100100"
            "00000000100000100010000000100101";
    ram.loadMachineCode(machineCode);

    cpu.execute();

    return 0;
}
