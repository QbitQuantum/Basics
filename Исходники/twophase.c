/*
 * Start preparing a state file.
 *
 * Initializes data structure and inserts the 2PC file header record.
 */
void
StartPrepare(GlobalTransaction gxact)
{
	TransactionId xid = gxact->proc.xid;
	TwoPhaseFileHeader hdr;
	TransactionId *children;
	RelFileNode *commitrels;
	RelFileNode *abortrels;

	/* Initialize linked list */
	records.head = palloc0(sizeof(XLogRecData));
	records.head->buffer = InvalidBuffer;
	records.head->len = 0;
	records.head->next = NULL;

	records.bytes_free = Max(sizeof(TwoPhaseFileHeader), 512);
	records.head->data = palloc(records.bytes_free);

	records.tail = records.head;

	records.total_len = 0;

	/* Create header */
	hdr.magic = TWOPHASE_MAGIC;
	hdr.total_len = 0;			/* EndPrepare will fill this in */
	hdr.xid = xid;
	hdr.database = gxact->proc.databaseId;
	hdr.prepared_at = gxact->prepared_at;
	hdr.owner = gxact->owner;
	hdr.nsubxacts = xactGetCommittedChildren(&children);
	hdr.ncommitrels = smgrGetPendingDeletes(true, &commitrels);
	hdr.nabortrels = smgrGetPendingDeletes(false, &abortrels);
	StrNCpy(hdr.gid, gxact->gid, GIDSIZE);

	save_state_data(&hdr, sizeof(TwoPhaseFileHeader));

	/* Add the additional info about subxacts and deletable files */
	if (hdr.nsubxacts > 0)
	{
		save_state_data(children, hdr.nsubxacts * sizeof(TransactionId));
		/* While we have the child-xact data, stuff it in the gxact too */
		GXactLoadSubxactData(gxact, hdr.nsubxacts, children);
		pfree(children);
	}
	if (hdr.ncommitrels > 0)
	{
		save_state_data(commitrels, hdr.ncommitrels * sizeof(RelFileNode));
		pfree(commitrels);
	}
	if (hdr.nabortrels > 0)
	{
		save_state_data(abortrels, hdr.nabortrels * sizeof(RelFileNode));
		pfree(abortrels);
	}
}