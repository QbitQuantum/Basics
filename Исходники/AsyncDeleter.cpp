void AsyncDeleter::executeThread(void)
{
    while(!exitApplication)
    {
        suspendThread();

        //! delete elements that require post process deleting
        //! because otherwise they would block or do invalid access on GUI thread
        while(!realDeleteElements.empty())
        {
            deleteMutex.lock();
            AsyncDeleter::Element *element = realDeleteElements.front();
            realDeleteElements.pop();
            deleteMutex.unlock();

            delete element;
        }
    }

}