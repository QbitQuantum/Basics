/****************************************************************//**
Evaluate the given foreign key SQL statement.
@return	error code or DB_SUCCESS */
static
ulint
dict_foreign_eval_sql(
/*==================*/
	pars_info_t*	info,	/*!< in: info struct, or NULL */
	const char*	sql,	/*!< in: SQL string to evaluate */
	dict_table_t*	table,	/*!< in: table */
	dict_foreign_t*	foreign,/*!< in: foreign */
	trx_t*		trx)	/*!< in: transaction */
{
	ulint		error;
	FILE*		ef	= dict_foreign_err_file;

	error = que_eval_sql(info, sql, FALSE, trx);

	if (error == DB_DUPLICATE_KEY) {
		mutex_enter(&dict_foreign_err_mutex);
		rewind(ef);
		ut_print_timestamp(ef);
		fputs(" Error in foreign key constraint creation for table ",
		      ef);
		ut_print_name(ef, trx, TRUE, table->name);
		fputs(".\nA foreign key constraint of name ", ef);
		ut_print_name(ef, trx, TRUE, foreign->id);
		fputs("\nalready exists."
		      " (Note that internally InnoDB adds 'databasename'\n"
		      "in front of the user-defined constraint name.)\n"
		      "Note that InnoDB's FOREIGN KEY system tables store\n"
		      "constraint names as case-insensitive, with the\n"
		      "MySQL standard latin1_swedish_ci collation. If you\n"
		      "create tables or databases whose names differ only in\n"
		      "the character case, then collisions in constraint\n"
		      "names can occur. Workaround: name your constraints\n"
		      "explicitly with unique names.\n",
		      ef);

		mutex_exit(&dict_foreign_err_mutex);

		return(error);
	}

	if (error != DB_SUCCESS) {
		fprintf(stderr,
			"InnoDB: Foreign key constraint creation failed:\n"
			"InnoDB: internal error number %lu\n", (ulong) error);

		mutex_enter(&dict_foreign_err_mutex);
		ut_print_timestamp(ef);
		fputs(" Internal error in foreign key constraint creation"
		      " for table ", ef);
		ut_print_name(ef, trx, TRUE, table->name);
		fputs(".\n"
		      "See the MySQL .err log in the datadir"
		      " for more information.\n", ef);
		mutex_exit(&dict_foreign_err_mutex);

		return(error);
	}

	return(DB_SUCCESS);
}