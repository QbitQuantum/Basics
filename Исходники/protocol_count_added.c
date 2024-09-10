void packet_handler(u_char *dumpfile, const struct pcap_pkthdr *header, const u_char *pkt_data)
{
	const struct ether_header *ethernet;  /* The ethernet header [1] */
	const struct sniff_ip *ip;              /* The IP header */
	const struct sniff_tcp *tcp;    
	ethernet=(struct ether_header*)pkt_data;        /* The TCP header */
	u_char *ptr;
	int size_ip;
	int size_tcp;
	int size_udp;
	int i;
	if(count==1)
	{
	printf("Start time and date of the capture is: %s\n",ctime(&header->ts.tv_sec)); 
	start=header->ts.tv_sec;
	}	
	end=header->ts.tv_sec;
	ethtype[p]=ntohs(ethernet->ether_type);
	p++;
	ip = (struct sniff_ip*)(pkt_data + 14);
	size_ip = IP_HL(ip)*4;
	if(size_ip==8 || size_ip==32 || size_ip==0)
	{
	size[count]=header->len;
	count++;
	return;
	}
	
	size[count]=header->len;
	fprintf(stdout,"source: %s \n",ether_ntoa((struct ether_header*)ethernet->ether_shost));
    	fprintf(stdout,"dest: %s \n",ether_ntoa((struct ether_header*)ethernet->ether_dhost));
	tcp = (struct sniff_tcp*)(pkt_data + 14 + size_ip);
	size_tcp = TH_OFF(tcp)*4;
	struct udphdr *udph = (struct udphdr*)(pkt_data + 14 + size_ip);
	
	if (size_ip==0) 
	{

		ip = (struct sniff_ip*)(pkt_data + 12+14);
		
		fprintf(stdout," prot %u \n ",ip->ip_p);
		//ipdst[to]=inet_ntoa(ip->ip_src);
		//printf("       To: %s\n", ipdst[to]);
		//printf("       To: %s\n", inet_ntoa(ip->ip_src));
		
		ip = (struct sniff_ip*)(pkt_data + 12);
		//ipsrc[to]=inet_ntoa(ip->ip_dst);
		//printf("       From ipsrc: %s\n",ipsrc[to]);
		
		//to++;
		count++;	
		printf("packet number is %d\n",count);	
				
		return;
	}
	
	/* print source and destination IP addresses */
	else
	{
		if(ip->ip_p==6)
		{
		tsport[p]=ntohs(tcp->th_sport);
		printf("   Src port: %d\n",tsport[p]);
		p++;
		printf("   Dst port: %d\n", ntohs(tcp->th_dport));
			if((tcp->th_flags & TH_ACK)!=0)
			{
			//printf("flag %X\n",tcp->th_flags);
			ack++;
			}
			if((tcp->th_flags & TH_RST)!=0)
			{
			//printf("flag %X\n",tcp->th_flags);
			rst++;
			}
			if((tcp->th_flags & TH_SYN)!=0)
			{
			//printf("flag %X\n",tcp->th_flags);
			syn++;
			}
			if((tcp->th_flags & TH_PUSH)!=0)
			{
			//printf("flag %X\n",tcp->th_flags);
			psh++;
			}
			if((tcp->th_flags & TH_FIN)!=0)
			{
			//printf("flag %X\n",tcp->th_flags);
			fin++;
			}
			if((tcp->th_flags & TH_URG)!=0)
			{
			//printf("flag %X\n",tcp->th_flags);
			urg++;
			}
			if((tcp->th_flags & TH_ECE)!=0)
			{
			//printf("flag %X\n",tcp->th_flags);
			ece++;
			}
			if((tcp->th_flags & TH_CWR)!=0)
			{
			//printf("flag %X\n",tcp->th_flags);
			cwr++;
			}
		//printf("   Flag: RST\n");
		}
				
		if(ip->ip_p==17)
		{
		printf("   Src port: %d\n", ntohs(udph->uh_sport));
		printf("   Dst port: %d\n", ntohs(udph->uh_dport));
		//printf("   checksum %X\n", ntohs(udph->uh_len));
		printf("   length %d\n",ntohs(udph->uh_ulen));
		}
	
	proto[p]=ip->ip_p;
	p1++;
	ipsrc[to]=inet_ntoa(ip->ip_src);
	//to++;
	
	//
	to++;
	ipdst[to]=inet_ntoa(ip->ip_dst);
	printf("       To : %s\n", ipdst[to]);
	count++;
	
	
	printf("packet number is %d\n",count);
	
	}
	
}