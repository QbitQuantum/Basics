//-----------------------------------------------------------------------------
// 描述: 通知所有线程退出
//-----------------------------------------------------------------------------
void ThreadList::terminateAllThreads()
{
    AutoLocker locker(mutex_);

    for (int i = 0; i < items_.getCount(); i++)
    {
        Thread *thread = items_[i];
        thread->terminate();
    }
}