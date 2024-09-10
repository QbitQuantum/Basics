APIRET os2APIENTRY DosSetFileLocks(os2HFILE hFile,
                                   PFILELOCK pflUnlock,
                                   PFILELOCK pflLock,
                                   ULONG /*timeout*/,
                                   ULONG flags)
{
        APIRET rc;
        int idx=(int)hFile;
        FileTable.lock(idx);
        if(FileTable[idx]) {
                rc=0;
                if(pflLock) {
                        OVERLAPPED o;
                        memset(&o,0,sizeof(o));
                        o.Offset = pflLock->lOffset;
                        o.OffsetHigh = 0;
                        if(!LockFileEx(FileTable[idx]->ntFileHandle,
                                       flags&1?0:LOCKFILE_EXCLUSIVE_LOCK,
                                       0,
                                       pflLock->lRange, 0,
                                       0
                                    )) {
                                rc = (APIRET)GetLastError();
                        }
                }
                if(rc==0 && pflUnlock) {
                        if(!UnlockFile(FileTable[idx]->ntFileHandle,
                                       pflUnlock->lOffset, 0,
                                       pflUnlock->lRange, 0
                                    )) {
                                UnlockFile(FileTable[idx]->ntFileHandle,
                                           pflLock->lOffset,0,
                                           pflLock->lRange,0
                                          );
                                rc = (APIRET)GetLastError();
                        }
                }
        } else
                rc = 6; //invalid handle
        FileTable.unlock(idx);
        return rc;
}