static int event_to_source_target(Packet *p, idmef_alert_t *alert)
{
        int ret;
        idmef_node_t *node;
        idmef_source_t *source;
        idmef_target_t *target;
        idmef_address_t *address;
        idmef_service_t *service;
        prelude_string_t *string;
        static char saddr[128], daddr[128];

        if ( !p )
            return 0;

        if ( ! IPH_IS_VALID(p) )
                return 0;

        ret = idmef_alert_new_source(alert, &source, IDMEF_LIST_APPEND);
        if ( ret < 0 )
                return ret;

        ret = idmef_source_new_interface(source, &string);
        if ( ret < 0 )
            return ret;
        prelude_string_set_ref(string, PRINT_INTERFACE(DAQ_GetInterfaceSpec()));

        ret = idmef_source_new_service(source, &service);
        if ( ret < 0 )
                return ret;

        if ( p->tcph || p->udph )
                idmef_service_set_port(service, p->sp);

        idmef_service_set_ip_version(service, GET_IPH_VER(p));
        idmef_service_set_iana_protocol_number(service, GET_IPH_PROTO(p));

        ret = idmef_source_new_node(source, &node);
        if ( ret < 0 )
                return ret;

        ret = idmef_node_new_address(node, &address, IDMEF_LIST_APPEND);
        if ( ret < 0 )
                return ret;

        ret = idmef_address_new_address(address, &string);
        if ( ret < 0 )
                return ret;

        SnortSnprintf(saddr, sizeof(saddr), "%s", inet_ntoa(GET_SRC_ADDR(p)));
        prelude_string_set_ref(string, saddr);

        ret = idmef_alert_new_target(alert, &target, IDMEF_LIST_APPEND);
        if ( ret < 0 )
                return ret;

        ret = idmef_target_new_interface(target, &string);
        if ( ret < 0 )
            return ret;
        prelude_string_set_ref(string, PRINT_INTERFACE(DAQ_GetInterfaceSpec()));

        ret = idmef_target_new_service(target, &service);
        if ( ! ret < 0 )
                return ret;

        if ( p->tcph || p->udph )
                idmef_service_set_port(service, p->dp);

        idmef_service_set_ip_version(service, GET_IPH_VER(p));
        idmef_service_set_iana_protocol_number(service, GET_IPH_PROTO(p));

        ret = idmef_target_new_node(target, &node);
        if ( ret < 0 )
                return ret;

        ret = idmef_node_new_address(node, &address, IDMEF_LIST_APPEND);
        if ( ret < 0 )
                return ret;

        ret = idmef_address_new_address(address, &string);
        if ( ret < 0 )
                return ret;

        SnortSnprintf(daddr, sizeof(daddr), "%s", inet_ntoa(GET_DST_ADDR(p)));
        prelude_string_set_ref(string, daddr);

        return 0;
}