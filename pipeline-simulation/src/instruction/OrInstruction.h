//
// Created by RueianOneecom on 2014/6/5.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//


#include "RTypeInstruction.h"

#ifndef __OrInstruction_H_
#define __OrInstruction_H_


class OrInstruction : public RTypeInstruction {
public:
    OrInstruction(string);

protected:

    virtual int ALUResult(int data1, int data2);

};


#endif //__OrInstruction_H_
