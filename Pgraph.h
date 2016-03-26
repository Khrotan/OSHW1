//
// Created by khrotan on 23.03.2016.
//

#ifndef OSHW1_PIPEGRAPH_H
#define OSHW1_PIPEGRAPH_H

#include <map>
#include "Pipe.h"
#include "Process.h"

//Process.cpp Process.h Pipe.cpp Pipe.h Pgraph.cpp Pgraph.h
class Pgraph
{
public:
    void start();
    bool isCompleted();
    map<string, Pipe*> pipes;
    multimap<string, Process*> processes;
};

#endif //OSHW1_PIPEGRAPH_H
