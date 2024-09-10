	//cursor display is reference counted (i.e. cursor is displayed if value >= 0)
	//so this function will only change the cursor state if required, avoiding
	//adding or removing extra references.
	void enableCursor(bool enable)
	{
	#ifdef _WIN32
		CURSORINFO ci;
		ci.cbSize        = sizeof(CURSORINFO);
		ci.flags         = 0;
		ci.hCursor       = 0;
		ci.ptScreenPos.x = 0;
		ci.ptScreenPos.y = 0;

		if ( GetCursorInfo(&ci) )
		{
			const bool cursorShowing = (ci.flags&CURSOR_SHOWING)!=0;
			if (cursorShowing != enable)
			{
				ShowCursor(enable);
			}
		}
	#endif
	}