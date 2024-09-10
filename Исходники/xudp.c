bool 
UdpSend( link_t *link, udp_hdr_t *udpHdr, ip_hdr_t *ipHdr, udp_descr_t *descr )
{
bool     success = FALSE;
u8       *frame;
static i8       UdpSendaddr[32];
i32      length;
    
    length = LinkLength(link);
    frame = (u8 *)x_malloc(length);  
    if(frame!=0) {
        if(LinkCopy(link, frame, (u16)length)) {
#ifdef XSTK_NUCNET
#ifdef XLIB_XSNMP
			plist[0].charptr = (i8 *)Inet_NtoA(ipHdr->dst);
			plist[1].intval  = udpHdr->dst;
            x_sprintf(UdpSendaddr,"udp:%s:%d"); 
#else
            sprintf(UdpSendaddr,"udp:%s:%d",Inet_NtoA(ipHdr->dst),udpHdr->dst); 
#endif
#else
#ifdef XLIB_XSNMP
			plist[0].charptr = (i8 *)Inet_NtoA(x_htonl(ipHdr->dst));
			plist[1].intval  = udpHdr->dst;
            x_sprintf(UdpSendaddr,"udp:%s:%d"); 
#else
            sprintf(UdpSendaddr,"udp:%s:%d",Inet_NtoA(x_htonl(ipHdr->dst)),udpHdr->dst); 
#endif
#endif
        
            if(NwDgSendTo(UdpSendaddr, frame, length, udpHdr->src)) {
                success = TRUE;
			} else {
			}
        }
       x_free(frame);
    }
    
    if(success) {
        udpStat.outDatagrams++;
	} else {
        udpStat.outErrors++;
	}
       
    return success;         
}