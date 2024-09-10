int
main(int argc, char *argv[])
{
    const char     *allowed_args = "hl:x:p:o:sv:i:r:V";
    char           *node = NULL;
    int             retval;
    int             async = 1;
    val_log_t      *logp;
    char           *label_str = NULL;
    struct val_daneparams daneparams;
    struct val_danestatus *danestatus = NULL;
    struct val_ssl_data *ssl_dane_data = NULL;
    int port = 443;
    int proto = DANE_PARAM_PROTO_TCP;
    val_context_t *context = NULL;
    val_status_t val_status;
    struct addrinfo *val_ainfo = NULL;
    struct addrinfo hints;
    int ret = 0;
    int dane_retval = VAL_DANE_INTERNAL_ERROR;
    int ai_retval = 0;
    int err;

    /* Parse the command line */
    while (1) {
        int             c;
#ifdef HAVE_GETOPT_LONG
        int             opt_index = 0;
#ifdef HAVE_GETOPT_LONG_ONLY
        c = getopt_long_only(argc, argv, allowed_args,
                             prog_options, &opt_index);
#else
        c = getopt_long(argc, argv, allowed_args, prog_options, &opt_index);
#endif
#else                           /* only have getopt */
        c = getopt(argc, argv, allowed_args);
#endif

        if (c == -1) {
            break;
        }

        switch (c) {
        case 'h':
            usage(argv[0]);
            return -1;
        case 'l':
            label_str = optarg;
            break;
        case 'o':
            logp = val_log_add_optarg(optarg, 1);
            if (NULL == logp) { /* err msg already logged */
                usage(argv[0]);
                return -1;
            }
            break;

        case 's':
            async = 0;
            break;

        case 'p':
            port = atoi(optarg);
            break;

        case 'x':
            if(strncmp(optarg, DANE_PARAM_PROTO_STR_TCP,
                       strlen(DANE_PARAM_PROTO_STR_TCP)))
                proto = DANE_PARAM_PROTO_TCP;
            else if (strncmp(optarg, DANE_PARAM_PROTO_STR_UDP,
                        strlen(DANE_PARAM_PROTO_STR_UDP)))
                proto = DANE_PARAM_PROTO_UDP;
            else if (strncmp(optarg, DANE_PARAM_PROTO_STR_SCTP, 
                        strlen(DANE_PARAM_PROTO_STR_SCTP)))
                proto = DANE_PARAM_PROTO_SCTP;
            else {
                usage(argv[0]);
                return -1;
            }
            break;

        case 'v':
            dnsval_conf_set(optarg);
            break;

        case 'i':
            root_hints_set(optarg);
            break;

        case 'r':
            resolv_conf_set(optarg);
            break;

        case 'V':
            version();
            return 0;
        default:
            fprintf(stderr, "Invalid option %s\n", argv[optind - 1]);
            usage(argv[0]);
            return -1;
        }
    }

    if (optind < argc) {
        node = argv[optind++];
    } else {
        fprintf(stderr, "Error: node name not specified\n");
        usage(argv[0]);
        return -1;
    }

    if (VAL_NO_ERROR != (retval = 
                val_create_context(label_str, &context))) {
        fprintf(stderr, "Cannot create context %s(%d)\n", 
                p_val_error(retval), retval);
        return -1;
    }

    daneparams.port = port;
    daneparams.proto = proto;
    memset(&hints, 0, sizeof(struct addrinfo));
#ifdef AI_ADDRCONFIG
    hints.ai_flags = AI_ADDRCONFIG;
#endif

    if (!async) {
        /* synchronous lookup and validation */
        ai_retval = val_getaddrinfo(context, node, NULL, &hints,
                                    &val_ainfo, &val_status);
        dane_retval = val_getdaneinfo(context, node, &daneparams, &danestatus); 
    }
    else {
#ifdef VAL_NO_ASYNC
        fprintf(stderr, "async support not available\n");
#else
        struct dane_cb cb_data_dane = { &dane_retval, &danestatus, 0 };
        val_dane_callback my_dane_cb = &_danecallback;
        struct timeval tv;
        val_async_status *das = NULL; /* helps us cancel the lookup if we need to */

        struct getaddr_s cb_data_ai = { &ai_retval, &val_ainfo, &val_status, 0 };
        val_gai_callback my_ai_cb = &_aicallback;
        val_gai_status *status = NULL;

        /*
         * submit requests
         */
        if (VAL_NO_ERROR != val_dane_submit(context, node, &daneparams,
                                 my_dane_cb, &cb_data_dane, &das) ||
            VAL_NO_ERROR != val_getaddrinfo_submit(context, node, NULL,
                                &hints, my_ai_cb, &cb_data_ai, 0, &status)) {
            dane_retval = VAL_DANE_INTERNAL_ERROR; 
            goto done;
        }

        /*
         * wait for it to complete
         */
#if 0
        while(0 == cb_data_dane.done ||
              0 == cb_data_ai.done) {
            tv.tv_sec = 10;
            tv.tv_usec = 0;
            val_async_check_wait(context, NULL, NULL, &tv, 0);
        }
#endif

#if 1
        while(0 == cb_data_dane.done || 
              0 == cb_data_ai.done) {
            fd_set  activefds;
            int nfds = 0;
            int ready;

            FD_ZERO(&activefds);

            tv.tv_sec = 10; /* 10 sec */
            tv.tv_usec = 0;

            val_async_select_info(context, &activefds, &nfds, &tv);
            ready = select(nfds+1, &activefds, NULL, NULL, &tv);
            if (ready < 0) {
                continue;
            } 
            val_async_check(context, &activefds, &nfds, 0);
        }
#endif

#endif
    }

done:
    if (ai_retval != 0) {
        fprintf(stderr, "Error in val_getaddrinfo(): %d\n", ai_retval);
        return -1;
    }

    if (!val_istrusted(val_status)) {
        fprintf(stderr, 
                "Address lookup information could not be validated: %s\n", 
                p_val_status(val_status));

    } else if(dane_retval == VAL_DANE_NOERROR && 
              proto == DANE_PARAM_PROTO_TCP) {

        /* Set up the SSL connection */
        SSL_library_init();
        SSL_load_error_strings();

        const SSL_METHOD *meth = SSLv23_client_method();
        SSL_CTX *sslctx = SSL_CTX_new(meth);

        struct addrinfo *ai = NULL;
        int presetup_okay;

        /*
         * OpenSSL only does protocol negotiation on SSLv23_client_method;
         * we need to set SNI to get the correct certificate from many
         * modern browsers, so we disable both SSLv2 and SSLv3 if we can.
         * That leaves (currently) TLSv1.0 TLSv1.1 TLSv1.2
         */
        long ssl_options = 0
#ifdef SSL_OP_NO_SSLv2
            | SSL_OP_NO_SSLv2
#endif
#ifdef SSL_OP_NO_SSLv3
            | SSL_OP_NO_SSLv3
#endif
            ;

        if (!SSL_CTX_set_options(sslctx, ssl_options)) {
            fprintf(stderr, "Failed to set SSL context options (%ld): %s\n",
              ssl_options, ssl_error());
            presetup_okay = 0;
        } else {
            presetup_okay = 1;
        }

        if (VAL_NO_ERROR != (err = val_enable_dane_ssl(context, sslctx, node,
                                        danestatus, &ssl_dane_data))) {
            fprintf(stderr,
                    "Could not set danestatus for SSL connection %s\n",
                    p_val_error(err));
        }

        ai = val_ainfo;
        while(presetup_okay && ai && (ai->ai_protocol == IPPROTO_TCP) && 
             (ai->ai_family == AF_INET || ai->ai_family == AF_INET6)) {

            int sock;
            char buf[INET6_ADDRSTRLEN];
            size_t buflen = sizeof(buf);
            const char *addr = NULL;

            if (ai->ai_family == AF_INET) {
                sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
                ((struct sockaddr_in *)(ai)->ai_addr)->sin_port = htons(port);
            } else {
                sock = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
                ((struct sockaddr_in6 *)(ai)->ai_addr)->sin6_port = htons(port);
            }

            INET_NTOP(ai->ai_family, ai->ai_addr, sizeof(ai->ai_addr), buf, buflen, addr);
            fprintf(stderr, "Connecting to %s\n", addr);

            if (0 == connect(sock, ai->ai_addr, ai->ai_addrlen)) {
                SSL *ssl = SSL_new(sslctx);
                BIO * sbio = BIO_new_socket(sock,BIO_NOCLOSE);


#if OPENSSL_VERSION_NUMBER >= 0x0090806fL && !defined(OPENSSL_NO_TLSEXT)
                SSL_set_tlsext_host_name(ssl, node);
#endif

                SSL_set_bio(ssl,sbio,sbio);

                if ((err = SSL_connect(ssl)) != 1) {
                    fprintf(stderr, "SSL Connect to %s failed: %d\n", node, err);
                } 
                SSL_shutdown(ssl);
                SSL_free(ssl);
            } else {
                fprintf(stderr, "TCP Connect to %s failed\n", node);
            }

            ai = (struct addrinfo *) (ai->ai_next);
        }

    } else if (dane_retval == VAL_DANE_IGNORE_TLSA) {
        fprintf(stderr, "TLSA is either provably non-existant or provably insecure. It will be ignored.\n");
    } else {
        fprintf(stderr, "TLSA record could not be validated.\n");
        ret = 1;
    }

    if (danestatus != NULL)
        val_free_dane(danestatus);

    if (val_ainfo != NULL)
        val_freeaddrinfo(val_ainfo);    

    val_free_dane_ssl(ssl_dane_data);/* MUST happen before we free the context*/
    val_free_context(context);
    val_free_validator_state();

    return ret;
}