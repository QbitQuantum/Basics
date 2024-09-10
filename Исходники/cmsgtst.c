/* Test u_formatMessage() and u_parseMessage() , format and parse sequence and round trip */
static void TestSampleFormatAndParse(void)
{

    UChar *result, *tzID, *str;
    UChar pattern[100];
    UChar expected[100];
    int32_t resultLengthOut, resultlength;
    UCalendar *cal;
    UDate d1,d;
    UDateFormat *def1;
    UErrorCode status = U_ZERO_ERROR;
    int32_t value = 0;
    UChar ret[30];

    ctest_setTimeZone(NULL, &status);

    log_verbose("Testing format and parse\n");

    str=(UChar*)malloc(sizeof(UChar) * 25);
    u_uastrcpy(str, "disturbance in force");
    tzID=(UChar*)malloc(sizeof(UChar) * 4);
    u_uastrcpy(tzID, "PST");
    cal=ucal_open(tzID, u_strlen(tzID), "en_US", UCAL_TRADITIONAL, &status);
    if(U_FAILURE(status)){
        log_data_err("error in ucal_open caldef : %s - (Are you missing data?)\n", myErrorName(status) );
    }
    ucal_setDateTime(cal, 1999, UCAL_MARCH, 18, 0, 0, 0, &status);
    d1=ucal_getMillis(cal, &status);
    if(U_FAILURE(status)){
            log_data_err("Error: failure in get millis: %s - (Are you missing data?)\n", myErrorName(status) );
    }
    
    log_verbose("\nTesting with pattern test#4");
    u_uastrcpy(pattern, "On {0, date, long}, there was a {1} on planet {2,number,integer}");
    u_uastrcpy(expected, "On March 18, 1999, there was a disturbance in force on planet 7"); 
    resultlength=1;
    result=(UChar*)malloc(sizeof(UChar) * resultlength);
    resultLengthOut=u_formatMessage( "en_US", pattern, u_strlen(pattern), result, resultlength, &status, d1, str, 7);
    if(status==U_BUFFER_OVERFLOW_ERROR)
    {
        status=U_ZERO_ERROR;
        resultlength=resultLengthOut+1;
        result=(UChar*)realloc(result, sizeof(UChar) * resultlength);
        u_formatMessage( "en_US", pattern, u_strlen(pattern), result, resultlength, &status, d1, str, 7);
        
    }
    if(U_FAILURE(status)){
        log_data_err("ERROR: failure in message format test#4: %s (Are you missing data?)\n", myErrorName(status));
    }
    else if(u_strcmp(result, expected)==0)
        log_verbose("PASS: MessagFormat successful on test#4\n");
    else{
        log_err("FAIL: Error in MessageFormat on test#4\n GOT: %s EXPECTED: %s\n", austrdup(result),
            austrdup(expected) );
    }
    
    
    /*try to parse this and check*/
    log_verbose("\nTesting the parse Message test#5\n");

    u_parseMessage("en_US", pattern, u_strlen(pattern), result, u_strlen(result), &status, &d, ret, &value);
    if(U_FAILURE(status)){
        log_data_err("ERROR: error in parsing: test#5: %s (Are you missing data?)\n", myErrorName(status));
    }
    else if(value!=7 && u_strcmp(str,ret)!=0)
        log_err("FAIL: Error in parseMessage on test#5 \n");
    else
        log_verbose("PASS: parseMessage successful on test#5\n");
        
    def1 = udat_open(UDAT_DEFAULT,UDAT_DEFAULT ,NULL, NULL, 0, NULL,0,&status);
    if(U_FAILURE(status))
    {
        log_data_err("error in creating the dateformat using short date and time style: %s (Are you missing data?)\n", myErrorName(status));
    }else{

        if(u_strcmp(myDateFormat(def1, d), myDateFormat(def1, d1))==0)
            log_verbose("PASS: parseMessage successful test#5\n");
        else{
            log_err("FAIL: parseMessage didn't parse the date successfully\n GOT: %s EXPECTED %s\n", 
                austrdup(myDateFormat(def1,d)), austrdup(myDateFormat(def1,d1)) );
        }
    }
    udat_close(def1);
    ucal_close(cal);

    free(result);
    free(str);
    free(tzID);
    
    ctest_resetTimeZone();
}