void *pluginsd_worker_thread(void *arg)
{
    struct plugind *cd = (struct plugind *)arg;
    char line[PLUGINSD_LINE_MAX + 1];

#ifdef DETACH_PLUGINS_FROM_NETDATA
    unsigned long long usec = 0, susec = 0;
    struct timeval last = {0, 0} , now = {0, 0};
#endif

    char *words[MAX_WORDS] = { NULL };
    uint32_t SET_HASH = simple_hash("SET");
    uint32_t BEGIN_HASH = simple_hash("BEGIN");
    uint32_t END_HASH = simple_hash("END");
    uint32_t FLUSH_HASH = simple_hash("FLUSH");
    uint32_t CHART_HASH = simple_hash("CHART");
    uint32_t DIMENSION_HASH = simple_hash("DIMENSION");
    uint32_t DISABLE_HASH = simple_hash("DISABLE");
#ifdef DETACH_PLUGINS_FROM_NETDATA
    uint32_t MYPID_HASH = simple_hash("MYPID");
    uint32_t STOPPING_WAKE_ME_UP_PLEASE_HASH = simple_hash("STOPPING_WAKE_ME_UP_PLEASE");
#endif

    size_t count = 0;

    for(;;) {
        if(unlikely(netdata_exit)) break;

        FILE *fp = mypopen(cd->cmd, &cd->pid);
        if(unlikely(!fp)) {
            error("Cannot popen(\"%s\", \"r\").", cd->cmd);
            break;
        }

        info("PLUGINSD: '%s' running on pid %d", cd->fullfilename, cd->pid);

        RRDSET *st = NULL;
        char *s;
        uint32_t hash;

        while(likely(fgets(line, PLUGINSD_LINE_MAX, fp) != NULL)) {
            if(unlikely(netdata_exit)) break;

            line[PLUGINSD_LINE_MAX] = '\0';

            // debug(D_PLUGINSD, "PLUGINSD: %s: %s", cd->filename, line);

            int w = pluginsd_split_words(line, words, MAX_WORDS);
            s = words[0];
            if(unlikely(!s || !*s || !w)) {
                // debug(D_PLUGINSD, "PLUGINSD: empty line");
                continue;
            }

            // debug(D_PLUGINSD, "PLUGINSD: words 0='%s' 1='%s' 2='%s' 3='%s' 4='%s' 5='%s' 6='%s' 7='%s' 8='%s' 9='%s'", words[0], words[1], words[2], words[3], words[4], words[5], words[6], words[7], words[8], words[9]);

            hash = simple_hash(s);

            if(likely(hash == SET_HASH && !strcmp(s, "SET"))) {
                char *dimension = words[1];
                char *value = words[2];

                if(unlikely(!dimension || !*dimension)) {
                    error("PLUGINSD: '%s' is requesting a SET on chart '%s', without a dimension. Disabling it.", cd->fullfilename, st->id);
                    cd->enabled = 0;
                    killpid(cd->pid, SIGTERM);
                    break;
                }

                if(unlikely(!value || !*value)) value = NULL;

                if(unlikely(!st)) {
                    error("PLUGINSD: '%s' is requesting a SET on dimension %s with value %s, without a BEGIN. Disabling it.", cd->fullfilename, dimension, value?value:"<nothing>");
                    cd->enabled = 0;
                    killpid(cd->pid, SIGTERM);
                    break;
                }

                if(unlikely(st->debug)) debug(D_PLUGINSD, "PLUGINSD: '%s' is setting dimension %s/%s to %s", cd->fullfilename, st->id, dimension, value?value:"<nothing>");

                if(value) rrddim_set(st, dimension, strtoll(value, NULL, 0));
            }
            else if(likely(hash == BEGIN_HASH && !strcmp(s, "BEGIN"))) {
                char *id = words[1];
                char *microseconds_txt = words[2];

                if(unlikely(!id)) {
                    error("PLUGINSD: '%s' is requesting a BEGIN without a chart id. Disabling it.", cd->fullfilename);
                    cd->enabled = 0;
                    killpid(cd->pid, SIGTERM);
                    break;
                }

                st = rrdset_find(id);
                if(unlikely(!st)) {
                    error("PLUGINSD: '%s' is requesting a BEGIN on chart '%s', which does not exist. Disabling it.", cd->fullfilename, id);
                    cd->enabled = 0;
                    killpid(cd->pid, SIGTERM);
                    break;
                }

                if(likely(st->counter_done)) {
                    unsigned long long microseconds = 0;
                    if(microseconds_txt && *microseconds_txt) microseconds = strtoull(microseconds_txt, NULL, 10);
                    if(microseconds) rrdset_next_usec(st, microseconds);
                    else rrdset_next_plugins(st);
                }
            }
            else if(likely(hash == END_HASH && !strcmp(s, "END"))) {
                if(unlikely(!st)) {
                    error("PLUGINSD: '%s' is requesting an END, without a BEGIN. Disabling it.", cd->fullfilename);
                    cd->enabled = 0;
                    killpid(cd->pid, SIGTERM);
                    break;
                }

                if(unlikely(st->debug)) debug(D_PLUGINSD, "PLUGINSD: '%s' is requesting an END on chart %s", cd->fullfilename, st->id);

                rrdset_done(st);
                st = NULL;

                count++;
            }
            else if(likely(hash == FLUSH_HASH && !strcmp(s, "FLUSH"))) {
                debug(D_PLUGINSD, "PLUGINSD: '%s' is requesting a FLUSH", cd->fullfilename);
                st = NULL;
            }
            else if(likely(hash == CHART_HASH && !strcmp(s, "CHART"))) {
                int noname = 0;
                st = NULL;

                if((words[1]) != NULL && (words[2]) != NULL && strcmp(words[1], words[2]) == 0)
                    noname = 1;

                char *type = words[1];
                char *id = NULL;
                if(likely(type)) {
                    id = strchr(type, '.');
                    if(likely(id)) { *id = '\0'; id++; }
                }
                char *name = words[2];
                char *title = words[3];
                char *units = words[4];
                char *family = words[5];
                char *context = words[6];
                char *chart = words[7];
                char *priority_s = words[8];
                char *update_every_s = words[9];

                if(unlikely(!type || !*type || !id || !*id)) {
                    error("PLUGINSD: '%s' is requesting a CHART, without a type.id. Disabling it.", cd->fullfilename);
                    cd->enabled = 0;
                    killpid(cd->pid, SIGTERM);
                    break;
                }

                int priority = 1000;
                if(likely(priority_s)) priority = atoi(priority_s);

                int update_every = cd->update_every;
                if(likely(update_every_s)) update_every = atoi(update_every_s);
                if(unlikely(!update_every)) update_every = cd->update_every;

                int chart_type = RRDSET_TYPE_LINE;
                if(unlikely(chart)) chart_type = rrdset_type_id(chart);

                if(unlikely(noname || !name || !*name || strcasecmp(name, "NULL") == 0 || strcasecmp(name, "(NULL)") == 0)) name = NULL;
                if(unlikely(!family || !*family)) family = NULL;
                if(unlikely(!context || !*context)) context = NULL;

                st = rrdset_find_bytype(type, id);
                if(unlikely(!st)) {
                    debug(D_PLUGINSD, "PLUGINSD: Creating chart type='%s', id='%s', name='%s', family='%s', context='%s', chart='%s', priority=%d, update_every=%d"
                        , type, id
                        , name?name:""
                        , family?family:""
                        , context?context:""
                        , rrdset_type_name(chart_type)
                        , priority
                        , update_every
                        );

                    st = rrdset_create(type, id, name, family, context, title, units, priority, update_every, chart_type);
                    cd->update_every = update_every;
                }
                else debug(D_PLUGINSD, "PLUGINSD: Chart '%s' already exists. Not adding it again.", st->id);
            }
            else if(likely(hash == DIMENSION_HASH && !strcmp(s, "DIMENSION"))) {
                char *id = words[1];
                char *name = words[2];
                char *algorithm = words[3];
                char *multiplier_s = words[4];
                char *divisor_s = words[5];
                char *options = words[6];

                if(unlikely(!id || !*id)) {
                    error("PLUGINSD: '%s' is requesting a DIMENSION, without an id. Disabling it.", cd->fullfilename);
                    cd->enabled = 0;
                    killpid(cd->pid, SIGTERM);
                    break;
                }

                if(unlikely(!st)) {
                    error("PLUGINSD: '%s' is requesting a DIMENSION, without a CHART. Disabling it.", cd->fullfilename);
                    cd->enabled = 0;
                    killpid(cd->pid, SIGTERM);
                    break;
                }

                long multiplier = 1;
                if(multiplier_s && *multiplier_s) multiplier = strtol(multiplier_s, NULL, 0);
                if(unlikely(!multiplier)) multiplier = 1;

                long divisor = 1;
                if(likely(divisor_s && *divisor_s)) divisor = strtol(divisor_s, NULL, 0);
                if(unlikely(!divisor)) divisor = 1;

                if(unlikely(!algorithm || !*algorithm)) algorithm = "absolute";

                if(unlikely(st->debug)) debug(D_PLUGINSD, "PLUGINSD: Creating dimension in chart %s, id='%s', name='%s', algorithm='%s', multiplier=%ld, divisor=%ld, hidden='%s'"
                    , st->id
                    , id
                    , name?name:""
                    , rrddim_algorithm_name(rrddim_algorithm_id(algorithm))
                    , multiplier
                    , divisor
                    , options?options:""
                    );

                RRDDIM *rd = rrddim_find(st, id);
                if(unlikely(!rd)) {
                    rd = rrddim_add(st, id, name, multiplier, divisor, rrddim_algorithm_id(algorithm));
                    rd->flags = 0x00000000;
                    if(options && *options) {
                        if(strstr(options, "hidden") != NULL) rd->flags |= RRDDIM_FLAG_HIDDEN;
                        if(strstr(options, "noreset") != NULL) rd->flags |= RRDDIM_FLAG_DONT_DETECT_RESETS_OR_OVERFLOWS;
                        if(strstr(options, "nooverflow") != NULL) rd->flags |= RRDDIM_FLAG_DONT_DETECT_RESETS_OR_OVERFLOWS;
                    }
                }
                else if(unlikely(st->debug)) debug(D_PLUGINSD, "PLUGINSD: dimension %s/%s already exists. Not adding it again.", st->id, id);
            }
            else if(unlikely(hash == DISABLE_HASH && !strcmp(s, "DISABLE"))) {
                error("PLUGINSD: '%s' called DISABLE. Disabling it.", cd->fullfilename);
                cd->enabled = 0;
                killpid(cd->pid, SIGTERM);
                break;
            }
#ifdef DETACH_PLUGINS_FROM_NETDATA
            else if(likely(hash == MYPID_HASH && !strcmp(s, "MYPID"))) {
                char *pid_s = words[1];
                pid_t pid = strtod(pid_s, NULL, 0);

                if(likely(pid)) cd->pid = pid;
                debug(D_PLUGINSD, "PLUGINSD: %s is on pid %d", cd->id, cd->pid);
            }
            else if(likely(hash == STOPPING_WAKE_ME_UP_PLEASE_HASH && !strcmp(s, "STOPPING_WAKE_ME_UP_PLEASE"))) {
                error("PLUGINSD: '%s' (pid %d) called STOPPING_WAKE_ME_UP_PLEASE.", cd->fullfilename, cd->pid);

                gettimeofday(&now, NULL);
                if(unlikely(!usec && !susec)) {
                    // our first run
                    susec = cd->rrd_update_every * 1000000ULL;
                }
                else {
                    // second+ run
                    usec = usec_dt(&now, &last) - susec;
                    error("PLUGINSD: %s last loop took %llu usec (worked for %llu, sleeped for %llu).\n", cd->fullfilename, usec + susec, usec, susec);
                    if(unlikely(usec < (rrd_update_every * 1000000ULL / 2ULL))) susec = (rrd_update_every * 1000000ULL) - usec;
                    else susec = rrd_update_every * 1000000ULL / 2ULL;
                }

                error("PLUGINSD: %s sleeping for %llu. Will kill with SIGCONT pid %d to wake it up.\n", cd->fullfilename, susec, cd->pid);
                usleep(susec);
                killpid(cd->pid, SIGCONT);
                memmove(&last, &now, sizeof(struct timeval));
                break;
            }
#endif
            else {
                error("PLUGINSD: '%s' is sending command '%s' which is not known by netdata. Disabling it.", cd->fullfilename, s);
                cd->enabled = 0;
                killpid(cd->pid, SIGTERM);
                break;
            }
        }
        if(likely(count)) {
            cd->successful_collections += count;
            cd->serial_failures = 0;
        }
        else
            cd->serial_failures++;

        info("PLUGINSD: '%s' on pid %d stopped after %zu successful data collections (ENDs).", cd->fullfilename, cd->pid, count);

        // get the return code
        int code = mypclose(fp, cd->pid);
        
        if(unlikely(netdata_exit)) break;
        else if(code != 0) {
            // the plugin reports failure

            if(likely(!cd->successful_collections)) {
                // nothing collected - disable it
                error("PLUGINSD: '%s' exited with error code %d. Disabling it.", cd->fullfilename, code);
                cd->enabled = 0;
            }
            else {
                // we have collected something

                if(likely(cd->serial_failures <= 10)) {
                    error("PLUGINSD: '%s' exited with error code %d, but has given useful output in the past (%zu times). Waiting a bit before starting it again.", cd->fullfilename, code, cd->successful_collections);
                    sleep((unsigned int) (cd->update_every * 10));
                }
                else {
                    error("PLUGINSD: '%s' exited with error code %d, but has given useful output in the past (%zu times). We tried %zu times to restart it, but it failed to generate data. Disabling it.", cd->fullfilename, code, cd->successful_collections, cd->serial_failures);
                    cd->enabled = 0;
                }
            }
        }
        else {
            // the plugin reports success

            if(unlikely(!cd->successful_collections)) {
                // we have collected nothing so far

                if(likely(cd->serial_failures <= 10)) {
                    error("PLUGINSD: '%s' (pid %d) does not generate useful output but it reports success (exits with 0). Waiting a bit before starting it again.", cd->fullfilename, cd->pid);
                    sleep((unsigned int) (cd->update_every * 10));
                }
                else {
                    error("PLUGINSD: '%s' (pid %d) does not generate useful output, although it reports success (exits with 0), but we have tried %zu times to collect something. Disabling it.", cd->fullfilename, cd->pid, cd->serial_failures);
                    cd->enabled = 0;
                }
            }
            else
                sleep((unsigned int) cd->update_every);
        }
        cd->pid = 0;

        if(unlikely(!cd->enabled)) break;
    }

    info("PLUGINSD: '%s' thread exiting", cd->fullfilename);

    cd->obsolete = 1;
    pthread_exit(NULL);
    return NULL;
}