static void ssa_db_rec_tbl_load(FILE *fd, enum ssa_db_helper_mode mode,
				struct db_table_def *p_data_tbl_def,
				struct db_dataset *p_dataset, void *p_data_tbl,
				struct db_dataset *p_dataset_field,
				struct db_field_def *p_field_tbl)
{
	struct db_field_def *p_field_rec;
	uint64_t i, k, j;
	uint8_t *p_data_rec, *p_data_field;
	char c;

	if (mode != SSA_DB_HELPER_STANDARD && mode != SSA_DB_HELPER_DEBUG)
		return;

	for (i = 0; i < ntohll(p_dataset->set_count); i++) {
		p_data_rec = (uint8_t *)((uint8_t *)p_data_tbl + i * ntohl(p_data_tbl_def->record_size));
		if (mode == SSA_DB_HELPER_STANDARD) {
			for (k = 0; k < ntohl(p_data_tbl_def->record_size); k++) {
				FSCANF_SINGLE(fd, "%c", &c, i, p_data_tbl_def->name);
				memcpy(p_data_rec + k, &c, sizeof(c));
			}
		} else {
			for (k = 0; k < ntohll(p_dataset_field->set_count); k++) {
				p_field_rec = &p_field_tbl[k];
				p_data_field = p_data_rec + ntohl(p_field_rec->field_offset) / 8;

				switch (p_field_rec->type) {
				case DBF_TYPE_U8:
					for (j = 0; j < ntohl(p_field_rec->field_size) / 8; j++) {
						if (j == (ntohl(p_field_rec->field_size) / 8) - 1) {
							FSCANF_SINGLE(fd, "%" SCNu8 SSA_DB_HELPER_DELIMITER,
								      ((uint8_t *)p_data_field + j), i,
								      p_data_tbl_def->name);
						} else {
							FSCANF_SINGLE(fd, "%" SCNu8 SSA_DB_HELPER_ARRAY_DELIMITER,
								      ((uint8_t *)p_data_field + j), i,
								      p_data_tbl_def->name);
						}
					}
					break;
				case DBF_TYPE_U16:
					for (j = 0; j < ntohl(p_field_rec->field_size) / 16; j++) {
						if (j == (ntohl(p_field_rec->field_size) / 16) - 1) {
							FSCANF_SINGLE(fd, "%" SCNu16 SSA_DB_HELPER_DELIMITER,
								      ((uint16_t *)p_data_field + (j * 2)), i,
								      p_data_tbl_def->name);
						} else {
							FSCANF_SINGLE(fd, "%" SCNu16 SSA_DB_HELPER_ARRAY_DELIMITER,
								      ((uint16_t *)p_data_field + (j * 2)), i,
								      p_data_tbl_def->name);
						}
					}
					break;
				case DBF_TYPE_U32:
					for (j = 0; j < ntohl(p_field_rec->field_size) / 32; j++) {
						if (j == (ntohl(p_field_rec->field_size) / 32) - 1) {
							FSCANF_SINGLE(fd, "%" PRIx32 SSA_DB_HELPER_DELIMITER,
								      ((uint32_t *)p_data_field + (j * 4)), i,
								      p_data_tbl_def->name);
						} else {
							FSCANF_SINGLE(fd, "%" PRIx32 SSA_DB_HELPER_ARRAY_DELIMITER,
								      ((uint32_t *)p_data_field + (j * 4)), i,
								      p_data_tbl_def->name);
						}
					}
					break;
				case DBF_TYPE_U64:
					for (j = 0; j < ntohl(p_field_rec->field_size) / 64; j++) {
						if (j == (ntohl(p_field_rec->field_size) / 64) - 1) {
							FSCANF_SINGLE(fd, "0x%" PRIx64 SSA_DB_HELPER_DELIMITER,
								      ((uint64_t *)p_data_field + (j * 8)), i,
								      p_data_tbl_def->name);
						} else {
							FSCANF_SINGLE(fd, "0x%" PRIx64 SSA_DB_HELPER_ARRAY_DELIMITER,
								      ((uint64_t *)p_data_field + (j * 8)), i,
								      p_data_tbl_def->name);
						}
					}
					break;
				case DBF_TYPE_NET16:
					for (j = 0; j < ntohl(p_field_rec->field_size) / 16; j++) {
						if (j == (ntohl(p_field_rec->field_size) / 16) - 1) {
							FSCANF_SINGLE(fd, "%" SCNu16 SSA_DB_HELPER_DELIMITER,
								      ((uint16_t *)p_data_field + (j * 2)), i,
								      p_data_tbl_def->name);
						} else {
							FSCANF_SINGLE(fd, "%" SCNu16 SSA_DB_HELPER_ARRAY_DELIMITER,
								      ((uint16_t *)p_data_field + (j * 2)), i,
								      p_data_tbl_def->name);
						}
						*((uint16_t *)p_data_field + (j * 2)) =
								htons(*((uint16_t *)p_data_field + (j * 2)));
					}
					break;
				case DBF_TYPE_NET32:
					for (j = 0; j < ntohl(p_field_rec->field_size) / 32; j++) {
						if (j == (ntohl(p_field_rec->field_size) / 32) - 1) {
							FSCANF_SINGLE(fd, "%" PRIx32 SSA_DB_HELPER_DELIMITER,
								      ((uint32_t *)p_data_field + (j * 4)), i,
								      p_data_tbl_def->name);
						} else {
							FSCANF_SINGLE(fd, "%" PRIx32 SSA_DB_HELPER_ARRAY_DELIMITER,
								      ((uint32_t *)p_data_field + (j * 4)), i,
								      p_data_tbl_def->name);
						}
						*((uint32_t *)p_data_field + (j * 4)) =
								htonl(*((uint32_t *)p_data_field + (j * 4)));
					}
					break;
				case DBF_TYPE_NET64:
					for (j = 0; j < ntohl(p_field_rec->field_size) / 64; j++) {
						if (j == (ntohl(p_field_rec->field_size) / 64) - 1) {
							FSCANF_SINGLE(fd, "0x%" PRIx64 SSA_DB_HELPER_DELIMITER,
								      ((uint64_t *)p_data_field + (j * 8)), i,
								      p_data_tbl_def->name);
						} else {
							FSCANF_SINGLE(fd, "0x%" PRIx64 SSA_DB_HELPER_ARRAY_DELIMITER,
								      ((uint64_t *)p_data_field + (j * 8)), i,
								      p_data_tbl_def->name);
						}
						*((uint64_t *)p_data_field + (j * 8)) =
								htonll(*((uint64_t *)p_data_field + (j * 8)));
					}
					break;
				case DBF_TYPE_NET128:
					/* TODO: add 128 bit handling */
					break;
				case DBF_TYPE_STRING:
					FSCANF_SINGLE(fd, "%s" SSA_DB_HELPER_DELIMITER, ((char *) p_data_field), i, p_data_tbl_def->name);
					break;
				default:
					ssa_log_err(SSA_LOG_DEFAULT, "Unknown field type\n");
					break;
				}
			}
		}

		/* moving file descriptor 1 byte forward due to '\n' char at the end of line */
		fseek(fd, 1, SEEK_CUR);
	}
}