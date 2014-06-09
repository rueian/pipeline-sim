//
// Created by RueianOneecom on 2014/6/4.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#include "AddInstruction.h"

AddInstruction::AddInstruction(string machineCode)
: RTypeInstruction(machineCode) {
}

int AddInstruction::ALUResult(int data1, int data2) {
    return data1 + data2;
}

REGISTER_INSTRUCTION(000000100000, AddInstruction)