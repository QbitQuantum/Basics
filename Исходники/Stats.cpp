void FStat::PrintStat ()
{
	int fontheight = ConFont->GetHeight() + 1;
	int y = SCREENHEIGHT;
	int count = 0;

	for (FStat *stat = FirstStat; stat != NULL; stat = stat->m_Next)
	{
		if (stat->m_Active)
		{
			FString stattext(stat->GetStats());

			if (stattext.Len() > 0)
			{
				y -= fontheight;	// there's at least one line of text
				for (unsigned i = 0; i < stattext.Len()-1; i++)
				{
					// Count number of linefeeds but ignore terminating ones.
					if (stattext[i] == '\n') y -= fontheight;
				}
				screen->DrawText(ConFont, CR_GREEN, 5, y, stattext, TAG_DONE);
				count++;
			}
		}
	}
	if (count)
	{
		ST_SetNeedRefresh();
	}
}