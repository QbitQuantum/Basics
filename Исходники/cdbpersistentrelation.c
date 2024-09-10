/*
 * Indicate we intend to create a relation file as part of the current transaction.
 *
 * This function adds an entry in 'gp_persistent_relation_node' for either a new table (segment file
 * # 0) or a new segment file under AO table (segment file # > 0 for row/column-oriented AO) with a state
 * 'Create Pending'. An XLOG IntentToCreate record is generated that will guard the subsequent file-system
 * create in case the transaction aborts.
 *
 * Paramaters
 * -----------
 * relFileNode = The tablespace, database, and relation OIDs for the create
 * segmentFileNum = As the name implies (   0 for heap
 *                                       >= 0 for RO/CO AO as applicable)
 * relStorageMgr = Persistent Relation storage Manager
 * relBufpoolKind = Buffer pool type beneath corrosponding relation
 * TODO bufferPollBulkLoad = ???
 * TODO mirrorExistenceState = ???
 * TODO relDataSynchronizationState = ???
 * flushToXlog = If true, the XLOG record for this change will be flushed to disk.
 * TODO isLocalBuf = ???
 *
 * Return
 * ------
 * relationName = Name of the relation used for either debugging or to store in PendingDelete LL.
 * persistentTid = Resulting TID of the gp_persistent_rel_files tuple for the relation
 * serialNum = Resulting serial number for the relation.  Distinquishes the uses of the tuple
 */
void PersistentRelation_AddCreatePending(
    RelFileNode 		*relFileNode,
    int32				segmentFileNum,
    PersistentFileSysRelStorageMgr relStorageMgr,
    PersistentFileSysRelBufpoolKind relBufpoolKind,
    bool				bufferPoolBulkLoad,
    MirroredObjectExistenceState mirrorExistenceState,
    MirroredRelDataSynchronizationState relDataSynchronizationState,
    char				*relationName,
    ItemPointer			persistentTid,
    int64				*serialNum,
    bool 				flushToXLog,
    bool				isLocalBuf)
{
    WRITE_PERSISTENT_STATE_ORDERED_LOCK_DECLARE;

    PersistentFileSysObjName fsObjName;

    XLogRecPtr mirrorBufpoolResyncCkptLoc;
    ItemPointerData previousFreeTid;

    Datum values[Natts_gp_persistent_relation_node];

    if(RelFileNode_IsEmpty(relFileNode))
        elog(ERROR, "Invalid RelFileNode (0,0,0)");

    MemSet(&previousFreeTid, 0, sizeof(ItemPointerData));
    MemSet(&mirrorBufpoolResyncCkptLoc, 0, sizeof(XLogRecPtr));

    if (Persistent_BeforePersistenceWork())
    {
        if (Debug_persistent_print)
            elog(Persistent_DebugPrintLevel(),
                 "Skipping persistent relation '%s' because we are before persistence work",
                 relpath(*relFileNode));

        MemSet(persistentTid, 0, sizeof(ItemPointerData));
        *serialNum = 0;

        return;	// The initdb process will load the persistent table once we out of bootstrap mode.
    }

    /* Verify if the needed shared mem data structures for persistent tables are setup and inited */
    PersistentRelation_VerifyInitScan();

    /* Setup the file system object name */
    PersistentFileSysObjName_SetRelationFile(
        &fsObjName,
        relFileNode,
        segmentFileNum);

    WRITE_PERSISTENT_STATE_ORDERED_LOCK;

    /* Create a values array which will be used to create a 'gp_persistent_relation_node' tuple */
    GpPersistentRelationNode_SetDatumValues(
        values,
        relFileNode->spcNode,
        relFileNode->dbNode,
        relFileNode->relNode,
        segmentFileNum,
        relStorageMgr,
        (bufferPoolBulkLoad ?
         PersistentFileSysState_BulkLoadCreatePending :
         PersistentFileSysState_CreatePending),
        /* createMirrorDataLossTrackingSessionNum */ 0,
        mirrorExistenceState,
        relDataSynchronizationState,
        /* mirrorBufpoolMarkedForScanIncrementalResync */ false,
        /* mirrorBufpoolResyncChangedPageCount */ 0,
        &mirrorBufpoolResyncCkptLoc,
        /* mirrorBufpoolResyncCkptBlockNum */ 0,
        /* mirrorAppendOnlyLossEof */ 0,
        /* mirrorAppendOnlyNewEof */ 0,
        relBufpoolKind,
        GetTopTransactionId(),
        /* persistentSerialNum */ 0,	// This will be set by PersistentFileSysObj_AddTuple.
        &previousFreeTid);

    /* Add a new tuple to 'gp_persistent_relation_node' table for the new relation/segment file
     * we intend to create. This will also create and apply a new persistent serial number. */
    PersistentFileSysObj_AddTuple(
        PersistentFsObjType_RelationFile,
        values,
        flushToXLog,
        persistentTid,
        serialNum);

    /*
     * This XLOG must be generated under the persistent write-lock.
     */
#ifdef MASTER_MIRROR_SYNC
    mmxlog_log_create_relfilenode(
        relFileNode->spcNode,
        relFileNode->dbNode,
        relFileNode->relNode,
        segmentFileNum);
#endif

#ifdef FAULT_INJECTOR
    FaultInjector_InjectFaultIfSet(
        FaultBeforePendingDeleteRelationEntry,
        DDLNotSpecified,
        "",  // databaseName
        ""); // tableName
#endif

    /* We'll add an entry to the PendingDelete LinkedList (LL) to remeber what we
     * created in this transaction (or sub-transaction). If the transaction
     * aborts then we can search for all such entries in this LL and get rid of (delete)
     * such relations or segment files on the disk.
    *
    * MPP-18228
    * To make adding 'Create Pending' entry to persistent table and adding
    * to the PendingDelete list atomic
    */
    PendingDelete_AddCreatePendingRelationEntry(
        &fsObjName,
        persistentTid,
        serialNum,
        relStorageMgr,
        relationName,
        isLocalBuf,
        bufferPoolBulkLoad);


    WRITE_PERSISTENT_STATE_ORDERED_UNLOCK;

    if (Debug_persistent_print)
        elog(Persistent_DebugPrintLevel(),
             "Persistent relation: Add '%s', relation name '%s' in state 'Create Pending', relation storage manager '%s', mirror existence state '%s', relation data resynchronization state '%s', serial number " INT64_FORMAT " at TID %s",
             PersistentFileSysObjName_ObjectName(&fsObjName),
             relationName,
             PersistentFileSysRelStorageMgr_Name(relStorageMgr),
             MirroredObjectExistenceState_Name(mirrorExistenceState),
             MirroredRelDataSynchronizationState_Name(relDataSynchronizationState),
             *serialNum,
             ItemPointerToString(persistentTid));
}