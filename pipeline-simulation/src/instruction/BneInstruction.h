//
// Created by RueianOneecom on 2014/6/7.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//


#include "BeqInstruction.h"

#ifndef __BneInstruction_H_
#define __BneInstruction_H_


class BneInstruction : public BeqInstruction {
public:
    BneInstruction(string);

protected:
    virtual int ALUResult(int i, int i1) override;
};


#endif //__BneInstruction_H_
