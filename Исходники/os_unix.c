/*
** Given a file descriptor, locate lockInfo and openCnt structures that
** describes that file descriptor.  Create a new ones if necessary.  The
** return values might be unset if an error occurs.
**
** Return the number of errors.
*/
static int findLockInfo(
  int fd,                      /* The file descriptor used in the key */
  struct lockInfo **ppLock,    /* Return the lockInfo structure here */
  struct openCnt **ppOpen      /* Return the openCnt structure here */
){
  int rc;
  struct lockKey key1;
  struct openKey key2;
  struct stat statbuf;
  struct lockInfo *pLock;
  struct openCnt *pOpen;
  rc = fstat(fd, &statbuf);
  if( rc!=0 ) return 1;
  memset(&key1, 0, sizeof(key1));
  key1.dev = statbuf.st_dev;
  key1.ino = statbuf.st_ino;
#ifdef SQLITE_UNIX_THREADS
  if( threadsOverrideEachOthersLocks<0 ){
    testThreadLockingBehavior(fd);
  }
  key1.tid = threadsOverrideEachOthersLocks ? 0 : pthread_self();
#endif
  memset(&key2, 0, sizeof(key2));
  key2.dev = statbuf.st_dev;
  key2.ino = statbuf.st_ino;
  pLock = (struct lockInfo*)sqlite3HashFind(&lockHash, &key1, sizeof(key1));
  if( pLock==0 ){
    struct lockInfo *pOld;
    pLock = (lockInfo*)sqliteMallocRaw( sizeof(*pLock) );
    if( pLock==0 ) return 1;
    pLock->key = key1;
    pLock->nRef = 1;
    pLock->cnt = 0;
    pLock->locktype = 0;
    pOld =  (lockInfo*)sqlite3HashInsert(&lockHash, &pLock->key, sizeof(key1), pLock);
    if( pOld!=0 ){
      assert( pOld==pLock );
      sqliteFree(pLock);
      return 1;
    }
  }else{
    pLock->nRef++;
  }
  *ppLock = pLock;
  pOpen = (struct openCnt*)sqlite3HashFind(&openHash, &key2, sizeof(key2));
  if( pOpen==0 ){
    struct openCnt *pOld;
    pOpen =  (openCnt*)sqliteMallocRaw( sizeof(*pOpen) );
    if( pOpen==0 ){
      releaseLockInfo(pLock);
      return 1;
    }
    pOpen->key = key2;
    pOpen->nRef = 1;
    pOpen->nLock = 0;
    pOpen->nPending = 0;
    pOpen->aPending = 0;
    pOld =  (openCnt*)sqlite3HashInsert(&openHash, &pOpen->key, sizeof(key2), pOpen);
    if( pOld!=0 ){
      assert( pOld==pOpen );
      sqliteFree(pOpen);
      releaseLockInfo(pLock);
      return 1;
    }
  }else{
    pOpen->nRef++;
  }
  *ppOpen = pOpen;
  return 0;
}