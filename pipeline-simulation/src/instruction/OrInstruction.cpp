//
// Created by RueianOneecom on 2014/6/5.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#include "OrInstruction.h"

OrInstruction::OrInstruction(string machineCode)
: RTypeInstruction(machineCode) {
}

int OrInstruction::ALUResult(int data1, int data2) {
    return data1 | data2;
}

//REGISTER_INSTRUCTION(000000100101, OrInstruction)