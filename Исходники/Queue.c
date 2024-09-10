SHARED_FUNCTION TNode * TQueue_GetMsg     (TQueue * queue)
{
    TNode * node = NULL;
    //enter critical section: Get first element and remove it from list (not free it)
    os_thread_MutexLock( &queue->messageQueue.Mutex );
    if (!ISLISTEMPTY(&queue->messageQueue))
    {
        node = (TNode*)GETFIRST(&queue->messageQueue);
        REMOVE(node);
    }
    os_thread_MutexUnlock( &queue->messageQueue.Mutex );
    return node;
}