void GetLoadPoint(
    Widget  w,              /* unused */
    XtPointer    closure,        /* unused */
    XtPointer    call_data)      /* pointer to (double) return value */
{
    double *loadavg = (double *)call_data;
    COUNTER fmtvalue;
    long ret;
    *loadavg = 0.0;
    ret = pdhcollectquerydata(query);
    if (ret!=0) return;
    ret = pdhgetformattedcountervalue(counter, 0x200, NULL, &fmtvalue);
    if (ret!=0) return;
    *loadavg = (fmtvalue.u.vDouble-0.01)/100.0;
}