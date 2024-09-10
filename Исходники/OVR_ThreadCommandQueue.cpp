// Pops the next command from the thread queue, if any is available.
bool ThreadCommandQueueImpl::PopCommand(ThreadCommand::PopBuffer* popBuffer)
{    
    Lock::Locker lock(&QueueLock);

    UByte* buffer = CommandBuffer.ReadBegin();
    if (!buffer)
    {
        // Notify thread while in lock scope, enabling initialization of wait.
        pQueue->OnPopEmpty_Locked();
        return false;
    }

    popBuffer->InitFromBuffer(buffer);
    CommandBuffer.ReadEnd(popBuffer->GetSize());

    if (!BlockedProducers.IsEmpty())
    {
        ThreadCommand::NotifyEvent* queueAvailableEvent = BlockedProducers.GetFirst();
        queueAvailableEvent->RemoveNode();
        queueAvailableEvent->PulseEvent();
        // Event is freed later by waiter.
    }    
    return true;
}