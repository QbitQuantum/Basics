int main (int argc, char **argv) {
	rd_kafka_topic_t *rkt;
	char *brokers = "localhost:9092";
	char mode = 'C';
	char *topic = NULL;
	int partition = RD_KAFKA_PARTITION_UA;
	int opt;
	rd_kafka_conf_t *conf;
	rd_kafka_topic_conf_t *topic_conf;
	char errstr[512];
	int64_t start_offset = 0;
        int report_offsets = 0;
	int do_conf_dump = 0;
	char tmp[16];
        int64_t seek_offset = 0;
        int64_t tmp_offset = 0;
	int get_wmarks = 0;

	quiet = !isatty(STDIN_FILENO);

	/* Kafka configuration */
	conf = rd_kafka_conf_new();

        /* Set logger */
        rd_kafka_conf_set_log_cb(conf, logger);

	/* Quick termination */
	snprintf(tmp, sizeof(tmp), "%i", SIGIO);
	rd_kafka_conf_set(conf, "internal.termination.signal", tmp, NULL, 0);

	/* Topic configuration */
	topic_conf = rd_kafka_topic_conf_new();

	while ((opt = getopt(argc, argv, "PCLt:p:b:z:qd:o:eX:As:")) != -1) {
		switch (opt) {
		case 'P':
		case 'C':
                case 'L':
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
		case 'z':
			if (rd_kafka_conf_set(conf, "compression.codec",
					      optarg,
					      errstr, sizeof(errstr)) !=
			    RD_KAFKA_CONF_OK) {
				fprintf(stderr, "%% %s\n", errstr);
				exit(1);
			}
			break;
		case 'o':
                case 's':
			if (!strcmp(optarg, "end"))
				tmp_offset = RD_KAFKA_OFFSET_END;
			else if (!strcmp(optarg, "beginning"))
				tmp_offset = RD_KAFKA_OFFSET_BEGINNING;
			else if (!strcmp(optarg, "stored"))
				tmp_offset = RD_KAFKA_OFFSET_STORED;
                        else if (!strcmp(optarg, "report"))
                                report_offsets = 1;
			else if (!strcmp(optarg, "wmark"))
				get_wmarks = 1;
			else {
				tmp_offset = strtoll(optarg, NULL, 10);

				if (tmp_offset < 0)
					tmp_offset = RD_KAFKA_OFFSET_TAIL(-tmp_offset);
			}

                        if (opt == 'o')
                                start_offset = tmp_offset;
                        else if (opt == 's')
                                seek_offset = tmp_offset;
			break;
		case 'e':
			exit_eof = 1;
			break;
		case 'd':
			if (rd_kafka_conf_set(conf, "debug", optarg,
					      errstr, sizeof(errstr)) !=
			    RD_KAFKA_CONF_OK) {
				fprintf(stderr,
					"%% Debug configuration failed: "
					"%s: %s\n",
					errstr, optarg);
				exit(1);
			}
			break;
		case 'q':
			quiet = 1;
			break;
		case 'A':
			output = OUTPUT_RAW;
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

			if (!strcmp(optarg, "dump")) {
				do_conf_dump = 1;
				continue;
			}

			name = optarg;
			if (!(val = strchr(name, '='))) {
				char dest[512];
				size_t dest_size = sizeof(dest);
				/* Return current value for property. */

				res = RD_KAFKA_CONF_UNKNOWN;
				if (!strncmp(name, "topic.", strlen("topic.")))
					res = rd_kafka_topic_conf_get(
						topic_conf,
						name+strlen("topic."),
						dest, &dest_size);
				if (res == RD_KAFKA_CONF_UNKNOWN)
					res = rd_kafka_conf_get(
						conf, name, dest, &dest_size);

				if (res == RD_KAFKA_CONF_OK) {
					printf("%s = %s\n", name, dest);
					exit(0);
				} else {
					fprintf(stderr,
						"%% %s property\n",
						res == RD_KAFKA_CONF_UNKNOWN ?
						"Unknown" : "Invalid");
					exit(1);
				}
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
							      strlen("topic."),
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

		default:
			goto usage;
		}
	}


	if (do_conf_dump) {
		const char **arr;
		size_t cnt;
		int pass;

		for (pass = 0 ; pass < 2 ; pass++) {
			int i;

			if (pass == 0) {
				arr = rd_kafka_conf_dump(conf, &cnt);
				printf("# Global config\n");
			} else {
				printf("# Topic config\n");
				arr = rd_kafka_topic_conf_dump(topic_conf,
							       &cnt);
			}

			for (i = 0 ; i < (int)cnt ; i += 2)
				printf("%s = %s\n",
				       arr[i], arr[i+1]);

			printf("\n");

			rd_kafka_conf_dump_free(arr, cnt);
		}

		exit(0);
	}


	if (optind != argc || (mode != 'L' && !topic)) {
	usage:
		fprintf(stderr,
			"Usage: %s -C|-P|-L -t <topic> "
			"[-p <partition>] [-b <host1:port1,host2:port2,..>]\n"
			"\n"
			"librdkafka version %s (0x%08x)\n"
			"\n"
			" Options:\n"
			"  -C | -P         Consumer or Producer mode\n"
                        "  -L              Metadata list mode\n"
			"  -t <topic>      Topic to fetch / produce\n"
			"  -p <num>        Partition (random partitioner)\n"
			"  -b <brokers>    Broker address (localhost:9092)\n"
			"  -z <codec>      Enable compression:\n"
			"                  none|gzip|snappy\n"
			"  -o <offset>     Start offset (consumer):\n"
			"                  beginning, end, NNNNN or -NNNNN\n"
			"                  wmark returns the current hi&lo "
			"watermarks.\n"
                        "  -o report       Report message offsets (producer)\n"
			"  -e              Exit consumer when last message\n"
			"                  in partition has been received.\n"
			"  -d [facs..]     Enable debugging contexts:\n"
			"                  %s\n"
			"  -q              Be quiet\n"
			"  -A              Raw payload output (consumer)\n"
			"  -X <prop=name>  Set arbitrary librdkafka "
			"configuration property\n"
			"                  Properties prefixed with \"topic.\" "
			"will be set on topic object.\n"
			"  -X list         Show full list of supported "
			"properties.\n"
			"  -X <prop>       Get single property value\n"
			"\n"
			" In Consumer mode:\n"
			"  writes fetched messages to stdout\n"
			" In Producer mode:\n"
			"  reads messages from stdin and sends to broker\n"
                        " In List mode:\n"
                        "  queries broker for metadata information, "
                        "topic is optional.\n"
			"\n"
			"\n"
			"\n",
			argv[0],
			rd_kafka_version_str(), rd_kafka_version(),
			RD_KAFKA_DEBUG_CONTEXTS);
		exit(1);
	}


	signal(SIGINT, stop);
	signal(SIGUSR1, sig_usr1);

	if (mode == 'P') {
		/*
		 * Producer
		 */
		char buf[2048];
		int sendcnt = 0;

		/* Set up a message delivery report callback.
		 * It will be called once for each message, either on successful
		 * delivery to broker, or upon failure to deliver to broker. */

                /* If offset reporting (-o report) is enabled, use the
                 * richer dr_msg_cb instead. */
                if (report_offsets) {
                        rd_kafka_topic_conf_set(topic_conf,
                                                "produce.offset.report",
                                                "true", errstr, sizeof(errstr));
                        rd_kafka_conf_set_dr_msg_cb(conf, msg_delivered2);
                } else
                        rd_kafka_conf_set_dr_cb(conf, msg_delivered);

		/* Create Kafka handle */
		if (!(rk = rd_kafka_new(RD_KAFKA_PRODUCER, conf,
					errstr, sizeof(errstr)))) {
			fprintf(stderr,
				"%% Failed to create new producer: %s\n",
				errstr);
			exit(1);
		}

		rd_kafka_set_log_level(rk, LOG_DEBUG);

		/* Add brokers */
		if (rd_kafka_brokers_add(rk, brokers) == 0) {
			fprintf(stderr, "%% No valid brokers specified\n");
			exit(1);
		}

		/* Create topic */
		rkt = rd_kafka_topic_new(rk, topic, topic_conf);
                topic_conf = NULL; /* Now owned by topic */

		if (!quiet)
			fprintf(stderr,
				"%% Type stuff and hit enter to send\n");

		while (run && fgets(buf, sizeof(buf), stdin)) {
			size_t len = strlen(buf);
			if (buf[len-1] == '\n')
				buf[--len] = '\0';

			/* Send/Produce message. */
			if (rd_kafka_produce(rkt, partition,
					     RD_KAFKA_MSG_F_COPY,
					     /* Payload and length */
					     buf, len,
					     /* Optional key and its length */
					     NULL, 0,
					     /* Message opaque, provided in
					      * delivery report callback as
					      * msg_opaque. */
					     NULL) == -1) {
				fprintf(stderr,
					"%% Failed to produce to topic %s "
					"partition %i: %s\n",
					rd_kafka_topic_name(rkt), partition,
					rd_kafka_err2str(rd_kafka_last_error()));
				/* Poll to handle delivery reports */
				rd_kafka_poll(rk, 0);
				continue;
			}

			if (!quiet)
				fprintf(stderr, "%% Sent %zd bytes to topic "
					"%s partition %i\n",
				len, rd_kafka_topic_name(rkt), partition);
			sendcnt++;
			/* Poll to handle delivery reports */
			rd_kafka_poll(rk, 0);
		}

		/* Poll to handle delivery reports */
		rd_kafka_poll(rk, 0);

		/* Wait for messages to be delivered */
		while (run && rd_kafka_outq_len(rk) > 0)
			rd_kafka_poll(rk, 100);

		/* Destroy topic */
		rd_kafka_topic_destroy(rkt);

		/* Destroy the handle */
		rd_kafka_destroy(rk);

	} else if (mode == 'C') {
		/*
		 * Consumer
		 */

		/* Create Kafka handle */
		if (!(rk = rd_kafka_new(RD_KAFKA_CONSUMER, conf,
					errstr, sizeof(errstr)))) {
			fprintf(stderr,
				"%% Failed to create new consumer: %s\n",
				errstr);
			exit(1);
		}

		rd_kafka_set_log_level(rk, LOG_DEBUG);

		/* Add brokers */
		if (rd_kafka_brokers_add(rk, brokers) == 0) {
			fprintf(stderr, "%% No valid brokers specified\n");
			exit(1);
		}

		if (get_wmarks) {
			int64_t lo, hi;
                        rd_kafka_resp_err_t err;

			/* Only query for hi&lo partition watermarks */

			if ((err = rd_kafka_query_watermark_offsets(
				     rk, topic, partition, &lo, &hi, 5000))) {
				fprintf(stderr, "%% query_watermark_offsets() "
					"failed: %s\n",
					rd_kafka_err2str(err));
				exit(1);
			}

			printf("%s [%d]: low - high offsets: "
			       "%"PRId64" - %"PRId64"\n",
			       topic, partition, lo, hi);

			rd_kafka_destroy(rk);
			exit(0);
		}


		/* Create topic */
		rkt = rd_kafka_topic_new(rk, topic, topic_conf);
                topic_conf = NULL; /* Now owned by topic */

		/* Start consuming */
		if (rd_kafka_consume_start(rkt, partition, start_offset) == -1){
			rd_kafka_resp_err_t err = rd_kafka_last_error();
			fprintf(stderr, "%% Failed to start consuming: %s\n",
				rd_kafka_err2str(err));
                        if (err == RD_KAFKA_RESP_ERR__INVALID_ARG)
                                fprintf(stderr,
                                        "%% Broker based offset storage "
                                        "requires a group.id, "
                                        "add: -X group.id=yourGroup\n");
			exit(1);
		}

		while (run) {
			rd_kafka_message_t *rkmessage;
                        rd_kafka_resp_err_t err;

                        /* Poll for errors, etc. */
                        rd_kafka_poll(rk, 0);

			/* Consume single message.
			 * See rdkafka_performance.c for high speed
			 * consuming of messages. */
			rkmessage = rd_kafka_consume(rkt, partition, 1000);
			if (!rkmessage) /* timeout */
				continue;

			msg_consume(rkmessage, NULL);

			/* Return message to rdkafka */
			rd_kafka_message_destroy(rkmessage);

                        if (seek_offset) {
                                err = rd_kafka_seek(rkt, partition, seek_offset,
                                                    2000);
                                if (err)
                                        printf("Seek failed: %s\n",
                                               rd_kafka_err2str(err));
                                else
                                        printf("Seeked to %"PRId64"\n",
                                               seek_offset);
                                seek_offset = 0;
                        }
		}

		/* Stop consuming */
		rd_kafka_consume_stop(rkt, partition);

                while (rd_kafka_outq_len(rk) > 0)
                        rd_kafka_poll(rk, 10);

		/* Destroy topic */
		rd_kafka_topic_destroy(rkt);

		/* Destroy handle */
		rd_kafka_destroy(rk);

        } else if (mode == 'L') {
                rd_kafka_resp_err_t err = RD_KAFKA_RESP_ERR_NO_ERROR;

		/* Create Kafka handle */
		if (!(rk = rd_kafka_new(RD_KAFKA_PRODUCER, conf,
					errstr, sizeof(errstr)))) {
			fprintf(stderr,
				"%% Failed to create new producer: %s\n",
				errstr);
			exit(1);
		}

		rd_kafka_set_log_level(rk, LOG_DEBUG);

		/* Add brokers */
		if (rd_kafka_brokers_add(rk, brokers) == 0) {
			fprintf(stderr, "%% No valid brokers specified\n");
			exit(1);
		}

                /* Create topic */
                if (topic) {
                        rkt = rd_kafka_topic_new(rk, topic, topic_conf);
                        topic_conf = NULL; /* Now owned by topic */
                } else
                        rkt = NULL;

                while (run) {
                        const struct rd_kafka_metadata *metadata;

                        /* Fetch metadata */
                        err = rd_kafka_metadata(rk, rkt ? 0 : 1, rkt,
                                                &metadata, 5000);
                        if (err != RD_KAFKA_RESP_ERR_NO_ERROR) {
                                fprintf(stderr,
                                        "%% Failed to acquire metadata: %s\n",
                                        rd_kafka_err2str(err));
                                run = 0;
                                break;
                        }

                        metadata_print(topic, metadata);

                        rd_kafka_metadata_destroy(metadata);
                        run = 0;
                }

		/* Destroy topic */
		if (rkt)
			rd_kafka_topic_destroy(rkt);

		/* Destroy the handle */
		rd_kafka_destroy(rk);

                if (topic_conf)
                        rd_kafka_topic_conf_destroy(topic_conf);


                /* Exit right away, dont wait for background cleanup, we haven't
                 * done anything important anyway. */
                exit(err ? 2 : 0);
        }

        if (topic_conf)
                rd_kafka_topic_conf_destroy(topic_conf);

	/* Let background threads clean up and terminate cleanly. */
	run = 5;
	while (run-- > 0 && rd_kafka_wait_destroyed(1000) == -1)
		printf("Waiting for librdkafka to decommission\n");
	if (run <= 0)
		rd_kafka_dump(stdout, rk);

	return 0;
}