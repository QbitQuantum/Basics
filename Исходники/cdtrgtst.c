/**
 * @bug 4073003
 */
void Test4073003()
{
    int32_t pos,i;
    UDate d,dd;
    UChar *datestr;
    UChar temp[15];
    UErrorCode status = U_ZERO_ERROR;
    UDateFormat *fmt;
    UChar *result, *result2;
    const char* tests [] = {
        "12/25/61",
        "12/25/1961",
        "4/3/1999",
        "4/3/99"
    };

    fmt= udat_open(UDAT_SHORT,UDAT_SHORT ,NULL, NULL, 0, NULL, 0, &status);
    if(U_FAILURE(status))
    {
        log_data_err("FAIL: error in creating the dateformat using short date and time style: %s (Are you missing data?)\n",
                     myErrorName(status));
        return;
    }
    u_uastrcpy(temp, "m/D/yy");
    udat_applyPattern(fmt, FALSE, temp, u_strlen(temp));

    for(i= 0; i < 4; i+=2) {
        status=U_ZERO_ERROR;
        datestr=(UChar*)malloc(sizeof(UChar) * (strlen(tests[i])+1));
        u_uastrcpy(datestr, tests[i]);

        pos=0;
        d = udat_parse(fmt, datestr, u_strlen(datestr), &pos, &status);
        if(U_FAILURE(status)) {
            log_err("ERROR : in test 4073003: %s\n", myErrorName(status));
        }

        free(datestr);
        datestr=(UChar*)malloc(sizeof(UChar) * (strlen(tests[i+1])+1));
        u_uastrcpy(datestr, tests[i+1]);

        pos=0;
        status=U_ZERO_ERROR;
        dd = udat_parse(fmt, datestr, u_strlen(datestr), &pos, &status);
        if(U_FAILURE(status)) {
            log_err("ERROR : in test 4073003: %s\n", myErrorName(status));
        }
        free(datestr);

        result =myFormatit(fmt, d);
        result2 =myFormatit(fmt, dd);
        if(!result || !result2) {
            log_data_err("Fail: could not format - exitting test\n");
            return;
        }
        if (u_strcmp(result, result2)!=0) {
            log_err("Fail: %s != %s\n", austrdup(result), austrdup(result2) );
        }
        else {
            log_verbose("Ok: %s == %s\n", austrdup(result), austrdup(result2) );
        }

    }
    udat_close(fmt);
}