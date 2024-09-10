 INT32 _dpsReplicaLogMgr::flushAll()
 {
    INT32 rc = SDB_OK ;
    rc = _flushAll() ;
    return rc ;
 }