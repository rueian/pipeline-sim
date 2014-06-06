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
    virtual bool needTakeBranch() override;

protected:
    virtual int ALUResult(int, int);
    virtual int readDataMemory();
    virtual void IDStage() override;

private:
    bool needTakeBranch(int, int);
};


#endif //__BeqInstruction_H_
