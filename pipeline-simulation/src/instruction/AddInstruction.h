//
// Created by RueianOneecom on 2014/6/4.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//


#include "RTypeInstruction.h"

#ifndef __AddInstruction_H_
#define __AddInstruction_H_


class AddInstruction : public RTypeInstruction {
public:
    AddInstruction(string);

protected:

    virtual int ALUResult(int data1, int data2);

};


#endif //__AddInstruction_H_
