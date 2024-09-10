unsigned short check_drivers(unsigned short dump) {
	SQLUSMALLINT dir = SQL_FETCH_FIRST;
	char driver[BUFLEN + 1];
	SQLSMALLINT driver_ret;
	char attr[BUFLEN + 1];
	SQLSMALLINT attr_ret;
	SQLRETURN ret;
	unsigned short found = 0;

	while (SQL_SUCCEEDED(ret = SQLDrivers(H_ENV, dir, driver, sizeof(driver), &driver_ret, attr, sizeof(attr), &attr_ret))) {
		dir = SQL_FETCH_NEXT;
		if (1 == dump) {
			printf("%s - %s\n", driver, attr);
			if (ret == SQL_SUCCESS_WITH_INFO) printf("\tdata truncation\n");
		}
		else if (strncmp(driver, SQLDRV, sizeof(driver)) == 0) {
			found = 1;
			break;
		}
	}

	return (0 == dump && 0 == found);
}