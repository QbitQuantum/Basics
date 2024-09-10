void gf_rtsp_set_response_value(GF_RTSPResponse *rsp, char *Header, char *Value)
{
	char LineBuffer[400], buf[1000], param_name[100], param_val[1000];
	s32 LinePos, Pos, nPos, s_val;
	GF_RTPInfo *info;
	GF_RTSPTransport *trans;
	GF_X_Attribute *x_Att;

	if (!stricmp(Header, "Accept")) rsp->Accept = gf_strdup(Value);
	else if (!stricmp(Header, "Accept-Encoding")) rsp->Accept_Encoding = gf_strdup(Value);
	else if (!stricmp(Header, "Accept-Language")) rsp->Accept_Language = gf_strdup(Value);
	else if (!stricmp(Header, "Allow")) rsp->Allow = gf_strdup(Value);
	else if (!stricmp(Header, "Authorization")) rsp->Authorization = gf_strdup(Value);
	else if (!stricmp(Header, "Bandwidth")) sscanf(Value, "%u", &rsp->Bandwidth);
	else if (!stricmp(Header, "Blocksize")) sscanf(Value, "%u", &rsp->Blocksize);
	else if (!stricmp(Header, "Cache-Control")) rsp->Cache_Control = gf_strdup(Value);
	else if (!stricmp(Header, "Conference")) rsp->Conference = gf_strdup(Value);
	else if (!stricmp(Header, "Connection")) rsp->Connection = gf_strdup(Value);
	else if (!stricmp(Header, "Content-Base")) rsp->Content_Base = gf_strdup(Value);	
	else if (!stricmp(Header, "Content-Encoding")) rsp->Content_Encoding = gf_strdup(Value);	
	else if (!stricmp(Header, "Content-Length")) sscanf(Value, "%u", &rsp->Content_Length);
	else if (!stricmp(Header, "Content-Language")) rsp->Content_Language = gf_strdup(Value);	
	else if (!stricmp(Header, "Content-Location")) rsp->Content_Location = gf_strdup(Value);	
	else if (!stricmp(Header, "Content-Type")) rsp->Content_Type = gf_strdup(Value);	
	else if (!stricmp(Header, "CSeq")) sscanf(Value, "%u", &rsp->CSeq);
	else if (!stricmp(Header, "Date")) rsp->Date = gf_strdup(Value);	
	else if (!stricmp(Header, "Expires")) rsp->Expires = gf_strdup(Value);	
	else if (!stricmp(Header, "From")) rsp->From = gf_strdup(Value);	
	else if (!stricmp(Header, "Host")) rsp->Host = gf_strdup(Value);	
	else if (!stricmp(Header, "If-Match")) rsp->If_Match = gf_strdup(Value);	
	else if (!stricmp(Header, "If-Modified-Since")) rsp->If_Modified_Since = gf_strdup(Value);	
	else if (!stricmp(Header, "Last-Modified")) rsp->Last_Modified = gf_strdup(Value);	
	else if (!stricmp(Header, "Location")) rsp->Location = gf_strdup(Value);	
	else if (!stricmp(Header, "Proxy-Authenticate")) rsp->Proxy_Authenticate = gf_strdup(Value);	
	else if (!stricmp(Header, "Proxy-Require")) rsp->Proxy_Require = gf_strdup(Value);	
	else if (!stricmp(Header, "Public")) rsp->Public = gf_strdup(Value);	
	else if (!stricmp(Header, "Referer")) rsp->Referer = gf_strdup(Value);	
	else if (!stricmp(Header, "Require")) rsp->Require = gf_strdup(Value);	
	else if (!stricmp(Header, "Retry-After")) rsp->Retry_After = gf_strdup(Value);	
	else if (!stricmp(Header, "Scale")) sscanf(Value, "%lf", &rsp->Scale);
	else if (!stricmp(Header, "Server")) rsp->Server = gf_strdup(Value);	
	else if (!stricmp(Header, "Speed")) sscanf(Value, "%lf", &rsp->Speed);
	else if (!stricmp(Header, "Timestamp")) rsp->Timestamp = gf_strdup(Value);	
	else if (!stricmp(Header, "Unsupported")) rsp->Unsupported = gf_strdup(Value);	
	else if (!stricmp(Header, "User-Agent")) rsp->User_Agent = gf_strdup(Value);	
	else if (!stricmp(Header, "Vary")) rsp->Vary = gf_strdup(Value);	
	else if (!stricmp(Header, "Via")) rsp->Vary = gf_strdup(Value);	
	else if (!stricmp(Header, "WWW_Authenticate")) rsp->Vary = gf_strdup(Value);	
	else if (!stricmp(Header, "Transport")) {
		LinePos = 0;
		while (1) {
			LinePos = gf_token_get(Value, LinePos, "\r\n", LineBuffer, 400);
			if (LinePos <= 0) return;
			trans = gf_rtsp_transport_parse(Value);
			if (trans) gf_list_add(rsp->Transports, trans);
		}
	}
	//Session
	else if (!stricmp(Header, "Session")) {
		LinePos = gf_token_get(Value, 0, ";\r\n", LineBuffer, 400);
		rsp->Session = gf_strdup(LineBuffer);
		//get timeout if any
		if (Value[LinePos] == ';') {
			LinePos += 1;
			LinePos = gf_token_get(Value, LinePos, ";\r\n", LineBuffer, 400);
			//default
			rsp->SessionTimeOut = 60;
			sscanf(LineBuffer, "timeout=%u", &rsp->SessionTimeOut);
		}
	}

	//Range
	else if (!stricmp(Header, "Range")) rsp->Range = gf_rtsp_range_parse(Value);
	//RTP-Info
	else if (!stricmp(Header, "RTP-Info")) {
		LinePos = 0;
		while (1) {
			LinePos = gf_token_get(Value, LinePos, ",\r\n", LineBuffer, 400);
			if (LinePos <= 0) return;

			GF_SAFEALLOC(info, GF_RTPInfo);
			Pos = 0;
			while (1) {	
				Pos = gf_token_get(LineBuffer, Pos, " ;", buf, 1000);
				if (Pos <= 0) break;
				if (strstr(buf, "=")) {
					nPos = gf_token_get(buf, 0, "=", param_name, 100);
					nPos += 1;
					nPos = gf_token_get(buf, nPos, "", param_val, 1000);
				} else {
					strcpy(param_name, buf);
				}
				if (!stricmp(param_name, "url")) info->url = gf_strdup(param_val);
				else if (!stricmp(param_name, "seq")) sscanf(param_val, "%u", &info->seq);
				else if (!stricmp(param_name, "rtptime")) {
					sscanf(param_val, "%i", &s_val);
					info->rtp_time = (s_val>0) ? s_val : 0;
				}
				else if (!stricmp(param_name, "ssrc")) {
					sscanf(param_val, "%i", &s_val);
					info->ssrc = (s_val>0) ? s_val : 0;
				}
			}
			gf_list_add(rsp->RTP_Infos, info);
		}
	}
	//check for extended attributes
	else if (!strnicmp(Header, "x-", 2)) {
		x_Att = (GF_X_Attribute*)gf_malloc(sizeof(GF_X_Attribute));
		x_Att->Name = gf_strdup(Header+2);
		x_Att->Value = NULL;
		if (Value && strlen(Value)) x_Att->Value = gf_strdup(Value);
		gf_list_add(rsp->Xtensions, x_Att);
	}
	//unknown field - skip it
}