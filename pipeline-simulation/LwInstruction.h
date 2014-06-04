//
// Created by RueianOneecom on 2014/6/3.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#include "ITypeInstruction.h"

#ifndef __LwInstruction_H_
#define __LwInstruction_H_


class LwInstruction : public ITypeInstruction {
public:
    LwInstruction(string);

protected:
    virtual void IDStage();

    virtual void EXStage();

    virtual void MEMStage();

    virtual void WBStage();
};


#endif //__LwInstruction_H_
