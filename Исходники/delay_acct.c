int main(int argc, char* argv[])
{
    int c, ret = -1;
    char* log_file = NULL;
    char* cpu_mask = NULL;
    int rc, mode = 0, tid;

    while ((c = getopt(argc, argv, "c:l:m:")) != -1) {
        switch(c) {
        case 'l' :
            log_file = strdup(optarg);
            break;
        case 'c' :
            cpu_mask = strdup(optarg);
            break;
        case 'm' :
            if (strcmp(optarg, "1") == 0)
                mode = 1;
            else if (strcmp(optarg, "2") == 0)
                mode = 2;
            else if (strcmp(optarg, "3") == 0)
                mode = 3;
            break;
        default :
            fprintf(stderr, "unknown option %c\n", c);
            exit(-1);
        }
    }

    /*
     * checking an dealing with input parameters
     */
    if (log_file) {
        if (!(f = fopen(log_file, "w"))) {
            fprintf(stderr, "cannot open file\n");
            goto out;
        }
    }
    else {
        f = stdout;
    }

    if (!mode) {
        ERROR("must specify mode\n");
        goto out;
    }

    if (!cpu_mask) {
        ERROR("need to specify CPU type\n");
        goto out;
    }

    /*
     * setting up system stuff
     */
    if ((pid_max = get_pid_max()) < 0) {
        ERROR("unable to get pid_max\n");
        goto out;
    }

    PRINTF("pid_max is %d\n", pid_max);
    
    signal(SIGINT, sig_int_cb);
    if ((nl_sd = create_nl_socket(NETLINK_GENERIC)) < 0) {
        ERROR("error creating Netlink socket\n");
        goto out;
    }

    /*
     * register taskstats notifier
     */
    fam_id = __get_family_id(nl_sd);
    if (!fam_id) {
        ERROR("Error getting family id, errno %d\n", errno);
        goto out;
    }

    my_pid = getpid();
    if ((rc = send_cmd(TASKSTATS_CMD_GET,
        TASKSTATS_CMD_ATTR_REGISTER_CPUMASK, cpu_mask, strlen(cpu_mask))) < 0) {
        ERROR("error sending register cpumask\n");
        goto out;
    }

    /*
     * now for the main loop
     * modes of operations 
     * i) get all process stats and print
     * ii) wait until receive signal (be polling for dead process in meantime)
     *     then get all process stats
     * iii) get all process stats, then wait for signal and print diff
     */
    if (mode == 1) {
        fill_infos(infos1);
        for (tid = 0; tid < pid_max; tid++) {
            if (!infos1[tid])
                continue;
            print_taskstats(&infos1[tid]->t);
        }
    }
    else if (mode == 2) {
        PRINTF("waiting for signal\n");
        while (!sig_int)
            sleep(1);
        fill_infos(infos1);
        for (tid = 0; tid < pid_max; tid++) {
            if (!infos1[tid])
                continue;
            print_taskstats(&infos1[tid]->t);
        }
    }
    else if (mode == 3) {
        struct timeval start_since_epoch;
        struct timespec start, end;
        static struct taskstats ts_tot = {0};

        if (fill_infos(infos1) < 0) {
            ERROR("error before start\n");
            goto out;
        }

        if (clock_gettime(CLOCK_MONOTONIC, &start) < 0) {
            ERROR("unable to get start time\n");
            goto out;
        }

        if (gettimeofday(&start_since_epoch, NULL)) { 
            ERROR("unable to get start time since epoch\n");
            goto out;
        }

        PRINTF("waiting for signal\n");
        while (!sig_int) {
            ret = recv_taskstats(MSG_DONTWAIT, infos2);

            if (ret == 0 || ret == -EAGAIN) {
                usleep(10000);
                continue;
            }

            ERROR("unable to recv taskstats, %d\n", ret);
            goto out;
        }

        if (fill_infos(infos2) < 0) {
            ERROR("error at end\n");
            goto out;
        }
        if (clock_gettime(CLOCK_MONOTONIC, &end) < 0) {
            ERROR("unable to get end time\n");
            goto out;
        }

        PRINTF("--- task dump start ---\n");

        for (tid = 0; tid < pid_max; tid++) {
            struct proc_info* p1 = infos1[tid];
            struct proc_info* p2 = infos2[tid];

            if (!(p1 || p2))
                continue;
            else if (p1 && p2) {
                static struct taskstats ts;
                diff_taskstats(&ts, &p2->t, &p1->t);
                print_taskstats(&ts);
            }
            else if (p2) {
                print_taskstats(&p2->t);
            }
        }
        PRINTF("--- task dump end ---\n");

        PRINTF("Start since epoch (s) %d\n", start_since_epoch.tv_sec);
        PRINTF("Elapsed time (ns) %llu\n",
            ((long long)end.tv_sec - start.tv_sec) * 1000000000LL +
            end.tv_nsec - start.tv_nsec);
    }

out : 
    if (f != stdout)
        fclose(f);

    return ret;
}