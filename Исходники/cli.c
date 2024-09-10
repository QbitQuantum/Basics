int cli_parse_show_stats(int argc, char **argv)
{
    int ret = 0;
    int msgs = 0;
    int opt;
    int opt_idx = 0;
    char lip_addr[16], rip_addr[16];
    uint32_t i = 0;
    uint32_t request_length, reply_length;
    cmdif_request_show_stats request;
    cmdif_reply_show_stats reply;

    memset(&request, 0, sizeof(request));
    request.hdr.xid = htonl(UINT32_MAX * rand());
    request.hdr.cmd = CMDIF_CMD_SHOW_STATS;
    request.hdr.length = htons(sizeof(request));
    memset(&reply, 0, sizeof(reply));
    memset(lip_addr, '\0', sizeof(lip_addr));
    memset(rip_addr, '\0', sizeof(rip_addr));

    while(1){
        opt = getopt_long(argc, argv, "hv", cli_cmd_ss_options, &opt_idx);
        if(opt == -1){
            break;
        }

        switch(opt){
        case CLI_CMD_RS_TX:
            request.cmd_options = CMDIF_CMD_STATS_OPTS_TX;
            break;
        case CLI_CMD_RS_RX:
            request.cmd_options = CMDIF_CMD_STATS_OPTS_RX;
            break;
        case 'v':
            log_set_level(LOG_DEBUG);
            break;
        case '?':
        default:
            ret = -1;
            break;
        }
    }

    if(ret < 0){
        return -1;
    }

    log_debug("request: xid = %u", ntohl(request.hdr.xid));

    request.cmd_options = htons(request.cmd_options);

    request_length = sizeof(request);
    reply_length = sizeof(reply);
    ret = cli_exec_cmd(&request, &request_length,
                       &reply, &reply_length);
    if(ret < 0){
        log_err("cannot execute a command.");
        return -1;
    }
    msgs++;

    log_debug("reply: xid = %u, status = %u, options = 0x%04x, n_stats = %u",
              ntohl(reply.hdr.xid), reply.hdr.status, ntohs(reply.cmd_options),
              ntohl(reply.n_stats));

    if(ntohl(reply.n_stats) == 0){
        return 0;
    }

    printf("ip_dst,tp_dst,ip_src,tp_src,n_pkts,n_octets\n");

    while(reply.hdr.status == CMDIF_STATUS_OK){
        for(i=0; i<ntohl(reply.n_stats); i++){
/*
            printf("%08x,%u,%08x,%u,%u,%llu\n",
                   ntohl(reply.st[i].lip), ntohs(reply.st[i].lport),
                   ntohl(reply.st[i].rip), ntohs(reply.st[i].rport),
                   ntohl(reply.st[i].n_pkts), ntohll(reply.st[i].n_octets));
*/
            printf("%s,%u,%s,%u,%u,%llu\n",
                   ultoipaddr(ntohl(reply.st[i].lip), lip_addr),
                   ntohs(reply.st[i].lport),
                   ultoipaddr(ntohl(reply.st[i].rip), rip_addr),
                   ntohs(reply.st[i].rport),
                   ntohl(reply.st[i].n_pkts), ntohll(reply.st[i].n_octets));
        }

        log_debug("cmd_options = %x", ntohs(reply.cmd_options));
        if((ntohs(reply.cmd_options) & CMDIF_CMD_STATS_CONTINUE) == 0){
            break;
        }

        memset(&reply, 0, sizeof(reply));
        ret = cli_exec_cmd_more_reply(&request, &request_length,
                                      &reply, &reply_length);
        if(ret < 0){
            log_err("cannot execute a command.");
            log_err("%u messages received.", msgs);
            return -1;
        }
        
        msgs++;

        log_debug("reply: xid = %u, status = %u, options = 0x%04x, n_stats = %u",
                  ntohl(reply.hdr.xid), reply.hdr.status, ntohs(reply.cmd_options),
                  ntohl(reply.n_stats));
    }

    log_debug("%u messages received.", msgs);

    return 0;
}