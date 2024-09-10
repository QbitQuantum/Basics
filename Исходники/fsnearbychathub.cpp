// If input of the form "/20foo" or "/20 foo", returns "foo" and channel 20.
// Otherwise returns input and channel 0.
LLWString FSNearbyChat::stripChannelNumber(const LLWString &mesg, S32* channel, S32* last_channel, bool* is_set)
{
	*is_set = false;

	if (mesg[0] == '/'
		&& mesg[1] == '/')
	{
		// This is a "repeat channel send"
		*is_set = true;
		*channel = *last_channel;
		return mesg.substr(2, mesg.length() - 2);
	}
	else if (mesg[0] == '/'
			 && mesg[1]
	//<FS:TS> FIRE-11412: Allow saying /-channel for negative numbers
	//        (this code was here; documenting for the future)
			 //&& LLStringOps::isDigit(mesg[1]))
			 && (LLStringOps::isDigit(mesg[1])
				 || (mesg[1] == '-'
				 	&& mesg[2]
				 	&& LLStringOps::isDigit(mesg[2]))))
	//</FS:TS> FIRE-11412
	{
		// This a special "/20" speak on a channel
		*is_set = true;
		S32 pos = 0;
		//<FS:TS> FIRE-11412: Allow saying /-channel for negative numbers
		//        (this code was here; documenting for the future)
		if (mesg[1] == '-')
		{
			pos++;
		}
		//</FS:TS> FIRE-11412
		
		// Copy the channel number into a string
		LLWString channel_string;
		llwchar c;
		do
		{
			c = mesg[pos + 1];
			channel_string.push_back(c);
			pos++;
		}
		while (c && pos < 64 && LLStringOps::isDigit(c));
		
		// Move the pointer forward to the first non-whitespace char
		// Check isspace before looping, so we can handle "/33foo"
		// as well as "/33 foo"
		while (c && iswspace(c))
		{
			c = mesg[pos+1];
			pos++;
		}
		
		*last_channel = strtol(wstring_to_utf8str(channel_string).c_str(), NULL, 10);
		//<FS:TS> FIRE-11412: Allow saying /-channel for negative numbers
		//        (this code was here; documenting for the future)
		if (mesg[1] == '-')
		{
			*last_channel = -(*last_channel);
		}
		//</FS:TS> FIRE-11412
		*channel = *last_channel;
		return mesg.substr(pos, mesg.length() - pos);
	}
	else
	{
		// This is normal chat.
		*channel = 0;
		return mesg;
	}
}