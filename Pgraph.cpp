//
// Created by khrotan on 23.03.2016.
//

#include "Pgraph.h"
#include <algorithm>
#include <wait.h>

bool Pgraph::isCompleted()
{
    for ( auto x : this->pipes )
    {
        if ( x.second->isCompleted() == false )
        {
            return false;
        }
    }
    return true;
}

void Pgraph::start()
{
    //FOR EVERY PROCESS
    for ( auto procMapEntry : this->processes )
    {
        //FORK
        //ARRANGE PIPES
        //CALL OTHER PATHS
        //EXECUTE

        auto proc = procMapEntry.second;

        pid_t pid1 = fork();

        if ( pid1 == 0 )
        {
            //THREE POSSIBILITIES

            //FROM STDIN TO A PROCESS
            if ( proc->inputPipe == "" )
            {
                //ARRANGE PIPES
                //FOR EVERY PIPE,
                for ( auto pip : this->pipes )
                {
                    auto pipID = pip.first;
                    //IF PIPE IS NOT IN PROCESS'S OUTPUT PIPES, THEN CLOSE
                    if ( std::find(proc->outputPipes.begin(), proc->outputPipes.end(), pipID) ==
                         proc->outputPipes.end())
                    {
                        for ( int i = 0 ; i < 3 ; i++ )
                        {
                            cout << "aaa" << endl;
                        }
                        Pipe* toBeClosedPipe = this->pipes[pipID];
                        toBeClosedPipe->terminate();
                    }
                }

                Pipe* firstOutputPipe = this->pipes.at(proc->outputPipes[0]);

                close(firstOutputPipe->fileDescriptor[0]);
                dup2(firstOutputPipe->fileDescriptor[1], 1);
                close(firstOutputPipe->fileDescriptor[1]);
                execvp(proc->toCharArray()[0], proc->toCharArray());

                //CALL OTHER PATHS
                for ( int i = 1 ; i < proc->outputPipes.size() ; i++ )
                {
                    auto pathProcIter = this->processes.equal_range( proc->outputPipes[i] );
                    //FORK
                    //fork()
                    pid_t pathFork = fork();

                    //TWO POSSIBILITIES

                    //BETWEEN TWO PROCESSES

                    //OR TO STDOUT
                }
            }
                // BETWEEN TWO PROCESSES
            else if ( proc->outputPipes.size() != 0 )
            {
                //ARRANGE PIPES
                //FOR EVERY PIPE,
                for ( auto pip : this->pipes )
                {
                    auto pipID = pip.first;
                    //IF PIPE IS NOT IN PROCESS'S OUTPUT PIPE OR IT IS NOT INPUT PIPE, THEN CLOSE
                    if ( std::find(proc->outputPipes.begin(), proc->outputPipes.end(), pipID) ==
                         proc->outputPipes.end() && proc->inputPipe != pipID )
                    {
                        cout << "hhh " << proc->command << endl;
                        Pipe* toBeClosedPipe = this->pipes[pipID];
                        toBeClosedPipe->terminate();
                    }
                }

                Pipe* inputPipe = this->pipes[proc->inputPipe];
                Pipe* firstOutputPipe = this->pipes[proc->outputPipes[0]];

                close(inputPipe->fileDescriptor[1]);
                dup2(inputPipe->fileDescriptor[0],0);
                close(inputPipe->fileDescriptor[0]);

                close(firstOutputPipe->fileDescriptor[0]);
                dup2(firstOutputPipe->fileDescriptor[1],1);
                close(firstOutputPipe->fileDescriptor[1]);
                execvp(proc->toCharArray()[0], proc->toCharArray());

                //CALL OTHER PATHS
                for ( int i = 1 ; i < proc->outputPipes.size() ; i++ )
                {

                }
            }
                // FROM A PROCESS TO STDOUT
            else
            {
                //ARRANGE PIPES
                //FOR EVERY PIPE,
                for ( auto pip : this->pipes )
                {
                    auto pipID = pip.first;
                    //IF PIPE IS NOT IN PROCESSES OUTPUT PIPE OR IS NOT INPUT PIPE, THEN CLOSE
                    if ( std::find(proc->outputPipes.begin(), proc->outputPipes.end(), pipID) ==
                         proc->outputPipes.end() && proc->inputPipe != pipID )
                    {
                        cout << "bbb " << proc->command << endl;
                        Pipe* toBeClosedPipe = this->pipes[pipID];
                        toBeClosedPipe->terminate();
                    }
                }

                Pipe* inputPipe = this->pipes[proc->inputPipe];

                close(inputPipe->fileDescriptor[1]);
                dup2(inputPipe->fileDescriptor[0], 0);
                close(inputPipe->fileDescriptor[0]);
                execvp(proc->toCharArray()[0], proc->toCharArray());
            }
            break;
        }
        else
        {

        }
    }

    for ( auto pip : this->pipes )
    {
        pip.second->terminate();
        cout << "I am terminated" << endl;
    }


    // TODO: CALCULATE HOW MANY TIMES WILL BE WAITED
    for ( int i = 0 ; i < this->processes.size() ; i++ )
    {
        int a;
        wait(&a);
    }


}
