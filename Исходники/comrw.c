int GetRules(struct sockaddr_in ServerID, struct rule_format rule[], int max_rules, struct htx_data * stats)
{
    SOCKET ToServerSock;
    struct CoordMsg CMsg;
    int rc;
    int i;
    int NoStanzas;
	char msg[1024]; 
	errno = 0;     

    ToServerSock = SetUpConnect(&ServerID, stats, 0); 
    memset(&CMsg, '\0', sizeof(CMsg));
    CMsg.msg_type = htonl(CM_REQ_RULES);
    CMsg.ID.Wsize.size  = htonl((uint32_t)sizeof(struct rule_format));
    rc = StreamWrite(ToServerSock, (char *) &CMsg, sizeof(CMsg));
    if(rc == -1) {
        sprintf(msg, "GetRules: Error writing to Server - %s\n", STRERROR(errno));
        hxfmsg(stats, HTXERROR(EX_RULE1,ERRNO), HTX_HE_SOFT_ERROR, msg);
        HE_exit(EX_RULE1);
    }
    StreamRead(ToServerSock, (char *) &CMsg, sizeof(CMsg));
    CMsg.msg_type = ntohl(CMsg.msg_type);
    CMsg.ID.Wsize.size  = ntohl(CMsg.ID.Wsize.size);
    if(CMsg.msg_type != CM_RULES_STANZA) {
        sprintf(msg, "GetRules: Illegal Packet recvd.\n"); 
        hxfmsg(stats, HTXERROR(EX_RULE3,0), HTX_HE_SOFT_ERROR, msg);
        HE_exit(EX_RULE3);
    }
	#ifdef __DEBUG__
		sprintf(msg, "GetRules: Sock = %d, Recvd msg = %x of size = %#x, rule_format size = %x, pid = %d \n", ToServerSock, CMsg.msg_type, sizeof(CMsg), (uint32_t)sizeof(struct rule_format), getpid()); 
		hxfmsg(stats, 0, 7, msg); 
	#endif 
    memset(rule, '\0', sizeof(struct rule_format) * max_rules);
	memset(&CMsg, '\0', sizeof(CMsg));
    for(i=0; i < max_rules; i++) {

        rc = StreamRead(ToServerSock, (char *) &CMsg.msg_type, sizeof(CMsg.msg_type));
        CMsg.msg_type = ntohl(CMsg.msg_type);
	#ifdef __DEBUG__
		sprintf(msg, "i = %#x, GetRules: Recvd msg = %x, of size = %x \n", i, CMsg.msg_type, sizeof(CMsg.msg_type)); 
		hxfmsg(stats, 0, 7, msg); 
	#endif 
        if(CMsg.msg_type == CM_RULES_FINISHED)
            break;
		 
        if(CMsg.msg_type != CM_RULES_STANZA) {
            sprintf(msg, "GetRules: Unable to obtain rules - type %x\n", (int)CMsg.msg_type);
            hxfmsg(stats, HTXERROR(EX_RULE2,ERRNO), HTX_HE_SOFT_ERROR, msg);
            HE_exit(EX_RULE2);
        }
		 
        rc = StreamRead(ToServerSock, (char*) &rule[i], sizeof(struct rule_format));
        if(rc != sizeof(struct rule_format)) {
            sprintf(msg, "GetRules: Unable to read rules from server - %s\n", STRERROR(errno));
            hxfmsg(stats, HTXERROR(EX_RULE4,ERRNO), HTX_HE_SOFT_ERROR, msg);
			HE_exit(EX_RULE3); 

        }

        NetToHostRules(&rule[i]);
    }
    NoStanzas = i;
    closesocket(ToServerSock);
    return NoStanzas;
}