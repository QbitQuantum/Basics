int compare_VMSEntryInfo_structs(VMSEntryInfo * entry1, VMSEntryInfo * entry2)
{
    int i, status;
    char date1[16], date2[16], time1[8], time2[8], month[4];

    switch (HTfileSortMethod) {
    case FILE_BY_SIZE:
	/* both equal or both 0 */
	if (entry1->size == entry2->size)
	    return (strcasecomp(entry1->filename,
				entry2->filename));
	else if (entry1->size > entry2->size)
	    return (1);
	else
	    return (-1);
    case FILE_BY_TYPE:
	if (entry1->type && entry2->type) {
	    status = strcasecomp(entry1->type, entry2->type);
	    if (status)
		return (status);
	    /* else fall to filename comparison */
	}
	return (strcasecomp(entry1->filename,
			    entry2->filename));
    case FILE_BY_DATE:
	if (entry1->date && entry2->date) {
	    /*
	     * Make sure we have the correct length. - FM
	     */
	    if (strlen(entry1->date) != 12 ||
		strlen(entry2->date) != 12) {
		return (strcasecomp(entry1->filename,
				    entry2->filename));
	    }
	    /*
	     * Set up for sorting in reverse
	     * chronological order. - FM
	     */
	    if (entry1->date[7] != ' ') {
		strcpy(date1, "9999");
		strcpy(time1, (char *) &entry1->date[7]);
	    } else {
		strcpy(date1, (char *) &entry1->date[8]);
		strcpy(time1, "00:00");
	    }
	    LYStrNCpy(month, entry1->date, 3);
	    for (i = 0; i < 12; i++) {
		if (!strcasecomp(month, months[i])) {
		    break;
		}
	    }
	    i++;
	    sprintf(month, "%02d", i);
	    strcat(date1, month);
	    StrNCat(date1, (char *) &entry1->date[4], 2);
	    date1[8] = '\0';
	    if (date1[6] == ' ') {
		date1[6] = '0';
	    }
	    strcat(date1, time1);
	    if (entry2->date[7] != ' ') {
		strcpy(date2, "9999");
		strcpy(time2, (char *) &entry2->date[7]);
	    } else {
		strcpy(date2, (char *) &entry2->date[8]);
		strcpy(time2, "00:00");
	    }
	    LYStrNCpy(month, entry2->date, 3);
	    for (i = 0; i < 12; i++) {
		if (!strcasecomp(month, months[i])) {
		    break;
		}
	    }
	    i++;
	    sprintf(month, "%02d", i);
	    strcat(date2, month);
	    StrNCat(date2, (char *) &entry2->date[4], 2);
	    date2[8] = '\0';
	    if (date2[6] == ' ') {
		date2[6] = '0';
	    }
	    strcat(date2, time2);
	    /*
	     * Do the comparison. - FM
	     */
	    status = strcasecomp(date2, date1);
	    if (status)
		return (status);
	    /* else fall to filename comparison */
	}
	return (strcasecomp(entry1->filename,
			    entry2->filename));
    case FILE_BY_NAME:
    default:
	return (strcmp(entry1->filename,
		       entry2->filename));
    }
}