//
// Created by RueianOneecom on 2014/6/3.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#include "Instruction.h"

#ifndef __RTypeInstruction_H_
#define __RTypeInstruction_H_


class RTypeInstruction : public Instruction {
public:
    RTypeInstruction(string);
    ~RTypeInstruction();

protected:
    string _opcode;
    int _rs;
    int _rt;
    int _rd;
    int _shamt;
    string _funct;

    void formatInstruction();

    virtual void IFStage() override;

    virtual void IDStage();
    virtual void EXStage();
    virtual void MEMStage();
    virtual void WBStage();

private:
    int getALUSrc(string);
    bool hazardHappened(string, string);
    bool lwHazardHappened(string);
};


#endif //__RTypeInstruction_H_
