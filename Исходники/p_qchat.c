int qcs__parse_qchat_msg(
	const char * pmsg, ssize_t pmsg_len,
	qcs_msg * msg )
{
	char ch;

	assert( pmsg && pmsg_len && msg );

	qcs__cleanupmsg(msg);

	GETCHAR(ch);
	switch(ch) {
	case '0':
		msg->msg = QCS_MSG_REFRESH_REQUEST;
		GETSTR(msg->src);
		break;
	case '1':
		msg->msg = QCS_MSG_REFRESH_ACK;
		GETSTR(msg->dst);
		GETSTR(msg->src);
		GETMODE(msg->umode);
		if( pmsg_len ) {
			/* check for `ACTIVE' bit in qc16 messages */
			GETACTIVE(msg->uactive);
		} else {
			/* uactive=TRUE per default */
			msg->uactive = 1;
		}
		break;
	case '2':
		msg->msg = QCS_MSG_CHANNEL_BROADCAST;
		GETCHAN(msg->chan);
		GETSTR(msg->src);
		GETSTR(msg->text);
		break;
	case '4':
		msg->msg = QCS_MSG_CHANNEL_JOIN;
		GETSTR(msg->src);
		GETCHAN(msg->chan);
		GETMODE(msg->umode);
		/*dummy byte skipped*/
		break;
	case '5':
		msg->msg = QCS_MSG_CHANNEL_LEAVE;
		GETSTR(msg->src);
		GETCHAN(msg->chan);
		/*dummy*/
		break;
	case 'A':
		msg->msg = QCS_MSG_CHANNEL_ME;
		GETCHAN(msg->chan);
		GETSTR(msg->src);
		GETSTR(msg->text);
		break;
	case '7':
		msg->msg = QCS_MSG_MESSAGE_ACK;
		GETMODE(msg->umode);
		GETSTR(msg->dst);
		GETSTR(msg->src);
		GETCHAR(ch);	/* dummy */
		GETSTR(msg->text);
		break;
	case 'E':
		msg->msg = QCS_MSG_MESSAGE_MASS;
		GETSTR(msg->src);
		GETSTR(msg->dst);
		GETSTR(msg->text);
		break;
	case '6':
		msg->msg = QCS_MSG_MESSAGE_SEND;
		GETSTR(msg->src);
		GETSTR(msg->dst);
		GETSTR(msg->text);
		break;
	case '3':
		msg->msg = QCS_MSG_RENAME;
		GETSTR(msg->src);
		GETSTR(msg->text);
		/*dummy*/
		break;
	case 'D':
		msg->msg = QCS_MSG_MODE_CHANGE;
		GETSTR(msg->src);
		GETMODE(msg->umode);
		/* dummy byte passed by */
		break;
	case 'M':
		msg->msg = QCS_MSG_ACTIVE_CHANGE;
		GETSTR(msg->src);
		GETACTIVE(msg->uactive);
		break;
	case 'C':
		msg->msg = QCS_MSG_TOPIC_REPLY;
		GETSTR(msg->dst);
		GETSTR(msg->text);
		
		/* add "Main" as msg->chan */
		msg->chan = malloc(5);
		if(!msg->chan) {
			qcs__cleanupmsg(msg);
			errno = ENOMEM;
			return 0;
		}
		memcpy(msg->chan, "Main", 5);
		break;
	case 'B':
		msg->msg = QCS_MSG_TOPIC_CHANGE;
		GETSTR(msg->text);
		
		/* fill in "Main": this is unsupported in qc,
		 * thus we need to fill it in */
		msg->chan = malloc(5);
		if(!msg->chan) {
			qcs__cleanupmsg(msg);
			errno = ENOMEM;
			return 0;
		}
		memcpy(msg->chan, "Main", 5);
		break;
	case 'G':
		msg->msg = QCS_MSG_INFO_REPLY;
		GETSTR(msg->dst);
		GETSTR(msg->src);
		GETSTR(msg->text);
		/* skip 3 strings - not used */
		GETSTR(msg->chan);free(msg->chan);
		GETSTR(msg->chan);free(msg->chan);
		GETSTR(msg->chan);free(msg->chan);
		GETSTR(msg->chan);
		GETSTR(msg->supp);
		break;
	case 'F':
		msg->msg = QCS_MSG_INFO_REQUEST;
		GETSTR(msg->dst);
		GETSTR(msg->src);
		break;
	case 'K':
		msg->msg = QCS_MSG_CHANMEMBER_REPLY;
		GETSTR(msg->dst);
		GETSTR(msg->chan);
		GETSTR(msg->src);
		break;
	case 'L':
		msg->msg = QCS_MSG_CHANMEMBER_REQUEST;
		GETSTR(msg->src);
		break;
	case 'O':
		msg->msg = QCS_MSG_CHANLIST_REPLY;
		GETSTR(msg->dst);
		GETSTR(msg->chan);
		break;
	case 'N':
		msg->msg = QCS_MSG_CHANLIST_REQUEST;
		GETSTR(msg->src);
		break;
	case 'H':
		GETCHAR(ch);
		switch(ch) {
		case '1': msg->msg = QCS_MSG_BEEP_ACK;	break;
		case '0': msg->msg = QCS_MSG_BEEP_SEND;	break;
		default: errno = ENOMSG;
			 return 0;
		}
		GETSTR(msg->dst);
		GETSTR(msg->src);
		/* dummy byte when 'H1' */
		break;
	case 'J':
		GETCHAR(ch);
		switch(ch) {
		case '0':msg->msg = QCS_MSG_PRIVATE_OPEN;	break;
		case '1':msg->msg = QCS_MSG_PRIVATE_CLOSE;	break;
		case '2':msg->msg = QCS_MSG_PRIVATE_TEXT;	break;
		case '3':msg->msg = QCS_MSG_PRIVATE_ME;		break;
		default: errno = ENOMSG;
			 return 0;
		}
		GETSTR(msg->src);
		GETSTR(msg->dst);
		if(ch=='2'||ch=='3') {
			GETSTR(msg->text);
		}
		break;
	default:
		errno = ENOMSG;
		return 0;
	}
	return 1;
}