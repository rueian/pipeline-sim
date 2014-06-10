//
// Created by RueianOneecom on 2014/6/3.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#include "RTypeInstruction.h"

#ifndef __SubInstruction_H_
#define __SubInstruction_H_


class SubInstruction : public RTypeInstruction {
public:
    SubInstruction(string);

protected:

    virtual int ALUResult(int data1, int data2);
};


#endif //__SubInstruction_H_
