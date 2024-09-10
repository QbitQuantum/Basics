/*
 * Test2 - exercise the response  variations triggered
 *         by est_client_get_csrattrs()
 */
static void us896_test2(void) {
    EST_CTX *ctx;
    unsigned char *pkey = NULL;
    unsigned char *cacerts = NULL;
    int cacerts_len = 0;
    EST_ERROR rc = EST_ERR_NONE;
    unsigned char *retrieved_cacerts = NULL;
    int retrieved_cacerts_len = 0;
    EVP_PKEY *priv_key;

    SLEEP(1);

    LOG_FUNC_NM
    ;

    /*
     * Read in the CA certificates
     */
    cacerts_len = read_binary_file(CLIENT_UT_CACERT, &cacerts);
    CU_ASSERT(cacerts_len > 0);

    /*
     * Read in the private key file
     */
    priv_key = read_private_key(CLIENT_UT_PUBKEY);
    if (priv_key == NULL) {
        printf("\nError while reading private key file %s\n", CLIENT_UT_PUBKEY);
        return;
    }

    ctx = est_client_init(cacerts, cacerts_len, EST_CERT_FORMAT_PEM,
            client_manual_cert_verify);
    CU_ASSERT(ctx != NULL);

    rc = est_client_set_auth(ctx, "", "", NULL, priv_key);
    CU_ASSERT(rc == EST_ERR_NONE);

    est_client_set_server(ctx, US896_SERVER_IP, US896_SERVER_PORT, NULL);

    /*
     * issue the get ca certs request
     */
    rc = est_client_get_cacerts(ctx, &retrieved_cacerts_len);
    /*
     * should be successful, and should have obtained a valid buffer
     * containing the CA certs
     */
    CU_ASSERT(rc == EST_ERR_NONE);
    CU_ASSERT(retrieved_cacerts_len > 0);

    retrieved_cacerts = malloc(retrieved_cacerts_len);

    rc = est_client_copy_cacerts(ctx, retrieved_cacerts);

    /*
     * output the retrieved ca certs and compare to what they should be
     */
    if (retrieved_cacerts) {

        printf("\nRetrieved CA Certs buffer:\n %s\n", retrieved_cacerts);
        printf("Retrieved CA certs buffer length: %d\n", retrieved_cacerts_len);
    }
    free(retrieved_cacerts);

    /* 
     * All of these are negative tests and require that code in the
     * EST server is modified such that it will allow bad/corrupted
     * attributes to be initialized so they can be sent to the client.
     */
#ifdef NEGATIVE_UNIT_TEST
    unsigned char *csr_data;
    int csr_len;

    /* clear callback */
    if (est_set_csr_cb(ectx, NULL)) {
        printf("\nUnable to set EST CSR Attributes callback.  Aborting!!!\n");
        exit(1);
    }

    rc = est_server_init_csrattrs(ectx, TEST_CORRUPT_ATTR1, strlen(TEST_CORRUPT_ATTR1));
    CU_ASSERT(rc == EST_ERR_NONE);

    rc = est_client_get_csrattrs(ctx, &csr_data, &csr_len);
    CU_ASSERT(rc != EST_ERR_NONE);
    CU_ASSERT(csr_len == 0);
    CU_ASSERT(csr_data == NULL);

    rc = est_server_init_csrattrs(ectx, TEST_CORRUPT_ATTR2, strlen(TEST_CORRUPT_ATTR2));
    CU_ASSERT(rc == EST_ERR_NONE);

    rc = est_client_get_csrattrs(ctx, &csr_data, &csr_len);
    CU_ASSERT(rc != EST_ERR_NONE);
    CU_ASSERT(csr_len == 0);
    CU_ASSERT(csr_data == NULL);

    rc = est_server_init_csrattrs(ectx, TEST_SHORT_ATTR, strlen(TEST_SHORT_ATTR));
    CU_ASSERT(rc == EST_ERR_NONE);

    rc = est_client_get_csrattrs(ctx, &csr_data, &csr_len);
    CU_ASSERT(rc != EST_ERR_NONE);
    CU_ASSERT(csr_len == 0);
    CU_ASSERT(csr_data == NULL);

    rc = est_server_init_csrattrs(ectx, TEST_LONG_ATTR, strlen(TEST_LONG_ATTR));
    CU_ASSERT(rc == EST_ERR_NONE);

    rc = est_client_get_csrattrs(ctx, &csr_data, &csr_len);
    CU_ASSERT(rc != EST_ERR_NONE);
    CU_ASSERT(csr_len == 0);
    CU_ASSERT(csr_data == NULL);

#endif

    if (ctx) {
        est_destroy(ctx);
    }
    if (cacerts) {
        free(cacerts);
    }
    if (pkey) {
        free(pkey);
    }
}