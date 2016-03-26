//
// Created by khrotan on 23.03.2016.
//

#include <cstring>
#include "Process.h"

char** Process::toCharArray()
{
    char** arr = new char* [this->commandVector.size() + 1];
    for ( size_t i = 0 ; i < this->commandVector.size() ; i++ )
    {
        arr[i] = new char[this->commandVector[i].size() + 1];
        strcpy(arr[i], this->commandVector[i].c_str());
    }
    arr[this->commandVector.size()] = NULL;
    return arr;
}

