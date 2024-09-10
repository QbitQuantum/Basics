int	VFPRINTF(HANDLE handle, const char *fmt, va_list argptr)
{
	/////////////////////////////////////////////////////////////////
	/* XXX Two streams are being used. Disabled to avoid inconsistency [flaviojs]
	static COORD saveposition = {0,0};
	*/

	/////////////////////////////////////////////////////////////////
	DWORD written;
	char *p, *q;
	NEWBUF(tempbuf); // temporary buffer

	if(!fmt || !*fmt)
		return 0;

	// Print everything to the buffer
	BUFVPRINTF(tempbuf,fmt,argptr);

	if( !is_console(handle) && stdout_with_ansisequence )
	{
		WriteFile(handle, BUFVAL(tempbuf), BUFLEN(tempbuf), &written, 0);
		return 0;
	}

	// start with processing
	p = BUFVAL(tempbuf);
	while ((q = strchr(p, 0x1b)) != NULL)
	{	// find the escape character
		if( 0==WriteConsole(handle, p, (DWORD)(q-p), &written, 0) ) // write up to the escape
			WriteFile(handle, p, (DWORD)(q-p), &written, 0);

		if( q[1]!='[' )
		{	// write the escape char (whatever purpose it has) 
			if(0==WriteConsole(handle, q, 1, &written, 0) )
				WriteFile(handle,q, 1, &written, 0);
			p=q+1;	//and start searching again
		}
		else
		{	// from here, we will skip the '\033['
			// we break at the first unprocessible position
			// assuming regular text is starting there
			uint8 numbers[16], numpoint=0;
			CONSOLE_SCREEN_BUFFER_INFO info;

			// initialize
			GetConsoleScreenBufferInfo(handle, &info);
			memset(numbers,0,sizeof(numbers));

			// skip escape and bracket
			q=q+2;
			for(;;)
			{
				if( ISDIGIT(*q) ) 
				{	// add number to number array, only accept 2digits, shift out the rest
					// so // \033[123456789m will become \033[89m
					numbers[numpoint] = (numbers[numpoint]<<4) | (*q-'0');
					++q;
					// and next character
					continue;
				}
				else if( *q == ';' )
				{	// delimiter
					if(numpoint<sizeof(numbers)/sizeof(*numbers))
					{	// go to next array position
						numpoint++;
					}
					else
					{	// array is full, so we 'forget' the first value
						memmove(numbers,numbers+1,sizeof(numbers)/sizeof(*numbers)-1);
						numbers[sizeof(numbers)/sizeof(*numbers)-1]=0;
					}
					++q;
					// and next number
					continue;
				}
				else if( *q == 'm' )
				{	// \033[#;...;#m - Set Graphics Rendition (SGR)
					uint8 i;
					for(i=0; i<= numpoint; ++i)
					{
						if( 0x00 == (0xF0 & numbers[i]) )
						{	// upper nibble 0
							if( 0 == numbers[i] )
							{	// reset
								info.wAttributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
							}
							else if( 1==numbers[i] )
							{	// set foreground intensity
								info.wAttributes |= FOREGROUND_INTENSITY;
							}
							else if( 5==numbers[i] )
							{	// set background intensity
								info.wAttributes |= BACKGROUND_INTENSITY;
							}
							else if( 7==numbers[i] )
							{	// reverse colors (just xor them)
								info.wAttributes ^= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE |
													BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
							}
							//case '2': // not existing
							//case '3':	// blinking (not implemented)
							//case '4':	// unterline (not implemented)
							//case '6': // not existing
							//case '8': // concealed (not implemented)
							//case '9': // not existing
						}
						else if( 0x20 == (0xF0 & numbers[i]) )
						{	// off

							if( 1==numbers[i] )
							{	// set foreground intensity off
								info.wAttributes &= ~FOREGROUND_INTENSITY;
							}
							else if( 5==numbers[i] )
							{	// set background intensity off
								info.wAttributes &= ~BACKGROUND_INTENSITY;
							}
							else if( 7==numbers[i] )
							{	// reverse colors (just xor them)
								info.wAttributes ^= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE |
													BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
							}
						}
						else if( 0x30 == (0xF0 & numbers[i]) )
						{	// foreground
							uint8 num = numbers[i]&0x0F;
							if(num==9) info.wAttributes |= FOREGROUND_INTENSITY;
							if(num>7) num=7;	// set white for 37, 38 and 39
							info.wAttributes &= ~(FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
							if( (num & 0x01)>0 ) // lowest bit set = red
								info.wAttributes |= FOREGROUND_RED;
							if( (num & 0x02)>0 ) // second bit set = green
								info.wAttributes |= FOREGROUND_GREEN;
							if( (num & 0x04)>0 ) // third bit set = blue
								info.wAttributes |= FOREGROUND_BLUE;
						}
						else if( 0x40 == (0xF0 & numbers[i]) )
						{	// background
							uint8 num = numbers[i]&0x0F;
							if(num==9) info.wAttributes |= BACKGROUND_INTENSITY;
							if(num>7) num=7;	// set white for 47, 48 and 49
							info.wAttributes &= ~(BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);
							if( (num & 0x01)>0 ) // lowest bit set = red
								info.wAttributes |= BACKGROUND_RED;
							if( (num & 0x02)>0 ) // second bit set = green
								info.wAttributes |= BACKGROUND_GREEN;
							if( (num & 0x04)>0 ) // third bit set = blue
								info.wAttributes |= BACKGROUND_BLUE;
						}
					}
					// set the attributes
					SetConsoleTextAttribute(handle, info.wAttributes);
				}
				else if( *q=='J' )
				{	// \033[#J - Erase Display (ED)
					//    \033[0J - Clears the screen from cursor to end of display. The cursor position is unchanged.
					//    \033[1J - Clears the screen from start to cursor. The cursor position is unchanged.
					//    \033[2J - Clears the screen and moves the cursor to the home position (line 1, column 1).
					uint8 num = (numbers[numpoint]>>4)*10+(numbers[numpoint]&0x0F);
					int cnt;
					DWORD tmp;
					COORD origin = {0,0};
					if(num==1)
					{	// chars from start up to and including cursor
						cnt = info.dwSize.X * info.dwCursorPosition.Y + info.dwCursorPosition.X + 1;
					}
					else if(num==2)
					{	// Number of chars on screen.
						cnt = info.dwSize.X * info.dwSize.Y;
						SetConsoleCursorPosition(handle, origin); 
					}
					else// 0 and default
					{	// number of chars from cursor to end
						origin = info.dwCursorPosition;
						cnt = info.dwSize.X * (info.dwSize.Y - info.dwCursorPosition.Y) - info.dwCursorPosition.X; 
					}
					FillConsoleOutputAttribute(handle, info.wAttributes, cnt, origin, &tmp);
					FillConsoleOutputCharacter(handle, ' ',              cnt, origin, &tmp);
				}
				else if( *q=='K' )
				{	// \033[K  : clear line from actual position to end of the line
					//    \033[0K - Clears all characters from the cursor position to the end of the line.
					//    \033[1K - Clears all characters from start of line to the cursor position.
					//    \033[2K - Clears all characters of the whole line.

					uint8 num = (numbers[numpoint]>>4)*10+(numbers[numpoint]&0x0F);
					COORD origin = {0,info.dwCursorPosition.Y}; //warning C4204
					SHORT cnt;
					DWORD tmp;
					if(num==1)
					{
						cnt = info.dwCursorPosition.X + 1;
					}
					else if(num==2)
					{
						cnt = info.dwSize.X;
					}
					else// 0 and default
					{
						origin = info.dwCursorPosition;
						cnt = info.dwSize.X - info.dwCursorPosition.X; // how many spaces until line is full
					}
					FillConsoleOutputAttribute(handle, info.wAttributes, cnt, origin, &tmp);
					FillConsoleOutputCharacter(handle, ' ',              cnt, origin, &tmp);
				}
				else if( *q == 'H' || *q == 'f' )