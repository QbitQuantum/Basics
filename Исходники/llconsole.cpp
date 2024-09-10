void LLConsole::addQueuedLines()
{
	for (line_queue_t::iterator iter = mLineQueue.begin();
		 iter != mLineQueue.end(); ++iter)
	{
		LineInfo& line_info = *iter;
		LLWString wline = line_info.wline;
		//F32 size = line_info.size;
		LLColor4 color = line_info.color;
		if (!wline.empty() && mFont != NULL)
		{
			// Wrap lines that are longer than the view is wide.
			S32 offset = 0;
			while( offset < (S32)wline.length() )
			{
				S32 skip_chars; // skip '\n'
				// Figure out if a word-wrapped line fits here.
				LLWString::size_type line_end = wline.find_first_of(llwchar('\n'), offset);
				if (line_end != LLWString::npos)
				{
					skip_chars = 1; // skip '\n'
				}
				else
				{
					line_end = wline.size();
					skip_chars = 0;
				}
				U32 drawable = mFont->maxDrawableChars(wline.c_str()+offset, (F32)mRect.getWidth(), line_end-offset, TRUE);
				if (drawable != 0)
				{
					LLFixedBuffer::addLine(wline.substr(offset, drawable));
					mAddTimes[mAddTimes.size()-1] = line_info.add_time;
				}
				else
				{
					// force a blank line
					LLFixedBuffer::addLine(" ");
				}
				mColors.push_back(color);
				offset += (drawable + skip_chars);
			}
		}
	}
	mLineQueue.clear();
}