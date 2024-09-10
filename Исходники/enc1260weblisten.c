int midParseInt(int identifier,int fd, char *data, int len)
{
	int recvlen;
	int cmd = 0;
	int actdata = 0;
	//char logoname[15] = "logo.png";
	int ret = 0;
	int web_ret = SERVER_RET_OK;

	int need_send = 0;


	char senddata[1024] = {0};
	int totallen = 0;

	recvlen = recv(fd, data, len, 0);
	int out = 0;

//	if(recvlen < 0) {
//		return -1;
//	}

	if(recvlen < 0 || len != sizeof(cmd) + sizeof(int)) {
		web_ret = SERVER_RET_INVAID_PARM_LEN;
		need_send = 1;
		goto EXIT;
	}


	memcpy(&cmd, data, sizeof(int));
	memcpy(&actdata, data + sizeof(int), len - sizeof(int));

	PRINTF("cmd = 0x%04x\n", cmd);

	switch(cmd) {
		case MSG_GETINPUTTYPE:
			PRINTF("cmd = 0x%04x is MSG_GETINPUTTYPE.\n", cmd);
			ret = getinputType(actdata, &out);
			need_send = 1;
			break;

		case MSG_SETINPUTTYPE:
			PRINTF("cmd = 0x%04x is MSG_SETINPUTTYPE.\n", cmd);
			ret = setInputType(actdata, &out);
			need_send = 1;
			break;

			//case MSG_STOP_MULT:
			//	stopMultParse(fd, cmd, &actdata);
			//	break;

		case MSG_GETCPULOAD:
			PRINTF("cmd = 0x%04x is MSG_GETCPULOAD.\n", cmd);
			ret = getcpuload(actdata, &out);
			need_send = 1;
			break;

		case MSG_RESTORESET:
			PRINTF("cmd = 0x%04x is MSG_RESTORESET.\n", cmd);
			ret = restoresetparse(actdata, &out);
			need_send = 1;
			break;

		case MSG_GET_CTRL_PROTO:
			PRINTF("cmd = 0x%04x is MSG_GET_CTRL_PROTO.\n", cmd);
			need_send = 1;
			getCtrlProto(actdata, &out);
			break;

		case MSG_SET_CTRL_PROTO:
			PRINTF("cmd = 0x%04x is MSG_SET_CTRL_PROTO.\n", cmd);
			need_send = 1;
			setCtrlProto(actdata, &out);
			break;

			/*
			case MSG_SAVEPARAM:
				saveParams(fd, cmd, &actdata);
				break;
			*/
#if 0

		case MSG_GETDHCPFLAG:
			PRINTF("cmd = 0x%04x is MSG_GETDHCPFLAG.\n", cmd);
			need_send = 1;
			PRINTF("MSG_GETDHCPFLAG actdata = %d\n", actdata);
			webgetDHCPFlag(actdata, &out);
			break;

		case MSG_SETDHCPFLAG:
			PRINTF("cmd = 0x%04x is MSG_SETDHCPFLAG.\n", cmd);
			need_send = 1;
			websetDHCPFlag(actdata, &out);
			break;
#endif

		case MSG_SETCOLORSPACE:
			PRINTF("cmd = 0x%04x is MSG_SETCOLORSPACE.\n", cmd);
			need_send = 1;
			ret = setColorSpace(actdata, &out);
			break;

		case MSG_GETCOLORSPACE:
			PRINTF("cmd = 0x%04x is MSG_GETCOLORSPACE.\n", cmd);
			getColorSpace(&out);
			need_send = 1;
			break;

			//case MSG_GETHDCPVAL:
			//	getHDCPValue(fd, cmd, &actdata);
			//	break;

		case MSG_REBOOTSYS:
			PRINTF("cmd = 0x%04x is MSG_REBOOTSYS.\n", cmd);
			need_send = 1;
			rebootSys(actdata, &out);
			break;

		case MSG_GETHDCPVALUE:
			PRINTF("cmd = 0x%04x is MSG_GETHDCPVALUE.\n", cmd);
			need_send = 1;
			getHDCPValue(actdata, &out);
			break;

		case MSG_LOCK_RESOLUTION:
			PRINTF("cmd = 0x%04x is MSG_LOCK_RESOLUTION.\n", cmd);
			ret = DoLockResolution(actdata, &out);
			need_send = 1;
			break;

		case MSG_GETOUTPUTRESOLUTION:
			PRINTF("cmd = 0x%04x is MSG_GETOUTPUTRESOLUTION.\n", cmd);
			ret = webgetOutputResolution(actdata, &out);
			need_send = 1;
			break;

		case MSG_RESIZE_MODE:
			PRINTF("cmd = 0x%04x is MSG_RESIZE_MODE.\n", cmd);
			//	setResizeMode(fd, cmd, &actdata);
			ret = setResizeMode(actdata, &out);
			need_send = 1;
			break;

		case MSG_GETRESIZEMODE:
			PRINTF("cmd = 0x%04x is MSG_GETRESIZEMODE.\n", cmd);
			//getResizeMode(fd, cmd, &actdata);
			ret = getResizeMode(actdata, &out);
			need_send = 1;
			break;

		case MSG_GETENCODELV:
			PRINTF("cmd = 0x%04x is MSG_GETENCODELV.\n", cmd);
			ret = getEncodelevel(actdata, &out);

			need_send = 1;
			break;

		case MSG_SETENCODELV:
			PRINTF("cmd = 0x%04x is MSG_SETENCODELV.\n", cmd);
			ret = setEncodelevel(actdata, &out);

			need_send = 1;
			break;

		case MSG_GETSCENE:
			PRINTF("cmd = 0x%04x is MSG_GETSCENE.\n", cmd);
			need_send = 1;
			getSceneconfig(actdata, &out);
			break;

		case MSG_SETSCENE:
			PRINTF("cmd = 0x%04x is MSG_SETSCENE.\n", cmd);
			need_send = 1;
			ret = setSceneconfig(actdata, &out);
			break;

		case MSG_GETFRAMERATE:
			PRINTF("cmd = 0x%04x is MSG_GETFRAMERATE.\n", cmd);
			need_send = 1;
			getFrameRate(actdata, &out);
			break;

		case MSG_SETFRAMERATE:
			PRINTF("cmd = 0x%04x is MSG_SETFRAMERATE.\n", cmd);
			need_send = 1;
			ret = setFrameRate(actdata, &out);
			break;

		case MSG_GETIFRAMEINTERVAL:
			PRINTF("cmd = 0x%04x is MSG_GETIFRAMEINTERVAL.\n", cmd);
			need_send = 1;
			getIFrameInterval(actdata, &out);
			break;

			//case MSG_SETIFRAMEINTERVAL:
			//	PRINTF("cmd = 0x%04x is MSG_SETIFRAMEINTERVAL.\n", cmd);
			//	need_send = 1;
			//	ret = setIFrameInterval(actdata, &out);
			//	break;

		case MSG_GETBITRATE:
			PRINTF("cmd = 0x%04x is MSG_GETBITRATE.\n", cmd);
			need_send = 1;
			getBitRate(actdata, &out);
			break;

		case MSG_SETBITRATE:
			PRINTF("cmd = 0x%04x is MSG_SETBITRATE.\n", cmd);
			need_send = 1;
			ret = setBitRate(actdata, &out);
			break;


		case MSG_SETMUTE:
			PRINTF("cmd = 0x%04x is MSG_SETMUTE.\n", cmd);
			need_send = 1;
			ret = webSetMute(actdata, &out);
			break;

		case MSG_GETMUTE:
			PRINTF("cmd = 0x%04x is MSG_GETMUTE.\n", cmd);
			webGetMute(actdata, &out);
			need_send = 1;
			break;

			//stream_ouput
		case MSG_RTSP_GET_USED:
		case MSG_RTSP_DEL_SERVER:
		case MSG_MULT_GET_NUM:
		case MSG_MULT_GET_TS_RATE:
		case MSG_MULT_GET_RTP_RATE:
		case MSG_MULT_GET_RTPTS_RATE:
			app_web_stream_output_process_int(cmd, actdata, &out);
			need_send = 1;
			break;

			//case MSG_GETSHOWTEXTLOGO:
			//	PRINTF("cmd = 0x%04x is MSG_GETSHOWTEXTLOGO.\n", cmd);
			//	webgetShowLogoTextFlag(actdata, &out);
			//	need_send = 1;
			//	break;

			//	case MSG_SETSHOWTEXTLOGO:
			//		PRINTF("cmd = 0x%04x is MSG_SETSHOWTEXTLOGO.\n", cmd);
			//		ret = websetShowLogoTextFlag(actdata, &out);
			//		need_send = 1;
			//		break;
			//		case MSG_GET_SHOWTEXT_FLAG:
			//			out = app_get_textshow_flag();
			//			need_send = 1;
			//			break;
			//		case MSG_SET_SHOWTEXT_FLAG:
			//			out = app_set_textshow_flag(actdata);
			//			need_send = 1;
			//			break;
			//		case MSG_GET_SHOWLOGO_FLAG:
			//			out = app_get_logoshow_flag();
			//			need_send = 1;
			//			break;
			//		case MSG_SET_SHOWLOGO_FLAG:
			//			out = app_set_logoshow_flag(actdata);
			//			need_send = 1;
			//			break;

		default:
			PRINTF("unkonwn cmd = %04x\n", cmd);
			need_send = 1;
			web_ret = SERVER_RET_UNKOWN_CMD;
			break;
			//	case
	}

	if(ret < 0) {
		web_ret = SERVER_RET_INVAID_PARM_VALUE;
	}

EXIT:

	if(need_send == 1) {
		totallen = MSGINFOHEAD + sizeof(cmd) + sizeof(web_ret) + sizeof(out);
		msgPacket(identifier,senddata, INT_TYPE, totallen, cmd, web_ret);
		memcpy(senddata + (totallen - sizeof(out)), &out, sizeof(out));
		PRINTF("the cmd =%04x,the value=%d,the ret=%04x\n", cmd, out, web_ret);
		send(fd, senddata, totallen, 0);
	}

	return 0;
}