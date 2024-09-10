void
running_check(int check_type)
{
    int        total_num=0, i, j, k;
    FILE      *fp;
    char       line[2][LEN_40960];
    char       filename[LEN_128] = {0};
    char       tmp[10][LEN_4096];
    char       check[LEN_40960] = {0};
    char       host_name[LEN_64] = {0};
    struct     module *mod = NULL;
    struct     stat statbuf;
    time_t     nowtime;
    double    *st_array;

    /* get hostname */
    if (0 != gethostname(host_name, sizeof(host_name))) {
        do_debug(LOG_FATAL, "tsar -check: gethostname err, errno=%d", errno);
    }
    i = 0;
    while (host_name[i]) {
        if (!isprint(host_name[i++])) {
            host_name[i-1] = '\0';
            break;
        }
    }
    memset(tmp, 0, 10 * LEN_4096);
    sprintf(check, "%s\ttsar\t", host_name);
    sprintf(filename, "%s", conf.output_file_path);
    fp = fopen(filename, "r");
    if (!fp) {
        do_debug(LOG_FATAL, "unable to open the log file %s.\n", filename);
    }
    /* check file update time */
    stat(filename, &statbuf);
    time(&nowtime);
    if (nowtime - statbuf.st_mtime > 300) {
        do_debug(LOG_FATAL, "/var/log/tsar.data is far away from now, now time is %d, last time is %d", nowtime, statbuf.st_mtime);
    }
    /* get file len */
    memset(&line[0], 0, LEN_40960);
    total_num =0;
    /* find two \n from end*/
    if (fseek(fp, -1, SEEK_END) != 0) {
        do_debug(LOG_FATAL, "fseek error:%s", strerror(errno));
    }
    while (1) {
        if (fgetc(fp) == '\n') {
            ++total_num;
        }
        if (total_num == 3) {
            break;
        }
        if (fseek(fp, -2, SEEK_CUR) != 0) {
            /* just 1 or 2 line, goto file header */
            if (fseek(fp, 0, SEEK_SET) != 0) {
                do_debug(LOG_FATAL, "fseek error:%s", strerror(errno));
            }
            break;
        }
    }
    /*FIX ME*/
    if (total_num == 0) {
        if (fclose(fp) < 0) {
            do_debug(LOG_FATAL, "fclose error:%s", strerror(errno));
        }
        memset(filename, 0, sizeof(filename));
        sprintf(filename, "%s.1", conf.output_file_path);
        fp = fopen(filename, "r");
        if (!fp) {
            do_debug(LOG_FATAL, "unable to open the log file %s.\n", filename);
        }
        total_num = 0;
        memset(&line[0], 0, 2 * LEN_40960);
        /* count tsar.data.1 lines */
        if (fseek(fp, -1, SEEK_END) != 0) {
            do_debug(LOG_FATAL, "fseek error:%s", strerror(errno));
        }
        while (1) {
            if (fgetc(fp) == '\n') {
                ++total_num;
            }
            if (total_num == 3) {
                break;
            }
            if (fseek(fp, -2, SEEK_CUR) != 0) {
                if (fseek(fp, 0, SEEK_SET) != 0) {
                    do_debug(LOG_FATAL, "fseek error:%s", strerror(errno));
                }
                break;
            }
        }
        if (total_num < 2) {
            do_debug(LOG_FATAL, "not enough lines at log file %s.\n", filename);
        }

        memset(&line[0], 0, LEN_40960);
        if (!fgets(line[0], LEN_40960, fp)) {
            do_debug(LOG_FATAL, "fgets error:%s", strerror(errno));
        }
        memset(&line[1], 0, LEN_40960);
        if (!fgets(line[1], LEN_40960, fp)) {
            do_debug(LOG_FATAL, "fgets error:%s", strerror(errno));
        }

    } else if (total_num == 1) {
        memset(&line[1], 0, LEN_40960);
        if (!fgets(line[1], LEN_40960, fp)) {
            do_debug(LOG_FATAL, "fgets error:%s", strerror(errno));
        }
        if (fclose(fp) < 0) {
            do_debug(LOG_FATAL, "fclose error:%s", strerror(errno));
        }
        sprintf(filename, "%s.1", conf.output_file_path);
        fp = fopen(filename, "r");
        if (!fp) {
            do_debug(LOG_FATAL, "unable to open the log file %s\n", filename);
        }
        total_num = 0;
        /* go to the start of the last line at tsar.data.1 */
        if (fseek(fp, -1, SEEK_END) != 0) {
            do_debug(LOG_FATAL, "fseek error:%s", strerror(errno));
        }
        while (1) {
            if (fgetc(fp) == '\n') {
                ++total_num;
            }
            /* find the sencond \n from the end, read fp point to the last line */
            if (total_num == 2) {
                break;
            }
            if (fseek(fp, -2, SEEK_CUR) != 0) {
                if (fseek(fp, 0, SEEK_SET) != 0) {
                    do_debug(LOG_FATAL, "fseek error:%s", strerror(errno));
                }
                break;
            }
        }

        if (total_num < 1) {
            do_debug(LOG_FATAL, "not enough lines at log file %s\n", filename);
        }
        memset(&line[0], 0, LEN_40960);
        if (!fgets(line[0], LEN_40960, fp)) {
            do_debug(LOG_FATAL, "fgets error:%s", strerror(errno));
        }

    } else {
        memset(&line[0], 0, LEN_40960);
        if (!fgets(line[0], LEN_40960, fp)) {
            do_debug(LOG_FATAL, "fgets error:%s", strerror(errno));
        }
        memset(&line[1], 0, LEN_40960);
        if (!fgets(line[1], LEN_40960, fp)) {
            do_debug(LOG_FATAL, "fgets error:%s", strerror(errno));
        }
    }
    /* set struct module fields */
    init_module_fields();

    /* read one line to init module parameter */
    read_line_to_module_record(line[0]);
    collect_record_stat();

    read_line_to_module_record(line[1]);
    collect_record_stat();
    /*display check detail*/
    /* ---------------------------RUN_CHECK_NEW--------------------------------------- */
    if (check_type == RUN_CHECK_NEW) {
        printf("%s\ttsar\t", host_name);
        for (i = 0; i < statis.total_mod_num; i++) {
            mod = &mods[i];
            if (!mod->enable) {
                continue;
            }
            struct mod_info *info = mod->info;
            /* get mod name */
            char *mod_name = strstr(mod->opt_line, "--");
            if (mod_name) {
                mod_name += 2;
            }

            char opt[LEN_128] = {0};
            char *n_record = strdup(mod->record);
            char *token = strtok(n_record, ITEM_SPLIT);
            char *s_token;

            for (j = 0; j < mod->n_item; j++) {
                memset(opt, 0, sizeof(opt));
                if (token) {
                    s_token = strstr(token, ITEM_SPSTART);
                    if (s_token) {
                        strncat(opt, token, s_token - token);
                        strcat(opt, ":");
                    }
                }
                st_array = &mod->st_array[j * mod->n_col];
                for (k=0; k < mod->n_col; k++) {
                    if (mod->spec) {
                        if (!st_array || !mod->st_flag) {
                            if (((DATA_SUMMARY == conf.print_mode) && (SPEC_BIT == info[k].summary_bit))
                                    || ((DATA_DETAIL == conf.print_mode) && (SPEC_BIT == info[k].summary_bit)))
                            {
                                printf("%s:%s%s=-%s", mod_name, opt, trim(info[k].hdr, LEN_128), " ");
                            }

                        } else {
                            if (((DATA_SUMMARY == conf.print_mode) && (SPEC_BIT == info[k].summary_bit))
                                    || ((DATA_DETAIL == conf.print_mode) && (SPEC_BIT == info[k].summary_bit)))
                            {
                                printf("%s:%s%s=", mod_name, opt, trim(info[k].hdr, LEN_128));
                                printf("%0.1f ", st_array[k]);
                            }
                        }

                    } else {
                        if (!st_array || !mod->st_flag) {
                            if (((DATA_SUMMARY == conf.print_mode) && (SUMMARY_BIT == info[k].summary_bit))
                                    || ((DATA_DETAIL == conf.print_mode) && (HIDE_BIT != info[k].summary_bit)))
                            {
                                printf("%s:%s%s=-%s", mod_name, opt, trim(info[k].hdr, LEN_128), " ");
                            }

                        } else {
                            if (((DATA_SUMMARY == conf.print_mode) && (SUMMARY_BIT == info[k].summary_bit))
                                    || ((DATA_DETAIL == conf.print_mode) && (HIDE_BIT != info[k].summary_bit)))
                            {
                                printf("%s:%s%s=", mod_name, opt, trim(info[k].hdr, LEN_128));
                                printf("%0.1f ", st_array[k]);
                            }
                        }

                    }
                }
                if (token) {
                    token = strtok(NULL, ITEM_SPLIT);
                }
            }
            if (n_record) {
                free(n_record);
                n_record = NULL;
            }
        }
        printf("\n");
        if (fclose(fp) < 0) {
            do_debug(LOG_FATAL, "fclose error:%s", strerror(errno));
        }
        fp = NULL;
        return;
    }
#ifdef OLDTSAR
    /*tsar -check output similar as:
      v014119.cm3   tsar   apache/qps=5.35 apache/rt=165.89 apache/busy=2 apache/idle=148 cpu=3.58 mem=74.93% load1=0.22 load5=0.27 load15=0.20 xvda=0.15 ifin=131.82 ifout=108.86 TCPretr=0.12 df/=4.04% df/home=10.00% df/opt=71.22% df/tmp=2.07% df/usr=21.27% df/var=5.19%
     */
    /* ------------------------------RUN_CHECK------------------------------------------- */
    if (check_type == RUN_CHECK) {
        for (i = 0; i < statis.total_mod_num; i++) {
            mod = &mods[i];
            if (!mod->enable){
                continue;
            }
            if (!strcmp(mod->name, "mod_apache")) {
                for (j = 0; j < mod->n_item; j++) {
                    st_array = &mod->st_array[j * mod->n_col];
                    if (!st_array || !mod->st_flag) {
                        sprintf(tmp[0], " apache/qps=- apache/rt=- apache/busy=- apache/idle=-");

                    } else {
                        sprintf(tmp[0], " apache/qps=%0.2f apache/rt=%0.2f apache/busy=%0.0f apache/idle=%0.0f", st_array[0], st_array[1], st_array[3], st_array[4]);
                    }
                }
            }
            if (!strcmp(mod->name, "mod_cpu")) {
                for (j = 0; j < mod->n_item; j++) {
                    st_array = &mod->st_array[j * mod->n_col];
                    if (!st_array || !mod->st_flag) {
                        sprintf(tmp[1], " cpu=-");

                    } else {
                        sprintf(tmp[1], " cpu=%0.2f", st_array[5]);
                    }
                }
            }
            if (!strcmp(mod->name, "mod_mem")) {
                for (j = 0; j < mod->n_item; j++) {
                    st_array = &mod->st_array[j * mod->n_col];
                    if (!st_array || !mod->st_flag) {
                        sprintf(tmp[2], " mem=-");

                    } else {
                        sprintf(tmp[2], " mem=%0.2f%%", st_array[5]);
                    }
                }
            }
            if (!strcmp(mod->name, "mod_load")) {
                for (j = 0; j < mod->n_item; j++) {
                    st_array = &mod->st_array[j * mod->n_col];
                    if (!st_array || !mod->st_flag) {
                        sprintf(tmp[3], " load1=- load5=- load15=-");

                    } else {
                        sprintf(tmp[3], " load1=%0.2f load5=%0.2f load15=%0.2f", st_array[0], st_array[1], st_array[2]);
                    }
                }
            }
            if (!strcmp(mod->name, "mod_io")) {
                char    opt[LEN_128] = {0};
                char    item[LEN_128] = {0};
                char   *n_record = strdup(mod->record);
                char   *token = strtok(n_record, ITEM_SPLIT);
                char   *s_token;
                for (j = 0; j < mod->n_item; j++) {
                    s_token = strstr(token, ITEM_SPSTART);
                    if (s_token) {
                        memset(opt, 0, sizeof(opt));
                        strncat(opt, token, s_token - token);
                        st_array = &mod->st_array[j * mod->n_col];
                        if (!st_array || !mod->st_flag) {
                            sprintf(item, " %s=-", opt);

                        } else {
                            sprintf(item, " %s=%0.2f", opt, st_array[10]);
                        }
                        strcat(tmp[4], item);
                    }
                    token = strtok(NULL, ITEM_SPLIT);
                }
                if (n_record) {
                    free(n_record);
                    n_record = NULL;
                }
            }
            if (!strcmp(mod->name, "mod_traffic")) {
                for (j = 0; j < mod->n_item; j++) {
                    st_array = &mod->st_array[j * mod->n_col];
                    if (!st_array || !mod->st_flag) {
                        sprintf(tmp[5], " ifin=- ifout=-");

                    } else {
                        sprintf(tmp[5], " ifin=%0.2f ifout=%0.2f", st_array[0] / 1000, st_array[1] / 1000);
                    }
                }
            }
            if (!strcmp(mod->name, "mod_tcp")) {
                for (j = 0; j < mod->n_item; j++) {
                    st_array = &mod->st_array[j * mod->n_col];
                    if (!st_array || !mod->st_flag) {
                        sprintf(tmp[6], " TCPretr=-");

                    } else {
                        sprintf(tmp[6], " TCPretr=%0.2f", st_array[7]);
                    }
                }
            }
            if (!strcmp(mod->name, "mod_partition")) {
                char    opt[LEN_128] = {0};
                char    item[LEN_128] = {0};
                char   *n_record = strdup(mod->record);
                char   *token = strtok(n_record, ITEM_SPLIT);
                char   *s_token;
                for (j = 0; j < mod->n_item; j++) {
                    s_token = strstr(token, ITEM_SPSTART);
                    if (s_token) {
                        memset(opt, 0, sizeof(opt));
                        strncat(opt, token, s_token - token);
                        st_array = &mod->st_array[j * mod->n_col];
                        if (!st_array || !mod->st_flag) {
                            sprintf(item, " df%s=-", opt);

                        } else {
                            sprintf(item, " df%s=%0.2f%%", opt, st_array[3]);
                        }
                        strcat(tmp[7], item);
                    }
                    token = strtok(NULL, ITEM_SPLIT);
                }
                if (n_record) {
                    free(n_record);
                    n_record = NULL;
                }
            }
            if (!strcmp(mod->name, "mod_nginx")){
                for (j = 0; j < mod->n_item; j++) {
                    st_array = &mod->st_array[j * mod->n_col];
                    if (!st_array || !mod->st_flag) {
                        sprintf(tmp[8], " nginx/qps=- nginx/rt=-");

                    } else {
                        sprintf(tmp[8], " nginx/qps=%0.2f nginx/rt=%0.2f", st_array[7], st_array[8]);
                    }
                }
            }
	    if (!strcmp(mod->name, "mod_swap")) {
	        for (j = 0; j < mod->n_item; j++) {
                    st_array = &mod->st_array[j * mod->n_col];
                    if (!st_array || !mod->st_flag) {
                        sprintf(tmp[9], " swap/total=- swap/util=-");

                    } else {
                        sprintf(tmp[9], " swap/total=%0.2f swap/util=%0.2f%%", st_array[2] / 1024 / 1024, st_array[3]);
                    }
                }
	    }
        }
        for (j = 0; j < 10; j++) {
            strcat(check, tmp[j]);
        }
        printf("%s\n", check);
        if (fclose(fp) < 0) {
            do_debug(LOG_FATAL, "fclose error:%s", strerror(errno));
        }
        fp = NULL;
    }
#endif
}