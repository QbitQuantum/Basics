/*! \fn int php_init(int php_process)
 *  \brief initialize either a specific PHP Script Server or all of them.
 *  \param php_process the process number to start or PHP_INIT
 *
 *  This function will either start an individual PHP Script Server process
 *  or all of them if the input parameter is the PHP_INIT constant.  The function
 *  will check the status of the process to verify that it is ready to process
 *  scripts as well.
 *
 *  \return TRUE if the PHP Script Server is know running or FALSE otherwise
 */
int php_init(int php_process) {
    int  cacti2php_pdes[2];
    int  php2cacti_pdes[2];
    pid_t  pid;
    char poller_id[TINY_BUFSIZE];
    char *argv[6];
    int  cancel_state;
    char *result_string = 0;
    int num_processes;
    int i;
    int retry_count = 0;

    /* special code to start all PHP Servers */
    if (php_process == PHP_INIT) {
        num_processes = set.php_servers;
    } else {
        num_processes = 1;
    }

    for (i=0; i < num_processes; i++) {
        SPINE_LOG_DEBUG(("DEBUG: SS[%i] PHP Script Server Routine Starting", i));

        /* create the output pipes from Spine to php*/
        if (pipe(cacti2php_pdes) < 0) {
            SPINE_LOG(("ERROR: SS[%i] Could not allocate php server pipes", i));
            return FALSE;
        }

        /* create the input pipes from php to Spine */
        if (pipe(php2cacti_pdes) < 0) {
            SPINE_LOG(("ERROR: SS[%i] Could not allocate php server pipes", i));
            return FALSE;
        }

        /* disable thread cancellation from this point forward. */
        pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &cancel_state);

        /* establish arguments for script server execution */
        argv[0] = set.path_php;
        argv[1] = "-q";
        argv[2] = set.path_php_server;
        argv[3] = "spine";
        snprintf(poller_id, TINY_BUFSIZE, "%d", set.poller_id);
        argv[4] = poller_id;
        argv[5] = NULL;

        /* fork a child process */
        SPINE_LOG_DEBUG(("DEBUG: SS[%i] PHP Script Server About to FORK Child Process", i));

retry:

        pid = vfork();

        /* check the pid status and process as required */
        switch (pid) {
        case -1: /* ERROR: Could not fork() */
            switch (errno) {
            case EAGAIN:
                if (retry_count < 3) {
                    retry_count++;
#ifndef SOLAR_THREAD
                    /* take a moment */
                    usleep(50000);
#endif
                    goto retry;
                } else {
                    SPINE_LOG(("ERROR: SS[%i] Could not fork PHP Script Server Out of Resources", i));
                }
            case ENOMEM:
                if (retry_count < 3) {
                    retry_count++;
#ifndef SOLAR_THREAD
                    /* take a moment */
                    usleep(50000);
#endif
                    goto retry;
                } else {
                    SPINE_LOG(("ERROR: SS[%i] Could not fork PHP Script Server Out of Memory", i));
                }
            default:
                SPINE_LOG(("ERROR: SS[%i] Could not fork PHP Script Server Unknown Reason", i));
            }

            close(php2cacti_pdes[0]);
            close(php2cacti_pdes[1]);
            close(cacti2php_pdes[0]);
            close(cacti2php_pdes[1]);

            SPINE_LOG(("ERROR: SS[%i] Could not fork PHP Script Server", i));
            pthread_setcancelstate(cancel_state, NULL);

            return FALSE;
        /* NOTREACHED */
        case 0:	/* SUCCESS: I am now the child */
            /* set the standard input/output channels of the new process.  */
            dup2(cacti2php_pdes[0], STDIN_FILENO);
            dup2(php2cacti_pdes[1], STDOUT_FILENO);

            /* close unneeded Pipes */
            (void)close(php2cacti_pdes[0]);
            (void)close(php2cacti_pdes[1]);
            (void)close(cacti2php_pdes[0]);
            (void)close(cacti2php_pdes[1]);

            /* start the php script server process */
            execv(argv[0], argv);
            _exit(127);
        /* NOTREACHED */
        default: /* I am the parent process */
            SPINE_LOG_DEBUG(("DEBUG: SS[%i] PHP Script Server Child FORK Success", i));
        }

        /* Parent */
        /* close unneeded pipes */
        close(cacti2php_pdes[0]);
        close(php2cacti_pdes[1]);

        if (php_process == PHP_INIT) {
            php_processes[i].php_pid = pid;
            php_processes[i].php_write_fd = cacti2php_pdes[1];
            php_processes[i].php_read_fd = php2cacti_pdes[0];
        } else {
            php_processes[php_process].php_pid = pid;
            php_processes[php_process].php_write_fd = cacti2php_pdes[1];
            php_processes[php_process].php_read_fd = php2cacti_pdes[0];
        }

        /* restore caller's cancellation state. */
        pthread_setcancelstate(cancel_state, NULL);

        /* check pipe to insure startup took place */
        if (php_process == PHP_INIT) {
            result_string = php_readpipe(i);
        } else {
            result_string = php_readpipe(php_process);
        }

        if (strstr(result_string, "Started")) {
            if (php_process == PHP_INIT) {
                SPINE_LOG_DEBUG(("DEBUG: SS[%i] Confirmed PHP Script Server running using readfd[%i], writefd[%i]", i, php2cacti_pdes[0], cacti2php_pdes[1]));

                php_processes[i].php_state = PHP_READY;
            } else {
                SPINE_LOG_DEBUG(("DEBUG: SS[%i] Confirmed PHP Script Server running using readfd[%i], writefd[%i]", php_process, php2cacti_pdes[0], cacti2php_pdes[1]));

                php_processes[php_process].php_state = PHP_READY;
            }
        } else {
            SPINE_LOG(("ERROR: SS[%i] Script Server did not start properly return message was: '%s'", php_process, result_string));

            if (php_process == PHP_INIT) {
                php_processes[i].php_state = PHP_BUSY;
            } else {
                php_processes[php_process].php_state = PHP_BUSY;
            }
        }
    }

    free(result_string);

    return TRUE;
}