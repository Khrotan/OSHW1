//
// Created by khrotan on 23.03.2016.
//

#include "Pipe.h"


bool Pipe::isCompleted()
{
    return (this->inputProcesses.size() != 0 && this->outputProcess != "");
}

void Pipe::terminate()
{
    close(this->fileDescriptor[0]);
    close(this->fileDescriptor[1]);
}