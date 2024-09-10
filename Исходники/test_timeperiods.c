int main(int argc, char **argv) {
	int result;
	int error = FALSE;
	char *buffer = NULL;
	int display_license = FALSE;
	int display_help = FALSE;
	int c = 0;
	struct tm *tm;
	time_t current_time;
	time_t test_time;
	time_t saved_test_time;
	time_t next_valid_time = 0L;
	time_t chosen_valid_time = 0L;
	char datestring[256];
	host *temp_host = NULL;
	hostgroup *temp_hostgroup = NULL;
	hostsmember *temp_member = NULL;
	timeperiod *temp_timeperiod = NULL;
	int is_valid_time = 0;
	int iterations = 1000;

	plan_tests(6043);

	/* reset program variables */
	reset_variables();

	printf("Reading configuration data...\n");

	config_file = strdup("smallconfig/nagios.cfg");
	/* read in the configuration files (main config file, resource and object config files) */
	result = read_main_config_file(config_file);
	ok(result == OK, "Read main configuration file okay - if fails, use nagios -v to check");

	result = read_all_object_data(config_file);
	ok(result == OK, "Read all object config files");

	result = pre_flight_check();
	ok(result == OK, "Preflight check okay");

	time(&current_time);
	test_time = current_time;
	saved_test_time = current_time;

	temp_timeperiod = find_timeperiod("none");

	is_valid_time = check_time_against_period(test_time, temp_timeperiod);
	ok(is_valid_time == ERROR, "No valid time because time period is empty");

	get_next_valid_time(current_time, &next_valid_time, temp_timeperiod);
	ok(current_time == next_valid_time, "There is no valid time due to timeperiod");

	temp_timeperiod = find_timeperiod("24x7");

	is_valid_time = check_time_against_period(test_time, temp_timeperiod);
	ok(is_valid_time == OK, "Fine because 24x7");

	get_next_valid_time(current_time, &next_valid_time, temp_timeperiod);
	ok((next_valid_time - current_time) <= 2, "Next valid time should be the current_time, but with a 2 second tolerance");


	/* 2009-10-25 is the day when clocks go back an hour in Europe. Bug happens during 23:00 to 00:00 */
	/* This is 23:01:01 */
	saved_test_time = 1256511661;
	saved_test_time = saved_test_time - (24 * 60 * 60);

	putenv("TZ=UTC");
	tzset();
	test_time = saved_test_time;
	c = 0;
	while(c < iterations) {
		is_valid_time = check_time_against_period(test_time, temp_timeperiod);
		ok(is_valid_time == OK, "Always OK for 24x7 with TZ=UTC, time_t=%lu", test_time);
		chosen_valid_time = 0L;
		_get_next_valid_time(test_time, test_time, &chosen_valid_time, temp_timeperiod);
		ok(test_time == chosen_valid_time, "get_next_valid_time always returns same time");
		test_time += 1800;
		c++;
		}

	putenv("TZ=Europe/London");
	tzset();
	test_time = saved_test_time;
	c = 0;
	while(c < iterations) {
		is_valid_time = check_time_against_period(test_time, temp_timeperiod);
		ok(is_valid_time == OK, "Always OK for 24x7 with TZ=Europe/London, time_t=%lu", test_time);
		_get_next_valid_time(test_time, test_time, &chosen_valid_time, temp_timeperiod);
		ok(test_time == chosen_valid_time, "get_next_valid_time always returns same time, time_t=%lu", test_time);
		test_time += 1800;
		c++;
		}

	/* 2009-11-01 is the day when clocks go back an hour in America. Bug happens during 23:00 to 00:00 */
	/* This is 23:01:01 */
	saved_test_time = 1256511661;
	saved_test_time = saved_test_time - (24 * 60 * 60);

	putenv("TZ=America/New_York");
	tzset();
	test_time = saved_test_time;
	c = 0;
	while(c < iterations) {
		is_valid_time = check_time_against_period(test_time, temp_timeperiod);
		ok(is_valid_time == OK, "Always OK for 24x7 with TZ=America/New_York, time_t=%lu", test_time);
		_get_next_valid_time(test_time, test_time, &chosen_valid_time, temp_timeperiod);
		ok(test_time == chosen_valid_time, "get_next_valid_time always returns same time, time_t=%lu", test_time);
		test_time += 1800;
		c++;
		}



	/* Tests around clock change going back for TZ=Europe/London. 1256511661 = Sun Oct
	25 23:01:01 2009 */
	/* A little trip to Paris*/
	putenv("TZ=Europe/Paris");
	tzset();


	/* Timeperiod exclude tests, from Jean Gabes */
	temp_timeperiod = find_timeperiod("Test_exclude");
	ok(temp_timeperiod != NULL, "ME: Testing Exclude timeperiod");
	test_time = 1278939600;
	/* printf("Testing at time %s", ctime(&test_time)); */
	is_valid_time = check_time_against_period(test_time, temp_timeperiod);
	ok(is_valid_time == ERROR, "ME: 12 Jul 2010 15:00:00 - false");

	_get_next_valid_time(test_time, test_time, &chosen_valid_time, temp_timeperiod);
	/* printf("JEAN: Got chosent time at %s", ctime(&chosen_valid_time)); */
	todo_start("Bug in exclude");
	ok(chosen_valid_time == 1288103400, "ME: Next valid time=Tue Oct 26 16:30:00 2010");
	todo_end();


	temp_timeperiod = find_timeperiod("Test_exclude2");
	ok(temp_timeperiod != NULL, "ME: Testing Exclude timeperiod 2");
	test_time = 1278939600;
	/* printf("Testing at time %s", ctime(&test_time)); */
	is_valid_time = check_time_against_period(test_time, temp_timeperiod);
	ok(is_valid_time == ERROR, "ME: 12 Jul 2010 15:00:00 - false");
	_get_next_valid_time(test_time, test_time, &chosen_valid_time, temp_timeperiod);
	/* printf("JEAN: Got chosent time at %s", ctime(&chosen_valid_time)); */
	todo_start("Bug in exclude 2");
	ok(chosen_valid_time == 1279058340, "ME: Next valid time=Tue Jul 13 23:59:00 2010");
	todo_end();


	temp_timeperiod = find_timeperiod("Test_exclude3");
	ok(temp_timeperiod != NULL, "ME: Testing Exclude timeperiod 3");
	test_time = 1278939600;
	/* printf("Testing at time %s", ctime(&test_time)); */
	is_valid_time = check_time_against_period(test_time, temp_timeperiod);
	ok(is_valid_time == ERROR, "ME: 12 Jul 2010 15:00:00 - false");
	_get_next_valid_time(test_time, test_time, &chosen_valid_time, temp_timeperiod);
	/* printf("JEAN: Got chosent time at %s", ctime(&chosen_valid_time)); */
	todo_start("Bug in exclude 3");
	ok(chosen_valid_time == 1284474600, "ME: Next valid time=Tue Sep 14 16:30:00 2010");
	todo_end();


	temp_timeperiod = find_timeperiod("Test_exclude4");
	ok(temp_timeperiod != NULL, "ME: Testing Exclude timeperiod 4");
	test_time = 1278939600;
	/* printf("Testing at time %s", ctime(&test_time)); */
	is_valid_time = check_time_against_period(test_time, temp_timeperiod);
	ok(is_valid_time == ERROR, "ME: 12 Jul 2010 15:00:00 - false");
	_get_next_valid_time(test_time, test_time, &chosen_valid_time, temp_timeperiod);
	/* printf("JEAN: Got chosent time at %s", ctime(&chosen_valid_time)); */
	todo_start("Bug in exclude 3");
	ok(chosen_valid_time == 1283265000, "ME: Next valid time=Tue Aug 31 16:30:00 2010");
	todo_end();




	/* Back to New york */
	putenv("TZ=America/New_York");
	tzset();


	temp_timeperiod = find_timeperiod("sunday_only");
	ok(temp_timeperiod != NULL, "Testing Sunday 00:00-01:15,03:15-22:00");
	putenv("TZ=Europe/London");
	tzset();


	test_time = 1256421000;
	is_valid_time = check_time_against_period(test_time, temp_timeperiod);
	ok(is_valid_time == ERROR, "Sat Oct 24 22:50:00 2009 - false");
	_get_next_valid_time(test_time, test_time, &chosen_valid_time, temp_timeperiod);
	ok(chosen_valid_time == 1256425200, "Next valid time=Sun Oct 25 00:00:00 2009");


	test_time = 1256421661;
	is_valid_time = check_time_against_period(test_time, temp_timeperiod);
	ok(is_valid_time == ERROR, "Sat Oct 24 23:01:01 2009 - false");
	_get_next_valid_time(test_time, test_time, &chosen_valid_time, temp_timeperiod);
	ok(chosen_valid_time == 1256425200, "Next valid time=Sun Oct 25 00:00:00 2009");

	test_time = 1256425400;
	is_valid_time = check_time_against_period(test_time, temp_timeperiod);
	ok(is_valid_time == OK, "Sun Oct 25 00:03:20 2009 - true");
	_get_next_valid_time(test_time, test_time, &chosen_valid_time, temp_timeperiod);
	ok(chosen_valid_time == test_time, "Next valid time=Sun Oct 25 00:03:20 2009");

	test_time = 1256429700;
	is_valid_time = check_time_against_period(test_time, temp_timeperiod);
	ok(is_valid_time == OK, "Sun Oct 25 01:15:00 2009 - true");
	_get_next_valid_time(test_time, test_time, &chosen_valid_time, temp_timeperiod);
	ok(chosen_valid_time == test_time, "Next valid time=Sun Oct 25 01:15:00 2009");

	test_time = 1256430400;
	is_valid_time = check_time_against_period(test_time, temp_timeperiod);
	ok(is_valid_time == ERROR, "Sun Oct 25 01:26:40 2009 - false");
	_get_next_valid_time(test_time, test_time, &chosen_valid_time, temp_timeperiod);
	todo_start("Is a bug in get_next_valid_time for a time that falls in the DST change hour period");
	ok(chosen_valid_time == 1256440500, "Next valid time=Sun Oct 25 03:15:00 2009") || printf("chosen_valid_time=%lu\n", chosen_valid_time);
	todo_end();

	test_time = 1256440500;
	is_valid_time = check_time_against_period(test_time, temp_timeperiod);
	ok(is_valid_time == OK, "Sun Oct 25 03:15:00 2009 - true");
	_get_next_valid_time(test_time, test_time, &chosen_valid_time, temp_timeperiod);
	ok(chosen_valid_time == test_time, "Next valid time=Sun Oct 25 03:15:00 2009");

	test_time = 1256500000;
	is_valid_time = check_time_against_period(test_time, temp_timeperiod);
	ok(is_valid_time == OK, "Sun Oct 25 19:46:40 2009 - true");
	_get_next_valid_time(test_time, test_time, &chosen_valid_time, temp_timeperiod);
	ok(chosen_valid_time == 1256500000, "Next valid time=Sun Oct 25 19:46:40 2009");

	test_time = 1256508000;
	is_valid_time = check_time_against_period(test_time, temp_timeperiod);
	ok(is_valid_time == OK, "Sun Oct 25 22:00:00 2009 - true");
	_get_next_valid_time(test_time, test_time, &chosen_valid_time, temp_timeperiod);
	ok(chosen_valid_time == 1256508000, "Next valid time=Sun Oct 25 22:00:00 2009");

	test_time = 1256508001;
	is_valid_time = check_time_against_period(test_time, temp_timeperiod);
	ok(is_valid_time == ERROR, "Sun Oct 25 22:00:01 2009 - false");
	_get_next_valid_time(test_time, test_time, &chosen_valid_time, temp_timeperiod);
	ok(chosen_valid_time == 1257033600, "Next valid time=Sun Nov 1 00:00:00 2009");

	test_time = 1256513000;
	is_valid_time = check_time_against_period(test_time, temp_timeperiod);
	ok(is_valid_time == ERROR, "Sun Oct 25 23:23:20 2009 - false");
	_get_next_valid_time(test_time, test_time, &chosen_valid_time, temp_timeperiod);
	ok(chosen_valid_time == 1257033600, "Next valid time=Sun Nov 1 00:00:00 2009");




	temp_timeperiod = find_timeperiod("weekly_complex");
	ok(temp_timeperiod != NULL, "Testing complex weekly timeperiod definition");
	putenv("TZ=America/New_York");
	tzset();

	test_time = 1268109420;
	is_valid_time = check_time_against_period(test_time, temp_timeperiod);
	ok(is_valid_time == ERROR, "Mon Mar  8 23:37:00 2010 - false");
	_get_next_valid_time(test_time, test_time, &chosen_valid_time, temp_timeperiod);
	ok(chosen_valid_time == 1268115300, "Next valid time=Tue Mar  9 01:15:00 2010");





	cleanup();

	my_free(config_file);

	return exit_status();
	}