/*
 *	Return values:
 *	 0 - equal ssa_db structures
 *	 1 - different ssa_db structures
 *	-1 - invalid ssa_db structures
 */
int ssa_db_cmp(struct ssa_db const * const ssa_db1, struct ssa_db const * const ssa_db2)
{
	uint64_t i, j;
	int ret = 0;

	if (!ssa_db1 ||				!ssa_db2 ||
	    !ssa_db1->p_def_tbl ||		!ssa_db2->p_def_tbl ||
	    !ssa_db1->p_db_field_tables ||	!ssa_db2->p_db_field_tables ||
	    !ssa_db1->pp_field_tables ||	!ssa_db2->pp_field_tables ||
	    !ssa_db1->p_db_tables ||		!ssa_db2->p_db_tables ||
	    !ssa_db1->pp_tables ||		!ssa_db2->pp_tables) {
		ret = -1;
		goto out;
	}

	if (ssa_db_def_cmp(&ssa_db1->db_def, &ssa_db2->db_def) ||
	    ssa_db_dataset_cmp(&ssa_db1->db_table_def, &ssa_db2->db_table_def)) {
		ret = 1;
		goto out;
	}

	for (i = 0; i < ntohll(ssa_db1->db_table_def.set_count); i++) {
		if (ssa_db_tbl_def_cmp(&ssa_db1->p_def_tbl[i],
				       &ssa_db2->p_def_tbl[i])) {
			ret = 1;
			goto out;
		}
	}

	if (ssa_db1->data_tbl_cnt != ssa_db2->data_tbl_cnt) {
		ret = 1;
		goto out;
	}

	for (i = 0; i < ssa_db1->data_tbl_cnt; i++) {
		struct db_dataset *dataset1 = &ssa_db1->p_db_field_tables[i];
		struct db_dataset *dataset2 = &ssa_db2->p_db_field_tables[i];

		if (ssa_db_dataset_cmp(dataset1, dataset2)) {
			ret = 1;
			goto out;
		}

		for (j = 0; j < ntohll(dataset1->set_count); j++) {
			if (ssa_db_field_def_cmp(&ssa_db1->pp_field_tables[i][j],
						 &ssa_db2->pp_field_tables[i][j])) {
				ret = 1;
				goto out;
			}
		}
	}

	for (i = 0; i < ssa_db1->data_tbl_cnt; i ++) {
		struct db_dataset *dataset1 = &ssa_db1->p_db_tables[i];
		struct db_dataset *dataset2 = &ssa_db2->p_db_tables[i];

		if (ssa_db_dataset_cmp(dataset1, dataset2)) {
			ret = 1;
			goto out;
		}

		if (memcmp(ssa_db1->pp_tables[i], ssa_db2->pp_tables[i],
			   ntohll(dataset1->set_size))) {
			ret = 1;
			goto out;
		}
	}

out:
	return ret;
}