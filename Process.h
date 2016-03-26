//
// Created by khrotan on 23.03.2016.
//

#ifndef OSHW1_PROCESS_H
#define OSHW1_PROCESS_H

#include <vector>
#include <string>

using namespace std;

class Pipe;

class Process
{
public:
    string inputPipe = "";
    vector<string> outputPipes;
    std::string command;
    vector<string> commandVector;
    char** toCharArray();
};


#endif //OSHW1_PROCESS_H
