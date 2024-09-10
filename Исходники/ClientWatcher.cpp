/*static*/
DECLCALLBACK(int) VirtualBox::ClientWatcher::worker(RTTHREAD hThreadSelf, void *pvUser)
{
    LogFlowFuncEnter();
    NOREF(hThreadSelf);

    VirtualBox::ClientWatcher *that = (VirtualBox::ClientWatcher *)pvUser;
    Assert(that);

    typedef std::vector<ComObjPtr<Machine> > MachineVector;
    typedef std::vector<ComObjPtr<SessionMachine> > SessionMachineVector;

    SessionMachineVector machines;
    MachineVector spawnedMachines;

    size_t cnt = 0;
    size_t cntSpawned = 0;

    VirtualBoxBase::initializeComForThread();

#if defined(RT_OS_WINDOWS)

    int vrc;

    /* Initialize all the subworker data. */
    that->maSubworkers[0].hThread = hThreadSelf;
    for (uint32_t iSubworker = 1; iSubworker < RT_ELEMENTS(that->maSubworkers); iSubworker++)
        that->maSubworkers[iSubworker].hThread    = NIL_RTTHREAD;
    for (uint32_t iSubworker = 0; iSubworker < RT_ELEMENTS(that->maSubworkers); iSubworker++)
    {
        that->maSubworkers[iSubworker].pSelf      = that;
        that->maSubworkers[iSubworker].iSubworker = iSubworker;
    }

    do
    {
        /* VirtualBox has been early uninitialized, terminate. */
        AutoCaller autoCaller(that->mVirtualBox);
        if (!autoCaller.isOk())
            break;

        bool fPidRace = false;          /* We poll if the PID of a spawning session hasn't been established yet.  */
        bool fRecentDeath = false;      /* We slowly poll if a session has recently been closed to do reaping. */
        for (;;)
        {
            /* release the caller to let uninit() ever proceed */
            autoCaller.release();

            /* Kick of the waiting. */
            uint32_t const cSubworkers = (that->mcWaitHandles + CW_MAX_HANDLES_PER_THREAD - 1) / CW_MAX_HANDLES_PER_THREAD;
            uint32_t const cMsWait     = fPidRace ? 500 : fRecentDeath ? 5000 : INFINITE;
            LogFlowFunc(("UPDATE: Waiting. %u handles, %u subworkers, %u ms wait\n", that->mcWaitHandles, cSubworkers, cMsWait));

            that->mcMsWait = cMsWait;
            ASMAtomicWriteU32(&that->mcActiveSubworkers, cSubworkers);
            RTThreadUserReset(hThreadSelf);

            for (uint32_t iSubworker = 1; iSubworker < cSubworkers; iSubworker++)
            {
                if (that->maSubworkers[iSubworker].hThread != NIL_RTTHREAD)
                {
                    vrc = RTThreadUserSignal(that->maSubworkers[iSubworker].hThread);
                    AssertLogRelMsg(RT_SUCCESS(vrc), ("RTThreadUserSignal -> %Rrc\n", vrc));
                }
                else
                {
                    vrc = RTThreadCreateF(&that->maSubworkers[iSubworker].hThread,
                                          VirtualBox::ClientWatcher::subworkerThread, &that->maSubworkers[iSubworker],
                                          _128K, RTTHREADTYPE_DEFAULT, RTTHREADFLAGS_WAITABLE, "Watcher%u", iSubworker);
                    AssertLogRelMsgStmt(RT_SUCCESS(vrc), ("%Rrc iSubworker=%u\n", vrc, iSubworker),
                                        that->maSubworkers[iSubworker].hThread = NIL_RTTHREAD);
                }
                if (RT_FAILURE(vrc))
                    that->subworkerWait(&that->maSubworkers[iSubworker], 1);
            }

            /* Wait ourselves. */
            that->subworkerWait(&that->maSubworkers[0], cMsWait);

            /* Make sure all waiters are done waiting. */
            BOOL fRc = SetEvent(that->mUpdateReq);
            Assert(fRc); NOREF(fRc);

            vrc = RTThreadUserWait(hThreadSelf, RT_INDEFINITE_WAIT);
            AssertLogRelMsg(RT_SUCCESS(vrc), ("RTThreadUserWait -> %Rrc\n", vrc));
            Assert(that->mcActiveSubworkers == 0);

            /* Consume pending update request before proceeding with processing the wait results. */
            fRc = ResetEvent(that->mUpdateReq);
            Assert(fRc);

            bool update = ASMAtomicXchgBool(&that->mfUpdateReq, false);
            if (update)
                LogFlowFunc(("UPDATE: Update request pending\n"));
            update |= fPidRace;

            /* Process the wait results. */
            autoCaller.add();
            if (!autoCaller.isOk())
                break;
            fRecentDeath = false;
            for (uint32_t iSubworker = 0; iSubworker < cSubworkers; iSubworker++)
            {
                DWORD dwWait = that->maSubworkers[iSubworker].dwWait;
                LogFlowFunc(("UPDATE: subworker #%u: dwWait=%#x\n", iSubworker, dwWait));
                if (   (dwWait > WAIT_OBJECT_0    && dwWait < WAIT_OBJECT_0    + CW_MAX_HANDLES_PER_THREAD)
                    || (dwWait > WAIT_ABANDONED_0 && dwWait < WAIT_ABANDONED_0 + CW_MAX_HANDLES_PER_THREAD) )
                {
                    uint32_t idxHandle = iSubworker * CW_MAX_HANDLES_PER_THREAD;
                    if (dwWait > WAIT_OBJECT_0    && dwWait < WAIT_OBJECT_0    + CW_MAX_HANDLES_PER_THREAD)
                        idxHandle += dwWait - WAIT_OBJECT_0;
                    else
                        idxHandle += dwWait - WAIT_ABANDONED_0;

                    uint32_t const idxMachine = idxHandle - (iSubworker + 1);
                    if (idxMachine < cnt)
                    {
                        /* Machine mutex is released or abandond due to client process termination. */
                        LogFlowFunc(("UPDATE: Calling i_checkForDeath on idxMachine=%u (idxHandle=%u) dwWait=%#x\n",
                                     idxMachine, idxHandle, dwWait));
                        fRecentDeath |= (machines[idxMachine])->i_checkForDeath();
                    }
                    else if (idxMachine < cnt + cntSpawned)
                    {
                        /* Spawned VM process has terminated normally. */
                        Assert(dwWait < WAIT_ABANDONED_0);
                        LogFlowFunc(("UPDATE: Calling i_checkForSpawnFailure on idxMachine=%u/%u idxHandle=%u dwWait=%#x\n",
                                     idxMachine, idxMachine - cnt, idxHandle, dwWait));
                        fRecentDeath |= (spawnedMachines[idxMachine - cnt])->i_checkForSpawnFailure();
                    }
                    else
                        AssertFailed();
                    update = true;
                }
                else
                    Assert(dwWait == WAIT_OBJECT_0 || dwWait == WAIT_TIMEOUT);
            }

            if (update)
            {
                LogFlowFunc(("UPDATE: Update pending (cnt=%u cntSpawned=%u)...\n", cnt, cntSpawned));

                /* close old process handles */
                that->winResetHandleArray((uint32_t)cntSpawned);

                // get reference to the machines list in VirtualBox
                VirtualBox::MachinesOList &allMachines = that->mVirtualBox->i_getMachinesList();

                // lock the machines list for reading
                AutoReadLock thatLock(allMachines.getLockHandle() COMMA_LOCKVAL_SRC_POS);

                /* obtain a new set of opened machines */
                cnt = 0;
                machines.clear();
                uint32_t idxHandle = 0;

                for (MachinesOList::iterator it = allMachines.begin();
                     it != allMachines.end();
                     ++it)
                {
                    AssertMsgBreak(idxHandle < CW_MAX_CLIENTS, ("CW_MAX_CLIENTS reached"));

                    ComObjPtr<SessionMachine> sm;
                    if ((*it)->i_isSessionOpenOrClosing(sm))
                    {
                        AutoCaller smCaller(sm);
                        if (smCaller.isOk())
                        {
                            AutoReadLock smLock(sm COMMA_LOCKVAL_SRC_POS);
                            Machine::ClientToken *ct = sm->i_getClientToken();
                            if (ct)
                            {
                                HANDLE ipcSem = ct->getToken();
                                machines.push_back(sm);
                                if (!(idxHandle % CW_MAX_HANDLES_PER_THREAD))
                                    idxHandle++;
                                that->mahWaitHandles[idxHandle++] = ipcSem;
                                ++cnt;
                            }
                        }
                    }
                }

                LogFlowFunc(("UPDATE: direct session count = %d\n", cnt));

                /* obtain a new set of spawned machines */
                fPidRace = false;
                cntSpawned = 0;
                spawnedMachines.clear();

                for (MachinesOList::iterator it = allMachines.begin();
                     it != allMachines.end();
                     ++it)
                {
                    AssertMsgBreak(idxHandle < CW_MAX_CLIENTS, ("CW_MAX_CLIENTS reached"));

                    if ((*it)->i_isSessionSpawning())
                    {
                        ULONG pid;
                        HRESULT hrc = (*it)->COMGETTER(SessionPID)(&pid);
                        if (SUCCEEDED(hrc))
                        {
                            if (pid != NIL_RTPROCESS)
                            {
                                HANDLE hProc = OpenProcess(SYNCHRONIZE, FALSE, pid);
                                AssertMsg(hProc != NULL, ("OpenProcess (pid=%d) failed with %d\n", pid, GetLastError()));
                                if (hProc != NULL)
                                {
                                    spawnedMachines.push_back(*it);
                                    if (!(idxHandle % CW_MAX_HANDLES_PER_THREAD))
                                        idxHandle++;
                                    that->mahWaitHandles[idxHandle++] = hProc;
                                    ++cntSpawned;
                                }
                            }
                            else
                                fPidRace = true;
                        }
                    }
                }

                LogFlowFunc(("UPDATE: spawned session count = %d\n", cntSpawned));

                /* Update mcWaitHandles and make sure there is at least one handle to wait on. */
                that->mcWaitHandles = RT_MAX(idxHandle, 1);

                // machines lock unwinds here
            }
            else
                LogFlowFunc(("UPDATE: No update pending.\n"));

            /* reap child processes */
            that->reapProcesses();

        } /* for ever (well, till autoCaller fails). */

    } while (0);

    /* Terminate subworker threads. */
    ASMAtomicWriteBool(&that->mfTerminate, true);
    for (uint32_t iSubworker = 1; iSubworker < RT_ELEMENTS(that->maSubworkers); iSubworker++)
        if (that->maSubworkers[iSubworker].hThread != NIL_RTTHREAD)
            RTThreadUserSignal(that->maSubworkers[iSubworker].hThread);
    for (uint32_t iSubworker = 1; iSubworker < RT_ELEMENTS(that->maSubworkers); iSubworker++)
        if (that->maSubworkers[iSubworker].hThread != NIL_RTTHREAD)
        {
            vrc = RTThreadWait(that->maSubworkers[iSubworker].hThread, RT_MS_1MIN, NULL /*prc*/);
            if (RT_SUCCESS(vrc))
                that->maSubworkers[iSubworker].hThread = NIL_RTTHREAD;
            else
                AssertLogRelMsgFailed(("RTThreadWait -> %Rrc\n", vrc));
        }

    /* close old process handles */
    that->winResetHandleArray((uint32_t)cntSpawned);

    /* release sets of machines if any */
    machines.clear();
    spawnedMachines.clear();

    ::CoUninitialize();

#elif defined(RT_OS_OS2)

    /* according to PMREF, 64 is the maximum for the muxwait list */
    SEMRECORD handles[64];

    HMUX muxSem = NULLHANDLE;

    do
    {
        AutoCaller autoCaller(that->mVirtualBox);
        /* VirtualBox has been early uninitialized, terminate */
        if (!autoCaller.isOk())
            break;

        for (;;)
        {
            /* release the caller to let uninit() ever proceed */
            autoCaller.release();

            int vrc = RTSemEventWait(that->mUpdateReq, 500);

            /* Restore the caller before using VirtualBox. If it fails, this
             * means VirtualBox is being uninitialized and we must terminate. */
            autoCaller.add();
            if (!autoCaller.isOk())
                break;

            bool update = false;
            bool updateSpawned = false;

            if (RT_SUCCESS(vrc))
            {
                /* update event is signaled */
                update = true;
                updateSpawned = true;
            }
            else
            {
                AssertMsg(vrc == VERR_TIMEOUT || vrc == VERR_INTERRUPTED,
                          ("RTSemEventWait returned %Rrc\n", vrc));

                /* are there any mutexes? */
                if (cnt > 0)
                {
                    /* figure out what's going on with machines */

                    unsigned long semId = 0;
                    APIRET arc = ::DosWaitMuxWaitSem(muxSem,
                                                     SEM_IMMEDIATE_RETURN, &semId);

                    if (arc == NO_ERROR)
                    {
                        /* machine mutex is normally released */
                        Assert(semId >= 0 && semId < cnt);
                        if (semId >= 0 && semId < cnt)
                        {
#if 0//def DEBUG
                            {
                                AutoReadLock machineLock(machines[semId] COMMA_LOCKVAL_SRC_POS);
                                LogFlowFunc(("released mutex: machine='%ls'\n",
                                             machines[semId]->name().raw()));
                            }
#endif
                            machines[semId]->i_checkForDeath();
                        }
                        update = true;
                    }
                    else if (arc == ERROR_SEM_OWNER_DIED)
                    {
                        /* machine mutex is abandoned due to client process
                         * termination; find which mutex is in the Owner Died
                         * state */
                        for (size_t i = 0; i < cnt; ++i)
                        {
                            PID pid; TID tid;
                            unsigned long reqCnt;
                            arc = DosQueryMutexSem((HMTX)handles[i].hsemCur, &pid, &tid, &reqCnt);
                            if (arc == ERROR_SEM_OWNER_DIED)
                            {
                                /* close the dead mutex as asked by PMREF */
                                ::DosCloseMutexSem((HMTX)handles[i].hsemCur);

                                Assert(i >= 0 && i < cnt);
                                if (i >= 0 && i < cnt)
                                {
#if 0//def DEBUG
                                    {
                                        AutoReadLock machineLock(machines[semId] COMMA_LOCKVAL_SRC_POS);
                                        LogFlowFunc(("mutex owner dead: machine='%ls'\n",
                                                     machines[i]->name().raw()));
                                    }
#endif
                                    machines[i]->i_checkForDeath();
                                }
                            }
                        }
                        update = true;
                    }
                    else
                        AssertMsg(arc == ERROR_INTERRUPT || arc == ERROR_TIMEOUT,
                                  ("DosWaitMuxWaitSem returned %d\n", arc));
                }

                /* are there any spawning sessions? */
                if (cntSpawned > 0)
                {
                    for (size_t i = 0; i < cntSpawned; ++i)
                        updateSpawned |= (spawnedMachines[i])->
                            i_checkForSpawnFailure();
                }
            }

            if (update || updateSpawned)
            {
                // get reference to the machines list in VirtualBox
                VirtualBox::MachinesOList &allMachines = that->mVirtualBox->i_getMachinesList();

                // lock the machines list for reading
                AutoReadLock thatLock(allMachines.getLockHandle() COMMA_LOCKVAL_SRC_POS);

                if (update)
                {
                    /* close the old muxsem */
                    if (muxSem != NULLHANDLE)
                        ::DosCloseMuxWaitSem(muxSem);

                    /* obtain a new set of opened machines */
                    cnt = 0;
                    machines.clear();

                    for (MachinesOList::iterator it = allMachines.begin();
                         it != allMachines.end(); ++it)
                    {
                        /// @todo handle situations with more than 64 objects
                        AssertMsg(cnt <= 64 /* according to PMREF */,
                                  ("maximum of 64 mutex semaphores reached (%d)",
                                   cnt));

                        ComObjPtr<SessionMachine> sm;
                        if ((*it)->i_isSessionOpenOrClosing(sm))
                        {
                            AutoCaller smCaller(sm);
                            if (smCaller.isOk())
                            {
                                AutoReadLock smLock(sm COMMA_LOCKVAL_SRC_POS);
                                ClientToken *ct = sm->i_getClientToken();
                                if (ct)
                                {
                                    HMTX ipcSem = ct->getToken();
                                    machines.push_back(sm);
                                    handles[cnt].hsemCur = (HSEM)ipcSem;
                                    handles[cnt].ulUser = cnt;
                                    ++cnt;
                                }
                            }
                        }
                    }

                    LogFlowFunc(("UPDATE: direct session count = %d\n", cnt));

                    if (cnt > 0)
                    {
                        /* create a new muxsem */
                        APIRET arc = ::DosCreateMuxWaitSem(NULL, &muxSem, cnt,
                                                           handles,
                                                           DCMW_WAIT_ANY);
                        AssertMsg(arc == NO_ERROR,
                                  ("DosCreateMuxWaitSem returned %d\n", arc));
                        NOREF(arc);
                    }
                }

                if (updateSpawned)
                {
                    /* obtain a new set of spawned machines */
                    spawnedMachines.clear();

                    for (MachinesOList::iterator it = allMachines.begin();
                         it != allMachines.end(); ++it)
                    {
                        if ((*it)->i_isSessionSpawning())
                            spawnedMachines.push_back(*it);
                    }

                    cntSpawned = spawnedMachines.size();
                    LogFlowFunc(("UPDATE: spawned session count = %d\n", cntSpawned));
                }
            }

            /* reap child processes */
            that->reapProcesses();

        } /* for ever (well, till autoCaller fails). */

    } while (0);

    /* close the muxsem */
    if (muxSem != NULLHANDLE)
        ::DosCloseMuxWaitSem(muxSem);

    /* release sets of machines if any */
    machines.clear();
    spawnedMachines.clear();

#elif defined(VBOX_WITH_SYS_V_IPC_SESSION_WATCHER)

    bool update = false;
    bool updateSpawned = false;

    do
    {
        AutoCaller autoCaller(that->mVirtualBox);
        if (!autoCaller.isOk())
            break;

        do
        {
            /* release the caller to let uninit() ever proceed */
            autoCaller.release();

            /* determine wait timeout adaptively: after updating information
             * relevant to the client watcher, check a few times more
             * frequently. This ensures good reaction time when the signalling
             * has to be done a bit before the actual change for technical
             * reasons, and saves CPU cycles when no activities are expected. */
            RTMSINTERVAL cMillies;
            {
                uint8_t uOld, uNew;
                do
                {
                    uOld = ASMAtomicUoReadU8(&that->mUpdateAdaptCtr);
                    uNew = uOld ? uOld - 1 : uOld;
                } while (!ASMAtomicCmpXchgU8(&that->mUpdateAdaptCtr, uNew, uOld));
                Assert(uOld <= RT_ELEMENTS(s_aUpdateTimeoutSteps) - 1);
                cMillies = s_aUpdateTimeoutSteps[uOld];
            }

            int rc = RTSemEventWait(that->mUpdateReq, cMillies);

            /*
             *  Restore the caller before using VirtualBox. If it fails, this
             *  means VirtualBox is being uninitialized and we must terminate.
             */
            autoCaller.add();
            if (!autoCaller.isOk())
                break;

            if (RT_SUCCESS(rc) || update || updateSpawned)
            {
                /* RT_SUCCESS(rc) means an update event is signaled */

                // get reference to the machines list in VirtualBox
                VirtualBox::MachinesOList &allMachines = that->mVirtualBox->i_getMachinesList();

                // lock the machines list for reading
                AutoReadLock thatLock(allMachines.getLockHandle() COMMA_LOCKVAL_SRC_POS);

                if (RT_SUCCESS(rc) || update)
                {
                    /* obtain a new set of opened machines */
                    machines.clear();

                    for (MachinesOList::iterator it = allMachines.begin();
                         it != allMachines.end();
                         ++it)
                    {
                        ComObjPtr<SessionMachine> sm;
                        if ((*it)->i_isSessionOpenOrClosing(sm))
                            machines.push_back(sm);
                    }

                    cnt = machines.size();
                    LogFlowFunc(("UPDATE: direct session count = %d\n", cnt));
                }

                if (RT_SUCCESS(rc) || updateSpawned)
                {
                    /* obtain a new set of spawned machines */
                    spawnedMachines.clear();

                    for (MachinesOList::iterator it = allMachines.begin();
                         it != allMachines.end();
                         ++it)
                    {
                        if ((*it)->i_isSessionSpawning())
                            spawnedMachines.push_back(*it);
                    }

                    cntSpawned = spawnedMachines.size();
                    LogFlowFunc(("UPDATE: spawned session count = %d\n", cntSpawned));
                }

                // machines lock unwinds here
            }

            update = false;
            for (size_t i = 0; i < cnt; ++i)
                update |= (machines[i])->i_checkForDeath();

            updateSpawned = false;
            for (size_t i = 0; i < cntSpawned; ++i)
                updateSpawned |= (spawnedMachines[i])->i_checkForSpawnFailure();

            /* reap child processes */
            that->reapProcesses();
        }
        while (true);
    }
    while (0);

    /* release sets of machines if any */
    machines.clear();
    spawnedMachines.clear();

#elif defined(VBOX_WITH_GENERIC_SESSION_WATCHER)

    bool updateSpawned = false;

    do
    {
        AutoCaller autoCaller(that->mVirtualBox);
        if (!autoCaller.isOk())
            break;

        do
        {
            /* release the caller to let uninit() ever proceed */
            autoCaller.release();

            /* determine wait timeout adaptively: after updating information
             * relevant to the client watcher, check a few times more
             * frequently. This ensures good reaction time when the signalling
             * has to be done a bit before the actual change for technical
             * reasons, and saves CPU cycles when no activities are expected. */
            RTMSINTERVAL cMillies;
            {
                uint8_t uOld, uNew;
                do
                {
                    uOld = ASMAtomicUoReadU8(&that->mUpdateAdaptCtr);
                    uNew = uOld ? (uint8_t)(uOld - 1) : uOld;
                } while (!ASMAtomicCmpXchgU8(&that->mUpdateAdaptCtr, uNew, uOld));
                Assert(uOld <= RT_ELEMENTS(s_aUpdateTimeoutSteps) - 1);
                cMillies = s_aUpdateTimeoutSteps[uOld];
            }

            int rc = RTSemEventWait(that->mUpdateReq, cMillies);

            /*
             *  Restore the caller before using VirtualBox. If it fails, this
             *  means VirtualBox is being uninitialized and we must terminate.
             */
            autoCaller.add();
            if (!autoCaller.isOk())
                break;

            /** @todo this quite big effort for catching machines in spawning
             * state which can't be caught by the token mechanism (as the token
             * can't be in the other process yet) could be eliminated if the
             * reaping is made smarter, having cross-reference information
             * from the pid to the corresponding machine object. Both cases do
             * more or less the same thing anyway. */
            if (RT_SUCCESS(rc) || updateSpawned)
            {
                /* RT_SUCCESS(rc) means an update event is signaled */

                // get reference to the machines list in VirtualBox
                VirtualBox::MachinesOList &allMachines = that->mVirtualBox->i_getMachinesList();

                // lock the machines list for reading
                AutoReadLock thatLock(allMachines.getLockHandle() COMMA_LOCKVAL_SRC_POS);

                if (RT_SUCCESS(rc) || updateSpawned)
                {
                    /* obtain a new set of spawned machines */
                    spawnedMachines.clear();

                    for (MachinesOList::iterator it = allMachines.begin();
                         it != allMachines.end();
                         ++it)
                    {
                        if ((*it)->i_isSessionSpawning())
                            spawnedMachines.push_back(*it);
                    }

                    cntSpawned = spawnedMachines.size();
                    LogFlowFunc(("UPDATE: spawned session count = %d\n", cntSpawned));
                }

                NOREF(cnt);
                // machines lock unwinds here
            }

            updateSpawned = false;
            for (size_t i = 0; i < cntSpawned; ++i)
                updateSpawned |= (spawnedMachines[i])->i_checkForSpawnFailure();

            /* reap child processes */
            that->reapProcesses();
        }
        while (true);
    }
    while (0);

    /* release sets of machines if any */
    machines.clear();
    spawnedMachines.clear();

#else
# error "Port me!"
#endif

    VirtualBoxBase::uninitializeComForThread();

    LogFlowFuncLeave();
    return 0;
}