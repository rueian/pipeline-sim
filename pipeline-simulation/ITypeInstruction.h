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
    string _opcode;
    int _rs;
    int _rt;
    int _immediate;

    void formatInstruction();
    virtual void IDStage();
    virtual void EXStage();
    virtual void MEMStage();
    virtual void WBStage();
    virtual int readDataMemory() = 0;

    virtual void IFStage() override;
};


#endif //__ITypeInstruction_H_
