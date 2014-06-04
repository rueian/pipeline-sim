//
// Created by RueianOneecom on 2014/6/3.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//
#include "iostream"
#include "AndInstruction.h"

AndInstruction::AndInstruction(string machineCode)
: RTypeInstruction(machineCode) {
}

int AndInstruction::ALUResoult(int data1, int data2) {
    return data1 & data2;
}

REGISTER_INSTRUCTION(000000100100, AndInstruction)

