//
// Created by RueianOneecom on 2014/6/3.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#include "RTypeInstruction.h"

#ifndef __AndInstruction_H_
#define __AndInstruction_H_


class AndInstruction : public RTypeInstruction {
public:
    AndInstruction(string);

protected:

    virtual int ALUResult(int data1, int data2);
};


#endif //__AndInstruction_H_
