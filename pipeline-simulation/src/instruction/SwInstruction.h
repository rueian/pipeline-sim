//
// Created by RueianOneecom on 2014/6/5.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//


#include "ITypeInstruction.h"

#ifndef __SwInstruction_H_
#define __SwInstruction_H_


class SwInstruction : public ITypeInstruction {
public:
    SwInstruction(string);

protected:
    virtual int ALUResult(int i, int i1);
    virtual void MEMStage();
    virtual int readDataMemory();
};


#endif //__SwInstruction_H_
