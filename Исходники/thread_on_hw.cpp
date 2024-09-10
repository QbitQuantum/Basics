/** pause execution of this thread and call scheduler */
void Thread::yield() {
    if(!isSchedulingEnabled) return; // I really do not like This! but required

    /** Optimisation: Avoid unnecesary context swtichs: see Scheduler::schedule()  ***/
    long long timeNow = NOW(); 
    Thread* preselection = findNextToRun(timeNow); 
    if(preselection == getCurrentThread()) return;

    // schedule is required, The scheduler shall not repeate my computations: 
    Scheduler::preSelectedNextToRun = preselection; 
    Scheduler::preSelectedTime = timeNow;

    /* reschedule next timer interrupt to avoid interruptions of while switching */
    Timer::stop();
    __asmSaveContextAndCallScheduler();
}