static void
dispatch_socket_msg(struct otu *u, const struct skynet_socket_message * message, int sz) {
	struct skynet_context * ctx = u->ctx;

	switch(message->type) {

	case SKYNET_SOCKET_TYPE_CONNECT: {
		assert (message->id == u->service_id);
		break;
		}

	case SKYNET_SOCKET_TYPE_UDP: {
		char* pkt = message->buffer;
		int pkt_sz = message->ud;
		int addr_sz = 0;
		const char * addr = skynet_socket_udp_address(message, &addr_sz);
		char* last_err = NULL;

		//Ver len check
		if(pkt_sz < sizeof(ot_pkt_hdr_t)){
			last_err = "1.ShortHdr.";
			goto exit_drop;
		}

		ot_pkt_hdr_t *hdr = (ot_pkt_hdr_t *)pkt;
		u16_t hdr_len = ntohs(hdr->len);

		if(hdr_len > pkt_sz || hdr_len < sizeof(ot_pkt_hdr_t) || hdr_len > OT_PACKET_SIZE_MAX){		//len check
			last_err = "2.HdrLenErr.";
			goto exit_drop;
		}

		if(hdr->proto_ver != OT_PROTO_VER_V3A){
			last_err = "3.HdrVerErr.";
			goto exit_drop;
		}

#define HDR_ONLY (hdr_len == sizeof(ot_pkt_hdr_t))
#define DID_IS_BROADCAST (IS_ALL_FF(hdr->did.byte, sizeof(hdr->did.byte)))

		if(HDR_ONLY){

			//时间戳请求处理
			if(DID_IS_BROADCAST){	

				hdr->ts = htonl(skynet_now()/100 + skynet_starttime());

				//int err = 
				skynet_socket_udp_send(ctx, message->id, addr, pkt, pkt_sz);

			}

			//保活
			else {

 				uint64_t did64 = ntohll(hdr->did.u64);
				int idx = hashid64_lookup(&u->hash, did64);
				if (idx >= 0) {
					struct udp_peer *p = &u->peer[idx];
					(void)p;
					//dispatch_msg(u, p, message->id, message->buffer, message->ud);
					goto exit_drop;

				} else {

					//todo 提交DID未知请求
					goto exit_drop;
				}


			}


		}


		break;


		//get key, decrypt packet.

		//dispatch_msg


exit_drop:
		skynet_free(message->buffer);

		break;
	}


	default:
		skynet_error(ctx, "OTU: unknown type(%d)", message->type);
		break;
	}
}