static int publish_main_service(struct userdata *u) {
    DNSServiceErrorType err;
    TXTRecordRef txt;

    pa_assert(u);

    if (u->main_service) {
        DNSServiceRefDeallocate(u->main_service);
        u->main_service = NULL;
    }

    TXTRecordCreate(&txt, 0, NULL);
    txt_record_server_data(u->core, &txt);

    err = DNSServiceRegister(&u->main_service,
                             0, /* flags */
                             kDNSServiceInterfaceIndexAny,
                             u->service_name,
                             SERVICE_TYPE_SERVER,
                             NULL, /* domain */
                             NULL, /* host */
                             compute_port(u),
                             TXTRecordGetLength(&txt),
                             TXTRecordGetBytesPtr(&txt),
                             NULL, NULL);

    if (err != kDNSServiceErr_NoError) {
        pa_log("%s(): DNSServiceRegister() returned err %d", __func__, err);
        return err;
    }

    TXTRecordDeallocate(&txt);

    return 0;
}