END_TEST

START_TEST(importdb_can_parse_exported_database)
{
	int i;
	char buffer[512];
	DATA filleddb;
	FILE *exportfile;

	initdb();
	strcpy(data.interface, "something");
	strcpy(data.nick, "nothing");
	data.totalrx = 1;
	data.totaltx = 2;
	data.currx = 3;
	data.curtx = 4;
	data.totalrxk = 5;
	data.totaltxk = 6;
	data.btime = 7;

	for (i=0; i<30; i++) {
		data.day[i].date = i+1;
		data.day[i].rx = data.day[i].tx = i*100;
		data.day[i].rxk = data.day[i].txk = i;
		data.day[i].used = 1;
	}

	for (i=0; i<10; i++) {
		data.top10[i].date = i+1;
		data.top10[i].rx = data.top10[i].tx = i*100;
		data.top10[i].rxk = data.top10[i].txk = i;
		data.top10[i].used = 1;
	}

	for (i=0; i<12; i++) {
		data.month[i].month = i+1;
		data.month[i].rx = data.month[i].tx = i*100;
		data.month[i].rxk = data.month[i].txk = i;
		data.month[i].used = 1;
	}

	for (i=0; i<24; i++) {
		data.hour[i].date = i+1;
		data.hour[i].rx = data.hour[i].tx = i*100;
	}

	memcpy(&filleddb, &data, sizeof(DATA));
	ck_assert_int_eq(remove_directory(TESTDIR), 1);
	ck_assert_int_eq(clean_testdbdir(), 1);

	fflush(stdout);
	snprintf(buffer, 512, "%s/dbexport", TESTDBDIR);
	exportfile = fopen(buffer, "w");
	dup2(fileno(exportfile), STDOUT_FILENO);
	fclose(exportfile);
	exportdb();
	fflush(stdout);
	memset(&data, '\0', sizeof(DATA));

	ck_assert_int_gt(importdb(buffer), 0);

	ck_assert_str_eq(data.interface, filleddb.interface);
	ck_assert_str_eq(data.nick, filleddb.nick);
	ck_assert_int_eq(data.version, filleddb.version);
	ck_assert_int_eq(data.active, filleddb.active);
	ck_assert_int_eq(data.totalrx, filleddb.totalrx);
	ck_assert_int_eq(data.totaltx, filleddb.totaltx);
	ck_assert_int_eq(data.currx, filleddb.currx);
	ck_assert_int_eq(data.curtx, filleddb.curtx);
	ck_assert_int_eq(data.totalrxk, filleddb.totalrxk);
	ck_assert_int_eq(data.totaltxk, filleddb.totaltxk);
	ck_assert_int_eq(data.btime, filleddb.btime);
	ck_assert_int_eq(data.created, filleddb.created);
	ck_assert_int_eq(data.lastupdated, filleddb.lastupdated);

	for (i=0; i<30; i++) {
		ck_assert_int_eq(data.day[i].date, filleddb.day[i].date);
		ck_assert_int_eq(data.day[i].rx, filleddb.day[i].rx);
		ck_assert_int_eq(data.day[i].tx, filleddb.day[i].tx);
		ck_assert_int_eq(data.day[i].rxk, filleddb.day[i].rxk);
		ck_assert_int_eq(data.day[i].txk, filleddb.day[i].txk);
		ck_assert_int_eq(data.day[i].used, filleddb.day[i].used);
	}

	for (i=0; i<10; i++) {
		ck_assert_int_eq(data.top10[i].date, filleddb.top10[i].date);
		ck_assert_int_eq(data.top10[i].rx, filleddb.top10[i].rx);
		ck_assert_int_eq(data.top10[i].tx, filleddb.top10[i].tx);
		ck_assert_int_eq(data.top10[i].rxk, filleddb.top10[i].rxk);
		ck_assert_int_eq(data.top10[i].txk, filleddb.top10[i].txk);
		ck_assert_int_eq(data.top10[i].used, filleddb.top10[i].used);
	}

	for (i=0; i<12; i++) {
		ck_assert_int_eq(data.month[i].month, filleddb.month[i].month);
		ck_assert_int_eq(data.month[i].rx, filleddb.month[i].rx);
		ck_assert_int_eq(data.month[i].tx, filleddb.month[i].tx);
		ck_assert_int_eq(data.month[i].rxk, filleddb.month[i].rxk);
		ck_assert_int_eq(data.month[i].txk, filleddb.month[i].txk);
		ck_assert_int_eq(data.month[i].used, filleddb.month[i].used);
	}

	for (i=0; i<24; i++) {
		ck_assert_int_eq(data.hour[i].date, filleddb.hour[i].date);
		ck_assert_int_eq(data.hour[i].rx, filleddb.hour[i].rx);
		ck_assert_int_eq(data.hour[i].tx, filleddb.hour[i].tx);
	}
}