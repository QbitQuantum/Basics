void Scheduler::RRAlgorithm::run() {
    vector<Process*>* allProcesses = scheduler->allProcesses;
    vector<Process*>* movedToReadyState = scheduler->movedToReadyState;
    vector<Process*>::iterator it = scheduler->it;

    queue<Process*>* readyQ = scheduler->readyQ;

    //set the callbacks for all processes
    for(it = allProcesses->begin(); it != allProcesses->end(); it++) {
        (*it)->setOnArrivedCallback(new OnProcessArrivedCallback(scheduler));
        (*it)->setOnReadyCallback(new OnProcessReadyCallback(scheduler));
        (*it)->setOnRunningCallback(new OnProcessRunningCallback(scheduler));
        (*it)->setOnBlockedCallback(new OnProcessBlockedCallback(scheduler));
        (*it)->setOnFinishedCallback(new OnProcessFinishedCallback(scheduler));
    }

    //loop while there are still unfinished processes
    while(scheduler->getFinishedProcessesCount() != scheduler->getProcessesCount()) {
        //if the readyQ isn't empty
        if(!readyQ->empty()) {
            Process* proc = readyQ->front();
            //and the process at top isn't running
            //start running it and set the quantum data
            if(!proc->isRunning()) {
                proc->setIsRunning();
                runningProcessId = proc->getProcessId();
                runningProcessQuantum = quantum;
            }
            //otherwise check if the quantum is 0
            else {
                if(proc->getProcessId() == runningProcessId) {
                    //if it is remove the process from the top
                    //and push it to the back and set the next
                    //process to run (could be the previous
                    //process if the readyQ is empty)
                    if(runningProcessQuantum == 0) {
                        readyQ->pop();
                        readyQ->push(proc);
                        proc->setIsReady();
                        proc = readyQ->front();
                        proc->setIsRunning();
                    }
                }
            }
        }

        cout << scheduler->getCurrentCycle() << " ";
        //run a cycle for each process
        for(it = allProcesses->begin(); it != allProcesses->end(); it++) {
            (*it)->cycle(scheduler->getCurrentCycle());
        }
        cout << endl;

        //if there are processes ready to be moved to the readyQ
        if(!movedToReadyState->empty()) {
            //sort the list so that lower ids are higher
            sort(movedToReadyState->begin(), movedToReadyState->end(), LowerProcessIdPriority());

            //push all of these processes to the readyQ
            for(it = movedToReadyState->begin(); it != movedToReadyState->end(); it++) {
                readyQ->push((*it));
            }

            //clear the list of processes waiting to be moved to the readyQ
            movedToReadyState->clear();
        }

        //increments the cycle count in the scheduler
        scheduler->incrementCycle();
        if(processRemovedThisCycle) {
            processRemovedThisCycle = false;
        }
        if(processBlockedThisCycle) {
            processBlockedThisCycle = false;
        }

        //if there's a running process decrement the quantum
        //we could probably move this to the running callback
        if(runningProcessId != -1) {
            runningProcessQuantum--;
        }
    }
    cout << endl;
}