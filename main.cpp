#include <iostream>
#include <vector>
#include <sstream>
#include "Pgraph.h"

using namespace std;

int main()
{
    string         line, dummyCommand, dummy, predecessorId;
    vector<string> commandVector;
    vector<string> successorPipes;
    Process* dummyProcess;
    Pipe   * dummyPipe;

    Pgraph pgraph;

    while ( getline(cin, line))
    {
        // INPUT PROCESSING
        istringstream iss;
        iss.str(line);
        iss >> dummy;
        if ( dummy == "quit" )
        {
            break;
        }
        //[<arguments>]
        while ( dummy != "<|" && dummy != ">|" )
        {
            commandVector.push_back(dummy);
            iss >> dummy;
        }

        for ( auto x : commandVector )
        {
            dummyCommand += x + " ";
        }

        // [<| <pipe_id>]
        if ( dummy == "<|" )
        {
            iss >> dummy;
            predecessorId = dummy;
            iss >> dummy;
        }

        // [>| <pipe_ids>]
        while ( iss >> dummy )
        {
            successorPipes.push_back(dummy);
        }
        //input has been taken

        // CREATION of newcomers
        // if there is [<| <pipe_id>]
        if ( predecessorId != "" && pgraph.pipes.find(predecessorId) == pgraph.pipes.end())
        {
            dummyPipe = new Pipe;
            dummyPipe->ID = predecessorId;
            pgraph.pipes.insert(make_pair(predecessorId, dummyPipe));
        }

        // if there is [>| <pipe_ids>]
        for ( auto pip : successorPipes )
        {
            if ( pgraph.pipes.find(pip) == pgraph.pipes.end())
            {
                dummyPipe = new Pipe;
                dummyPipe->ID = pip;
                pgraph.pipes.insert(make_pair(pip, dummyPipe));
            }
        }

        // there will always be a process
        dummyProcess = new Process;
        dummyProcess->command = dummyCommand;
        dummyProcess->commandVector = commandVector;
        pgraph.processes.insert(make_pair(dummyCommand, dummyProcess));
        //creation completed

        // ARRANGING connection between pipes and the process
        //predecessor -> process
        if ( predecessorId != "")
        {
            (*(pgraph.pipes.find(predecessorId))).second->outputProcess = dummyCommand;
            dummyProcess->inputPipe = predecessorId;
        }
        //process -> successor
        for (auto pip: successorPipes) {
            (*pgraph.pipes.find(pip)).second->inputProcesses.push_back(dummyCommand);
            dummyProcess->outputPipes.push_back(pip);
        }

        //WIPEOUT
        commandVector.clear();
        successorPipes.clear();
        dummyProcess = NULL;
        dummyPipe = NULL;
        predecessorId = "";
        dummyCommand = "";
        dummy = "";
        line = "";

        if ( pgraph.isCompleted() )
        {
            //START THE ACTION
            pgraph.start();
        }
    }
    cout << "Hello, World!" << endl;
    return 0;
}