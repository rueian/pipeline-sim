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
    virtual void WBStage();
    virtual int ALUResult(int data1, int data2);
    virtual int readDataMemory();

public:
    virtual bool needStallPipeline() override;
};


#endif //__LwInstruction_H_
