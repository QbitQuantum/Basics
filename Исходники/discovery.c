static void Publish_tests(void)
{
    IWSDiscoveryPublisher *publisher = NULL;
    IWSDiscoveryPublisherNotify *sink1 = NULL, *sink2 = NULL;
    IWSDiscoveryPublisherNotifyImpl *sink1Impl = NULL, *sink2Impl = NULL;
    char endpointReferenceString[MAX_PATH], app_sequence_string[MAX_PATH];
    LPWSTR publisherIdW = NULL, sequenceIdW = NULL;
    messageStorage *msgStorage;
    WSADATA wsaData;
    BOOL messageOK, hello_message_seen = FALSE, endpoint_reference_seen = FALSE, app_sequence_seen = FALSE;
    BOOL metadata_version_seen = FALSE, any_header_seen = FALSE, wine_ns_seen = FALSE, body_hello_seen = FALSE;
    BOOL any_body_seen = FALSE, types_seen = FALSE, xml_namespaces_seen = FALSE, scopes_seen = FALSE;
    BOOL xaddrs_seen = FALSE;
    int ret, i;
    HRESULT rc;
    ULONG ref;
    char *msg;
    WSDXML_ELEMENT *header_any_element, *body_any_element, *endpoint_any_element, *ref_param_any_element;
    WSDXML_NAME header_any_name, another_name;
    WSDXML_NAMESPACE ns, ns2;
    WCHAR header_any_name_text[] = {'B','e','e','r',0};
    static const WCHAR header_any_text[] = {'P','u','b','l','i','s','h','T','e','s','t',0};
    static const WCHAR body_any_text[] = {'B','o','d','y','T','e','s','t',0};
    static const WCHAR endpoint_any_text[] = {'E','n','d','P','T','e','s','t',0};
    static const WCHAR ref_param_any_text[] = {'R','e','f','P','T','e','s','t',0};
    static const WCHAR uri[] = {'h','t','t','p',':','/','/','w','i','n','e','.','t','e','s','t','/',0};
    static const WCHAR prefix[] = {'w','i','n','e',0};
    static const WCHAR uri3[] = {'h','t','t','p',':','/','/','t','h','i','r','d','.','u','r','l','/',0};
    WSD_NAME_LIST types_list;
    WSD_URI_LIST scopes_list, xaddrs_list;
    unsigned char *probe_uuid_str;

    rc = WSDCreateDiscoveryPublisher(NULL, &publisher);
    ok(rc == S_OK, "WSDCreateDiscoveryPublisher(NULL, &publisher) failed: %08x\n", rc);
    ok(publisher != NULL, "WSDCreateDiscoveryPublisher(NULL, &publisher) failed: publisher == NULL\n");

    /* Test SetAddressFamily */
    rc = IWSDiscoveryPublisher_SetAddressFamily(publisher, 12345);
    ok(rc == E_INVALIDARG, "IWSDiscoveryPublisher_SetAddressFamily(12345) returned unexpected result: %08x\n", rc);

    rc = IWSDiscoveryPublisher_SetAddressFamily(publisher, WSDAPI_ADDRESSFAMILY_IPV4);
    ok(rc == S_OK, "IWSDiscoveryPublisher_SetAddressFamily(WSDAPI_ADDRESSFAMILY_IPV4) failed: %08x\n", rc);

    /* Try to update the address family after already setting it */
    rc = IWSDiscoveryPublisher_SetAddressFamily(publisher, WSDAPI_ADDRESSFAMILY_IPV6);
    ok(rc == STG_E_INVALIDFUNCTION, "IWSDiscoveryPublisher_SetAddressFamily(WSDAPI_ADDRESSFAMILY_IPV6) returned unexpected result: %08x\n", rc);

    /* Create notification sinks */
    ok(create_discovery_publisher_notify(&sink1) == TRUE, "create_discovery_publisher_notify failed\n");
    ok(create_discovery_publisher_notify(&sink2) == TRUE, "create_discovery_publisher_notify failed\n");

    /* Get underlying implementation so we can check the ref count */
    sink1Impl = impl_from_IWSDiscoveryPublisherNotify(sink1);
    sink2Impl = impl_from_IWSDiscoveryPublisherNotify(sink2);

    /* Attempt to unregister sink before registering it */
    rc = IWSDiscoveryPublisher_UnRegisterNotificationSink(publisher, sink1);
    ok(rc == E_FAIL, "IWSDiscoveryPublisher_UnRegisterNotificationSink returned unexpected result: %08x\n", rc);

    /* Register notification sinks */
    rc = IWSDiscoveryPublisher_RegisterNotificationSink(publisher, sink1);
    ok(rc == S_OK, "IWSDiscoveryPublisher_RegisterNotificationSink failed: %08x\n", rc);
    ok(sink1Impl->ref == 2, "Ref count for sink 1 is not as expected: %d\n", sink1Impl->ref);

    rc = IWSDiscoveryPublisher_RegisterNotificationSink(publisher, sink2);
    ok(rc == S_OK, "IWSDiscoveryPublisher_RegisterNotificationSink failed: %08x\n", rc);
    ok(sink2Impl->ref == 2, "Ref count for sink 2 is not as expected: %d\n", sink2Impl->ref);

    /* Unregister the first sink */
    rc = IWSDiscoveryPublisher_UnRegisterNotificationSink(publisher, sink1);
    ok(rc == S_OK, "IWSDiscoveryPublisher_UnRegisterNotificationSink failed: %08x\n", rc);
    ok(sink1Impl->ref == 1, "Ref count for sink 1 is not as expected: %d\n", sink1Impl->ref);

    /* Set up network listener */
    publisherIdW = utf8_to_wide(publisherId);
    if (publisherIdW == NULL) goto after_publish_test;

    sequenceIdW = utf8_to_wide(sequenceId);
    if (sequenceIdW == NULL) goto after_publish_test;

    msgStorage = heap_alloc_zero(sizeof(messageStorage));
    if (msgStorage == NULL) goto after_publish_test;

    msgStorage->running = TRUE;
    InitializeCriticalSection(&msgStorage->criticalSection);

    ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
    ok(ret == 0, "WSAStartup failed (ret = %d)\n", ret);

    ret = start_listening_on_all_addresses(msgStorage, AF_INET);
    ok(ret == TRUE, "Unable to listen on IPv4 addresses (ret == %d)\n", ret);

    /* Create "any" elements for header */
    ns.Uri = uri;
    ns.PreferredPrefix = prefix;

    header_any_name.LocalName = header_any_name_text;
    header_any_name.Space = &ns;

    rc = WSDXMLBuildAnyForSingleElement(&header_any_name, header_any_text, &header_any_element);
    ok(rc == S_OK, "WSDXMLBuildAnyForSingleElement failed with %08x\n", rc);

    rc = WSDXMLBuildAnyForSingleElement(&header_any_name, body_any_text, &body_any_element);
    ok(rc == S_OK, "WSDXMLBuildAnyForSingleElement failed with %08x\n", rc);

    rc = WSDXMLBuildAnyForSingleElement(&header_any_name, endpoint_any_text, &endpoint_any_element);
    ok(rc == S_OK, "WSDXMLBuildAnyForSingleElement failed with %08x\n", rc);

    rc = WSDXMLBuildAnyForSingleElement(&header_any_name, ref_param_any_text, &ref_param_any_element);
    ok(rc == S_OK, "WSDXMLBuildAnyForSingleElement failed with %08x\n", rc);

    /* Create types list */
    ns2.Uri = uri_more_tests;
    ns2.PreferredPrefix = prefix_grog;

    another_name.LocalName = (WCHAR *) name_cider;
    another_name.Space = &ns2;

    types_list.Next = malloc(sizeof(WSD_NAME_LIST));
    types_list.Element = &another_name;

    types_list.Next->Next = NULL;
    types_list.Next->Element = &header_any_name;

    /* Create scopes and xaddrs lists */
    scopes_list.Next = malloc(sizeof(WSD_URI_LIST));
    scopes_list.Element = uri;

    scopes_list.Next->Next = NULL;
    scopes_list.Next->Element = uri_more_tests;

    xaddrs_list.Next = malloc(sizeof(WSD_URI_LIST));
    xaddrs_list.Element = uri_more_tests;

    xaddrs_list.Next->Next = NULL;
    xaddrs_list.Next->Element = uri3;

    /* Publish the service */
    rc = IWSDiscoveryPublisher_PublishEx(publisher, publisherIdW, 1, 1, 1, sequenceIdW, &types_list, &scopes_list,
        &xaddrs_list, header_any_element, ref_param_any_element, NULL, endpoint_any_element, body_any_element);

    WSDFreeLinkedMemory(header_any_element);
    WSDFreeLinkedMemory(body_any_element);
    WSDFreeLinkedMemory(endpoint_any_element);
    WSDFreeLinkedMemory(ref_param_any_element);
    free(types_list.Next);
    free(scopes_list.Next);
    free(xaddrs_list.Next);

    ok(rc == S_OK, "Publish failed: %08x\n", rc);

    /* Wait up to 2 seconds for messages to be received */
    if (WaitForMultipleObjects(msgStorage->numThreadHandles, msgStorage->threadHandles, TRUE, 2000) == WAIT_TIMEOUT)
    {
        /* Wait up to 1 more second for threads to terminate */
        msgStorage->running = FALSE;
        WaitForMultipleObjects(msgStorage->numThreadHandles, msgStorage->threadHandles, TRUE, 1000);
    }

    DeleteCriticalSection(&msgStorage->criticalSection);

    /* Verify we've received a message */
    ok(msgStorage->messageCount >= 1, "No messages received\n");

    sprintf(endpointReferenceString, "<wsa:EndpointReference><wsa:Address>%s</wsa:Address><wsa:ReferenceParameters>"
        "<wine:Beer>RefPTest</wine:Beer></wsa:ReferenceParameters><wine:Beer>EndPTest</wine:Beer>"
        "</wsa:EndpointReference>", publisherId);

    sprintf(app_sequence_string, "<wsd:AppSequence InstanceId=\"1\" SequenceId=\"%s\" MessageNumber=\"1\"></wsd:AppSequence>",
        sequenceId);

    messageOK = FALSE;

    /* Check we're received the correct message */
    for (i = 0; i < msgStorage->messageCount; i++)
    {
        msg = msgStorage->messages[i];
        messageOK = FALSE;

        hello_message_seen = (strstr(msg, "<wsa:Action>http://schemas.xmlsoap.org/ws/2005/04/discovery/Hello</wsa:Action>") != NULL);
        endpoint_reference_seen = (strstr(msg, endpointReferenceString) != NULL);
        app_sequence_seen = (strstr(msg, app_sequence_string) != NULL);
        metadata_version_seen = (strstr(msg, "<wsd:MetadataVersion>1</wsd:MetadataVersion>") != NULL);
        any_header_seen = (strstr(msg, "<wine:Beer>PublishTest</wine:Beer>") != NULL);
        wine_ns_seen = (strstr(msg, "xmlns:wine=\"http://wine.test/\"") != NULL);
        body_hello_seen = (strstr(msg, "<soap:Body><wsd:Hello") != NULL);
        any_body_seen = (strstr(msg, "<wine:Beer>BodyTest</wine:Beer>") != NULL);
        types_seen = (strstr(msg, "<wsd:Types>grog:Cider wine:Beer</wsd:Types>") != NULL);
        scopes_seen = (strstr(msg, "<wsd:Scopes>http://wine.test/ http://more.tests/</wsd:Scopes>") != NULL);
        xaddrs_seen = (strstr(msg, "<wsd:XAddrs>http://more.tests/ http://third.url/</wsd:XAddrs>") != NULL);
        xml_namespaces_seen = (strstr(msg, "xmlns:wine=\"http://wine.test/\" xmlns:grog=\"http://more.tests/\"") != NULL);
        messageOK = hello_message_seen && endpoint_reference_seen && app_sequence_seen && metadata_version_seen &&
            any_header_seen && wine_ns_seen && body_hello_seen && any_body_seen && types_seen && xml_namespaces_seen &&
            scopes_seen && xaddrs_seen;

        if (messageOK) break;
    }

    for (i = 0; i < msgStorage->messageCount; i++)
    {
        heap_free(msgStorage->messages[i]);
    }

    heap_free(msgStorage);

    ok(hello_message_seen == TRUE, "Hello message not received\n");
    ok(endpoint_reference_seen == TRUE, "EndpointReference not received\n");
    ok(app_sequence_seen == TRUE, "AppSequence not received\n");
    ok(metadata_version_seen == TRUE, "MetadataVersion not received\n");
    ok(messageOK == TRUE, "Hello message metadata not received\n");
    ok(any_header_seen == TRUE, "Custom header not received\n");
    ok(wine_ns_seen == TRUE, "Wine namespace not received\n");
    ok(body_hello_seen == TRUE, "Body and Hello elements not received\n");
    ok(any_body_seen == TRUE, "Custom body element not received\n");
    ok(types_seen == TRUE, "Types not received\n");
    ok(xml_namespaces_seen == TRUE, "XML namespaces not received\n");
    ok(scopes_seen == TRUE, "Scopes not received\n");
    ok(xaddrs_seen == TRUE, "XAddrs not received\n");

after_publish_test:

    heap_free(publisherIdW);
    heap_free(sequenceIdW);

    /* Test the receiving of a probe message */
    probe_event = CreateEventW(NULL, TRUE, FALSE, NULL);

    UuidCreate(&probe_message_id);
    UuidToStringA(&probe_message_id, &probe_uuid_str);

    ok(probe_uuid_str != NULL, "Failed to create UUID for probe message\n");

    if (probe_uuid_str != NULL)
    {
        char probe_message[sizeof(testProbeMessage) + 50];
        sprintf(probe_message, testProbeMessage, probe_uuid_str);

        ok(send_udp_multicast_of_type(probe_message, strlen(probe_message), AF_INET) == TRUE, "Sending Probe message failed\n");
        todo_wine ok(WaitForSingleObject(probe_event, 2000) == WAIT_OBJECT_0, "Probe message not received\n");

        RpcStringFreeA(&probe_uuid_str);
    }

    CloseHandle(probe_event);

    ref = IWSDiscoveryPublisher_Release(publisher);
    ok(ref == 0, "IWSDiscoveryPublisher_Release() has %d references, should have 0\n", ref);

    /* Check that the sinks have been released by the publisher */
    ok(sink1Impl->ref == 1, "Ref count for sink 1 is not as expected: %d\n", sink1Impl->ref);
    ok(sink2Impl->ref == 1, "Ref count for sink 2 is not as expected: %d\n", sink2Impl->ref);

    /* Release the sinks */
    IWSDiscoveryPublisherNotify_Release(sink1);
    IWSDiscoveryPublisherNotify_Release(sink2);

    WSACleanup();
}