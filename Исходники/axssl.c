/**
 * Implement the SSL client logic.
 */
static void do_client(int argc, char *argv[])
{
#ifdef CONFIG_SSL_ENABLE_CLIENT
    int res, i = 2;
    uint16_t port = 4433;
    uint32_t options = SSL_SERVER_VERIFY_LATER | SSL_DISPLAY_CERTS;
    int client_fd;
    char *private_key_file = NULL;
    struct sockaddr_in client_addr;
    struct hostent *hostent;
    int reconnect = 0;
    uint32_t sin_addr;
    SSL_CTX *ssl_ctx;
    SSL *ssl = NULL;
    int quiet = 0;
    int cert_index = 0, ca_cert_index = 0;
    int cert_size, ca_cert_size;
    char **ca_cert, **cert;
    uint8_t session_id[SSL_SESSION_ID_SIZE];
    fd_set read_set;
    const char *password = NULL;

    FD_ZERO(&read_set);
    sin_addr = inet_addr("127.0.0.1");
    cert_size = ssl_get_config(SSL_MAX_CERT_CFG_OFFSET);
    ca_cert_size = ssl_get_config(SSL_MAX_CA_CERT_CFG_OFFSET);
    ca_cert = (char **)calloc(1, sizeof(char *)*ca_cert_size);
    cert = (char **)calloc(1, sizeof(char *)*cert_size);

    while (i < argc) {
        if (strcmp(argv[i], "-connect") == 0)        {
            char *host, *ptr;

            if (i >= argc - 1) {
                print_client_options(argv[i]);
            }

            host = argv[++i];
            if ((ptr = strchr(host, ':')) == NULL) {
                print_client_options(argv[i]);
            }

            *ptr++ = 0;
            port = atoi(ptr);
            hostent = gethostbyname(host);

            if (hostent == NULL) {
                print_client_options(argv[i]);
            }

            sin_addr = *((uint32_t **)hostent->h_addr_list)[0];
        } else if (strcmp(argv[i], "-cert") == 0) {
            if (i >= argc - 1 || cert_index >= cert_size) {
                print_client_options(argv[i]);
            }

            cert[cert_index++] = argv[++i];
        } else if (strcmp(argv[i], "-key") == 0) {
            if (i >= argc - 1) {
                print_client_options(argv[i]);
            }

            private_key_file = argv[++i];
            options |= SSL_NO_DEFAULT_KEY;
        } else if (strcmp(argv[i], "-CAfile") == 0) {
            if (i >= argc - 1 || ca_cert_index >= ca_cert_size) {
                print_client_options(argv[i]);
            }

            ca_cert[ca_cert_index++] = argv[++i];
        } else if (strcmp(argv[i], "-verify") == 0) {
            options &= ~SSL_SERVER_VERIFY_LATER;
        } else if (strcmp(argv[i], "-reconnect") == 0) {
            reconnect = 4;
        } else if (strcmp(argv[i], "-quiet") == 0) {
            quiet = 1;
            options &= ~SSL_DISPLAY_CERTS;
        } else if (strcmp(argv[i], "-pass") == 0) {
            if (i >= argc - 1) {
                print_client_options(argv[i]);
            }

            password = argv[++i];
        }
#ifdef CONFIG_SSL_FULL_MODE
        else if (strcmp(argv[i], "-debug") == 0)  {
            options |= SSL_DISPLAY_BYTES;
        } else if (strcmp(argv[i], "-state") == 0)  {
            options |= SSL_DISPLAY_STATES;
        } else if (strcmp(argv[i], "-show-rsa") == 0) {
            options |= SSL_DISPLAY_RSA;
        }
#endif
        else  {
            /* don't know what this is */
            print_client_options(argv[i]);
        }

        i++;
    }

    if ((ssl_ctx = ssl_ctx_new(options, SSL_DEFAULT_CLNT_SESS)) == NULL) {
        fprintf(stderr, "Error: Client context is invalid\n");
        exit(1);
    }

    if (private_key_file)  {
        int obj_type = SSL_OBJ_RSA_KEY;

        /* auto-detect the key type from the file extension */
        if (strstr(private_key_file, ".p8")) {
            obj_type = SSL_OBJ_PKCS8;
        } else if (strstr(private_key_file, ".p12")) {
            obj_type = SSL_OBJ_PKCS12;
        }

        if (ssl_obj_load(ssl_ctx, obj_type, private_key_file, password))  {
            fprintf(stderr, "Error: Private key '%s' is undefined.\n",
                    private_key_file);
            exit(1);
        }
    }

    for (i = 0; i < cert_index; i++) {
        if (ssl_obj_load(ssl_ctx, SSL_OBJ_X509_CERT, cert[i], NULL)) {
            printf("Certificate '%s' is undefined.\n", cert[i]);
            exit(1);
        }
    }
    for (i = 0; i < ca_cert_index; i++) {
        if (ssl_obj_load(ssl_ctx, SSL_OBJ_X509_CACERT, ca_cert[i], NULL)) {
            printf("Certificate '%s' is undefined.\n", ca_cert[i]);
            exit(1);
        }
    }


    free(cert);
    free(ca_cert);

    /*************************************************************************
     * This is where the interesting stuff happens. Up until now we've
     * just been setting up sockets etc. Now we do the SSL handshake.
     *************************************************************************/
    client_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(port);
    client_addr.sin_addr.s_addr = sin_addr;

    if (connect(client_fd, (struct sockaddr *)&client_addr,
                sizeof(client_addr)) < 0) {
        perror("connect");
        exit(1);
    }

    if (!quiet) {
        printf("CONNECTED\n");
        TTY_FLUSH();
    }

    /* Try session resumption? */
    if (reconnect) {
        while (reconnect--) {
            ssl = ssl_client_new(ssl_ctx, client_fd, session_id,
                                 sizeof(session_id));
            if ((res = ssl_handshake_status(ssl)) != SSL_OK) {
                if (!quiet) {
                    ssl_display_error(res);
                }

                ssl_free(ssl);
                exit(1);
            }

            display_session_id(ssl);
            memcpy(session_id, ssl_get_session_id(ssl), SSL_SESSION_ID_SIZE);

            if (reconnect) {
                ssl_free(ssl);
                SOCKET_CLOSE(client_fd);

                client_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
                connect(client_fd, (struct sockaddr *)&client_addr,
                        sizeof(client_addr));
            }
        }
    } else {
        ssl = ssl_client_new(ssl_ctx, client_fd, NULL, 0);
    }

    /* check the return status */
    if ((res = ssl_handshake_status(ssl)) != SSL_OK) {
        if (!quiet) {
            ssl_display_error(res);
        }

        exit(1);
    }

    if (!quiet) {
        const char *common_name = ssl_get_cert_dn(ssl,
                                  SSL_X509_CERT_COMMON_NAME);
        if (common_name) {
            printf("Common Name:\t\t\t%s\n", common_name);
        }

        display_session_id(ssl);
        display_cipher(ssl);
    }

    for (;;) {
        uint8_t buf[1024];

        /* allow parallel reading of server and standard input */
        FD_SET(client_fd, &read_set);
#ifndef WIN32
        /* win32 doesn't like mixing up stdin and sockets */
        FD_SET(STDIN_FILENO, &read_set);

        if ((res = select(client_fd + 1, &read_set, NULL, NULL, NULL)) > 0) {
            /* read standard input? */
            if (FD_ISSET(STDIN_FILENO, &read_set))
#endif
            {
                if (fgets((char *)buf, sizeof(buf), stdin) == NULL) {
                    /* bomb out of here */
                    ssl_free(ssl);
                    break;
                } else {
                    /* small hack to check renegotiation */
                    if (buf[0] == 'R' && (buf[1] == '\n' || buf[1] == '\r')) {
                        res = ssl_renegotiate(ssl);
                    } else {
                        res = ssl_write(ssl, buf, strlen((char *)buf));
                    }
                }
            }
#ifndef WIN32
            else {  /* a socket read */
                uint8_t *read_buf;

                res = ssl_read(ssl, &read_buf);

                if (res > 0) {  /* display our interesting output */
                    int written = 0;
                    while (written < res) {
                        written += write(STDOUT_FILENO, read_buf + written,
                                         res - written);
                    }
                    TTY_FLUSH();
                }
            }
        }
#endif

        if (res < 0) {
            if (!quiet) {
                ssl_display_error(res);
            }

            break;      /* get outta here */
        }
    }

    ssl_ctx_free(ssl_ctx);
    SOCKET_CLOSE(client_fd);
#else
    print_client_options(argv[1]);
#endif
}