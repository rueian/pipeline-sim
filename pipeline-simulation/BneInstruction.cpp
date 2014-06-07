//
// Created by RueianOneecom on 2014/6/7.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#include "BneInstruction.h"

int BneInstruction::ALUResult(int i, int i1) {
    return i != i1;
}

BneInstruction::BneInstruction(string string1)
: BeqInstruction(string1) {
}

REGISTER_INSTRUCTION(000101, BneInstruction);

