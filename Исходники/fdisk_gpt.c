static int
check_gpt_label(void)
{
	struct partition *first = pt_offset(MBRbuffer, 0);
	struct pte pe;
	uint32_t crc;

	/* LBA 0 contains the legacy MBR */

	if (!valid_part_table_flag(MBRbuffer)
	 || first->sys_ind != LEGACY_GPT_TYPE
	) {
		current_label_type = 0;
		return 0;
	}

	/* LBA 1 contains the GPT header */

	read_pte(&pe, 1);
	gpt_hdr = (void *)pe.sectorbuffer;

	if (gpt_hdr->magic != SWAP_LE64(GPT_MAGIC)) {
		current_label_type = 0;
		return 0;
	}

	if (!global_crc32_table) {
		global_crc32_table = crc32_filltable(NULL, 0);
	}

	crc = SWAP_LE32(gpt_hdr->hdr_crc32);
	gpt_hdr->hdr_crc32 = 0;
	if (gpt_crc32(gpt_hdr, SWAP_LE32(gpt_hdr->hdr_size)) != crc) {
		/* FIXME: read the backup table */
		puts("\nwarning: GPT header CRC is invalid\n");
	}

	n_parts = SWAP_LE32(gpt_hdr->n_parts);
	part_entry_len = SWAP_LE32(gpt_hdr->part_entry_len);
	if (n_parts > GPT_MAX_PARTS
	 || part_entry_len > GPT_MAX_PART_ENTRY_LEN
	 || SWAP_LE32(gpt_hdr->hdr_size) > sector_size
	) {
		puts("\nwarning: unable to parse GPT disklabel\n");
		current_label_type = 0;
		return 0;
	}

	part_array_len = n_parts * part_entry_len;
	part_array = xmalloc(part_array_len);
	seek_sector(SWAP_LE64(gpt_hdr->first_part_lba));
	if (full_read(dev_fd, part_array, part_array_len) != part_array_len) {
		fdisk_fatal(unable_to_read);
	}

	if (gpt_crc32(part_array, part_array_len) != gpt_hdr->part_array_crc32) {
		/* FIXME: read the backup table */
		puts("\nwarning: GPT array CRC is invalid\n");
	}

	puts("Found valid GPT with protective MBR; using GPT\n");

	current_label_type = LABEL_GPT;
	return 1;
}