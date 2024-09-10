    void OperationQueue::Impl::workerThread()
    {
        for (;;)
        {
            Record::Ptr item;
            {
                LockGuard lock(_inputMutex);
                item = getFirstUndoInputRecord();
                if (!item)
                {
                    exitThread(ThreadInfo::thisThreadId());
                    return;
                }

                item->state = Record::State::Doing;

                if (item->isCancel)
                {
                    popupInputRecord(item->Id);
                    continue;
                }
            }

            item->operation->action();

            {
                LockGuard lock(_inputMutex);
                if (!item->isCancel && item->callback != nullptr)
                {
                    s_addItem(_outputs, item, _outputMutex);
                }
                popupInputRecord(item->Id);
            }
        }
    }