BOOL LogMng::WriteMsg(ULONG packetNo, LPCSTR msg, ULONG command, int opt, time_t t,
	ShareInfo *shareInfo, int64 *msg_id)
{
	U8str	buf(MAX_UDPBUF);
	char	*p = buf.Buf();

	if (msg_id) {
		*msg_id = 0;
	}

	p += strcpyz(p, LOGMSG_AT);
	p += strcpyz(p, Ctime(&t)); 
	p += strcpyz(p, " ");

	logMsg->packet_no = packetNo;
	logMsg->date = t;

	if (command & IPMSG_BROADCASTOPT) {
		p += strcpyz(p, LoadStrU8(IDS_BROADCASTLOG));
	}

	if (command & IPMSG_AUTORETOPT) {
		p += strcpyz(p, LoadStrU8(IDS_AUTORETLOG));
		logMsg->flags |= DB_FLAG_AUTOREP;
	}

	if (command & IPMSG_MULTICASTOPT) {
		p += strcpyz(p, LoadStrU8(IDS_MULTICASTLOG));
		logMsg->flags |= DB_FLAG_MULTI;
	}

	if (command & IPMSG_ENCRYPTOPT) {
		int		id = 0;
		if (opt & LOG_SIGN2_OK) {
			id = IDS_ENCRYPT2_SIGNED2;
			logMsg->flags |= DB_FLAG_SIGNED2|DB_FLAG_RSA2;
		}
		else if (opt & LOG_SIGN_OK) {
			id = IDS_ENCRYPT2_SIGNED;
			logMsg->flags |= DB_FLAG_SIGNED|DB_FLAG_RSA2;
		}
		else if (opt & LOG_SIGN_ERR) {
			id = IDS_ENCRYPT2_ERROR;
			logMsg->flags |= DB_FLAG_SIGNERR|DB_FLAG_RSA2;
		}
		else if (opt & LOG_ENC2) {
			id = IDS_ENCRYPT2;
			logMsg->flags |= DB_FLAG_RSA2;
		}
		else {
			id = IDS_ENCRYPT;
			logMsg->flags |= DB_FLAG_RSA;
		}
		p += strcpyz(p, LoadStrU8(id));
	}
	else if (opt & LOG_UNAUTH) {
		p += strcpyz(p, LoadStrU8(IDS_UNAUTHORIZED));
		logMsg->flags |= DB_FLAG_UNAUTH;
	}

	if (command & IPMSG_SECRETOPT)
	{
		if (command & IPMSG_PASSWORDOPT) {
			p += strcpyz(p, LoadStrU8(IDS_PASSWDLOG));
		}
		else {
			p += strcpyz(p, LoadStrU8(IDS_SECRETLOG));
		}
		logMsg->flags |= DB_FLAG_SEAL;

		// 未開封フラグのセット
		for (auto itr=logMsg->host.begin(); itr != logMsg->host.end(); itr++) {
			if ((logMsg->flags & DB_FLAG_FROM) == 0 || itr == logMsg->host.begin()) {
				itr->flags = DB_FLAGMH_UNOPEN;
			}
		}
		if ((logMsg->flags & DB_FLAG_FROM)) {
			logMsg->flags |= DB_FLAG_UNOPENR;
		}
	}
	if (opt & LOG_DELAY) {
		p += strcpyz(p, LoadStrU8(IDS_DELAYSEND));
		logMsg->flags |= DB_FLAG_DELAY;
	}

	if (shareInfo && (command & IPMSG_FILEATTACHOPT))
	{
		int	clip_num = 0;
		int	noclip_num = 0;

		for (int i=0; i < shareInfo->fileCnt; i++) {
			if (GET_MODE(shareInfo->fileInfo[i]->Attr()) == IPMSG_FILE_CLIPBOARD) {
				clip_num++;
			}
			else {
				noclip_num++;
			}
		}
		p += strcpyz(p, "\r\n  ");
		if (clip_num || noclip_num) {
			int id = clip_num ? noclip_num ? IDS_FILEWITHCLIP : IDS_WITHCLIP : IDS_FILEATTACH;
			p += strcpyz(p, LoadStrU8(id));
			p += strcpyz(p, " ");
		}

		for (int i=0; i < shareInfo->fileCnt && p - buf.Buf() < MAX_BUF; i++)
		{
			char	fname[MAX_PATH_U8];
			ForcePathToFname(shareInfo->fileInfo[i]->Fname(), fname);
			p += snprintfz(p, MAX_BUF, "%s%s", fname, i+1 == shareInfo->fileCnt ? "" : ", ");

			if (GET_MODE(shareInfo->fileInfo[i]->Attr()) == IPMSG_FILE_CLIPBOARD) {
				LogClip	clip;
				clip.fname = fname;
				SetClipDimension(cfg, &clip);
				logMsg->clip.push_back(clip);
				logMsg->flags |= DB_FLAG_CLIP;
			}
			else {
				logMsg->files.push_back(fname);
				logMsg->flags |= DB_FLAG_FILE;
			}
		}
	}
	p += strcpyz(p, "\r\n");
	p += strcpyz(p, LOGMSG_HEAD_END);

	Wstr	wmsg(msg);
	LocalNewLineToUnixW(wmsg.s(), wmsg.Buf(), wmsg.Len()+1);
	logMsg->body = wmsg;
	logMsg->lines = get_linenum_n(logMsg->body.s(), logMsg->body.StripLen());

	BOOL ret = Write(buf.s()) && Write(msg) && Write("\r\n\r\n");

#ifdef IPMSG_PRO
#define LOGMNG_WRITEMSG
#include "miscext.dat"
#undef  LOGMNG_WRITEMSG
#endif


	if (logDb && cfg->LogCheck) {
		logDb->InsertOneData(logMsg);
		PostMessage(GetMainWnd(), WM_LOGVIEW_UPDATE,
			MakeMsgIdHigh(logMsg->msg_id), MakeMsgIdLow(logMsg->msg_id));
		if (msg_id) {
			*msg_id = logMsg->msg_id;
		}
	}
	logMsg->Init();

	return	ret;
}