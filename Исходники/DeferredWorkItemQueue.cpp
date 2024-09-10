DeferredWorkItem* DeferredWorkItemQueue::dequeue(void)
{
    // Returns the first item in the queue if it the work item time is >= the current time.

    EsifMutexHelper esifMutexHelper(&m_mutex);
    esifMutexHelper.lock();

    DeferredWorkItem* firstReadyWorkItem = getFirstReadyWorkItemFromQueue();
    setTimer();

    esifMutexHelper.unlock();

    return firstReadyWorkItem;
}