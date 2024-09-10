int
main(int argc, char **argv)
{
	LOGINREC *login;
	DBPROCESS *dbproc;
	int i, rows_sent=0;
	int failed = 0;
	const char *table_name = "all_types_bcp_unittest";

	set_malloc_options();

	read_login_info();

	fprintf(stdout, "Start\n");
	add_bread_crumb();

	dbinit();

	add_bread_crumb();
	dberrhandle(syb_err_handler);
	dbmsghandle(syb_msg_handler);

	fprintf(stdout, "About to logon\n");

	add_bread_crumb();
	login = dblogin();
	DBSETLPWD(login, PASSWORD);
	DBSETLUSER(login, USER);
	DBSETLAPP(login, "bcp.c unit test");
	BCP_SETL(login, 1);

	fprintf(stdout, "About to open %s.%s\n", SERVER, DATABASE);

	add_bread_crumb();
	dbproc = dbopen(login, SERVER);
	if (strlen(DATABASE))
		dbuse(dbproc, DATABASE);
	add_bread_crumb();

	add_bread_crumb();

	if (init(dbproc, table_name))
		exit(1);

	/* set up and send the bcp */
	sprintf(cmd, "%s..%s", DATABASE, table_name);
	fprintf(stdout, "preparing to insert into %s ... ", cmd);
	if (bcp_init(dbproc, cmd, (BYTE *)NULL, (BYTE *)NULL, DB_IN) == FAIL) {
		fprintf(stdout, "failed\n");
    		exit(1);
	}
	fprintf(stdout, "OK\n");

	bind(dbproc);

	fprintf(stdout, "Sending same row 10 times... \n");
	for (i=0; i<10; i++) {
		if (bcp_sendrow(dbproc) == FAIL) {
			fprintf(stdout, "send failed\n");
		        exit(1);
		}
	}
#if 1
	rows_sent = bcp_batch(dbproc);
	if (rows_sent == -1) {
		fprintf(stdout, "batch failed\n");
	        exit(1);
	}
#endif

	fprintf(stdout, "OK\n");

	/* end bcp.  */
	if ((rows_sent += bcp_done(dbproc)) == -1)
	    printf("Bulk copy unsuccessful.\n");
	else
	    printf("%d rows copied.\n", rows_sent);


	printf("done\n");

	add_bread_crumb();

	fprintf(stdout, "Dropping table %s\n", table_name);
	add_bread_crumb();
	sprintf(cmd, "drop table %s", table_name);
	dbcmd(dbproc, cmd);
	add_bread_crumb();
	dbsqlexec(dbproc);
	add_bread_crumb();
	while (dbresults(dbproc) != NO_MORE_RESULTS) {
		/* nop */
	}
	add_bread_crumb();

	failed = 0;

	fprintf(stdout, "dblib %s on %s\n", (failed ? "failed!" : "okay"), __FILE__);
	return failed ? 1 : 0;
}