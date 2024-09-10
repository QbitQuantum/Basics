/* FoundAdvertisedName callback */
void AJ_CALL found_advertised_name(const void* context, const char* name, alljoyn_transportmask transport, const char* namePrefix)
{
    printf("[Callback] found_advertised_name(name=%s, prefix=%s)\n", name, namePrefix);
    if (0 == strcmp(name, OBJECT_NAME)) {
        /* We found a remote bus that is advertising basic service's  well-known name so connect to it */
        alljoyn_sessionopts opts = alljoyn_sessionopts_create(ALLJOYN_TRAFFIC_TYPE_MESSAGES, QCC_FALSE, ALLJOYN_PROXIMITY_ANY, ALLJOYN_TRANSPORT_ANY);
        QStatus status;
        /* enable concurrent callbacks so joinsession can be called */
        alljoyn_busattachment_enableconcurrentcallbacks(g_msgBus);
        status = alljoyn_busattachment_joinsession(g_msgBus, name, SERVICE_PORT, NULL, &s_sessionId, opts);

        if (ER_OK != status) {
            printf("alljoyn_busattachment_joinsession failed (status=%s)\n", QCC_StatusText(status));
        } else {
            printf("alljoyn_busattachment_joinsession SUCCESS (Session id=%d)\n", s_sessionId);
        }
        alljoyn_sessionopts_destroy(opts);
    }
    s_joinComplete = QCC_TRUE;
}