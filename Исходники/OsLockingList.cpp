/* ============================ ACCESSORS ================================= */
int OsLockingList::getCount()
{
        OsLock localLock(listMutex);
        return(list.entries());
}