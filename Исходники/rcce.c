int RCCE_init(int *argc, char ***argv)
{
    int ue;
    void *nothing = NULL;

    assert(*argc >= 3);

    setup_routes(*argc, *argv);

    // save pointer to executable name for later insertion into the argument list
    char *executable_name = (*argv)[0];

    RCCE_NP        = atoi(*(++(*argv)));
    RC_REFCLOCKGHZ = atof(*(++(*argv)));

    if(RC_REFCLOCKGHZ == 0) {
        printf("Barrelfish RCCE extension: Computing reference clock GHz automatically...\n");
        uint64_t tscperms;
        errval_t err = sys_debug_get_tsc_per_ms(&tscperms);
        assert(err_is_ok(err));
        RC_REFCLOCKGHZ = ((double)tscperms) / 1000000.0;
        printf("Reference clock computed to be %.2g\n", RC_REFCLOCKGHZ);
    }

    // put the participating core ids (unsorted) into an array
    for (ue=0; ue<RCCE_NP; ue++) {
        RC_COREID[ue] = atoi(*(++(*argv)));
    }

    // make sure executable name is as expected
    (*argv)[0] = executable_name;

    RC_MY_COREID = MYCOREID();

    // adjust apparent number of command line arguments, so it will appear to main
    // program that number of UEs, clock frequency, and core ID list were not on
    // command line
    *argc -= RCCE_NP+2;

    // sort array of participating phyical core IDs to determine their ranks
    qsort((char *)RC_COREID, RCCE_NP, sizeof(int), id_compare);

    // determine rank of calling core
    for (ue=0; ue<RCCE_NP; ue++) {
        if (RC_COREID[ue] == RC_MY_COREID) RCCE_IAM = ue;
    }

    // leave in one reassuring debug print
    printf("My rank is %d, physical core ID is %d\n", RCCE_IAM, RC_MY_COREID);
    if (RCCE_IAM<0) {
        return(RCCE_ERROR_CORE_NOT_IN_HOSTFILE);
    }

    // create global communicator (equivalent of MPI_COMM_WORLD); this will also allocate
    // the two synchronization flags associated with the global barrier
    RCCE_comm_split(RCCE_global_color, nothing, &RCCE_COMM_WORLD);

#ifdef MEASURE_TIME
    measure_start = RCCE_wtime();
    measure_rcce_time = 0.0;
#endif

#ifdef MEASURE_DATA
    memset(measure_rcce_data, 0, sizeof(measure_rcce_data));
#endif

    return (RCCE_SUCCESS);
}