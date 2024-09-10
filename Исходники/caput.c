int main (int argc, char *argv[])
{
    int i;
    int result;                 /* CA result */
    OutputT format = plain;     /* User specified format */
    RequestT request = get;     /* User specified request type */
    int isArray = 0;            /* Flag for array operation */
    int enumAsString = 0;       /* Force ENUM values to be strings */

    int count = 1;
    int opt;                    /* getopt() current option */
    chtype dbrType = DBR_STRING;
    char *pend;
    EpicsStr *sbuf;
    double *dbuf;
    char *cbuf = 0;
    char *ebuf = 0;
    void *pbuf;
    int len = 0;
    int waitStatus;
    struct dbr_gr_enum bufGrEnum;

    int nPvs;                   /* Number of PVs */
    pv* pvs;                /* Array of PV structures */

    LINE_BUFFER(stdout);        /* Configure stdout buffering */
    putenv("POSIXLY_CORRECT="); /* Behave correct on GNU getopt systems */

    while ((opt = getopt(argc, argv, ":cnlhatsS#:w:p:F:")) != -1) {
        switch (opt) {
        case 'h':               /* Print usage */
            usage();
            return 0;
        case 'n':               /* Force interpret ENUM as index number */
            enumAsNr = 1;
            enumAsString = 0;
            break;
        case 's':               /* Force interpret ENUM as menu string */
            enumAsString = 1;
            enumAsNr = 0;
            break;
        case 'S':               /* Treat char array as (long) string */
            charArrAsStr = 1;
            isArray = 0;
            break;
        case 't':               /* Select terse output format */
            format = terse;
            break;
        case 'l':               /* Select long output format */
            format = all;
            break;
        case 'a':               /* Select array mode */
            isArray = 1;
            charArrAsStr = 0;
            break;
        case 'c':               /* Select put_callback mode */
            request = callback;
            break;
        case 'w':               /* Set CA timeout value */
            if(epicsScanDouble(optarg, &caTimeout) != 1)
            {
                fprintf(stderr, "'%s' is not a valid timeout value "
                        "- ignored. ('caput -h' for help.)\n", optarg);
                caTimeout = DEFAULT_TIMEOUT;
            }
            break;
        case '#':               /* Array count */
            if (sscanf(optarg,"%d", &count) != 1)
            {
                fprintf(stderr, "'%s' is not a valid array element count "
                        "- ignored. ('caput -h' for help.)\n", optarg);
                count = 0;
            }
            break;
        case 'p':               /* CA priority */
            if (sscanf(optarg,"%u", &caPriority) != 1)
            {
                fprintf(stderr, "'%s' is not a valid CA priority "
                        "- ignored. ('caget -h' for help.)\n", optarg);
                caPriority = DEFAULT_CA_PRIORITY;
            }
            if (caPriority > CA_PRIORITY_MAX) caPriority = CA_PRIORITY_MAX;
            break;
        case 'F':               /* Store this for output and tool_lib formatting */
            fieldSeparator = (char) *optarg;
            break;
        case '?':
            fprintf(stderr,
                    "Unrecognized option: '-%c'. ('caput -h' for help.)\n",
                    optopt);
            return 1;
        case ':':
            fprintf(stderr,
                    "Option '-%c' requires an argument. ('caput -h' for help.)\n",
                    optopt);
            return 1;
        default :
            usage();
            return 1;
        }
    }

    nPvs = argc - optind;       /* Remaining arg list are PV names and values */

    if (nPvs < 1) {
        fprintf(stderr, "No pv name specified. ('caput -h' for help.)\n");
        return 1;
    }
    if (nPvs == 1) {
        fprintf(stderr, "No value specified. ('caput -h' for help.)\n");
        return 1;
    }

    nPvs = 1;                   /* One PV - the rest is value(s) */

    epId = epicsEventCreate(epicsEventEmpty);  /* Create empty EPICS event (semaphore) */

                                /* Start up Channel Access */

    result = ca_context_create(ca_enable_preemptive_callback);
    if (result != ECA_NORMAL) {
        fprintf(stderr, "CA error %s occurred while trying "
                "to start channel access.\n", ca_message(result));
        return 1;
    }
                                /* Allocate PV structure array */

    pvs = calloc (nPvs, sizeof(pv));
    if (!pvs) {
        fprintf(stderr, "Memory allocation for channel structure failed.\n");
        return 1;
    }
                                /* Connect channels */

    pvs[0].name = argv[optind] ;   /* Copy PV name from command line */

    result = connect_pvs(pvs, nPvs); /* If the connection fails, we're done */
    if (result) {
        ca_context_destroy();
        return result;
    }

                                /* Get values from command line */
    optind++;

    if (isArray) {
        optind++;               /* In case of array skip first value (nr
                                 * of elements) - actual number of values is used */
        count = argc - optind;

    } else {                    /* Concatenate the remaining line to one string
                                 * (sucks but is compatible to the former version) */
        for (i = optind; i < argc; i++) {
            len += strlen(argv[i]);
            len++;
        }
        cbuf = calloc(len, sizeof(char));
        if (!cbuf) {
            fprintf(stderr, "Memory allocation failed.\n");
            return 1;
        }
        strcpy(cbuf, argv[optind]);

        if (argc > optind+1) {
            for (i = optind + 1; i < argc; i++) {
                strcat(cbuf, " ");
                strcat(cbuf, argv[i]); 
            }
        }

        if ((argc - optind) >= 1)
            count = 1;
        argv[optind] = cbuf;
    }

    sbuf = calloc (count, sizeof(EpicsStr));
    dbuf = calloc (count, sizeof(double));
    if(!sbuf || !dbuf) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

                                /*  ENUM? Special treatment */

    if (ca_field_type(pvs[0].chid) == DBR_ENUM) {

                                /* Get the ENUM strings */

        result = ca_array_get (DBR_GR_ENUM, 1, pvs[0].chid, &bufGrEnum);
        result = ca_pend_io(caTimeout);
        if (result == ECA_TIMEOUT) {
            fprintf(stderr, "Read operation timed out: ENUM data was not read.\n");
            return 1;
        }

        if (enumAsNr) {         /* Interpret values as numbers */

            for (i = 0; i < count; ++i) {
                dbuf[i] = epicsStrtod(*(argv+optind+i), &pend);
                if (*(argv+optind+i) == pend) { /* Conversion didn't work */
                    fprintf(stderr, "Enum index value '%s' is not a number.\n",
                            *(argv+optind+i));
                    return 1;
                }
                if (dbuf[i] >= bufGrEnum.no_str) {
                    fprintf(stderr, "Warning: enum index value '%s' may be too large.\n",
                            *(argv+optind+i));
                }
            }
            dbrType = DBR_DOUBLE;

        } else {                /* Interpret values as strings */

            for (i = 0; i < count; ++i) {
                epicsStrnRawFromEscaped(sbuf[i], sizeof(EpicsStr), *(argv+optind+i), sizeof(EpicsStr));
                *( sbuf[i]+sizeof(EpicsStr)-1 ) = '\0';
                dbrType = DBR_STRING;

                                /* Compare to ENUM strings */
                for (len = 0; len < bufGrEnum.no_str; len++)
                    if (!strcmp(sbuf[i], bufGrEnum.strs[len]))
                        break;

                if (len >= bufGrEnum.no_str) {
                                         /* Not a string? Try as number */
                    dbuf[i] = epicsStrtod(sbuf[i], &pend);
                    if (sbuf[i] == pend || enumAsString) {
                        fprintf(stderr, "Enum string value '%s' invalid.\n", sbuf[i]);
                        return 1;
                    }
                    if (dbuf[i] >= bufGrEnum.no_str) {
                        fprintf(stderr, "Warning: enum index value '%s' may be too large.\n", sbuf[i]);
                    }
                    dbrType = DBR_DOUBLE;
                }
            }
        }

    } else {                    /* Not an ENUM */

        if (charArrAsStr) {
            dbrType = DBR_CHAR;
            ebuf = calloc(len, sizeof(char));
            if(!ebuf) {
                fprintf(stderr, "Memory allocation failed\n");
                return 1;
            }
            count = epicsStrnRawFromEscaped(ebuf, len, cbuf, len-1) + 1;
        } else {
            for (i = 0; i < count; ++i) {
                epicsStrnRawFromEscaped(sbuf[i], sizeof(EpicsStr), *(argv+optind+i), sizeof(EpicsStr));
                *( sbuf[i]+sizeof(EpicsStr)-1 ) = '\0';
            }
            dbrType = DBR_STRING;
        }
    }

                                /* Read and print old data */
    if (format != terse) {
        printf("Old : ");
        result = caget(pvs, nPvs, format, 0, 0);
    }

                                /* Write new data */
    if (dbrType == DBR_STRING) pbuf = sbuf;
    else if (dbrType == DBR_CHAR) pbuf = ebuf;
    else pbuf = dbuf;

    if (request == callback) {
        /* Use callback version of put */
        pvs[0].status = ECA_NORMAL;   /* All ok at the moment */
        result = ca_array_put_callback (
            dbrType, count, pvs[0].chid, pbuf, put_event_handler, (void *) pvs);
    } else {
        /* Use standard put with defined timeout */
        result = ca_array_put (dbrType, count, pvs[0].chid, pbuf);
    }
    result = ca_pend_io(caTimeout);
    if (result == ECA_TIMEOUT) {
        fprintf(stderr, "Write operation timed out: Data was not written.\n");
        return 1;
    }
    if (request == callback) {   /* Also wait for callbacks */
        waitStatus = epicsEventWaitWithTimeout( epId, caTimeout );
        if (waitStatus)
            fprintf(stderr, "Write callback operation timed out\n");

        /* retrieve status from callback */
        result = pvs[0].status;
    }

    if (result != ECA_NORMAL) {
        fprintf(stderr, "Error occured writing data.\n");
        return 1;
    }

                                /* Read and print new data */
    if (format != terse)
        printf("New : ");

    result = caget(pvs, nPvs, format, 0, 0);

                                /* Shut down Channel Access */
    ca_context_destroy();

    return result;
}