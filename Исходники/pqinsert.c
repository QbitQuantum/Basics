int main(
        int ac,
        char *av[]
)
{
        const char* const       pqfname = getQueuePath();
        const char* const progname = ubasename(av[0]);
        int useProductID = FALSE;
        int signatureFromId = FALSE;
        char *productID = NULL;
        int multipleFiles = FALSE;
        char identifier[KEYSIZE];
        int status;
        int seq_start = 0;
        enum ExitCode {
            exit_success = 0,   /* all files inserted successfully */
            exit_system = 1,    /* operating-system failure */
            exit_pq_open = 2,   /* couldn't open product-queue */
            exit_infile = 3,    /* couldn't process input file */
            exit_dup = 4,       /* input-file already in product-queue */
            exit_md5 = 6        /* couldn't initialize MD5 processing */
        } exitCode = exit_success;

#ifndef HAVE_MMAP
        pqeIndex = PQE_NONE;
#endif

        {
            extern int optind;
            extern int opterr;
            extern char *optarg;
            int ch;

            (void) openulog(progname, LOG_NOTIME, LOG_LDM, "-");
            (void) setulogmask(LOG_UPTO(LOG_NOTICE));

            opterr = 0; /* Suppress getopt(3) error messages */

            while ((ch = getopt(ac, av, ":ivxl:q:f:s:p:")) != EOF)
                    switch (ch) {
                    case 'i':
                            signatureFromId = 1;
                            break;
                    case 'v':
                            (void) setulogmask(getulogmask() | LOG_MASK(LOG_INFO));
                            break;
                    case 'x':
                            (void) setulogmask(getulogmask() | LOG_MASK(LOG_DEBUG));
                            break;
                    case 'l':
                            openulog(progname, ulog_get_options(), LOG_LDM, optarg);
                            break;
                    case 'q':
                            setQueuePath(optarg);
                            break;
                    case 's':
                            seq_start = atoi(optarg);
                            break;
                    case 'f':
                            feedtype = atofeedtypet(optarg);
                            if(feedtype == NONE)
                            {
                                fprintf(stderr, "Unknown feedtype \"%s\"\n", optarg);
                                    usage(progname);
                            }
                            break;
                    case 'p':
                            useProductID = TRUE;
                            productID = optarg;
                            break;
                    case ':': {
                        LOG_ADD1("Option \"-%c\" requires an operand", optopt);
                        usage(progname);
                    }
                    /* no break */
                    default:
                        LOG_ADD1("Unknown option: \"%c\"", optopt);
                        usage(progname);
                        /* no break */
                    }

            ac -= optind; av += optind ;

            if(ac < 1) usage(progname);
            }

        /*
         * register exit handler
         */
        if(atexit(cleanup) != 0)
        {
                serror("atexit");
                exit(exit_system);
        }

        /*
         * set up signal handlers
         */
        set_sigactions();

        /*
         * who am i, anyway
         */
        (void) strncpy(myname, ghostname(), sizeof(myname));
        myname[sizeof(myname)-1] = 0;

        /*
         * open the product queue
         */
        if(status = pq_open(pqfname, PQ_DEFAULT, &pq))
        {
                if (PQ_CORRUPT == status) {
                    uerror("The product-queue \"%s\" is inconsistent\n",
                            pqfname);
                }
                else {
                    uerror("pq_open: \"%s\" failed: %s",
                            pqfname, status > 0 ? strerror(status) :
                                            "Internal error");
                }
                exit(exit_pq_open);
        }


        {
        char *filename;
        int fd;
        struct stat statb;
        product prod;
        MD5_CTX *md5ctxp = NULL;

        /*
         * Allocate an MD5 context
         */
        md5ctxp = new_MD5_CTX();
        if(md5ctxp == NULL)
        {
                serror("new_md5_CTX failed");
                exit(exit_md5);
        }


        /* These members are constant over the loop. */
        prod.info.origin = myname;
        prod.info.feedtype = feedtype;

        if (ac > 1) {
          multipleFiles = TRUE;
        }

        for(prod.info.seqno = seq_start ; ac > 0 ;
                         av++, ac--, prod.info.seqno++)
        {
                filename = *av;

                fd = open(filename, O_RDONLY, 0);
                if(fd == -1)
                {
                        serror("open: %s", filename);
                        exitCode = exit_infile;
                        continue;
                }

                if( fstat(fd, &statb) == -1) 
                {
                        serror("fstat: %s", filename);
                        (void) close(fd);
                        exitCode = exit_infile;
                        continue;
                }

                /* Determine what to use for product identifier */
                if (useProductID) 
                  {
                    if (multipleFiles) 
                      {
                        sprintf(identifier,"%s.%d", productID, prod.info.seqno);
                        prod.info.ident = identifier;
                      }
                    else
                      prod.info.ident = productID;
                   }
                else
                    prod.info.ident = filename;
                
                prod.info.sz = statb.st_size;
                prod.data = NULL;

                /* These members, and seqno, vary over the loop. */
                status = set_timestamp(&prod.info.arrival);
                if(status != ENOERR) {
                        serror("set_timestamp: %s, filename");
                        exitCode = exit_infile;
                        continue;
                }

#ifdef HAVE_MMAP
                prod.data = mmap(0, prod.info.sz,
                        PROT_READ, MAP_PRIVATE, fd, 0);
                if(prod.data == NULL)
                {
                        serror("mmap: %s", filename);
                        (void) close(fd);
                        exitCode = exit_infile;
                        continue;
                }

                status = 
                    signatureFromId
                        ? mm_md5(md5ctxp, prod.info.ident,
                            strlen(prod.info.ident), prod.info.signature)
                        : mm_md5(md5ctxp, prod.data, prod.info.sz,
                            prod.info.signature);

                (void)exitIfDone(1);

                if (status != 0) {
                    serror("mm_md5: %s", filename);
                    (void) munmap(prod.data, prod.info.sz);
                    (void) close(fd);
                    exitCode = exit_infile;
                    continue;
                }

                /* These members, and seqno, vary over the loop. */
                status = set_timestamp(&prod.info.arrival);
                if(status != ENOERR) {
                        serror("set_timestamp: %s, filename");
                        exitCode = exit_infile;
                        continue;
                }

                /*
                 * Do the deed
                 */
                status = pq_insert(pq, &prod);

                switch (status) {
                case ENOERR:
                    /* no error */
                    if(ulogIsVerbose())
                        uinfo("%s", s_prod_info(NULL, 0, &prod.info,
                            ulogIsDebug())) ;
                    break;
                case PQUEUE_DUP:
                    uerror("Product already in queue: %s",
                        s_prod_info(NULL, 0, &prod.info, 1));
                    exitCode = exit_dup;
                    break;
                case PQUEUE_BIG:
                    uerror("Product too big for queue: %s",
                        s_prod_info(NULL, 0, &prod.info, 1));
                    exitCode = exit_infile;
                    break;
                case ENOMEM:
                    uerror("queue full?");
                    exitCode = exit_system;
                    break;  
                case EINTR:
#if defined(EDEADLOCK) && EDEADLOCK != EDEADLK
                case EDEADLOCK:
                    /*FALLTHROUGH*/
#endif
                case EDEADLK:
                    /* TODO: retry ? */
                    /*FALLTHROUGH*/
                default:
                    uerror("pq_insert: %s", status > 0
                        ? strerror(status) : "Internal error");
                    break;
                }

                (void) munmap(prod.data, prod.info.sz);
#else /*HAVE_MMAP*/
                status = 
                    signatureFromId
                        ? mm_md5(md5ctxp, prod.info.ident,
                            strlen(prod.info.ident), prod.info.signature)
                        : fd_md5(md5ctxp, fd, statb.st_size,
                            prod.info.signature);

                (void)exitIfDone(1);

                if (status != 0) {
                        serror("fd_md5: %s", filename);
                        (void) close(fd);
                        exitCode = exit_infile;
                        continue;
                }

                if(lseek(fd, 0, SEEK_SET) == (off_t)-1)
                {
                        serror("rewind: %s", filename);
                        (void) close(fd);
                        exitCode = exit_infile;
                        continue;
                }

                index = PQE_NONE;
                status = pqe_new(pq, &prod.info, &prod.data, &index);

                if(status != ENOERR) {
                    serror("pqe_new: %s", filename);
                    exitCode = exit_infile;
                }
                else {
                    ssize_t     nread = read(fd, prod.data, prod.info.sz);

                    (void)exitIfDone(1);

                    if (nread != prod.info.sz) {
                        serror("read %s %u", filename, prod.info.sz);
                        status = EIO;
                    }
                    else {
                        status = pqe_insert(pq, index);
                        index = PQE_NONE;

                        switch (status) {
                        case ENOERR:
                            /* no error */
                            if(ulogIsVerbose())
                                uinfo("%s", s_prod_info(NULL, 0, &prod.info,
                                    ulogIsDebug())) ;
                            break;
                        case PQUEUE_DUP:
                            uerror("Product already in queue: %s",
                                s_prod_info(NULL, 0, &prod.info, 1));
                            exitCode = exit_dup;
                            break;
                        case ENOMEM:
                            uerror("queue full?");
                            break;  
                        case EINTR:
#if defined(EDEADLOCK) && EDEADLOCK != EDEADLK
                        case EDEADLOCK:
                            /*FALLTHROUGH*/
#endif
                        case EDEADLK:
                            /* TODO: retry ? */
                            /*FALLTHROUGH*/
                        default:
                            uerror("pq_insert: %s", status > 0
                                ? strerror(status) : "Internal error");
                        }
                    }                   /* data read into "index" region */

                    if (status != ENOERR) {
                        (void)pqe_discard(pq, index);
                        index = PQE_NONE;
                    }
                }                       /* "index" region allocated */

#endif /*HAVE_MMAP*/
                (void) close(fd);
        }                               /* input-file loop */

        free_MD5_CTX(md5ctxp);  
        }                               /* code block */

        exit(exitCode);
}