int main(int argc, char **argv)
{
    int c, compress, pstdout, is_forced, index = 0, reindex = 0;
    BGZF *fp;
    void *buffer;
    long start, end, size;
    char *index_fname = NULL;

    static struct option loptions[] =
    {
        {"help",0,0,'h'},
        {"offset",1,0,'b'},
        {"stdout",0,0,'c'},
        {"decompress",0,0,'d'},
        {"force",0,0,'f'},
        {"index",0,0,'i'},
        {"index-name",1,0,'I'},
        {"reindex",0,0,'r'},
        {"size",1,0,'s'},
        {0,0,0,0}
    };

    compress = 1; pstdout = 0; start = 0; size = -1; end = -1; is_forced = 0;
    while((c  = getopt_long(argc, argv, "cdh?fb:s:iI:r",loptions,NULL)) >= 0){
        switch(c){
        case 'd': compress = 0; break;
        case 'c': pstdout = 1; break;
        case 'b': start = atol(optarg); compress = 0; pstdout = 1; break;
        case 's': size = atol(optarg); pstdout = 1; break;
        case 'f': is_forced = 1; break;
        case 'i': index = 1; break;
        case 'I': index_fname = optarg; break;
        case 'r': reindex = 1; compress = 0; break;
        case 'h':
        case '?': return bgzip_main_usage();
        }
    }
    if (size >= 0) end = start + size;
    if (end >= 0 && end < start) {
        fprintf(stderr, "[bgzip] Illegal region: [%ld, %ld]\n", start, end);
        return 1;
    }
    if (compress == 1) {
        struct stat sbuf;
        int f_src = fileno(stdin);
        int f_dst = fileno(stdout);

        if ( argc>optind )
        {
            if ( stat(argv[optind],&sbuf)<0 )
            {
                fprintf(stderr, "[bgzip] %s: %s\n", strerror(errno), argv[optind]);
                return 1;
            }

            if ((f_src = open(argv[optind], O_RDONLY)) < 0) {
                fprintf(stderr, "[bgzip] %s: %s\n", strerror(errno), argv[optind]);
                return 1;
            }

            if (pstdout)
                f_dst = fileno(stdout);
            else
            {
                char *name = malloc(strlen(argv[optind]) + 5);
                strcpy(name, argv[optind]);
                strcat(name, ".gz");
                f_dst = write_open(name, is_forced);
                free(name);
                if (f_dst < 0) return 1;
            }
        }
        else if (!pstdout && isatty(fileno((FILE *)stdout)) )
            return bgzip_main_usage();
        else if ( index && !index_fname )
        {
            fprintf(stderr, "[bgzip] Index file name expected when writing to stdout\n");
            return 1;
        }

        fp = bgzf_fdopen(f_dst, "w");
        if ( index ) bgzf_index_build_init(fp);
        buffer = malloc(WINDOW_SIZE);
        while ((c = read(f_src, buffer, WINDOW_SIZE)) > 0)
            if (bgzf_write(fp, buffer, c) < 0) error("Could not write %d bytes: Error %d\n", c, fp->errcode);
        // f_dst will be closed here
        if ( index )
        {
            if ( index_fname ) bgzf_index_dump(fp, index_fname, NULL);
            else bgzf_index_dump(fp, argv[optind], ".gz.gzi");
        }
        if (bgzf_close(fp) < 0) error("Close failed: Error %d", fp->errcode);
        if (argc > optind && !pstdout) unlink(argv[optind]);
        free(buffer);
        close(f_src);
        return 0;
    }
    else if ( reindex )
    {
        if ( argc>optind )
        {
            fp = bgzf_open(argv[optind], "r");
            if ( !fp ) error("[bgzip] Could not open file: %s\n", argv[optind]);
        }
        else
        {
            if ( !index_fname ) error("[bgzip] Index file name expected when reading from stdin\n");
            fp = bgzf_fdopen(fileno(stdin), "r");
            if ( !fp ) error("[bgzip] Could not read from stdin: %s\n", strerror(errno));
        }

        buffer = malloc(BGZF_BLOCK_SIZE);
        bgzf_index_build_init(fp);
        int ret;
        while ( (ret=bgzf_read(fp, buffer, BGZF_BLOCK_SIZE))>0 ) ;
        free(buffer);
        if ( ret<0 ) error("Is the file gzipped or bgzipped? The latter is required for indexing.\n");

        if ( index_fname )
            bgzf_index_dump(fp, index_fname, NULL);
        else
            bgzf_index_dump(fp, argv[optind], ".gzi");

        if ( bgzf_close(fp)<0 ) error("Close failed: Error %d\n",fp->errcode);
        return 0;
    }
    else
    {
        struct stat sbuf;
        int f_dst;

        if ( argc>optind )
        {
            if ( stat(argv[optind],&sbuf)<0 )
            {
                fprintf(stderr, "[bgzip] %s: %s\n", strerror(errno), argv[optind]);
                return 1;
            }
            char *name;
            int len = strlen(argv[optind]);
            if ( strcmp(argv[optind]+len-3,".gz") )
            {
                fprintf(stderr, "[bgzip] %s: unknown suffix -- ignored\n", argv[optind]);
                return 1;
            }
            fp = bgzf_open(argv[optind], "r");
            if (fp == NULL) {
                fprintf(stderr, "[bgzip] Could not open file: %s\n", argv[optind]);
                return 1;
            }

            if (pstdout) {
                f_dst = fileno(stdout);
            }
            else {
                name = strdup(argv[optind]);
                name[strlen(name) - 3] = '\0';
                f_dst = write_open(name, is_forced);
                free(name);
            }
        }
        else if (!pstdout && isatty(fileno((FILE *)stdin)) )
            return bgzip_main_usage();
        else
        {
            f_dst = fileno(stdout);
            fp = bgzf_fdopen(fileno(stdin), "r");
            if (fp == NULL) {
                fprintf(stderr, "[bgzip] Could not read from stdin: %s\n", strerror(errno));
                return 1;
            }
        }
        buffer = malloc(WINDOW_SIZE);
        if ( start>0 )
        {
            if ( bgzf_index_load(fp, argv[optind], ".gzi") < 0 ) error("Could not load index: %s.gzi\n", argv[optind]);
            if ( bgzf_useek(fp, start, SEEK_SET) < 0 ) error("Could not seek to %d-th (uncompressd) byte\n", start);
        }
        while (1) {
            if (end < 0) c = bgzf_read(fp, buffer, WINDOW_SIZE);
            else c = bgzf_read(fp, buffer, (end - start > WINDOW_SIZE)? WINDOW_SIZE:(end - start));
            if (c == 0) break;
            if (c < 0) error("Could not read %d bytes: Error %d\n", (end - start > WINDOW_SIZE)? WINDOW_SIZE:(end - start), fp->errcode);
            start += c;
            if ( write(f_dst, buffer, c) != c ) error("Could not write %d bytes\n", c);
            if (end >= 0 && start >= end) break;
        }
        free(buffer);
        if (bgzf_close(fp) < 0) error("Close failed: Error %d\n",fp->errcode);
        if (!pstdout) unlink(argv[optind]);
        return 0;
    }
    return 0;
}