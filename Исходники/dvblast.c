bool config_ParseHost( output_config_t *p_config, char *psz_string )
{
    struct addrinfo *p_ai;
    int i_mtu;

    p_config->psz_displayname = strdup( psz_string );

    p_ai = ParseNodeService( psz_string, &psz_string, DEFAULT_PORT );
    if ( p_ai == NULL ) return false;
    memcpy( &p_config->connect_addr, p_ai->ai_addr, p_ai->ai_addrlen );
    freeaddrinfo( p_ai );

    p_config->i_family = p_config->connect_addr.ss_family;
    if ( p_config->i_family == AF_UNSPEC ) return false;

    if ( psz_string == NULL || !*psz_string ) goto end;

    if ( *psz_string == '@' )
    {
        psz_string++;
        p_ai = ParseNodeService( psz_string, &psz_string, 0 );
        if ( p_ai == NULL || p_ai->ai_family != p_config->i_family )
            msg_Warn( NULL, "invalid bind address" );
        else
            memcpy( &p_config->bind_addr, p_ai->ai_addr, p_ai->ai_addrlen );
        freeaddrinfo( p_ai );
    }

    while ( (psz_string = strchr( psz_string, '/' )) != NULL )
    {
        *psz_string++ = '\0';

#define IS_OPTION( option ) (!strncasecmp( psz_string, option, strlen(option) ))
#define ARG_OPTION( option ) (psz_string + strlen(option))

        if ( IS_OPTION("udp") )
            p_config->i_config |= OUTPUT_UDP;
        else if ( IS_OPTION("dvb") )
            p_config->i_config |= OUTPUT_DVB;
        else if ( IS_OPTION("epg") )
            p_config->i_config |= OUTPUT_EPG;
        else if ( IS_OPTION("tsid=") )
            p_config->i_tsid = strtol( ARG_OPTION("tsid="), NULL, 0 );
        else if ( IS_OPTION("retention=") )
            p_config->i_max_retention = strtoll( ARG_OPTION("retention="),
                                                 NULL, 0 ) * 1000;
        else if ( IS_OPTION("latency=") )
            p_config->i_output_latency = strtoll( ARG_OPTION("latency="),
                                                  NULL, 0 ) * 1000;
        else if ( IS_OPTION("ttl=") )
            p_config->i_ttl = strtol( ARG_OPTION("ttl="), NULL, 0 );
        else if ( IS_OPTION("tos=") )
            p_config->i_tos = strtol( ARG_OPTION("tos="), NULL, 0 );
        else if ( IS_OPTION("mtu=") )
            p_config->i_mtu = strtol( ARG_OPTION("mtu="), NULL, 0 );
        else if ( IS_OPTION("ifindex=") )
            p_config->i_if_index_v6 = strtol( ARG_OPTION("ifindex="), NULL, 0 );
        else if ( IS_OPTION("srvname=")  )
        {
            if ( p_config->psz_service_name )
                free( p_config->psz_service_name );
            p_config->psz_service_name = config_stropt( ARG_OPTION("srvname=") );
        }
        else if ( IS_OPTION("srvprovider=") )
        {
            if ( !p_config->psz_service_provider )
                free( p_config->psz_service_provider );
            p_config->psz_service_provider = config_stropt( ARG_OPTION("srvprovider=") );
        }
        else if ( IS_OPTION("srcaddr=") )
        {
            if ( p_config->i_family != AF_INET ) {
                msg_Err( NULL, "RAW sockets currently implemented for ipv4 only");
                return false;
            }
            if ( !p_config->psz_srcaddr )
                free( p_config->psz_srcaddr );
            p_config->psz_srcaddr = config_stropt( ARG_OPTION("srcaddr=") );
            p_config->i_config |= OUTPUT_RAW;
        }
        else if ( IS_OPTION("srcport=") )
            p_config->i_srcport = strtol( ARG_OPTION("srcport="), NULL, 0 );
        else if ( IS_OPTION("ssrc=") )
        {
            in_addr_t i_addr = inet_addr( ARG_OPTION("ssrc=") );
            memcpy( p_config->pi_ssrc, &i_addr, 4 * sizeof(uint8_t) );
        }
        else if ( IS_OPTION("pidmap=") )
        {
            char *str1;
            char *saveptr = NULL;
            char *tok = NULL;
            int i, i_newpid;
            for (i = 0, str1 = config_stropt( (ARG_OPTION("pidmap="))); i < N_MAP_PIDS; i++, str1 = NULL)
            {
                tok = strtok_r(str1, ",", &saveptr);
                if ( !tok )
                    break;
                i_newpid = strtoul(tok, NULL, 0);
                if ( !i_newpid ) {
                     msg_Warn( NULL, "Invalid output pidmap setting" );
                }
                p_config->pi_confpids[i] = i_newpid;
            }
            p_config->b_do_remap = true;
        }
        else
            msg_Warn( NULL, "unrecognized option %s", psz_string );

#undef IS_OPTION
#undef ARG_OPTION
    }

    if ( !p_config->psz_service_provider && psz_provider_name )
        p_config->psz_service_provider = strdup( psz_provider_name );

end:
    i_mtu = p_config->i_family == AF_INET6 ? DEFAULT_IPV6_MTU :
            DEFAULT_IPV4_MTU;

    if ( !p_config->i_mtu )
        p_config->i_mtu = i_mtu;
    else if ( p_config->i_mtu < TS_SIZE + RTP_HEADER_SIZE )
    {
        msg_Warn( NULL, "invalid MTU %d, setting %d", p_config->i_mtu, i_mtu );
        p_config->i_mtu = i_mtu;
    }

    return true;
}