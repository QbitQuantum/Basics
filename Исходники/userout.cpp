void TERMWINDOWMEMBER GiveRoomPrompt(Bool JustDisplayedEvent)
	{
	static int roomCounter;
	label rn, gn, np, ex, hn;
	char rd[81];
	char tm[128], dt[128];
	int i;

	CommPort->FlushInput();

	OC.User.Reset();

	OC.Echo = BOTH;
	OC.setio();

	OC.ansiattr = cfg.attr;

	doEvent(EVT_ROOMPROMPT);

	if (CurrentUser->IsYouAreHere())
		{
		youAreHere();
		}

#ifdef WINCIT
	// if (!PendingSystemEvents)
    	// {
    	OC.SetOutFlag(PendingSystemEvents ? NOSTOP : IMPERVIOUS);
	// }

//	if (IdlePrompt)
//		{
//		return;
//		}

	if (!(CurrentUser->IsErasePrompt() && JustDisplayedEvent))
    	{
	    doCR();
		}

	if (JustDisplayedEvent)
		{
		numLines = 0;
		}
#endif

	OC.Formatting = FALSE;

	roomCounter++;

	RoomTab[thisRoom].GetName(rn, sizeof(rn));

	*gn = 0;
	if (RoomTab[thisRoom].IsGroupOnly())
		{
		if (RoomTab[thisRoom].IsBooleanGroup())
			{
			CopyStringToBuffer(gn, getmsg(471));
			}
		else
			{
			GroupData[RoomTab[thisRoom].GetGroupNumber()].GetName(gn, sizeof(gn));
			}
		}

	*np = 0;
	if (RoomTab[thisRoom].IsShared())
		{
		label Buffer;
		CopyStringToBuffer(np, loggedIn ? CurrentUser->GetNetPrefix(Buffer, sizeof(Buffer)) : cfg.netPrefix);
		}


	*ex = 0;
	i = 0;
	if (RoomTab[thisRoom].IsMsDOSdir())
		{
		if (CurrentUser->IsIBMRoom() && TermCap->IsIBMExtended())
			{
			ex[i++] = roomCounter == 6969 ? '\xcc' : '\xb9';
			}
		else
			{
			ex[i++] = roomCounter == 6969 ? '[' : ']';
			}
		}

	if (RoomTab[thisRoom].IsGroupOnly())
		{
		if (CurrentUser->IsIBMRoom() && TermCap->IsIBMExtended())
			{
			ex[i++] = roomCounter == 6969 ? '\xba' : '\xb3';
			}
		else
			{
			ex[i++] = roomCounter == 6969 ? ';' : ':';
			}
		}

	if (RoomTab[thisRoom].IsHidden())
		{
		ex[i++] = roomCounter == 6969 ? '(' : ')';
		}
	if (RoomTab[thisRoom].IsBIO())
		{
		ex[i++] = roomCounter == 6969 ? '{' : '}';
		}
	else if (!RoomTab[thisRoom].IsGroupOnly() && !RoomTab[thisRoom].IsMsDOSdir() && !RoomTab[thisRoom].IsHidden())
		{
		if (!(iswindow(thisRoom) && CurrentUser->IsIBMRoom() && TermCap->IsIBMExtended()))
			{
			ex[i++] = roomCounter == 6969 ? '<' : '>';
			}
		}

	if (iswindow(thisRoom))
		{
		if (CurrentUser->IsIBMRoom() && TermCap->IsIBMExtended())
			{
			ex[i++] = roomCounter == 6969 ? '\xae' : '\xaf';
			}
		else
			{
			ex[i++] = roomCounter == 6969 ? '<' : '>';
			}
		}
	ex[i] = 0;

	HallData[thisHall].GetName(hn, sizeof(hn));
	CurrentRoom->GetInfoLine(rd, sizeof(rd));

	char Buffer[64];
	strftime(tm, 127, (loggedIn) ? special_deansi(CurrentUser->GetDateStamp(Buffer, sizeof(Buffer)),
			TERM_TIME) : special_deansi(cfg.datestamp, TERM_TIME), 0l);

	strftime(dt, 127, (loggedIn) ? special_deansi(CurrentUser->GetVerboseDateStamp(Buffer,
			sizeof(Buffer)), TERM_DATE) : special_deansi(cfg.vdatestamp, TERM_DATE), 0l);

	Andy(loggedIn ? CurrentUser->GetPromptFormat(Buffer, sizeof(Buffer)) :
			cfg.prompt, getmsg(638), rn, gn, np, ex, hn, rd, tm, dt);

	OC.Formatting = TRUE;
	ansi(14);
	OC.MCI_goto = FALSE;

	termCap(TERM_NORMAL);
	mPrintf(spc);
    CursorIsAtPrompt = TRUE;

	OC.SetOutFlag(OUTOK);

	if (roomCounter == 6969)
		{
		roomCounter = 0;
		}
	}