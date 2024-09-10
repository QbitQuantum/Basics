/*
funcational description:
schedual module ,extract some information about this flow
author:jzheng
date:2014-06-01
*/
int sched_module_classify(struct rte_mbuf*pktbuf,struct sched_stat_str *lpstat)
{
	dbg_local struct ether_hdr *eh;
	dbg_local struct ether_arp *ea;
	dbg_local struct iphdr *iph;
	dbg_local uint32_t uiSIP;
	dbg_local uint32_t uiDIP;
	
	memset(lpstat,0x0,sizeof(struct sched_stat_str));//reset all fields
	lpstat->iport_in=GETLONIB(pktbuf->pkt.in_port);
	lpstat->iport_out=GETHINIB(pktbuf->pkt.in_port);
	lpstat->iDiscard=FALSE;
	if(gPortParaConf[lpstat->iport_in].port_grp!=gPortParaConf[lpstat->iport_out].port_grp){
		lpstat->enDir=TRAFFIC_DIR_UNDEF;
	}else{
		lpstat->enDir=TRAFFIC_DIR_UNDEF;
		
		switch(gPortParaConf[lpstat->iport_in].ePortRole)
		{
			case PORT_ROLE_INTERIOR:
				if(gPortParaConf[lpstat->iport_out].ePortRole==PORT_ROLE_EXTERIOR)
					lpstat->enDir=TRAFFIC_DIR_OUTBOUND;
				break;
			case PORT_ROLE_EXTERIOR:
				if(gPortParaConf[lpstat->iport_out].ePortRole==PORT_ROLE_INTERIOR)
					lpstat->enDir=TRAFFIC_DIR_INBOUND;
				break;
			case PORT_ROLE_PE:
				if(gPortParaConf[lpstat->iport_out].ePortRole==PORT_ROLE_CE)
					lpstat->enDir=TRAFFIC_DIR_INBOUND;
				break;
			case PORT_ROLE_CE:
				if(gPortParaConf[lpstat->iport_out].ePortRole==PORT_ROLE_PE)
					lpstat->enDir=TRAFFIC_DIR_OUTBOUND;
				break;
		}
	}
	eh=rte_pktmbuf_mtod(pktbuf,struct ether_hdr *);
	lpstat->iPayloadLength=pktbuf->pkt.pkt_len-sizeof(struct ether_hdr);//payload length do not include datalink layer header
	switch(HTONS(eh->ether_type))
	{
		case ETH_TYPE_ARP:
			ea=(struct ether_arp *)(sizeof(struct ether_hdr)+(char*)eh);
			uiSIP=HTONL(MAKEUINT32FROMUINT8ARR(ea->arp_spa));
			uiDIP=HTONL(MAKEUINT32FROMUINT8ARR(ea->arp_tpa));
			lpstat->iPaketType=ETH_TYPE_ARP;
			break;
		case ETH_TYPE_IP:
			iph=(struct iphdr *)(sizeof(struct ether_hdr)+(char*)eh);
			uiSIP=HTONL(iph->ip_src);
			uiDIP=HTONL(iph->ip_dst);
			lpstat->iPaketType=ETH_TYPE_IP;
			break;
		default:
			uiSIP=uiDIP=0;
			lpstat->iPaketType=HTONS(eh->ether_type);
			break;
	}
	switch(lpstat->enDir)
	{
		case TRAFFIC_DIR_INBOUND:
			lpstat->iFlowIdx=find_net_entry(uiDIP,TRUE);
			break;
		case TRAFFIC_DIR_OUTBOUND:
			lpstat->iFlowIdx=find_net_entry(uiSIP,TRUE);
			break;
		default:
			lpstat->iDiscard=TRUE;
			lpstat->iFlowIdx=-1;
			break;
	}
	return 0;	
}