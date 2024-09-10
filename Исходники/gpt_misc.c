/**
 * Write any changes for the GPT data back to the drive, then free the buffers.
 *
 * Returns 0 if successful, 1 if error.
 */
int WriteAndFreeGptData(VbExDiskHandle_t disk_handle, GptData *gptdata)
{
	int legacy = 0;
	GptHeader *header = (GptHeader *)gptdata->primary_header;
	uint64_t entries_bytes = header->number_of_entries
				* header->size_of_entry;
	uint64_t entries_sectors = entries_bytes / gptdata->sector_bytes;
	int ret = 1;

	/*
	 * TODO(namnguyen): Preserve padding between primary GPT header and
	 * its entries.
	 */
	uint64_t entries_lba = GPT_PMBR_SECTORS + GPT_HEADER_SECTORS;
	if (gptdata->primary_header) {
		GptHeader *h = (GptHeader *)(gptdata->primary_header);
		entries_lba = h->entries_lba;

		/*
		 * Avoid even looking at this data if we don't need to. We
		 * may in fact not have read it from disk if the read failed,
		 * and this avoids a valgrind complaint.
		 */
		if (gptdata->modified) {
			legacy = !Memcmp(h->signature, GPT_HEADER_SIGNATURE2,
					GPT_HEADER_SIGNATURE_SIZE);
		}
		if (gptdata->modified & GPT_MODIFIED_HEADER1) {
			if (legacy) {
				VBDEBUG(("Not updating GPT header 1: "
					 "legacy mode is enabled.\n"));
			} else {
				VBDEBUG(("Updating GPT header 1\n"));
				if (0 != VbExDiskWrite(disk_handle, 1, 1,
						       gptdata->primary_header))
					goto fail;
			}
		}
	}

	if (gptdata->primary_entries) {
		if (gptdata->modified & GPT_MODIFIED_ENTRIES1) {
			if (legacy) {
				VBDEBUG(("Not updating GPT entries 1: "
					 "legacy mode is enabled.\n"));
			} else {
				VBDEBUG(("Updating GPT entries 1\n"));
				if (0 != VbExDiskWrite(disk_handle, entries_lba,
						entries_sectors,
						gptdata->primary_entries))
					goto fail;
			}
		}
	}

	entries_lba = (gptdata->gpt_drive_sectors - entries_sectors -
		GPT_HEADER_SECTORS);
	if (gptdata->secondary_header) {
		GptHeader *h = (GptHeader *)(gptdata->secondary_header);
		entries_lba = h->entries_lba;
		if (gptdata->modified & GPT_MODIFIED_HEADER2) {
			VBDEBUG(("Updating GPT entries 2\n"));
			if (0 != VbExDiskWrite(disk_handle,
					       gptdata->gpt_drive_sectors - 1, 1,
					       gptdata->secondary_header))
				goto fail;
		}
	}

	if (gptdata->secondary_entries) {
		if (gptdata->modified & GPT_MODIFIED_ENTRIES2) {
			VBDEBUG(("Updating GPT header 2\n"));
			if (0 != VbExDiskWrite(disk_handle,
				entries_lba, entries_sectors,
				gptdata->secondary_entries))
				goto fail;
		}
	}

	ret = 0;

fail:
	/* Avoid leaking memory on disk write failure */
	if (gptdata->primary_header)
		VbExFree(gptdata->primary_header);
	if (gptdata->primary_entries)
		VbExFree(gptdata->primary_entries);
	if (gptdata->secondary_entries)
		VbExFree(gptdata->secondary_entries);
	if (gptdata->secondary_header)
		VbExFree(gptdata->secondary_header);

	/* Success */
	return ret;
}