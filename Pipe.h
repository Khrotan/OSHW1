//
// Created by khrotan on 23.03.2016.
//

#ifndef OSHW1_PIPE_H
#define OSHW1_PIPE_H

#include "Process.h"
#include <unistd.h>
#include <iostream>

using namespace std;

class Pipe
{
public:
    int fileDescriptor[2];
    vector<string> inputProcesses;
    string outputProcess = "";
    string ID;
    bool isCompleted();
    void terminate();

    Pipe()
    {
        pipe(fileDescriptor);
    }
};


#endif //OSHW1_PIPE_H
