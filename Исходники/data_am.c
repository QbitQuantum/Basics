/*
 * @return:'1' for success, '-1' for rollback.
 */
int TrulyDataInsert(int table_id, int index, TupleId tuple_id, TupleId value, int nid)
{
	int index2;
	int status;
	TransactionData* tdata;
	TransactionId tid;
	DataLock lockrd;
	THREAD* threadinfo;

	tdata=(TransactionData*)pthread_getspecific(TransactionDataKey);
	tid=tdata->tid;

	threadinfo=(THREAD*)pthread_getspecific(ThreadInfoKey);
	index2=threadinfo->index;

	int lindex;
	lindex = GetLocalIndex(index2);

    if((Send6(lindex, nid, cmd_trulyinsert, table_id, tuple_id, value, index, tid)) == -1)
    	printf("truly insert send error!\n");
    if((Recv(lindex, nid, 1)) == -1)
    	printf("truly insert recv error!\n");

	/* record the lock. */
	lockrd.table_id=table_id;
	lockrd.tuple_id=tuple_id;
	lockrd.index = index;
	lockrd.node_id = nid;
	lockrd.lockmode=LOCK_EXCLUSIVE;
	DataLockInsert(&lockrd);

    status = *(recv_buffer[lindex]);
    if (status == 4)
    	return -1;
	return 1;
}