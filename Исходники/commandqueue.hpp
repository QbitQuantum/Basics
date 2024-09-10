    void doSizedSend(size_t size, Args...args)
    {
        ULONG head = mHead.load();
        while(1)
        {
            ULONG rem_size = sQueueSize - head;
            if(rem_size < size)
            {
                if(rem_size >= sizeof(CommandSkip))
                {
                    doSizedSend<CommandSkip>(rem_size, rem_size);
                    head = mHead.load();
                    rem_size = sQueueSize - head;
                }
                else do {
                    doSizedSend<CommandNoOp>(sizeof(CommandNoOp));
                    head = mHead.load();
                    rem_size = sQueueSize - head;
                } while(rem_size < size);
            }
            if(((mTail-head-1)&sQueueMask) >= size)
                break;

            EnterCriticalSection(&mLock);
            WakeAllConditionVariable(&mCondVar);
            SleepConditionVariableCS(&mCondVar, &mLock, INFINITE);
            LeaveCriticalSection(&mLock);
            head = mHead.load();
        }

        Command *cmd = new(&mQueueData[head]) T(args...);
        TRACE("Sending %p\n", cmd);

        head += size;
        mHead.store(head&sQueueMask);
    }