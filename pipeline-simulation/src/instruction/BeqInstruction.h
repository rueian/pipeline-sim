//
// Created by RueianOneecom on 2014/6/6.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//


#include "ITypeInstruction.h"

#ifndef __BeqInstruction_H_
#define __BeqInstruction_H_


class BeqInstruction : public ITypeInstruction {
public:
    BeqInstruction(string);
    virtual bool needStallPipeline() override;
    virtual bool needTakeBranch() override;

protected:
    virtual int ALUResult(int, int);
    virtual int readDataMemory();
    virtual void IDStage() override;
    virtual void EXStage() override;
    virtual void MEMStage() override;
    virtual bool isDone() override;

private:
    bool IDStallPipeline();
    bool needTakeBranch(int, int);
    bool hazardHappened(string, string);
    int getALUsrc(string);

};


#endif //__BeqInstruction_H_
