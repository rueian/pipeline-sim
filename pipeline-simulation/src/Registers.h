//
// Created by RueianOneecom on 2014/6/4.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//
#include <map>
#include <string>
#include <vector>

using namespace std;

#ifndef __Registers_H_
#define __Registers_H_


class Registers {
public:
    Registers(vector<int>);
    void updatePipeLineRegs();

    vector<int> reg;
    map< string, map< string, string > > plReg;
    map< string, map< string, string > > plRegNew;

private:
    static map< string, map< string, string > > newPipelineRegs();
};


#endif //__Registers_H_
