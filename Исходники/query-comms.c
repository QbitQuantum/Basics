/* 
 * -- parse_timestr()
 * 
 * This function parse the time string of a query. The string is made of 
 * two parts representing the two extreme of the time window. They two 
 * parts are separated by a colon (:). 
 * Valid formats for the start and end times are as follows: 
 * 
 *   .   0, to indicate the time the query is received;
 *   .   @[cc[yy[mm[dd[hhmmss]]]]], to indicate an exact time; 
 *   .   [+|-][[^0-9]d][[^0-9]h][[^0-9]m][[^0-9]s], to indicate an offset 
 *       from the time the query is received.  
 * 
 */
static uint32_t
parse_timestr(char * str, timestamp_t * base) 
{
    struct tm timeinfo; 
    time_t ts;
    char * wh; 
    size_t len;
    int adding; 

    assert(str != NULL); 
    assert(base != NULL); 

    ts = TS2SEC(*base);
    gmtime_r(&ts, &timeinfo); 

    /* look if this is a start or end */
    wh = index(str, ':'); 
    len = (wh == NULL)? strlen(str) : (size_t) (wh - str); 
    adding = 0; 

    switch (str[0]) { 
    case '@': 		/* absolute timestamp */
	for (str++, len--; len > 0; str += 2, len -= 2) { 
	    char val[3] = {0}; 

	    /* get two digits */
	    bcopy(str, val, 2); 

	    if (len == 14)  			/* century */
		timeinfo.tm_year = (atoi(val) * 100) - 1900; 
	    else if (len == 12)  		/* year */
		timeinfo.tm_year = atoi(val) + 100*(timeinfo.tm_year/100); 
	    else if (len == 10)  		/* month */
		timeinfo.tm_mon = atoi(val) - 1; 
	    else if (len == 8)  		/* day */
		timeinfo.tm_mday = atoi(val); 
	    else if (len == 6)  		/* hour */
		timeinfo.tm_hour = atoi(val); 
	    else if (len == 4)  		/* minute */
		timeinfo.tm_min = atoi(val); 
	    else if (len == 2)  		/* second */
		timeinfo.tm_sec = atoi(val); 
	    else 				/* error */
		break; 				
	} 
		
	if (len > 0) {
	    logmsg(LOGWARN, "time %s incorrect, using current time\n", str); 
	    return TS2SEC(*base); 
	} 

	ts = timegm(&timeinfo); 
	*base = TIME2TS(ts, 0);
	break; 
	
    case '+': 		/* relative timestamp (after current time) */
	adding = 2; 
	/* pass thru */

    case '-': 		/* relative timestamp (before current time) */
	adding--; 
	
        /* skip first character */
	str++; len--; 

	/* check for one letter (in [dhms]) at a time */ 
	while (len > 0) { 
	    int x; 
	    int val; 

	    val = atoi(str); 
 	    x = strspn(str, "1234567890"); 
	    str += x; 
	    len -= x; 

	    if (str[0] == 'd') 			/* day */
                timeinfo.tm_mday += adding*val; 
            else if (str[0] == 'h') 		/* hour */
                timeinfo.tm_hour += adding*val; 
            else if (str[0] == 'm')             /* minute */
                timeinfo.tm_min += adding*val;
            else if (str[0] == 's') 		/* seconds */
                timeinfo.tm_sec += adding*val; 
	    else 				/* error */
		break; 				

	    /* skip letter */
	    str++; len--;
	} 
	
	if (len > 0) {
	    logmsg(LOGWARN, "time %s incorrect, using current time\n", str); 
	    return (uint32_t) timegm(&timeinfo); 
	} 

	ts = timegm(&timeinfo); 
	break; 

    default: 		/* nothing set, use current time */
	break;
    } 

    return (uint32_t) ts; 
}