int main(int argc, char** argv) {
    int i, retval;

    const char *usage = 
      "\nUsage: %s -app <app-name> [OPTIONS]\n"
      "Start validator for application <app-name>\n\n"
      "Optional arguments:\n"
      "  --one_pass_N_WU N       Validate at most N WUs, then exit\n"
      "  --one_pass              Make one pass through WU table, then exit\n"
      "  --mod n i               Process only WUs with (id mod n) == i\n"
      "  --max_claimed_credit X  If a result claims more credit than this, mark it as invalid\n"
      "  --max_granted_credit X  Grant no more than this amount of credit to a result\n"
      "  --grant_claimed_credit  Grant the claimed credit, regardless of what other results for this workunit claimed\n"
      "  --update_credited_job   Add record to credited_job table after granting credit\n"
      "  --credit_from_wu        Credit is specified in WU XML\n"
      "  --sleep_interval n      Set sleep-interval to n\n"
      "  -d n, --debug_level n   Set log verbosity level, 1-4\n\n";

    if ((argc > 1) && (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))) {
        printf (usage, argv[0] );
        exit(1);
    }


    check_stop_daemons();

    for (i=1; i<argc; i++) {
        if (is_arg(argv[i], "one_pass_N_WU")) {
            one_pass_N_WU = atoi(argv[++i]);
            one_pass = true;
        } else if (is_arg(argv[i], "sleep_interval")) {
            sleep_interval = atoi(argv[++i]);
        } else if (is_arg(argv[i], "one_pass")) {
            one_pass = true;
        } else if (is_arg(argv[i], "app")) {
            strcpy(app_name, argv[++i]);
        } else if (is_arg(argv[i], "d") || is_arg(argv[i], "debug_level")) {
            debug_level = atoi(argv[++i]);
            log_messages.set_debug_level(debug_level);
            if (debug_level == 4) g_print_queries = true;
        } else if (is_arg(argv[i], "mod")) {
            wu_id_modulus = atoi(argv[++i]);
            wu_id_remainder = atoi(argv[++i]);
        } else if (is_arg(argv[i], "max_granted_credit")) {
            max_granted_credit = atof(argv[++i]);
        } else if (is_arg(argv[i], "max_claimed_credit")) {
            max_claimed_credit = atof(argv[++i]);
        } else if (is_arg(argv[i], "grant_claimed_credit")) {
            grant_claimed_credit = true;
        } else if (is_arg(argv[i], "update_credited_job")) {
            update_credited_job = true;
        } else if (is_arg(argv[i], "credit_from_wu")) {
            credit_from_wu = true;
        } else {
            fprintf(stderr,
                "Invalid option '%s'\nTry `%s --help` for more information\n",
                argv[i], argv[0]
            );
            log_messages.printf(MSG_CRITICAL, "unrecognized arg: %s\n", argv[i]);
            exit(1);
        }
    }

    if (app_name[0] == 0) {
        log_messages.printf(MSG_CRITICAL,
            "must use '--app' to specify an application\n"
        );
        printf (usage, argv[0] );
        exit(1);      
    }

    retval = config.parse_file();
    if (retval) {
        log_messages.printf(MSG_CRITICAL,
            "Can't parse config.xml: %s\n", boincerror(retval)
        );
        exit(1);
    }

    log_messages.printf(MSG_NORMAL,
        "Starting validator, debug level %d\n", log_messages.debug_level
    );
    if (wu_id_modulus) {
        log_messages.printf(MSG_NORMAL,
            "Modulus %d, remainder %d\n", wu_id_modulus, wu_id_remainder
        );
    }

    install_stop_signal_handler();

    main_loop();
}