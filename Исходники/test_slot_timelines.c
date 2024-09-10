/*
 * Create a new logical slot, with invalid LSN and xid, directly. This does not
 * use the snapshot builder or logical decoding machinery. It's only intended
 * for creating a slot on a replica that mirrors the state of a slot on an
 * upstream master.
 *
 * Note that this is test harness code. You shouldn't expose slot internals
 * to SQL like this for any real world usage. See the README.
 */
Datum
test_slot_timelines_create_logical_slot(PG_FUNCTION_ARGS)
{
	char	   *slotname = text_to_cstring(PG_GETARG_TEXT_P(0));
	char	   *plugin = text_to_cstring(PG_GETARG_TEXT_P(1));

	CheckSlotRequirements();

	ReplicationSlotCreate(slotname, true, RS_PERSISTENT);

	/* register the plugin name with the slot */
	StrNCpy(NameStr(MyReplicationSlot->data.plugin), plugin, NAMEDATALEN);

	/*
	 * Initialize persistent state to placeholders to be set by
	 * test_slot_timelines_advance_logical_slot .
	 */
	MyReplicationSlot->data.xmin = InvalidTransactionId;
	MyReplicationSlot->data.catalog_xmin = InvalidTransactionId;
	MyReplicationSlot->data.restart_lsn = InvalidXLogRecPtr;
	MyReplicationSlot->data.confirmed_flush = InvalidXLogRecPtr;

	clear_slot_transient_state();

	ReplicationSlotRelease();

	PG_RETURN_VOID();
}