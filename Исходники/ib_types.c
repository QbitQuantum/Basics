/*********************************************************************
CREATE TABLE T(
 	c1 VARCHAR(n),
       	c2 INT NOT NULL,
       	c3 FLOAT,
       	c4 DOUBLE,
       	c5 BLOB,
	c6 DECIMAL,
	PK(c1));  */
static
ib_err_t
create_table(
/*=========*/
	const char*	dbname,			/*!< in: database name */
	const char*	name)			/*!< in: table name */
{
	ib_trx_t	ib_trx;
	ib_id_t		table_id = 0;
	ib_err_t	err = DB_SUCCESS;
	ib_tbl_sch_t	ib_tbl_sch = NULL;
	ib_idx_sch_t	ib_idx_sch = NULL;
	char		table_name[IB_MAX_TABLE_NAME_LEN];

#ifdef __WIN__
	sprintf(table_name, "%s/%s", dbname, name);
#else
	snprintf(table_name, sizeof(table_name), "%s/%s", dbname, name);
#endif

	/* Pass a table page size of 0, ie., use default page size. */
	err = ib_table_schema_create(
		table_name, &ib_tbl_sch, IB_TBL_COMPACT, 0);

	assert(err == DB_SUCCESS);

	err = ib_table_schema_add_col(
		ib_tbl_sch, "c1", IB_VARCHAR, IB_COL_NONE, 0, 10);

	assert(err == DB_SUCCESS);

	err = ib_table_schema_add_col(
		ib_tbl_sch, "c2", IB_INT, IB_COL_NOT_NULL, 0, sizeof(ib_u32_t));
	assert(err == DB_SUCCESS);

	err = ib_table_schema_add_col(
		ib_tbl_sch, "c3", IB_FLOAT, IB_COL_NONE, 0, sizeof(float));
	assert(err == DB_SUCCESS);

	err = ib_table_schema_add_col(
		ib_tbl_sch, "c4", IB_DOUBLE, IB_COL_NONE, 0, sizeof(double));
	assert(err == DB_SUCCESS);

	err = ib_table_schema_add_col(
		ib_tbl_sch, "c5", IB_BLOB, IB_COL_NONE, 0, 0);
	assert(err == DB_SUCCESS);

	err = ib_table_schema_add_col(
		ib_tbl_sch, "c6", IB_DECIMAL, IB_COL_NONE, 0, 0);
	assert(err == DB_SUCCESS);

	err = ib_table_schema_add_index(ib_tbl_sch, "PRIMARY", &ib_idx_sch);
	assert(err == DB_SUCCESS);

	/* Set prefix length to 0. */
	err = ib_index_schema_add_col( ib_idx_sch, "c1", 0);
	assert(err == DB_SUCCESS);

	err = ib_index_schema_set_clustered(ib_idx_sch);
	assert(err == DB_SUCCESS);

	/* create table */
	ib_trx = ib_trx_begin(IB_TRX_REPEATABLE_READ);
	err = ib_schema_lock_exclusive(ib_trx);
	assert(err == DB_SUCCESS);

	err = ib_table_create(ib_trx, ib_tbl_sch, &table_id);
	assert(err == DB_SUCCESS);

	err = ib_trx_commit(ib_trx);
	assert(err == DB_SUCCESS);

	if (ib_tbl_sch != NULL) {
		ib_table_schema_delete(ib_tbl_sch);
	}

	return(err);
}