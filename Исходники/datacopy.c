static int
transfer_data(BCPPARAMDATA params, DBPROCESS * dbsrc, DBPROCESS * dbdest)
{
	char ls_command[256];
	int col;

	DBINT src_numcols = 0;

	DBINT src_datlen;

	typedef struct migcoldata
	{
		DBINT coltype;
		DBINT collen;
		DBINT nullind;
		DBCHAR *data;
	} MIGCOLDATA;

	MIGCOLDATA **srcdata;

	DBINT rows_read = 0;
	DBINT rows_sent = 0;
	DBINT rows_done = 0;
	DBINT ret;

	struct timeval start_time;
	struct timeval end_time;
	double elapsed_time;
	struct timeval batch_start;
	struct timeval batch_end;
	double elapsed_batch = 0.0;

	if (params.vflag) {
		printf("\nStarting copy...\n");
	}

	if (params.tflag) {

		sprintf(ls_command, "truncate table %s", params.ddbobject);

		if (dbcmd(dbdest, ls_command) == FAIL) {
			printf("dbcmd failed\n");
			return FALSE;
		}

		if (dbsqlexec(dbdest) == FAIL) {
			printf("dbsqlexec failed\n");
			return FALSE;
		}

		if (dbresults(dbdest) == FAIL) {
			printf("Error in dbresults\n");
			return FALSE;
		}
	}


	sprintf(ls_command, "select * from %s", params.sdbobject);

	if (dbcmd(dbsrc, ls_command) == FAIL) {
		printf("dbcmd failed\n");
		return FALSE;
	}

	if (dbsqlexec(dbsrc) == FAIL) {
		printf("dbsqlexec failed\n");
		return FALSE;
	}

	if (NO_MORE_RESULTS != dbresults(dbsrc));
	{
		if (0 == (src_numcols = dbnumcols(dbsrc))) {
			printf("Error in dbnumcols\n");
			return FALSE;
		}
	}



	if (bcp_init(dbdest, params.ddbobject, (char *) NULL, (char *) NULL, DB_IN) == FAIL) {
		printf("Error in bcp_init\n");
		return FALSE;
	}

	srcdata = (MIGCOLDATA **) malloc(sizeof(MIGCOLDATA *) * src_numcols);

	for (col = 0; col < src_numcols; col++) {

		srcdata[col] = (MIGCOLDATA *) malloc(sizeof(MIGCOLDATA));
		memset(srcdata[col], '\0', sizeof(MIGCOLDATA));
		srcdata[col]->coltype = dbcoltype(dbsrc, col + 1);
		srcdata[col]->collen = dbcollen(dbsrc, col + 1);

		switch (srcdata[col]->coltype) {
		case SYBBIT:
			srcdata[col]->data = malloc(sizeof(DBBIT));
			if (srcdata[col]->data == (char *) NULL) {
				printf("allocation error\n");
				return FALSE;
			}
			dbbind(dbsrc, col + 1, BITBIND, sizeof(DBBIT), (BYTE *) srcdata[col]->data);
			dbnullbind(dbsrc, col + 1, &(srcdata[col]->nullind));
			if (bcp_bind(dbdest, (BYTE *) srcdata[col]->data, 0, -1, NULL, 0, SYBBIT, col + 1) == FAIL) {
				printf("bcp_bind error\n");
				return FALSE;
			}
			break;
		case SYBINT1:
			srcdata[col]->data = malloc(sizeof(DBTINYINT));
			if (srcdata[col]->data == (char *) NULL) {
				printf("allocation error\n");
				return FALSE;
			}
			dbbind(dbsrc, col + 1, TINYBIND, sizeof(DBTINYINT), (BYTE *) srcdata[col]->data);
			dbnullbind(dbsrc, col + 1, &(srcdata[col]->nullind));
			if (bcp_bind(dbdest, (BYTE *) srcdata[col]->data, 0, -1, NULL, 0, SYBINT1, col + 1) == FAIL) {
				printf("bcp_bind error\n");
				return FALSE;
			}
			break;

		case SYBINT2:
			srcdata[col]->data = malloc(sizeof(DBSMALLINT));
			if (srcdata[col]->data == (char *) NULL) {
				printf("allocation error\n");
				return FALSE;
			}
			dbbind(dbsrc, col + 1, SMALLBIND, sizeof(DBSMALLINT), (BYTE *) srcdata[col]->data);
			dbnullbind(dbsrc, col + 1, &(srcdata[col]->nullind));
			if (bcp_bind(dbdest, (BYTE *) srcdata[col]->data, 0, -1, NULL, 0, SYBINT2, col + 1) == FAIL) {
				printf("bcp_bind error\n");
				return FALSE;
			}
			break;

		case SYBINT4:
			srcdata[col]->data = malloc(sizeof(DBINT));
			if (srcdata[col]->data == (char *) NULL) {
				printf("allocation error\n");
				return FALSE;
			}
			dbbind(dbsrc, col + 1, INTBIND, sizeof(DBINT), (BYTE *) srcdata[col]->data);
			dbnullbind(dbsrc, col + 1, &(srcdata[col]->nullind));
			if (bcp_bind(dbdest, (BYTE *) srcdata[col]->data, 0, -1, NULL, 0, SYBINT4, col + 1) == FAIL) {
				printf("bcp_bind error\n");
				return FALSE;
			}
			break;

		case SYBFLT8:
			srcdata[col]->data = malloc(sizeof(DBFLT8));
			if (srcdata[col]->data == (char *) NULL) {
				printf("allocation error\n");
				return FALSE;
			}
			dbbind(dbsrc, col + 1, FLT8BIND, sizeof(DBFLT8), (BYTE *) srcdata[col]->data);
			dbnullbind(dbsrc, col + 1, &(srcdata[col]->nullind));
			if (bcp_bind(dbdest, (BYTE *) srcdata[col]->data, 0, -1, NULL, 0, SYBFLT8, col + 1) == FAIL) {
				printf("bcp_bind error\n");
				return FALSE;
			}
			break;

		case SYBREAL:
			srcdata[col]->data = malloc(sizeof(DBREAL));
			if (srcdata[col]->data == (char *) NULL) {
				printf("allocation error\n");
				return FALSE;
			}
			dbbind(dbsrc, col + 1, REALBIND, sizeof(DBREAL), (BYTE *) srcdata[col]->data);
			dbnullbind(dbsrc, col + 1, &(srcdata[col]->nullind));
			if (bcp_bind(dbdest, (BYTE *) srcdata[col]->data, 0, -1, NULL, 0, SYBREAL, col + 1) == FAIL) {
				printf("bcp_bind error\n");
				return FALSE;
			}
			break;

		case SYBMONEY:
			srcdata[col]->data = malloc(sizeof(DBMONEY));
			if (srcdata[col]->data == (char *) NULL) {
				printf("allocation error\n");
				return FALSE;
			}
			dbbind(dbsrc, col + 1, MONEYBIND, sizeof(DBMONEY), (BYTE *) srcdata[col]->data);
			dbnullbind(dbsrc, col + 1, &(srcdata[col]->nullind));
			if (bcp_bind(dbdest, (BYTE *) srcdata[col]->data, 0, -1, NULL, 0, SYBMONEY, col + 1) == FAIL) {
				printf("bcp_bind error\n");
				return FALSE;
			}
			break;

		case SYBMONEY4:
			srcdata[col]->data = malloc(sizeof(DBMONEY4));
			if (srcdata[col]->data == (char *) NULL) {
				printf("allocation error\n");
				return FALSE;
			}
			dbbind(dbsrc, col + 1, SMALLMONEYBIND, sizeof(DBMONEY4), (BYTE *) srcdata[col]->data);
			dbnullbind(dbsrc, col + 1, &(srcdata[col]->nullind));
			if (bcp_bind(dbdest, (BYTE *) srcdata[col]->data, 0, -1, NULL, 0, SYBMONEY4, col + 1) == FAIL) {
				printf("bcp_bind error\n");
				return FALSE;
			}
			break;

		case SYBDATETIME:
			srcdata[col]->data = malloc(sizeof(DBDATETIME));
			if (srcdata[col]->data == (char *) NULL) {
				printf("allocation error\n");
				return FALSE;
			}
			dbbind(dbsrc, col + 1, DATETIMEBIND, sizeof(DBDATETIME), (BYTE *) srcdata[col]->data);
			dbnullbind(dbsrc, col + 1, &(srcdata[col]->nullind));
			if (bcp_bind(dbdest, (BYTE *) srcdata[col]->data, 0, -1, NULL, 0, SYBDATETIME, col + 1) == FAIL) {
				printf("bcp_bind error\n");
				return FALSE;
			}
			break;

		case SYBDATETIME4:
			srcdata[col]->data = malloc(sizeof(DBDATETIME4));
			if (srcdata[col]->data == (char *) NULL) {
				printf("allocation error\n");
				return FALSE;
			}
			dbbind(dbsrc, col + 1, SMALLDATETIMEBIND, sizeof(DBDATETIME), (BYTE *) srcdata[col]->data);
			dbnullbind(dbsrc, col + 1, &(srcdata[col]->nullind));
			if (bcp_bind(dbdest, (BYTE *) srcdata[col]->data, 0, -1, NULL, 0, SYBDATETIME4, col + 1) == FAIL) {
				printf("bcp_bind error\n");
				return FALSE;
			}
			break;

		case SYBNUMERIC:
			srcdata[col]->data = malloc(sizeof(DBNUMERIC));
			if (srcdata[col]->data == (char *) NULL) {
				printf("allocation error\n");
				return FALSE;
			}
			dbbind(dbsrc, col + 1, NUMERICBIND, sizeof(DBNUMERIC), (BYTE *) srcdata[col]->data);
			dbnullbind(dbsrc, col + 1, &(srcdata[col]->nullind));
			if (bcp_bind(dbdest, (BYTE *) srcdata[col]->data, 0, sizeof(DBNUMERIC), NULL, 0, SYBNUMERIC, col + 1) ==
			    FAIL) {
				printf("bcp_bind error\n");
				return FALSE;
			}
			break;

		case SYBDECIMAL:
			srcdata[col]->data = malloc(sizeof(DBDECIMAL));
			if (srcdata[col]->data == (char *) NULL) {
				printf("allocation error\n");
				return FALSE;
			}
			dbbind(dbsrc, col + 1, DECIMALBIND, sizeof(DBDECIMAL), (BYTE *) srcdata[col]->data);
			dbnullbind(dbsrc, col + 1, &(srcdata[col]->nullind));
			if (bcp_bind(dbdest, (BYTE *) srcdata[col]->data, 0, sizeof(DBDECIMAL), NULL, 0, SYBDECIMAL, col + 1) ==
			    FAIL) {
				printf("bcp_bind error\n");
				return FALSE;
			}
			break;
		case SYBTEXT:
		case SYBCHAR:
			srcdata[col]->data = malloc(srcdata[col]->collen + 1);
			if (srcdata[col]->data == (char *) NULL) {
				printf("allocation error\n");
				return FALSE;
			}
			dbbind(dbsrc, col + 1, NTBSTRINGBIND, srcdata[col]->collen + 1, (BYTE *) srcdata[col]->data);
			dbnullbind(dbsrc, col + 1, &(srcdata[col]->nullind));
			if (bcp_bind(dbdest, (BYTE *) srcdata[col]->data, 0, -1, NULL, 0, SYBCHAR, col + 1) == FAIL) {
				printf("bcp_bind error\n");
				return FALSE;
			}
			break;
		}
	}

	gettimeofday(&start_time, 0);

	while (dbnextrow(dbsrc) != NO_MORE_ROWS) {
		rows_read++;
		for (col = 0; col < src_numcols; col++) {
			switch (srcdata[col]->coltype) {
			case SYBBIT:
			case SYBINT1:
			case SYBINT2:
			case SYBINT4:
			case SYBFLT8:
			case SYBREAL:
			case SYBDATETIME:
			case SYBDATETIME4:
			case SYBMONEY:
			case SYBMONEY4:
				if (srcdata[col]->nullind == -1) {	/* NULL data retrieved from source */
					bcp_collen(dbdest, 0, col + 1);
				} else {
					bcp_collen(dbdest, -1, col + 1);
				}
				break;
			case SYBNUMERIC:
				if (srcdata[col]->nullind == -1) {	/* NULL data retrieved from source */
					bcp_collen(dbdest, 0, col + 1);
				} else {
					bcp_collen(dbdest, sizeof(DBNUMERIC), col + 1);
				}
				break;
			case SYBDECIMAL:
				if (srcdata[col]->nullind == -1) {	/* NULL data retrieved from source */
					bcp_collen(dbdest, 0, col + 1);
				} else {
					bcp_collen(dbdest, sizeof(DBDECIMAL), col + 1);
				}
				break;
			case SYBTEXT:
			case SYBCHAR:
				if (srcdata[col]->nullind == -1) {	/* NULL data retrieved from source */
					bcp_collen(dbdest, 0, col + 1);
				} else {

					/*
					 * if there is zero length data, then the
					 * input data MUST have been all blanks,
					 * trimmed down to nothing by the bind
					 * type of NTBSTRINGBIND.
					 * so find out the source data length and
					 * re-set the data accordingly...
					 */

					if (strlen(srcdata[col]->data) == 0) {
						src_datlen = dbdatlen(dbsrc, col + 1);
						memset(srcdata[col]->data, ' ', src_datlen);
						srcdata[col]->data[src_datlen] = '\0';
					}
					bcp_collen(dbdest, strlen(srcdata[col]->data), col + 1);
				}
				break;
			}
		}
		if (bcp_sendrow(dbdest) == FAIL) {
			fprintf(stderr, "bcp_sendrow failed.  \n");
			return FALSE;
		} else {
			rows_sent++;
			if (rows_sent == params.batchsize) {
				gettimeofday(&batch_start, 0);
				ret = bcp_batch(dbdest);
				gettimeofday(&batch_end, 0);
				elapsed_batch = elapsed_batch +
					((double) (batch_end.tv_sec - batch_start.tv_sec) +
					 ((double) (batch_end.tv_usec - batch_start.tv_usec) / 1000000.00)
					);
				if (ret == -1) {
					printf("bcp_batch error\n");
					return FALSE;
				} else {
					rows_done += ret;
					printf("%d rows successfully copied (total %d)\n", ret, rows_done);
					rows_sent = 0;
				}
			}
		}
	}

	if (rows_read) {
		gettimeofday(&batch_start, 0);
		ret = bcp_done(dbdest);
		gettimeofday(&batch_end, 0);
		elapsed_batch = elapsed_batch +
			((double) (batch_end.tv_sec - batch_start.tv_sec) +
			 ((double) (batch_end.tv_usec - batch_start.tv_usec) / 1000000.00)
			);
		if (ret == -1) {
			fprintf(stderr, "bcp_done failed.  \n");
			return FALSE;
		} else {
			rows_done += ret;
		}
	}

	gettimeofday(&end_time, 0);


	elapsed_time = (double) (end_time.tv_sec - start_time.tv_sec) +
		((double) (end_time.tv_usec - start_time.tv_usec) / 1000000.00);

	if (params.vflag) {
		printf("\n");
		printf("rows read            : %d\n", rows_read);
		printf("rows written         : %d\n", rows_done);
		printf("elapsed time (secs)  : %f\n", elapsed_time);
		printf("rows per second      : %f\n", rows_done / elapsed_time);
	}

	return TRUE;


}