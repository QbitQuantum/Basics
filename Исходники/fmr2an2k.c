static int
create_type1(RECORD **anrecord) 
{
	ITEM *item = NULL;
	SUBFIELD *subfield = NULL;
	FIELD *field = NULL;
	RECORD *lrecord;	// For local convenience
	char buf[32];
	char *date_str;
	time_t tod;
	struct tm *tm;

	if (new_ANSI_NIST_record(anrecord, TYPE_1_ID) != 0) 
		ALLOC_ERR_EXIT("Type-1 Record");

	lrecord = *anrecord;

	/*** 1.001 Logical record length ***/
	// Set the length to 0 for now; it will be updated when the record
	// is closed
	APPEND_TYPE1_FIELD(lrecord, LEN_ID, "0");

	/*** 1.002 - Version number ***/
	snprintf(buf, sizeof(buf), "%04d", VERSION_0300);
	APPEND_TYPE1_FIELD(lrecord, VER_ID, buf);

	/*** 1.003 - File content ***/
	snprintf(buf, sizeof(buf), "%d", TYPE_1_ID);
	// Allocate a new subfield and set the first item
	if (value2subfield(&subfield, buf) != 0)
		ERR_OUT("allocating Type-1 subfield");
	// Add the second item to the subfield, the count of remaining records
	if (value2item(&item, "0") != 0)
		ERR_OUT("allocating Type-1 item");
	if (append_ANSI_NIST_subfield(subfield, item) != 0)
		ERR_OUT("appending Type-1 item");
	// Add the subfield to the field
	if (new_ANSI_NIST_field(&field, TYPE_1_ID, CNT_ID) != 0)
		ERR_OUT("allocating Type-1 field");
	if (append_ANSI_NIST_field(field, subfield) != 0)
		ERR_OUT("appending Type-1 subfield");

	// Add the entire field to the record
	if (append_ANSI_NIST_record(lrecord, field) != 0)
		ERR_OUT("appending Type-1 field");

	/*** 1.004 - Type of transaction ***/
	APPEND_TYPE1_FIELD(lrecord, 4, "LFFS");

	/*** 1.005 - Date ***/
	if (get_ANSI_NIST_date(&date_str) != 0)
		ERR_OUT("getting ANSI/NIST date");
	APPEND_TYPE1_FIELD(lrecord, DAT_ID, date_str);
	free(date_str);

	/*** 1.007 - Destination agency identifier ***/
	APPEND_TYPE1_FIELD(lrecord, 7, "ANSI/NIST");

	/*** 1.008 - Originating agency identifier ***/
	APPEND_TYPE1_FIELD(lrecord, 8, "M1/FMR");

	/*** 1.009 - Transaction control number ***/
	// Use the current UTC time string YYYYMMDDHHMMSS
	tod = time(NULL);
	tm = gmtime(&tod);
	snprintf(buf, sizeof(buf), "%04d%02d%02d%02d%02d%02d",
	    tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, tm->tm_hour, 
	    tm->tm_min, tm->tm_sec);
	
	APPEND_TYPE1_FIELD(lrecord, 9, buf);

	/*** 1.011 - Native scanning resolution ***/
	// XXX Set the NSR to the minimum, but we may want to base this
	// XXX value on something from the FMR
	snprintf(buf, sizeof(buf), "%5.2f", MIN_RESOLUTION);
	APPEND_TYPE1_FIELD(lrecord, 11, buf);

	/*** 1.012 - Nominal transmitting resolution ***/
	APPEND_TYPE1_FIELD(lrecord, 12, buf);

	if (update_ANSI_NIST_tagged_record_LEN(lrecord) != 0)
		ERR_OUT("updating record length");
	
	return 0;

err_out:
	fprintf(stderr, "Error creating Type-1 record\n");
	if (item != NULL)
		free_ANSI_NIST_item(item);
	if (subfield != NULL)
		free_ANSI_NIST_subfield(subfield);
	if (field != NULL)
		free_ANSI_NIST_field(field);
	if (lrecord != NULL)
		free_ANSI_NIST_record(lrecord);

	return -1;
}