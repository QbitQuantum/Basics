Bool TERMWINDOWMEMBER theAlgorithm(r_slot rm, h_slot hl, Bool exclude)
	{
	assert(rm >= -1);
	assert(rm < cfg.maxrooms);
	assert(hl >= -1);
	assert(hl < cfg.maxhalls);

	static BitBag *hallCheck;
	Bool lowest = FALSE;

	if (!hallCheck)
		{
		if (rm == thisRoom || (rm == LOBBY && cfg.subhubs == 4))
			{
			return (TRUE);
			}

		if ((exclude && CurrentUser->IsRoomExcluded(rm)) || !CurrentUser->CanAccessRoom(rm))
			{
			return (FALSE);
			}

		hallCheck = new BitBag(cfg.maxhalls);

		lowest = TRUE;
		}

	if (!hallCheck)
		{
		OutOfMemory(78);
		}
	else
		{
		if (hallCheck->BitTest(hl))
			{
			return (FALSE);
			}
		else
			{
			hallCheck->BitSet(hl, TRUE);

			if (roominhall(rm, hl))
				{
				delete hallCheck;
				hallCheck = NULL;

				return (TRUE);
				}

			for (r_slot rmCnt = 0; rmCnt < cfg.maxrooms; rmCnt++)
				{
				if (CurrentUser->CanAccessRoom(rmCnt) && (!exclude || !CurrentUser->IsRoomExcluded(rmCnt)) &&
						roominhall(rmCnt, hl) && iswindow(rmCnt))
					{
					for (h_slot hlCnt = 0; hlCnt < cfg.maxhalls; hlCnt++)
						{
						if (HallData[hlCnt].IsInuse() && CurrentUser->CanAccessHall(hlCnt) &&
								HallData[hlCnt].IsWindowedIntoHall(rmCnt))
							{
							if (theAlgorithm(rm, hlCnt, exclude))
								{
								return (TRUE);
								}
							}
						}
					}
				}
			}
		}

	if (lowest && hallCheck)
		{
		delete hallCheck;
		hallCheck = NULL;
		}

	return (FALSE);
	}