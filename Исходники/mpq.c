/* this function read a file and verify if it is a valid mpq archive, then it read and decrypt the hash table. */
int32_t libmpq__archive_open(mpq_archive_s **mpq_archive, const char *mpq_filename, libmpq__off_t archive_offset) {

	/* some common variables. */
	uint32_t i              = 0;
	uint32_t count          = 0;
	int32_t result          = 0;
	uint32_t header_search	= FALSE;

	if (archive_offset == -1) {
		archive_offset = 0;
		header_search = TRUE;
	}

	if ((*mpq_archive = calloc(1, sizeof(mpq_archive_s))) == NULL) {

		/* archive struct could not be allocated */
		return LIBMPQ_ERROR_MALLOC;
	}

	/* check if file exists and is readable */
	if (((*mpq_archive)->fp = fopen(mpq_filename, "rb")) == NULL) {

		/* file could not be opened. */
		result = LIBMPQ_ERROR_OPEN;
		goto error;
	}

	/* assign some default values. */
	(*mpq_archive)->mpq_header.mpq_magic = 0;
	(*mpq_archive)->files                = 0;

	/* loop through file and search for mpq signature. */
	while (TRUE) {

		/* reset header values. */
		(*mpq_archive)->mpq_header.mpq_magic = 0;

		/* seek in file. */
		if (fseeko((*mpq_archive)->fp, archive_offset, SEEK_SET) < 0) {

			/* seek in file failed. */
			result = LIBMPQ_ERROR_SEEK;
			goto error;
		}

		/* read header from file. */
		if (fread(&(*mpq_archive)->mpq_header, 1, sizeof(mpq_header_s), (*mpq_archive)->fp) != sizeof(mpq_header_s)) {

			/* no valid mpq archive. */
			result = LIBMPQ_ERROR_FORMAT;
			goto error;
		}

		/* check if we found a valid mpq header. */
		if ((*mpq_archive)->mpq_header.mpq_magic == LIBMPQ_HEADER) {

			/* check if we process old mpq archive version. */
			if ((*mpq_archive)->mpq_header.version == LIBMPQ_ARCHIVE_VERSION_ONE) {

				/* check if the archive is protected. */
				if ((*mpq_archive)->mpq_header.header_size != sizeof(mpq_header_s)) {

					/* correct header size. */
					(*mpq_archive)->mpq_header.header_size = sizeof(mpq_header_s);
				}
			}

			/* check if we process new mpq archive version. */
			if ((*mpq_archive)->mpq_header.version == LIBMPQ_ARCHIVE_VERSION_TWO) {

				/* check if the archive is protected. */
				if ((*mpq_archive)->mpq_header.header_size != sizeof(mpq_header_s) + sizeof(mpq_header_ex_s)) {

					/* correct header size. */
					(*mpq_archive)->mpq_header.header_size = sizeof(mpq_header_s) + sizeof(mpq_header_ex_s);
				}
			}

			/* break the loop, because header was found. */
			break;
		}

		/* move to the next possible offset. */
		if (!header_search) {

			/* no valid mpq archive. */
			result = LIBMPQ_ERROR_FORMAT;
			goto error;
		}
		archive_offset += 512;
	}

	/* store block size for later use. */
	(*mpq_archive)->block_size = 512 << (*mpq_archive)->mpq_header.block_size;

	/* store archive offset and size for later use. */
	(*mpq_archive)->archive_offset = archive_offset;

	/* check if we process new mpq archive version. */
	if ((*mpq_archive)->mpq_header.version == LIBMPQ_ARCHIVE_VERSION_TWO) {

		/* seek in file. */
		if (fseeko((*mpq_archive)->fp, sizeof(mpq_header_s) + archive_offset, SEEK_SET) < 0) {

			/* seek in file failed. */
			result = LIBMPQ_ERROR_SEEK;
			goto error;
		}

		/* read header from file. */
		if (fread(&(*mpq_archive)->mpq_header_ex, 1, sizeof(mpq_header_ex_s), (*mpq_archive)->fp) != sizeof(mpq_header_ex_s)) {

			/* no valid mpq archive. */
			result = LIBMPQ_ERROR_FORMAT;
			goto error;
		}
	}

	/* allocate memory for the block table, hash table, file and block table to file mapping. */
	if (((*mpq_archive)->mpq_block    = calloc((*mpq_archive)->mpq_header.block_table_count, sizeof(mpq_block_s))) == NULL ||
	    ((*mpq_archive)->mpq_block_ex = calloc((*mpq_archive)->mpq_header.block_table_count, sizeof(mpq_block_ex_s))) == NULL ||
	    ((*mpq_archive)->mpq_hash     = calloc((*mpq_archive)->mpq_header.hash_table_count,  sizeof(mpq_hash_s))) == NULL ||
	    ((*mpq_archive)->mpq_file     = calloc((*mpq_archive)->mpq_header.block_table_count, sizeof(mpq_file_s))) == NULL ||
	    ((*mpq_archive)->mpq_map      = calloc((*mpq_archive)->mpq_header.block_table_count, sizeof(mpq_map_s))) == NULL) {

		/* memory allocation problem. */
		result = LIBMPQ_ERROR_MALLOC;
		goto error;
	}

	/* seek in file. */
	if (fseeko((*mpq_archive)->fp, (*mpq_archive)->mpq_header.hash_table_offset + (((long long)((*mpq_archive)->mpq_header_ex.hash_table_offset_high)) << 32) + (*mpq_archive)->archive_offset, SEEK_SET) < 0) {

		/* seek in file failed. */
		result = LIBMPQ_ERROR_SEEK;
		goto error;
	}

	/* read the hash table into the buffer. */
	if (fread((*mpq_archive)->mpq_hash, 1, (*mpq_archive)->mpq_header.hash_table_count * sizeof(mpq_hash_s), (*mpq_archive)->fp) != (*mpq_archive)->mpq_header.hash_table_count * sizeof(mpq_hash_s)) {

		/* something on read failed. */
		result = LIBMPQ_ERROR_READ;
		goto error;
	}

	/* decrypt the hashtable. */
	libmpq__decrypt_block((uint32_t *)((*mpq_archive)->mpq_hash), (*mpq_archive)->mpq_header.hash_table_count * sizeof(mpq_hash_s), libmpq__hash_string("(hash table)", 0x300));

	/* seek in file. */
	if (fseeko((*mpq_archive)->fp, (*mpq_archive)->mpq_header.block_table_offset + (((long long)((*mpq_archive)->mpq_header_ex.block_table_offset_high)) << 32) + (*mpq_archive)->archive_offset, SEEK_SET) < 0) {

		/* seek in file failed. */
		result = LIBMPQ_ERROR_SEEK;
		goto error;
	}

	/* read the block table into the buffer. */
	if (fread((*mpq_archive)->mpq_block, 1, (*mpq_archive)->mpq_header.block_table_count * sizeof(mpq_block_s), (*mpq_archive)->fp) != (*mpq_archive)->mpq_header.block_table_count * sizeof(mpq_block_s)) {

		/* something on read failed. */
		result = LIBMPQ_ERROR_READ;
		goto error;
	}

	/* decrypt block table. */
	libmpq__decrypt_block((uint32_t *)((*mpq_archive)->mpq_block), (*mpq_archive)->mpq_header.block_table_count * sizeof(mpq_block_s), libmpq__hash_string("(block table)", 0x300));

	/* check if extended block table is present, regardless of version 2 it is only present in archives > 4GB. */
	if ((*mpq_archive)->mpq_header_ex.extended_offset > 0) {

		/* seek in file. */
		if (fseeko((*mpq_archive)->fp, (*mpq_archive)->mpq_header_ex.extended_offset + archive_offset, SEEK_SET) < 0) {

			/* seek in file failed. */
			result = LIBMPQ_ERROR_SEEK;
			goto error;
		}

		/* read header from file. */
		if (fread((*mpq_archive)->mpq_block_ex, 1, (*mpq_archive)->mpq_header.block_table_count * sizeof(mpq_block_ex_s), (*mpq_archive)->fp) != (*mpq_archive)->mpq_header.block_table_count * sizeof(mpq_block_ex_s)) {

			/* no valid mpq archive. */
			result = LIBMPQ_ERROR_FORMAT;
			goto error;
		}
	}

	/* loop through all files in mpq archive and check if they are valid. */
	for (i = 0; i < (*mpq_archive)->mpq_header.block_table_count; i++) {

		/* save block difference between valid and invalid blocks. */
		(*mpq_archive)->mpq_map[i].block_table_diff = i - count;

		/* check if file exists, sizes and offsets are correct. */
		if (((*mpq_archive)->mpq_block[i].flags & LIBMPQ_FLAG_EXISTS) == 0) {

			/* file does not exist, so nothing to do with that block. */
			continue;
		}

		/* create final indices tables. */
		(*mpq_archive)->mpq_map[count].block_table_indices = i;

		/* increase file counter. */
		count++;
	}

	/* save the number of files. */
	(*mpq_archive)->files = count;

	/* if no error was found, return zero. */
	return LIBMPQ_SUCCESS;

error:
	if ((*mpq_archive)->fp)
		fclose((*mpq_archive)->fp);

	free((*mpq_archive)->mpq_map);
	free((*mpq_archive)->mpq_file);
	free((*mpq_archive)->mpq_hash);
	free((*mpq_archive)->mpq_block);
	free((*mpq_archive)->mpq_block_ex);
	free(*mpq_archive);

	*mpq_archive = NULL;

	return result;
}