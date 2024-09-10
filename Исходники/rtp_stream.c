RTPStream *RP_NewStream(RTPClient *rtp, GF_SDPMedia *media, GF_SDPInfo *sdp, RTPStream *input_stream)
{
	GF_RTSPRange *range;
	RTPStream *tmp;
	GF_RTPMap *map;
	u32 i, ESID, ODID, ssrc, rtp_seq, rtp_time;
	Bool force_bcast = 0;
	Double Start, End;
	Float CurrentTime;
	u16 rvc_predef = 0;
	char *rvc_config_att = NULL;
	u32 s_port_first, s_port_last;
	GF_X_Attribute *att;
	Bool is_migration = 0;
	char *ctrl;
	GF_SDPConnection *conn;
	GF_RTSPTransport trans;
	u32 mid, prev_stream, base_stream;

	//extract all relevant info from the GF_SDPMedia
	Start = 0.0;
	End = -1.0;
	CurrentTime = 0.0f;
	ODID = 0;
	ESID = 0;
	ctrl = NULL;
	range = NULL;
	s_port_first = s_port_last = 0;
	ssrc = rtp_seq = rtp_time = 0;
	mid = prev_stream = base_stream = 0;
	i=0;
	while ((att = (GF_X_Attribute*)gf_list_enum(media->Attributes, &i))) {
		if (!stricmp(att->Name, "control")) ctrl = att->Value;
		else if (!stricmp(att->Name, "gpac-broadcast")) force_bcast = 1;
		else if (!stricmp(att->Name, "mpeg4-esid") && att->Value) ESID = atoi(att->Value);
		else if (!stricmp(att->Name, "mpeg4-odid") && att->Value) ODID = atoi(att->Value);
		else if (!stricmp(att->Name, "range") && !range) range = gf_rtsp_range_parse(att->Value);
		else if (!stricmp(att->Name, "x-stream-state") ) {
			sscanf(att->Value, "server-port=%u-%u;ssrc=%X;npt=%g;seq=%u;rtptime=%u",
			       &s_port_first, &s_port_last, &ssrc, &CurrentTime, &rtp_seq, &rtp_time);
			is_migration = 1;
		}
		else if (!stricmp(att->Name, "x-server-port") ) {
			sscanf(att->Value, "%u-%u", &s_port_first, &s_port_last);
		} else if (!stricmp(att->Name, "rvc-config-predef")) {
			rvc_predef = atoi(att->Value);
		} else if (!stricmp(att->Name, "rvc-config")) {
			rvc_config_att = att->Value;
		} else if (!stricmp(att->Name, "mid")) {
			sscanf(att->Value, "L%d", &mid);
		} else if (!stricmp(att->Name, "depend")) {
			char buf[3000];
			memset(buf, 0, 3000);
			sscanf(att->Value, "%*d lay L%d %*s %s", &base_stream, buf);
			if (!strlen(buf))
				sscanf(att->Value, "%*d lay %s", buf);
			sscanf(buf, "L%d", &prev_stream);
		}
	}

	if (range) {
		Start = range->start;
		End = range->end;
		gf_rtsp_range_del(range);
	}

	/*check connection*/
	conn = sdp->c_connection;
	if (conn && (!conn->host || !strcmp(conn->host, "0.0.0.0"))) conn = NULL;

	if (!conn) conn = (GF_SDPConnection*)gf_list_get(media->Connections, 0);
	if (conn && (!conn->host || !strcmp(conn->host, "0.0.0.0"))) conn = NULL;

	if (!conn) {
		/*RTSP RFC recommends an empty "c= " line but some server don't send it. Use session info (o=)*/
		if (!sdp->o_net_type || !sdp->o_add_type || strcmp(sdp->o_net_type, "IN")) return NULL;
		if (strcmp(sdp->o_add_type, "IP4") && strcmp(sdp->o_add_type, "IP6")) return NULL;
	} else {
		if (strcmp(conn->net_type, "IN")) return NULL;
		if (strcmp(conn->add_type, "IP4") && strcmp(conn->add_type, "IP6")) return NULL;
	}
	/*do we support transport*/
	if (strcmp(media->Profile, "RTP/AVP") && strcmp(media->Profile, "RTP/AVP/TCP")
	        && strcmp(media->Profile, "RTP/SAVP") && strcmp(media->Profile, "RTP/SAVP/TCP")
	   ) return NULL;

	/*check RTP map. For now we only support 1 RTPMap*/
	if (media->fmt_list || (gf_list_count(media->RTPMaps) > 1)) return NULL;

	/*check payload type*/
	map = (GF_RTPMap*)gf_list_get(media->RTPMaps, 0);

	/*this is an ESD-URL setup, we likely have namespace conflicts so overwrite given ES_ID
	by the app one (client side), but keep control (server side) if provided*/
	if (input_stream) {
		ESID = input_stream->ES_ID;
		if (!ctrl) ctrl = input_stream->control;
		tmp = input_stream;
	} else {
		tmp = RP_FindChannel(rtp, NULL, ESID, NULL, 0);
		if (tmp) return NULL;

		GF_SAFEALLOC(tmp, RTPStream);
		tmp->owner = rtp;
	}

	/*create an RTP channel*/
	tmp->rtp_ch = gf_rtp_new();
	if (ctrl) tmp->control = gf_strdup(ctrl);
	tmp->ES_ID = ESID;
	tmp->OD_ID = ODID;
	tmp->mid = mid;
	tmp->prev_stream = prev_stream;
	tmp->base_stream = base_stream;

	memset(&trans, 0, sizeof(GF_RTSPTransport));
	trans.Profile = media->Profile;
	trans.source = conn ? conn->host : sdp->o_address;
	trans.IsUnicast = gf_sk_is_multicast_address(trans.source) ? 0 : 1;
	if (!trans.IsUnicast) {
		trans.port_first = media->PortNumber;
		trans.port_last = media->PortNumber + 1;
		trans.TTL = conn ? conn->TTL : 0;
	} else {
		trans.client_port_first = media->PortNumber;
		trans.client_port_last = media->PortNumber + 1;
		trans.port_first = s_port_first ? s_port_first : trans.client_port_first;
		trans.port_last = s_port_last ? s_port_last : trans.client_port_last;
	}

	if (gf_rtp_setup_transport(tmp->rtp_ch, &trans, NULL) != GF_OK) {
		RP_DeleteStream(tmp);
		return NULL;
	}
	/*setup depacketizer*/
	tmp->depacketizer = gf_rtp_depacketizer_new(media, rtp_sl_packet_cbk, tmp);
	if (!tmp->depacketizer) {
		RP_DeleteStream(tmp);
		return NULL;
	}
	/*setup channel*/
	gf_rtp_setup_payload(tmp->rtp_ch, map);

//	tmp->status = NM_Disconnected;

	ctrl = (char *) gf_modules_get_option((GF_BaseInterface *) gf_service_get_interface(rtp->service), "Streaming", "DisableRTCP");
	if (!ctrl || stricmp(ctrl, "yes")) tmp->flags |= RTP_ENABLE_RTCP;

	/*setup NAT keep-alive*/
	ctrl = (char *) gf_modules_get_option((GF_BaseInterface *) gf_service_get_interface(rtp->service), "Streaming", "NATKeepAlive");
	if (ctrl) gf_rtp_enable_nat_keepalive(tmp->rtp_ch, atoi(ctrl));

	tmp->range_start = Start;
	tmp->range_end = End;
	if (End != -1.0) tmp->flags |= RTP_HAS_RANGE;

	if (force_bcast) tmp->flags |= RTP_FORCE_BROADCAST;

	if (is_migration) {
		tmp->current_start = (Double) CurrentTime;
		tmp->check_rtp_time = RTP_SET_TIME_RTP;
		gf_rtp_set_info_rtp(tmp->rtp_ch, rtp_seq, rtp_time, ssrc);
		tmp->status = RTP_SessionResume;
	}

	if (rvc_predef) {
		tmp->depacketizer->sl_map.rvc_predef = rvc_predef ;
	} else if (rvc_config_att) {
		char *rvc_data=NULL;
		u32 rvc_size;
		Bool is_gz = 0;
		if (!strncmp(rvc_config_att, "data:application/rvc-config+xml", 32) && strstr(rvc_config_att, "base64") ) {
			char *data = strchr(rvc_config_att, ',');
			if (data) {
				rvc_size = (u32) strlen(data) * 3 / 4 + 1;
				rvc_data = gf_malloc(sizeof(char) * rvc_size);
				rvc_size = gf_base64_decode(data, (u32) strlen(data), rvc_data, rvc_size);
				rvc_data[rvc_size] = 0;
			}
			if (!strncmp(rvc_config_att, "data:application/rvc-config+xml+gz", 35)) is_gz = 1;
		} else if (!strnicmp(rvc_config_att, "http://", 7) || !strnicmp(rvc_config_att, "https://", 8) ) {
			char *mime;
			if (gf_dm_get_file_memory(rvc_config_att, &rvc_data, &rvc_size, &mime) == GF_OK) {
				if (mime && strstr(mime, "+gz")) is_gz = 1;
				if (mime) gf_free(mime);
			}
		}
		if (rvc_data) {
			if (is_gz) {
#ifdef GPAC_DISABLE_ZLIB
				fprintf(stderr, "Error: no zlib support - RVC not supported in RTP\n");
				return NULL;
#endif
				gf_gz_decompress_payload(rvc_data, rvc_size, &tmp->depacketizer->sl_map.rvc_config, &tmp->depacketizer->sl_map.rvc_config_size);
				gf_free(rvc_data);
			} else {
				tmp->depacketizer->sl_map.rvc_config = rvc_data;
				tmp->depacketizer->sl_map.rvc_config_size = rvc_size;
			}
		}
	}

	return tmp;
}