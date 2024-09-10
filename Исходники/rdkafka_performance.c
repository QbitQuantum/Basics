int main (int argc, char **argv) {
    char *brokers = "localhost";
    char mode = 'C';
    char *topic = NULL;
    const char *key = NULL;
    int partition = RD_KAFKA_PARTITION_UA; /* random */
    int opt;
    int msgcnt = -1;
    int sendflags = 0;
    char *msgpattern = "librdkafka_performance testing!";
    int msgsize = strlen(msgpattern);
    const char *debug = NULL;
    rd_ts_t now;
    char errstr[512];
    uint64_t seq = 0;
    int seed = time(NULL);
    rd_kafka_topic_t *rkt;
    rd_kafka_conf_t *conf;
    rd_kafka_topic_conf_t *topic_conf;
    const char *compression = "no";
    int64_t start_offset = 0;
    int batch_size = 0;
    int idle = 0;

    /* Kafka configuration */
    conf = rd_kafka_conf_new();
    rd_kafka_conf_set_error_cb(conf, err_cb);
    rd_kafka_conf_set_dr_cb(conf, msg_delivered);

    /* Producer config */
    rd_kafka_conf_set(conf, "queue.buffering.max.messages", "500000",
                      NULL, 0);
    rd_kafka_conf_set(conf, "message.send.max.retries", "3", NULL, 0);
    rd_kafka_conf_set(conf, "retry.backoff.ms", "500", NULL, 0);

    /* Consumer config */
    /* Tell rdkafka to (try to) maintain 1M messages
     * in its internal receive buffers. This is to avoid
     * application -> rdkafka -> broker  per-message ping-pong
     * latency.
     * The larger the local queue, the higher the performance.
     * Try other values with: ... -X queued.min.messages=1000
     */
    rd_kafka_conf_set(conf, "queued.min.messages", "1000000", NULL, 0);



    /* Kafka topic configuration */
    topic_conf = rd_kafka_topic_conf_new();
    rd_kafka_topic_conf_set(topic_conf, "message.timeout.ms", "5000",
                            NULL, 0);

    while ((opt =
                getopt(argc, argv,
                       "PCt:p:b:s:k:c:fi:Dd:m:S:x:R:a:z:o:X:B:eT:qI")) != -1) {
        switch (opt) {
        case 'P':
        case 'C':
            mode = opt;
            break;
        case 't':
            topic = optarg;
            break;
        case 'p':
            partition = atoi(optarg);
            break;
        case 'b':
            brokers = optarg;
            break;
        case 's':
            msgsize = atoi(optarg);
            break;
        case 'k':
            key = optarg;
            break;
        case 'c':
            msgcnt = atoi(optarg);
            break;
        case 'D':
            sendflags |= RD_KAFKA_MSG_F_FREE;
            break;
        case 'i':
            dispintvl = atoi(optarg);
            break;
        case 'm':
            msgpattern = optarg;
            break;
        case 'S':
            seq = strtoull(optarg, NULL, 10);
            do_seq = 1;
            break;
        case 'x':
            exit_after = atoi(optarg);
            break;
        case 'R':
            seed = atoi(optarg);
            break;
        case 'a':
            if (rd_kafka_topic_conf_set(topic_conf,
                                        "request.required.acks",
                                        optarg,
                                        errstr, sizeof(errstr)) !=
                    RD_KAFKA_CONF_OK) {
                fprintf(stderr, "%% %s\n", errstr);
                exit(1);
            }
            break;
        case 'B':
            batch_size = atoi(optarg);
            break;
        case 'z':
            if (rd_kafka_conf_set(conf, "compression.codec",
                                  optarg,
                                  errstr, sizeof(errstr)) !=
                    RD_KAFKA_CONF_OK) {
                fprintf(stderr, "%% %s\n", errstr);
                exit(1);
            }
            compression = optarg;
            break;
        case 'o':
            start_offset = strtoll(optarg, NULL, 10);
            break;
        case 'e':
            exit_eof = 1;
            break;
        case 'd':
            debug = optarg;
            break;
        case 'X':
        {
            char *name, *val;
            rd_kafka_conf_res_t res;

            if (!strcmp(optarg, "list") ||
                    !strcmp(optarg, "help")) {
                rd_kafka_conf_properties_show(stdout);
                exit(0);
            }

            name = optarg;
            if (!(val = strchr(name, '='))) {
                fprintf(stderr, "%% Expected "
                        "-X property=value, not %s\n", name);
                exit(1);
            }

            *val = '\0';
            val++;

            res = RD_KAFKA_CONF_UNKNOWN;
            /* Try "topic." prefixed properties on topic
             * conf first, and then fall through to global if
             * it didnt match a topic configuration property. */
            if (!strncmp(name, "topic.", strlen("topic.")))
                res = rd_kafka_topic_conf_set(topic_conf,
                                              name+
                                              strlen("topic"),
                                              val,
                                              errstr,
                                              sizeof(errstr));

            if (res == RD_KAFKA_CONF_UNKNOWN)
                res = rd_kafka_conf_set(conf, name, val,
                                        errstr, sizeof(errstr));

            if (res != RD_KAFKA_CONF_OK) {
                fprintf(stderr, "%% %s\n", errstr);
                exit(1);
            }
        }
        break;

        case 'T':
            if (rd_kafka_conf_set(conf, "statistics.interval.ms",
                                  optarg, errstr, sizeof(errstr)) !=
                    RD_KAFKA_CONF_OK) {
                fprintf(stderr, "%% %s\n", errstr);
                exit(1);
            }
            rd_kafka_conf_set_stats_cb(conf, stats_cb);
            break;

        case 'q':
            quiet = 1;
            break;

        case 'I':
            idle = 1;
            break;

        default:
            goto usage;
        }
    }

    if (!topic || optind != argc) {
usage:
        fprintf(stderr,
                "Usage: %s [-C|-P] -t <topic> "
                "[-p <partition>] [-b <broker,broker..>] [options..]\n"
                "\n"
                "librdkafka version %s (0x%08x)\n"
                "\n"
                " Options:\n"
                "  -C | -P      Consumer or Producer mode\n"
                "  -t <topic>   Topic to fetch / produce\n"
                "  -p <num>     Partition (defaults to random)\n"
                "  -b <brokers> Broker address list (host[:port],..)\n"
                "  -s <size>    Message size (producer)\n"
                "  -k <key>     Message key (producer)\n"
                "  -c <cnt>     Messages to transmit/receive\n"
                "  -D           Copy/Duplicate data buffer (producer)\n"
                "  -i <ms>      Display interval\n"
                "  -m <msg>     Message payload pattern\n"
                "  -S <start>   Send a sequence number starting at "
                "<start> as payload\n"
                "  -R <seed>    Random seed value (defaults to time)\n"
                "  -a <acks>    Required acks (producer): "
                "-1, 0, 1, >1\n"
                "  -B <size>    Consume batch size (# of msgs)\n"
                "  -z <codec>   Enable compression:\n"
                "               none|gzip|snappy\n"
                "  -o <offset>  Start offset (consumer)\n"
                "  -d [facs..]  Enable debugging contexts:\n"
                "               %s\n"
                "  -X <prop=name> Set arbitrary librdkafka "
                "configuration property\n"
                "               Properties prefixed with \"topic.\" "
                "will be set on topic object.\n"
                "               Use '-X list' to see the full list\n"
                "               of supported properties.\n"
                "  -T <intvl>   Enable statistics from librdkafka at "
                "specified interval (ms)\n"
                "  -q           Be more quiet\n"
                "  -I           Idle: dont produce any messages\n"
                "\n"
                " In Consumer mode:\n"
                "  consumes messages and prints thruput\n"
                "  If -B <..> is supplied the batch consumer\n"
                "  mode is used, else the callback mode is used.\n"
                "\n"
                " In Producer mode:\n"
                "  writes messages of size -s <..> and prints thruput\n"
                "\n",
                argv[0],
                rd_kafka_version_str(), rd_kafka_version(),
                RD_KAFKA_DEBUG_CONTEXTS);
        exit(1);
    }


    dispintvl *= 1000; /* us */

    printf("%% Using random seed %i\n", seed);
    srand(seed);
    signal(SIGINT, stop);
    signal(SIGUSR1, sig_usr1);


    if (debug &&
            rd_kafka_conf_set(conf, "debug", debug, errstr, sizeof(errstr)) !=
            RD_KAFKA_CONF_OK) {
        printf("%% Debug configuration failed: %s: %s\n",
               errstr, debug);
        exit(1);
    }

    /* Socket hangups are gracefully handled in librdkafka on socket error
     * without the use of signals, so SIGPIPE should be ignored by the
     * calling program. */
    signal(SIGPIPE, SIG_IGN);

    if (msgcnt != -1)
        forever = 0;

    if (mode == 'P') {
        /*
         * Producer
         */
        char *sbuf;
        char *pbuf;
        int outq;
        int i;
        int keylen = key ? strlen(key) : 0;
        off_t rof = 0;
        size_t plen = strlen(msgpattern);

        if (do_seq) {
            if (msgsize < strlen("18446744073709551615: ")+1)
                msgsize = strlen("18446744073709551615: ")+1;
            /* Force duplication of payload */
            sendflags |= RD_KAFKA_MSG_F_FREE;
        }

        sbuf = malloc(msgsize);

        /* Copy payload content to new buffer */
        while (rof < msgsize) {
            size_t xlen = RD_MIN(msgsize-rof, plen);
            memcpy(sbuf+rof, msgpattern, xlen);
            rof += xlen;
        }

        if (msgcnt == -1)
            printf("%% Sending messages of size %i bytes\n",
                   msgsize);
        else
            printf("%% Sending %i messages of size %i bytes\n",
                   msgcnt, msgsize);

        /* Create Kafka handle */
        if (!(rk = rd_kafka_new(RD_KAFKA_PRODUCER, conf,
                                errstr, sizeof(errstr)))) {
            fprintf(stderr,
                    "%% Failed to create Kafka producer: %s\n",
                    errstr);
            exit(1);
        }

        if (debug)
            rd_kafka_set_log_level(rk, 7);

        /* Add broker(s) */
        if (rd_kafka_brokers_add(rk, brokers) < 1) {
            fprintf(stderr, "%% No valid brokers specified\n");
            exit(1);
        }

        /* Explicitly create topic to avoid per-msg lookups. */
        rkt = rd_kafka_topic_new(rk, topic, topic_conf);

        cnt.t_start = rd_clock();

        while (run && (msgcnt == -1 || cnt.msgs < msgcnt)) {
            /* Send/Produce message. */

            if (idle) {
                rd_kafka_poll(rk, 1000);
                continue;
            }

            if (do_seq) {
                snprintf(sbuf, msgsize-1, "%"PRIu64": ", seq);
                seq++;
            }

            if (sendflags & RD_KAFKA_MSG_F_FREE) {
                /* Duplicate memory */
                pbuf = malloc(msgsize);
                memcpy(pbuf, sbuf, msgsize);
            } else
                pbuf = sbuf;

            cnt.tx++;
            while (run &&
                    rd_kafka_produce(rkt, partition,
                                     sendflags, pbuf, msgsize,
                                     key, keylen, NULL) == -1) {
                if (errno == ESRCH)
                    printf("No such partition: %"PRId32"\n",
                           partition);
                else if (!quiet || errno != ENOBUFS)
                    printf("produce error: %s%s\n",
                           strerror(errno),
                           errno == ENOBUFS ?
                           " (backpressure)":"");
                msgs_failed++;
                cnt.tx_err++;
                if (errno != ENOBUFS) {
                    run = 0;
                    break;
                }
                now = rd_clock();
                if (cnt.t_last + dispintvl <= now) {
                    printf("%% Backpressure %i "
                           "(tx %"PRIu64", "
                           "txerr %"PRIu64")\n",
                           rd_kafka_outq_len(rk),
                           cnt.tx, cnt.tx_err);
                    cnt.t_last = now;
                }
                /* Poll to handle delivery reports */
                rd_kafka_poll(rk, 10);
            }

            msgs_wait_cnt++;
            cnt.msgs++;
            cnt.bytes += msgsize;

            print_stats(mode, 0, compression);

            /* Must poll to handle delivery reports */
            rd_kafka_poll(rk, 0);

        }

        forever = 0;
        printf("All messages produced, "
               "now waiting for %li deliveries\n",
               msgs_wait_cnt);
        rd_kafka_dump(stdout, rk);

        /* Wait for messages to be delivered */
        i = 0;
        while (run && rd_kafka_poll(rk, 1000) != -1) {
            if (!(i++ % (dispintvl/1000)))
                printf("%% Waiting for %li, "
                       "%i messages in outq "
                       "to be sent. Abort with Ctrl-c\n",
                       msgs_wait_cnt,
                       rd_kafka_outq_len(rk));
        }


        outq = rd_kafka_outq_len(rk);
        printf("%% %i messages in outq\n", outq);
        cnt.msgs -= outq;
        cnt.bytes -= msgsize * outq;

        cnt.t_end = t_end;

        if (cnt.tx_err > 0)
            printf("%% %"PRIu64" backpressures for %"PRIu64
                   " produce calls: %.3f%% backpressure rate\n",
                   cnt.tx_err, cnt.tx,
                   ((double)cnt.tx_err / (double)cnt.tx) * 100.0);

        rd_kafka_dump(stdout, rk);

        /* Destroy the handle */
        rd_kafka_destroy(rk);

    } else if (mode == 'C') {
        /*
         * Consumer
         */

        rd_kafka_message_t **rkmessages = NULL;

#if 0 /* Future API */
        /* The offset storage file is optional but its presence
         * avoids starting all over from offset 0 again when
         * the program restarts.
         * ZooKeeper functionality will be implemented in future
         * versions and then the offset will be stored there instead. */
        conf.consumer.offset_file = "."; /* current directory */

        /* Indicate to rdkafka that the application is responsible
         * for storing the offset. This allows the application to
         * successfully handle a message before storing the offset.
         * If this flag is not set rdkafka will store the offset
         * just prior to returning the message from rd_kafka_consume().
         */
        conf.flags |= RD_KAFKA_CONF_F_APP_OFFSET_STORE;
#endif

        /* Create Kafka handle */
        if (!(rk = rd_kafka_new(RD_KAFKA_CONSUMER, conf,
                                errstr, sizeof(errstr)))) {
            fprintf(stderr,
                    "%% Failed to create Kafka consumer: %s\n",
                    errstr);
            exit(1);
        }

        if (debug)
            rd_kafka_set_log_level(rk, 7);

        /* Add broker(s) */
        if (rd_kafka_brokers_add(rk, brokers) < 1) {
            fprintf(stderr, "%% No valid brokers specified\n");
            exit(1);
        }

        /* Create topic to consume from */
        rkt = rd_kafka_topic_new(rk, topic, topic_conf);

        /* Batch consumer */
        if (batch_size)
            rkmessages = malloc(sizeof(*rkmessages) * batch_size);

        /* Start consuming */
        if (rd_kafka_consume_start(rkt, partition, start_offset) == -1) {
            fprintf(stderr, "%% Failed to start consuming: %s\n",
                    strerror(errno));
            exit(1);
        }

        cnt.t_start = rd_clock();
        while (run && (msgcnt == -1 || msgcnt > cnt.msgs)) {
            /* Consume messages.
             * A message may either be a real message, or
             * an error signaling (if rkmessage->err is set).
             */
            uint64_t latency;
            int r;

            latency = rd_clock();

            if (batch_size) {
                int i;

                /* Batch fetch mode */
                r = rd_kafka_consume_batch(rkt, partition,
                                           1000,
                                           rkmessages,
                                           batch_size);
                if (r != -1) {
                    for (i = 0 ; i < r ; i++) {
                        msg_consume(rkmessages[i],NULL);
                        rd_kafka_message_destroy(
                            rkmessages[i]);
                    }
                }
            } else {
                /* Callback mode */
                r = rd_kafka_consume_callback(rkt, partition,
                                              1000/*timeout*/,
                                              msg_consume,
                                              NULL);
            }

            cnt.t_latency += rd_clock() - latency;

            if (r == -1)
                fprintf(stderr, "%% Error: %s\n",
                        strerror(errno));

            print_stats(mode, 0, compression);

            /* Poll to handle stats callbacks */
            rd_kafka_poll(rk, 0);
        }
        cnt.t_end = rd_clock();

        /* Stop consuming */
        rd_kafka_consume_stop(rkt, partition);

        /* Destroy topic */
        rd_kafka_topic_destroy(rkt);

        if (batch_size)
            free(rkmessages);

        /* Destroy the handle */
        rd_kafka_destroy(rk);

    }

    print_stats(mode, 1, compression);

    if (cnt.t_latency && cnt.msgs)
        printf("%% Average application fetch latency: %"PRIu64"us\n",
               cnt.t_latency / cnt.msgs);

    /* Let background threads clean up and terminate cleanly. */
    rd_kafka_wait_destroyed(2000);

    return 0;
}