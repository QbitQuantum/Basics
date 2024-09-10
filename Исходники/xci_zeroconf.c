static void *dcc_xci_zeroconf_main(void *param) {
    context *ctx = param;
    const char *service;
    DNSServiceErrorType rv;

    service = dcc_xci_zeroconf_service_name();

    if ((rv = DNSServiceRegister(&ctx->zc, 0, 0, NULL, service,
                                 NULL, NULL, htons(arg_port), 0, NULL,
                                 dcc_xci_zeroconf_reply, ctx)) !=
        kDNSServiceErr_NoError) {
        rs_log_error("DNSServiceRegister() failed: error %d", rv);
        return NULL;
    }

    while ((rv = DNSServiceProcessResult(ctx->zc) == kDNSServiceErr_NoError)) {
    }

    rs_log_error("DNSServiceProcessResult() failed: error %d", rv);

    ctx->thread_live = 0;
    return NULL;
}