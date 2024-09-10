int
parse_cmd(char *cmd_str, long int **cmd, int *cmd_len)
    /* read a command string, check if it is valid and translate it */
{
    long int buf[SOCKET_MSG_LEN];
    int word_size = 0;
    int i = 0, j = 0, rank = -1;
    long int int_buf = 0;
    struct passwd *pass = NULL;
#ifdef SYSFCRONTAB
    long int sysfcrontab_uid = SYSFCRONTAB_UID;
#endif

    bzero(buf, sizeof(buf));
    *cmd_len = 0;
    remove_blanks(cmd_str);     /* at the end of the string */

    if ((word_size = get_word(&cmd_str)) == 0) {
        fprintf(stderr, "Warning : Zero-length command name : line ignored.\n");
        return ZEROLEN_CMD;
    }

    for (i = 0; i < cmd_list_len; i++) {
        int j;
        if (Strncmp(cmd_str, cmd_list[i].cmd_name, word_size) == 0) {
            rank = i;
            break;
        }
        for (j = 0; j < MAX_NUM_ALIAS && cmd_list[i].cmd_alias[j] != NULL; j++) {
            if (Strncmp(cmd_str, cmd_list[i].cmd_alias[j], word_size) == 0) {
                rank = i;
                break;
            }
        }
    }
    if (rank == (-1)) {
        fprintf(stderr, "Error : Unknown command.\n");
        return CMD_NOT_FOUND;
    }
    else if (cmd_list[rank].cmd_code == QUIT_CMD) {
        if (debug_opt)
            fprintf(stderr, "quit command\n");
        return QUIT_CMD;
    }
    else if (cmd_list[rank].cmd_code == HELP_CMD) {
        if (debug_opt)
            fprintf(stderr, "Help command\n");
        return HELP_CMD;
    }

    Write_cmd(cmd_list[rank].cmd_code);

    if (debug_opt)
        fprintf(stderr, "command : %s\n", cmd_list[i].cmd_name);

    cmd_str += word_size;
    for (i = 0; i < cmd_list[rank].cmd_numopt; i++) {

        if ((word_size = get_word(&cmd_str)) == 0) {

            if (cmd_list[rank].cmd_default[i] == ARG_REQUIRED) {
                fprintf(stderr, "Error : arg required !\n");
                return INVALID_ARG;
            }

            /* use default value : currently, works only with CUR_USER */
            if (user_uid == rootuid) {
                /* default for root = all */
                int_buf = ALL;
                Write_cmd(int_buf);
                if (debug_opt)
                    fprintf(stderr, "  uid = ALL\n");
            }
            else {
                Write_cmd(user_uid);
                if (debug_opt)
                    fprintf(stderr, "  uid = %d\n", (int)user_uid);
            }

        }

        else {

            /* get value from line ... */
            switch (cmd_list[rank].cmd_opt[i]) {

            case USER:
                int_buf = (long int)*(cmd_str + word_size);
                *(cmd_str + word_size) = '\0';
#ifdef SYSFCRONTAB
                if (strcmp(cmd_str, SYSFCRONTAB) == 0) {
                    Write_cmd(sysfcrontab_uid);
                }
                else {
#endif
                    if ((pass = getpwnam(cmd_str)) == NULL) {
                        fprintf(stderr,
                                "Error : '%s' isn't a valid username.\n",
                                cmd_str);
                        return INVALID_ARG;
                    }
                    Write_cmd(pass->pw_uid);
#ifdef SYSFCRONTAB
                }
#endif
                *(cmd_str + word_size) = (char)int_buf;
                cmd_str += word_size;
                if (debug_opt)
                    fprintf(stderr, "  uid = %d\n",
#ifdef SYSFCRONTAB
                            (pass) ? (int)pass->pw_uid : (int)SYSFCRONTAB_UID
#else
                            (int)pass->pw_uid
#endif
                        );
                break;

            case JOBID:
                /* after strtol(), cmd_str will be updated (first non-number char) */
                if ((int_buf = strtol(cmd_str, &cmd_str, 10)) < 0
                    || int_buf >= LONG_MAX || (!isspace((int)*cmd_str)
                                               && *cmd_str != '\0')) {
                    fprintf(stderr, "Error : invalid jobid.\n");
                    return INVALID_ARG;
                }
                Write_cmd(int_buf);
                if (debug_opt)
                    fprintf(stderr, "  jobid = %ld\n", int_buf);
                break;

            case TIME_AND_DATE:
                /* argghh !!! no standard function ! */
                break;

            case NICE_VALUE:
                /* after strtol(), cmd_str will be updated (first non-number char) */
                if ((int_buf = strtol(cmd_str, &cmd_str, 10)) > 20
                    || (int_buf < 0 && getuid() != rootuid) || int_buf < -20
                    || (!isspace((int)*cmd_str) && *cmd_str != '\0')) {
                    fprintf(stderr, "Error : invalid nice value.\n");
                    return INVALID_ARG;
                }
                Write_cmd(int_buf);
                if (debug_opt)
                    fprintf(stderr, "  nicevalue = %ld\n", int_buf);
                break;

            case SIGNAL:
                if (isalpha((int)*cmd_str)) {
                    for (j = 0; j < word_size; j++)
                        *(cmd_str + j) = tolower(*(cmd_str + j));
                    if (Strncmp(cmd_str, "hup", word_size) == 0)
                        int_buf = SIGHUP;
                    else if (Strncmp(cmd_str, "int", word_size) == 0)
                        int_buf = SIGINT;
                    else if (Strncmp(cmd_str, "quit", word_size) == 0)
                        int_buf = SIGQUIT;
                    else if (Strncmp(cmd_str, "kill", word_size) == 0)
                        int_buf = SIGKILL;
                    else if (Strncmp(cmd_str, "alrm", word_size) == 0)
                        int_buf = SIGALRM;
                    else if (Strncmp(cmd_str, "term", word_size) == 0)
                        int_buf = SIGTERM;
                    else if (Strncmp(cmd_str, "usr1", word_size) == 0)
                        int_buf = SIGUSR1;
                    else if (Strncmp(cmd_str, "usr2", word_size) == 0)
                        int_buf = SIGUSR2;
                    else if (Strncmp(cmd_str, "cont", word_size) == 0)
                        int_buf = SIGCONT;
                    else if (Strncmp(cmd_str, "stop", word_size) == 0)
                        int_buf = SIGSTOP;
                    else if (Strncmp(cmd_str, "tstp", word_size) == 0)
                        int_buf = SIGTSTP;
                    else {
                        fprintf(stderr,
                                "Error : unknow signal (try integer value)\n");
                        return INVALID_ARG;
                    }
                    cmd_str += word_size;
                }
                /* after strtol(), cmd_str will be updated (first non-number char) */
                else if ((int_buf = strtol(cmd_str, &cmd_str, 10)) <= 0
                         || int_buf >= LONG_MAX || (!isspace((int)*cmd_str)
                                                    && *cmd_str != '\0')) {
                    fprintf(stderr, "Error : invalid signal value.\n");
                    return INVALID_ARG;
                }
                Write_cmd(int_buf);
                if (debug_opt)
                    fprintf(stderr, "  signal = %ld\n", int_buf);
                break;

            default:
                fprintf(stderr, "Error : Unknown arg !");
                return INVALID_ARG;
            }
        }
    }

    Skip_blanks(cmd_str);
    if (*cmd_str != '\0')
        fprintf(stderr, "Warning : too much arguments : '%s' ignored.\n",
                cmd_str);

    /* This is a valid command ... */
    *cmd = alloc_safe(*cmd_len * sizeof(long int), "command string");
    memcpy(*cmd, buf, *cmd_len * sizeof(long int));

    return OK;
}