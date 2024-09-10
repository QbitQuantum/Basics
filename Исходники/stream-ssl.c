static int
do_ca_cert_bootstrap(struct stream *stream)
{
    struct ssl_stream *sslv = ssl_stream_cast(stream);
    STACK_OF(X509) *chain;
    X509 *cert;
    FILE *file;
    int error;
    int fd;

    chain = SSL_get_peer_cert_chain(sslv->ssl);
    if (!chain || !sk_X509_num(chain)) {
        VLOG_ERR("could not bootstrap CA cert: no certificate presented by "
                 "peer");
        return EPROTO;
    }
    cert = sk_X509_value(chain, sk_X509_num(chain) - 1);

    /* Check that 'cert' is self-signed.  Otherwise it is not a CA
     * certificate and we should not attempt to use it as one. */
    error = X509_check_issued(cert, cert);
    if (error) {
        VLOG_ERR("could not bootstrap CA cert: obtained certificate is "
                 "not self-signed (%s)",
                 X509_verify_cert_error_string(error));
        if (sk_X509_num(chain) < 2) {
            VLOG_ERR("only one certificate was received, so probably the peer "
                     "is not configured to send its CA certificate");
        }
        return EPROTO;
    }

    fd = open(ca_cert.file_name, O_CREAT | O_EXCL | O_WRONLY, 0444);
    if (fd < 0) {
        if (errno == EEXIST) {
            VLOG_INFO_RL(&rl, "reading CA cert %s created by another process",
                         ca_cert.file_name);
            stream_ssl_set_ca_cert_file__(ca_cert.file_name, true, true);
            return EPROTO;
        } else {
            VLOG_ERR("could not bootstrap CA cert: creating %s failed: %s",
                     ca_cert.file_name, ovs_strerror(errno));
            return errno;
        }
    }

    file = fdopen(fd, "w");
    if (!file) {
        error = errno;
        VLOG_ERR("could not bootstrap CA cert: fdopen failed: %s",
                 ovs_strerror(error));
        unlink(ca_cert.file_name);
        return error;
    }

    if (!PEM_write_X509(file, cert)) {
        VLOG_ERR("could not bootstrap CA cert: PEM_write_X509 to %s failed: "
                 "%s", ca_cert.file_name,
                 ERR_error_string(ERR_get_error(), NULL));
        fclose(file);
        unlink(ca_cert.file_name);
        return EIO;
    }

    if (fclose(file)) {
        error = errno;
        VLOG_ERR("could not bootstrap CA cert: writing %s failed: %s",
                 ca_cert.file_name, ovs_strerror(error));
        unlink(ca_cert.file_name);
        return error;
    }

    VLOG_INFO("successfully bootstrapped CA cert to %s", ca_cert.file_name);
    log_ca_cert(ca_cert.file_name, cert);
    bootstrap_ca_cert = false;
    ca_cert.read = true;

    /* SSL_CTX_add_client_CA makes a copy of cert's relevant data. */
    SSL_CTX_add_client_CA(ctx, cert);

    SSL_CTX_set_cert_store(ctx, X509_STORE_new());
    if (SSL_CTX_load_verify_locations(ctx, ca_cert.file_name, NULL) != 1) {
        VLOG_ERR("SSL_CTX_load_verify_locations: %s",
                 ERR_error_string(ERR_get_error(), NULL));
        return EPROTO;
    }
    VLOG_INFO("killing successful connection to retry using CA cert");
    return EPROTO;
}