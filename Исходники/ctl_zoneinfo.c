int main(int argc, char **argv)
{
    int opt, r = 0;
    char *alt_config = NULL, *pub = NULL, *ver = NULL, *winfile = NULL;
    char prefix[2048];
    enum { REBUILD, WINZONES, NONE } op = NONE;

    if ((geteuid()) == 0 && (become_cyrus(/*ismaster*/0) != 0)) {
        fatal("must run as the Cyrus user", EC_USAGE);
    }

    while ((opt = getopt(argc, argv, "C:r:vw:")) != EOF) {
        switch (opt) {
        case 'C': /* alt config file */
            alt_config = optarg;
            break;

        case 'r':
            if (op == NONE) {
                op = REBUILD;
                pub = optarg;
                ver = strchr(optarg, ':');
                if (ver) *ver++ = '\0';
                else usage();
            }
            else usage();
            break;

        case 'v':
            verbose = 1;
            break;

        case 'w':
            if (op == NONE) {
                op = WINZONES;
                winfile = optarg;
            }
            else usage();
            break;

        default:
            usage();
        }
    }

    cyrus_init(alt_config, "ctl_zoneinfo", 0, 0);

    signals_set_shutdown(&shut_down);
    signals_add_handlers(0);

    snprintf(prefix, sizeof(prefix), "%s%s", config_dir, FNAME_ZONEINFODIR);

    switch (op) {
    case REBUILD: {
        struct hash_table tzentries;
        struct zoneinfo *info;
        struct txn *tid = NULL;
        char buf[1024];
        FILE *fp;

        construct_hash_table(&tzentries, 500, 1);

        /* Add INFO record (overall lastmod and TZ DB source version) */
        info = xzmalloc(sizeof(struct zoneinfo));
        info->type = ZI_INFO;
        appendstrlist(&info->data, pub);
        appendstrlist(&info->data, ver);
        hash_insert(INFO_TZID, info, &tzentries);

        /* Add LEAP record (last updated and hash) */
        snprintf(buf, sizeof(buf), "%s%s", prefix, FNAME_LEAPSECFILE);
        if (verbose) printf("Processing leap seconds file %s\n", buf);
        if (!(fp = fopen(buf, "r"))) {
            fprintf(stderr, "Could not open leap seconds file %s\n", buf);
        }
        else {
            struct zoneinfo *leap = xzmalloc(sizeof(struct zoneinfo));
            leap->type = ZI_INFO;

            while(fgets(buf, sizeof(buf), fp)) {
                if (buf[0] == '#') {
                    /* comment line */

                    if (buf[1] == '$') {
                        /* last updated */
                        unsigned long last;

                        sscanf(buf+2, "\t%lu", &last);
                        leap->dtstamp = last - NIST_EPOCH_OFFSET;
                    }
                    else if (buf[1] == 'h') {
                        /* hash */
                        char *p, *hash = buf+3 /* skip "#h\t" */;

                        /* trim trailing whitespace */
                        for (p = hash + strlen(hash); isspace(*--p); *p = '\0');
                        appendstrlist(&leap->data, hash);
                    }
                }
            }
            fclose(fp);

            hash_insert(LEAP_TZID, leap, &tzentries);
            info->dtstamp = leap->dtstamp;
        }

        /* Add ZONE/LINK records */
        do_zonedir(prefix, &tzentries, info);

        zoneinfo_open(NULL);

        /* Store records */
        hash_enumerate(&tzentries, &store_zoneinfo, &tid);

        zoneinfo_close(tid);

        free_hash_table(&tzentries, &free_zoneinfo);
        break;
    }

    case WINZONES: {
        xmlParserCtxtPtr ctxt;
        xmlDocPtr doc;
        xmlNodePtr node;
        struct buf tzidbuf = BUF_INITIALIZER;
        struct buf aliasbuf = BUF_INITIALIZER;

        if (verbose) printf("Processing Windows Zone file %s\n", winfile);

        /* Parse the XML file */
        ctxt = xmlNewParserCtxt();
        if (!ctxt) {
            fprintf(stderr, "Failed to create XML parser context\n");
            break;
        }

        doc = xmlCtxtReadFile(ctxt, winfile, NULL, 0);
        xmlFreeParserCtxt(ctxt);
        if (!doc) {
            fprintf(stderr, "Failed to parse XML document\n");
            break;
        }

        node = xmlDocGetRootElement(doc);
        if (!node || xmlStrcmp(node->name, BAD_CAST "supplementalData")) {
            fprintf(stderr, "Incorrect root node\n");
            goto done;
        }

        for (node = xmlFirstElementChild(node);
             node && xmlStrcmp(node->name, BAD_CAST "windowsZones");
             node = xmlNextElementSibling(node));
        if (!node) {
            fprintf(stderr, "Missing windowsZones node\n");
            goto done;
        }

        node = xmlFirstElementChild(node);
        if (!node || xmlStrcmp(node->name, BAD_CAST "mapTimezones")) {
            fprintf(stderr, "Missing mapTimezones node\n");
            goto done;
        }

        if (chdir(prefix)) {
            fprintf(stderr, "chdir(%s) failed\n", prefix);
            goto done;
        }

        for (node = xmlFirstElementChild(node);
             node;
             node = xmlNextElementSibling(node)) {
            if (!xmlStrcmp(node->name, BAD_CAST "mapZone") &&
                !xmlStrcmp(xmlGetProp(node, BAD_CAST "territory"),
                           BAD_CAST "001")) {
                const char *tzid, *alias;

                buf_setcstr(&tzidbuf,
                            (const char *) xmlGetProp(node, BAD_CAST "type"));
                buf_appendcstr(&tzidbuf, ".ics");
                tzid = buf_cstring(&tzidbuf);
                buf_setcstr(&aliasbuf,
                            (const char *) xmlGetProp(node, BAD_CAST "other"));
                buf_appendcstr(&aliasbuf, ".ics");
                alias = buf_cstring(&aliasbuf);

                if (verbose) printf("\tLINK: %s -> %s\n", alias, tzid);

                if (symlink(tzid, alias)) {
                    if (errno == EEXIST) {
                        struct stat sbuf;

                        if (stat(alias, &sbuf)) {
                            fprintf(stderr, "stat(%s) failed: %s\n",
                                    alias, strerror(errno));
                            errno = EEXIST;
                        }
                        else if (sbuf.st_mode & S_IFLNK) {
                            char link[MAX_MAILBOX_PATH+1];
                            int n = readlink(alias, link, MAX_MAILBOX_PATH);

                            if (n == -1) {
                                fprintf(stderr, "readlink(%s) failed: %s\n",
                                        alias, strerror(errno));
                                errno = EEXIST;
                            }
                            else if (n == (int) strlen(tzid) &&
                                     !strncmp(tzid, link, n)) {
                                errno = 0;
                            }
                        }
                    }

                    if (errno) {
                        fprintf(stderr, "symlink(%s, %s) failed: %s\n",
                                tzid, alias, strerror(errno));
                    }
                }
            }
        }

  done:
        buf_free(&aliasbuf);
        buf_free(&tzidbuf);
        xmlFreeDoc(doc);
        break;
    }

    case NONE:
        r = 2;
        usage();
        break;
    }

    cyrus_done();

    return r;
}