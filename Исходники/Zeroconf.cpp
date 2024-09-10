int Trick::Zeroconf::init() {

#ifdef HAVE_ZEROCONF
#if __linux
    int error;
    int ret ;
    char r[128] ;

    if (!(simple_poll = avahi_simple_poll_new())) {
        fprintf(stderr, "Failed to create simple poll object.\n");
        return -1 ;
    }

    client = avahi_client_new(avahi_simple_poll_get(simple_poll), (AvahiClientFlags)0, NULL, NULL, &error);

    if ( client != NULL ) {
        group = avahi_entry_group_new(client, entry_group_callback, (void *)name.c_str()) ;
        if (avahi_entry_group_is_empty(group)) {
            ret = avahi_entry_group_add_service(group, AVAHI_IF_UNSPEC, AVAHI_PROTO_UNSPEC, (AvahiPublishFlags)0,
                name.c_str(), type.c_str(), NULL, NULL, var_server_get_port(), NULL, r, NULL) ;
            ret = avahi_entry_group_commit(group) ;
        }
    }
#endif
#if __APPLE__
    DNSServiceErrorType error ;

    error = DNSServiceRegister(&dns_service_ref,
                         0, 0,
                         name.c_str(), type.c_str(),
                         NULL, NULL,
                         htons(var_server_get_port()),
                         0, NULL, // txt record stuff
                         NULL, NULL); // callback stuff
#endif
#endif

    return 0 ;

}