void GSGUI_STRING_INPUT::PlaceInput(const Vector2& pos, const str_type::string& font, const unsigned int nMaxChars, 
				const float size, const Color& dwColor, VideoPtr video,
				InputPtr input)
{
	const unsigned int time = video->GetElapsedTime();
	if ((time-lastBlink) > blinkTime)
	{
		showingCarret = showingCarret==0 ? 1 : 0;
		lastBlink = video->GetElapsedTime();
	}

	// pick the text cursor position with a mouse click
	if (input->GetLeftClickState() == GSKS_HIT)
	{
		cursor = video->FindClosestCarretPosition(font, ss, pos, input->GetCursorPositionF(video));
	}
	
	// don't let the cursor exceed the text range
	cursor = Min(cursor, static_cast<unsigned int>(ss.length()));

	str_type::char_t lastInput = input->GetLastCharInput();
	if (lastInput != '\0' && ss.length() < nMaxChars)
	{
		if (numbersOnly)
		{
			if ((lastInput < 'a' || lastInput > 'z') &&
				(lastInput < 'A' || lastInput > 'Z'))
			{
				ss.insert(cursor, 1, lastInput);
			}
		}
		else
		{
			ss.insert(cursor, 1, lastInput);
		}
		cursor++;
	}

	if (input->GetKeyState(GSK_BACK) == GSKS_HIT)
	{
		if (cursor > 0)
		{
			ss.erase(cursor-1, 1);
			cursor--;
		}
	}
	
	if (input->GetKeyState(GSK_DELETE) == GSKS_HIT)
	{
		if (cursor < ss.length())
		{
			ss.erase(cursor, 1);
		}
	}
	
	if (input->GetKeyState(GSK_LEFT) == GSKS_HIT)
	{
		if (cursor > 0)
			cursor--;
	}
	if (input->GetKeyState(GSK_RIGHT) == GSKS_HIT)
	{
		cursor = Min(++cursor, static_cast<unsigned int>(ss.length()));
	}
	if (input->GetKeyState(GSK_END) == GSKS_HIT)
	{
		SendCursorToEnd();
	}

	const Vector2 cursorPosition = video->ComputeCarretPosition(font, ss, cursor);
	video->DrawBitmapText(pos, ss, font, dwColor);
	if (showingCarret==1)
		video->DrawRectangle(cursorPosition+pos-Vector2(2,0), Vector2(2,size), gs2d::constant::BLACK, gs2d::constant::BLACK, gs2d::constant::BLACK, gs2d::constant::BLACK, 0.0f);
}