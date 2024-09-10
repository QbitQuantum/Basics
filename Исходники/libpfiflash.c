/**
 * process_raw_volumes - writes the raw sections of the PFI data
 * @pfi		PFI data file pointer
 * @pfi_raws	list of PFI raw headers
 * @rawdev	device to use to write raw data
 *
 * Error handling:
 *	when early EOF in PFI data
 *	- returns -PFIFLASH_ERR_EOF, err_buf matches text to err
 *	when file I/O error
 *	- returns -PFIFLASH_ERR_FIO, err_buf matches text to err
 *	when CRC check fails
 *	- returns -PFIFLASH_ERR_CRC_CHECK, err_buf matches text to err
 *	when opening MTD device fails
 *	- reutrns -PFIFLASH_ERR_MTD_OPEN, err_buf matches text to err
 *	when closing MTD device fails
 *	- returns -PFIFLASH_ERR_MTD_CLOSE, err_buf matches text to err
 **/
static int
process_raw_volumes(FILE* pfi, list_t pfi_raws, const char* rawdev,
		    char* err_buf, size_t err_buf_size)
{
	int rc;
	char *pfi_data;
	void *i;
	uint32_t crc, crc32_table[256];
	size_t j, k;
	FILE* mtd = NULL;
	list_t ptr;

	if (is_empty(pfi_raws))
		return 0;

	if (rawdev == NULL)
		return 0;

	rc = 0;

	pfi_data = NULL;

	log_msg("[ rawupdate dev=%s", rawdev);

	crc = UBI_CRC32_INIT;
	init_crc32_table(crc32_table);

	/* most likely only one element in list, but just in case */
	foreach(i, ptr, pfi_raws) {
		pfi_raw_t r = (pfi_raw_t)i;

		/* read in pfi data */
		if (pfi_data != NULL)
			free(pfi_data);
		pfi_data = malloc(r->data_size * sizeof(char));
		for (j = 0; j < r->data_size; j++) {
			int c = fgetc(pfi);
			if (c == EOF) {
				rc = -PFIFLASH_ERR_EOF;
				EBUF(PFIFLASH_ERRSTR[-rc]);
				goto err;
			} else if (ferror(pfi)) {
				rc = -PFIFLASH_ERR_FIO;
				EBUF(PFIFLASH_ERRSTR[-rc]);
				goto err;
			}
			pfi_data[j] = (char)c;
		}
		crc = clc_crc32(crc32_table, crc, pfi_data, r->data_size);

		/* check crc */
		if (crc != r->crc) {
			rc = -PFIFLASH_ERR_CRC_CHECK;
			EBUF(PFIFLASH_ERRSTR[-rc], r->crc, crc);
			goto err;
		}

		/* open device */
		mtd = fopen(rawdev, "r+");
		if (mtd == NULL) {
			rc = -PFIFLASH_ERR_MTD_OPEN;
			EBUF(PFIFLASH_ERRSTR[-rc], rawdev);
			goto err;
		}

		for (j = 0; j < r->starts_size; j++) {
			rc = erase_mtd_region(mtd, r->starts[j], r->data_size);
			if (rc) {
				EBUF(PFIFLASH_ERRSTR[-rc]);
				goto err;
			}

			fseek(mtd, r->starts[j], SEEK_SET);
			for (k = 0; k < r->data_size; k++) {
				int c = fputc((int)pfi_data[k], mtd);
				if (c == EOF) {
					fclose(mtd);
					rc = -PFIFLASH_ERR_EOF;
					EBUF(PFIFLASH_ERRSTR[-rc]);
					goto err;
				}
				if ((char)c != pfi_data[k]) {
					fclose(mtd);
					rc = -1;
					goto err;
				}
			}
		}
		rc = fclose(mtd);
		mtd = NULL;
		if (rc != 0) {
			rc = -PFIFLASH_ERR_MTD_CLOSE;
			EBUF(PFIFLASH_ERRSTR[-rc], rawdev);
			goto err;
		}
	}