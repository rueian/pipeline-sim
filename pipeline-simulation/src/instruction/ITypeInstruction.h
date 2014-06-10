//
// Created by RueianOneecom on 2014/6/3.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//


#include "Instruction.h"

#ifndef __ITypeInstruction_H_
#define __ITypeInstruction_H_


class ITypeInstruction : public Instruction {
public:
    ITypeInstruction(string);
    ~ITypeInstruction();

protected:
    virtual void IDStage();
    virtual void EXStage();
    virtual void MEMStage();
    virtual void WBStage();
    virtual int readDataMemory() = 0;
};


#endif //__ITypeInstruction_H_
