static int hostfile_parse(const char *hostfile, opal_list_t* updates,
                          opal_list_t* exclude, bool keep_all)
{
    int token;
    int rc = ORTE_SUCCESS;


    cur_hostfile_name = hostfile;
    
    orte_util_hostfile_done = false;
    orte_util_hostfile_in = fopen(hostfile, "r");
    if (NULL == orte_util_hostfile_in) {
        if (NULL == orte_default_hostfile ||
            0 != strcmp(orte_default_hostfile, hostfile)) {
            /* not the default hostfile, so not finding it
             * is an error
             */
            orte_show_help("help-hostfile.txt", "no-hostfile", true, hostfile);
            rc = ORTE_ERR_SILENT;
            goto unlock;
        }
        /* if this is the default hostfile and it was given,
         * then it's an error
         */
        if (orte_default_hostfile_given) {
            orte_show_help("help-hostfile.txt", "no-hostfile", true, hostfile);
            rc = ORTE_ERR_NOT_FOUND;
            goto unlock;
        }
        /* otherwise, not finding it is okay */
        rc = ORTE_SUCCESS;
        goto unlock;
    }

    while (!orte_util_hostfile_done) {
        token = orte_util_hostfile_lex();

        switch (token) {
        case ORTE_HOSTFILE_DONE:
            orte_util_hostfile_done = true;
            break;

        case ORTE_HOSTFILE_NEWLINE:
            break;

        /*
         * This looks odd, since we have several forms of host-definitions:
         *   hostname              just plain as it is, being a ORTE_HOSTFILE_STRING
         *   IP4s and user@IPv4s
         *   hostname.domain and [email protected]
         */
        case ORTE_HOSTFILE_STRING:
        case ORTE_HOSTFILE_INT:
        case ORTE_HOSTFILE_HOSTNAME:
        case ORTE_HOSTFILE_IPV4:
        case ORTE_HOSTFILE_IPV6:
        case ORTE_HOSTFILE_RELATIVE:
        case ORTE_HOSTFILE_RANK:
            rc = hostfile_parse_line(token, updates, exclude, keep_all);
            if (ORTE_SUCCESS != rc) {
                goto unlock;
            }
            break;

        default:
            hostfile_parse_error(token);
            goto unlock;
        }
    }
    fclose(orte_util_hostfile_in);
    orte_util_hostfile_in = NULL;

unlock:
    cur_hostfile_name = NULL;

    return rc;
}