static void
conf_zonefiles_parse_thread(void *v)
{
    struct XParseThread *p = (struct XParseThread *)v;
    struct Catalog *db = p->db_load;
    struct Configuration *cfg = p->cfg;
    struct ZoneFileParser *parser;
    static const struct DomainPointer root = {(const unsigned char*)"\0",1};
    size_t directory_index;
    size_t file_index;
    size_t current_index;

    fflush(stderr);
    fflush(stdout);


    /*
     * Start the parsing
     */
    parser = zonefile_begin(
                root, 
                60, 128,
                cfg->options.directory,
                zonefile_load, 
                db,
                cfg->insertion_threads
                );

    /*
     * Find the starting point. This converts the single
     * integer number into a [directory, file] index pair.
     */
    current_index = 0;
    for (directory_index = 0; directory_index < cfg->zonedirs_length; directory_index++) {
        struct Cfg_ZoneDir *zonedir = cfg->zonedirs[directory_index];
        current_index += zonedir->file_count;
        if (current_index >= p->start_index)
            break;
    }
    file_index = current_index - p->start_index;


    
    /*
     * 'for all zonefiles in this directory...'
     */
    if (directory_index < cfg->zonedirs_length)
    while (current_index < p->end_index) {
        const char *filename;
        FILE *fp;
        int err;
        uint64_t filesize;
        struct Cfg_ZoneDir *zonedir;
        
        /* If we've gone past the end of this directory,
         * then start parsing the next directory */
        zonedir = cfg->zonedirs[directory_index];
        if (file_index >= zonedir->file_count) {
            file_index = 0;
            directory_index++;
            if (directory_index >= cfg->zonedirs_length)
                break;
            zonedir = cfg->zonedirs[directory_index];
        }

        filename = zonedir->files[file_index].filename;
        filesize = zonedir->files[file_index].size;
        current_index++;
        file_index++;

        /*
         * Open the file
         */
        fflush(stdout);
        fflush(stderr);
        err = fopen_s(&fp, filename, "rb");
        if (err || fp == NULL) {
            perror(filename);
            p->status = Failure;
            return;
        }
        p->total_bytes += filesize;

        /*
         * Set parameters
         */
        zonefile_begin_again(
            parser,
            root,   /* . domain origin */
            60,     /* one minute ttl */
            filesize, 
            filename);

        /*
         * Continue parsing the file until end, reporting progress as we
         * go along
         */
        for (;;) {
            unsigned char buf[65536];
            size_t bytes_read;

            bytes_read = fread((char*)buf, 1, sizeof(buf), fp);
            if (bytes_read == 0)
                break;

            zonefile_parse(
                parser,
                buf,
                bytes_read
                );

        }
        fclose(fp);
    }

    /* We are done parsing the directories. Now let's parse
     * the individual zonefiles */
    while (current_index < p->end_index) {
        const char *filename;
        FILE *fp;
        int err;
        uint64_t filesize;
        struct Cfg_Zone *zone;
        
        if (file_index >= cfg->zones_length)
            break;
        zone = cfg->zones[file_index];

        filename = zone->file;
        filesize = zone->file_size;
        current_index++;
        file_index++;

        /*
         * Open the file
         */
        fflush(stdout);
        fflush(stderr);
        err = fopen_s(&fp, filename, "rb");
        if (err || fp == NULL) {
            perror(filename);
            p->status = Failure;
            return;
        }
        p->total_bytes += filesize;

        /*
         * Set parameters
         */
        zonefile_begin_again(
            parser,
            root,   /* . domain origin */
            60,     /* one minute ttl */
            filesize, 
            filename);

        /*
         * Continue parsing the file until end, reporting progress as we
         * go along
         */
        for (;;) {
            unsigned char buf[65536];
            size_t bytes_read;

            bytes_read = fread((char*)buf, 1, sizeof(buf), fp);
            if (bytes_read == 0)
                break;

            zonefile_parse(
                parser,
                buf,
                bytes_read
                );

        }
        fclose(fp);
    }

    if (zonefile_end(parser) == Success) {
        p->status = Success;
    } else {
        fprintf(stderr, "%s: failure\n", "");
        p->status = Failure;
    }
}