void cp_parallelized_crypt(
	   int   is_encrypt, xts_key *key, fc_callback on_complete, 
	   void *param, const unsigned char *in, unsigned char *out, u32 len, u64 offset)
{
	req_item *item;
	req_part *part;
	u32       part_sz;
	u32       part_of;

	if ( (len < F_OP_THRESOLD) ||
		 ((item = ExAllocateFromNPagedLookasideList(&pool_req_mem)) == NULL) )
	{
		if (is_encrypt != 0) {
			xts_encrypt(in, out, len, offset, key);
		} else {
			xts_decrypt(in, out, len, offset, key);
		}
		on_complete(param); return;
	}
	item->is_encrypt = is_encrypt;
	item->length = len;
	item->in  = in;
	item->out = out;
	item->offset      = offset;
	item->on_complete = on_complete;
	item->param = param;
	item->key   = key;

	part_sz = _align(len / dc_cpu_count, F_MIN_REQ);
	part_of = 0; part = &item->parts[0];
	do
	{
		part_sz      = min(part_sz, len);
		part->item   = item;
		part->offset = part_of;
		part->length = part_sz;

		InterlockedPushEntrySList(&pool_head, &part->entry);

		part_of += part_sz; len -= part_sz; part++;
	} while (len != 0);

	KeSetEvent(&pool_signal_event, IO_NO_INCREMENT, FALSE);
}