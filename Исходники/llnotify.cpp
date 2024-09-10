// static
LLRect LLNotifyBox::getNotifyTipRect(const std::string &utf8message)
{
	LLWString message = utf8str_to_wstring(utf8message);
	S32 message_len = message.length();

	const S32 NOTIFY_WIDTH = gSavedSettings.getS32("NotifyBoxWidth");
	// Make room for the icon area.
	const S32 text_area_width = NOTIFY_WIDTH - HPAD * 4 - 32;

	const llwchar* wchars = message.c_str();
	const llwchar* start = wchars;
	const llwchar* end;
	S32 total_drawn = 0;
	bool done = false;
	S32 line_count;

	for (line_count = 2; !done; ++line_count)
	{
		for (end = start; *end != 0 && *end != '\n'; end++);

		if (*end == 0)
		{
			end = wchars + message_len;
			done = true;
		}
		
		for (S32 remaining = end - start; remaining;)
		{
			S32 drawn = sFont->maxDrawableChars(start, (F32)text_area_width, remaining, LLFontGL::WORD_BOUNDARY_IF_POSSIBLE);

			if (0 == drawn)
			{
				drawn = 1;  // Draw at least one character, even if it doesn't all fit. (avoids an infinite loop)
			}

			total_drawn += drawn; 
			start += drawn;
			remaining -= drawn;

			if (total_drawn < message_len)
			{
				if (wchars[ total_drawn ] != '\n')
				{
					// wrap because line was too long
					line_count++;
				}
			}
			else
			{
				done = true;
			}
		}

		total_drawn++;	// for '\n'
		start = ++end;
	}

	const S32 MIN_NOTIFY_HEIGHT = 72;
	const S32 MAX_NOTIFY_HEIGHT = 600;
	S32 notify_height = llceil((F32) (line_count+1) * sFont->getLineHeight());
	if (gOverlayBar)
	{
		notify_height += gOverlayBar->getBoundingRect().mTop;
	}
	else
	{
		// *FIX: this is derived from the padding caused by the
		// rounded rects, shouldn't be a const here.
		notify_height += 10;  
	}
	notify_height += VPAD;
	notify_height = llclamp(notify_height, MIN_NOTIFY_HEIGHT, MAX_NOTIFY_HEIGHT);

	const S32 RIGHT = gNotifyBoxView->getRect().getWidth();
	const S32 LEFT = RIGHT - NOTIFY_WIDTH;

	// Make sure it goes slightly offscreen
	return LLRect(LEFT, notify_height-1, RIGHT, -1);
}