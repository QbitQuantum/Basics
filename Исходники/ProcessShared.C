/*virtual*/ SysStatus
ProcessShared<ALLOC>::waitForTermination()
{
    ProcessID tmppid = _SGETUVAL(getPID());
    BaseProcessRef tmpref;
    Scheduler::DeactivateSelf();
    while (_SUCCESS(DREFGOBJ(TheProcessSetRef)->
				getRefFromPID(tmppid, tmpref))) {
	// cprintf("waiting for \"%s\".\n", name.getString());
	Scheduler::DelayMicrosecs(100000);
    }
    Scheduler::ActivateSelf();

    return 0;
}