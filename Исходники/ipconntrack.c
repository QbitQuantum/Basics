// track a tcp stream.  returns the difference between this packet's
// SEQ and the expected next SEQ.
int
IpConnTrack_track_stream(IpConnTrack *self, IpConn *conn, 
			 IpConnTcpQueue *queue, 
			 struct netpkt *pkt, 
			 int buffer_stream) {
    netpkt_tcp *tcp;
    netpkt_udp *udp;
    tcp_seq_t seq;
    char *dst, *src;
    int len, diff=0;
    
    do {
	tcp = pkt->pkt_tcp;
	udp = pkt->pkt_udp;
	src = pkt->pkt_msg;
	len = pkt->pkt_len;
	diff = 0;
	
	if( tcp ) {
	    if( tcp_ack(tcp) ) {
		queue->ack = ntohl(tcp->ack_seq);
	    }
	    queue->win = ntohs(tcp->window);

	    seq = ntohl(tcp->seq);

	    if( !queue->seq_ok ) {
		queue->seq_syn = seq;
		queue->seq =  seq;
		queue->seq_ok = 1;
		if( tcp_syn(tcp) ) {
		    queue->seq++;
		}
		else {
		    conn->conn_pkt_flags |= CONN_PKT_TCP_MISSED_SYN;
		}
	    }
	
	    diff = tcp_seq_diff(seq, queue->seq);

	    if( diff > 1 ) {
		// ignore packets (far) in the future
		conn->conn_pkt_flags |= CONN_PKT_TCP_FUTURE_SEQ;
		break;
	    }

	    src += -diff;
	    len -= -diff;
	    if( len <= 0 ) {
		// ignore past packets
		break;
	    }
	    queue->seq += len;
	}
	else if( udp ) {
	}
	
	if( buffer_stream ) {
	    dst = (char*)array_add(&queue->buf, len);
	    assertb(dst);
	    memcpy(dst, src, len);
	}
    } while(0);
    
    return diff;
}