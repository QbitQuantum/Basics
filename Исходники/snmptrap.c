int
main(int argc, char *argv[])
{
    netsnmp_session session, *ss;
    netsnmp_pdu    *pdu, *response;
    oid             name[MAX_OID_LEN];
    size_t          name_length;
    int             arg;
    int             status;
    char           *trap = NULL;
    char           *prognam;
    int             exitval = 0;
#ifndef NETSNMP_DISABLE_SNMPV1
    char           *specific = NULL, *description = NULL, *agent = NULL;
    in_addr_t      *pdu_in_addr_t;
#endif

    prognam = strrchr(argv[0], '/');
    if (prognam)
        prognam++;
    else
        prognam = argv[0];

    putenv(strdup("POSIXLY_CORRECT=1"));

    if (strcmp(prognam, "snmpinform") == 0)
        inform = 1;
    switch (arg = snmp_parse_args(argc, argv, &session, "C:", optProc)) {
    case -2:
        exit(0);
    case -1:
        usage();
        exit(1);
    default:
        break;
    }

    SOCK_STARTUP;

    session.callback = snmp_input;
    session.callback_magic = NULL;

    if (session.version == SNMP_VERSION_3 && !inform) {
        /*
         * for traps, we use ourselves as the authoritative engine
         * which is really stupid since command line apps don't have a
         * notion of a persistent engine.  Hence, our boots and time
         * values are probably always really wacked with respect to what
         * a manager would like to see.
         * 
         * The following should be enough to:
         * 
         * 1) prevent the library from doing discovery for engineid & time.
         * 2) use our engineid instead of the remote engineid for
         * authoritative & privacy related operations.
         * 3) The remote engine must be configured with users for our engineID.
         * 
         * -- Wes 
         */

        /*
         * setup the engineID based on IP addr.  Need a different
         * algorthim here.  This will cause problems with agents on the
         * same machine sending traps. 
         */
        setup_engineID(NULL, NULL);

        /*
         * pick our own engineID 
         */
        if (session.securityEngineIDLen == 0 ||
            session.securityEngineID == NULL) {
            session.securityEngineID =
                snmpv3_generate_engineID(&session.securityEngineIDLen);
        }
        if (session.contextEngineIDLen == 0 ||
            session.contextEngineID == NULL) {
            session.contextEngineID =
                snmpv3_generate_engineID(&session.contextEngineIDLen);
        }

        /*
         * set boots and time, which will cause problems if this
         * machine ever reboots and a remote trap receiver has cached our
         * boots and time...  I'll cause a not-in-time-window report to
         * be sent back to this machine. 
         */
        if (session.engineBoots == 0)
            session.engineBoots = 1;
        if (session.engineTime == 0)    /* not really correct, */
            session.engineTime = get_uptime();  /* but it'll work. Sort of. */
    }

    ss = snmp_add(&session,
                  netsnmp_transport_open_client("snmptrap", session.peername),
                  NULL, NULL);
    if (ss == NULL) {
        /*
         * diagnose netsnmp_transport_open_client and snmp_add errors with
         * the input netsnmp_session pointer
         */
        snmp_sess_perror("snmptrap", &session);
        SOCK_CLEANUP;
        exit(1);
    }

#ifndef NETSNMP_DISABLE_SNMPV1
    if (session.version == SNMP_VERSION_1) {
        if (inform) {
            fprintf(stderr, "Cannot send INFORM as SNMPv1 PDU\n");
            exit(1);
        }
        pdu = snmp_pdu_create(SNMP_MSG_TRAP);
        pdu_in_addr_t = (in_addr_t *) pdu->agent_addr;
        if (arg == argc) {
            fprintf(stderr, "No enterprise oid\n");
            usage();
            SOCK_CLEANUP;
            exit(1);
        }
        if (argv[arg][0] == 0) {
            pdu->enterprise = (oid *) malloc(sizeof(objid_enterprise));
            memcpy(pdu->enterprise, objid_enterprise,
                   sizeof(objid_enterprise));
            pdu->enterprise_length =
                sizeof(objid_enterprise) / sizeof(oid);
        } else {
            name_length = MAX_OID_LEN;
            if (!snmp_parse_oid(argv[arg], name, &name_length)) {
                snmp_perror(argv[arg]);
                usage();
                SOCK_CLEANUP;
                exit(1);
            }
            pdu->enterprise = (oid *) malloc(name_length * sizeof(oid));
            memcpy(pdu->enterprise, name, name_length * sizeof(oid));
            pdu->enterprise_length = name_length;
        }
        if (++arg >= argc) {
            fprintf(stderr, "Missing agent parameter\n");
            usage();
            SOCK_CLEANUP;
            exit(1);
        }
        agent = argv[arg];
        if (agent != NULL && strlen(agent) != 0) {
            *pdu_in_addr_t = parse_address(agent);
        } else {
            *pdu_in_addr_t = get_myaddr();
        }
        if (++arg == argc) {
            fprintf(stderr, "Missing generic-trap parameter\n");
            usage();
            SOCK_CLEANUP;
            exit(1);
        }
        trap = argv[arg];
        pdu->trap_type = atoi(trap);
        if (++arg == argc) {
            fprintf(stderr, "Missing specific-trap parameter\n");
            usage();
            SOCK_CLEANUP;
            exit(1);
        }
        specific = argv[arg];
        pdu->specific_type = atoi(specific);
        if (++arg == argc) {
            fprintf(stderr, "Missing uptime parameter\n");
            usage();
            SOCK_CLEANUP;
            exit(1);
        }
        description = argv[arg];
        if (description == NULL || *description == 0)
            pdu->time = get_uptime();
        else
            pdu->time = atol(description);
    } else
#endif
    {
        long            sysuptime;
        char            csysuptime[20];

        pdu = snmp_pdu_create(inform ? SNMP_MSG_INFORM : SNMP_MSG_TRAP2);
        if (arg == argc) {
            fprintf(stderr, "Missing up-time parameter\n");
            usage();
            SOCK_CLEANUP;
            exit(1);
        }
        trap = argv[arg];
        if (*trap == 0) {
            sysuptime = get_uptime();
            sprintf(csysuptime, "%ld", sysuptime);
            trap = csysuptime;
        }
        snmp_add_var(pdu, objid_sysuptime,
                     sizeof(objid_sysuptime) / sizeof(oid), 't', trap);
        if (++arg == argc) {
            fprintf(stderr, "Missing trap-oid parameter\n");
            usage();
            SOCK_CLEANUP;
            exit(1);
        }
        if (snmp_add_var
            (pdu, objid_snmptrap, sizeof(objid_snmptrap) / sizeof(oid),
             'o', argv[arg]) != 0) {
            snmp_perror(argv[arg]);
            SOCK_CLEANUP;
            exit(1);
        }
    }
    arg++;

    while (arg < argc) {
        arg += 3;
        if (arg > argc) {
            fprintf(stderr, "%s: Missing type/value for variable\n",
                    argv[arg - 3]);
            SOCK_CLEANUP;
            exit(1);
        }
        name_length = MAX_OID_LEN;
        if (!snmp_parse_oid(argv[arg - 3], name, &name_length)) {
            snmp_perror(argv[arg - 3]);
            SOCK_CLEANUP;
            exit(1);
        }
        if (snmp_add_var
            (pdu, name, name_length, argv[arg - 2][0],
             argv[arg - 1]) != 0) {
            snmp_perror(argv[arg - 3]);
            SOCK_CLEANUP;
            exit(1);
        }
    }

    if (inform)
        status = snmp_synch_response(ss, pdu, &response);
    else
        status = snmp_send(ss, pdu) == 0;
    if (status) {
        snmp_sess_perror(inform ? "snmpinform" : "snmptrap", ss);
        if (!inform)
            snmp_free_pdu(pdu);
        exitval = 1;
    } else if (inform)
        snmp_free_pdu(response);

    snmp_close(ss);
    snmp_shutdown("snmpapp");
    SOCK_CLEANUP;
    return exitval;
}