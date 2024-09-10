// Internal
void CFontGen::DetermineExistingChars()
{
	HDC dc = GetDC(0);

	HFONT font = CreateFont(10);
	HFONT oldFont = (HFONT)SelectObject(dc, font);

	if( fGetGlyphIndicesA )
	{
		numCharsAvailable = 0;
		numCharsSelected = 0;

		if( useUnicode )
		{
			ClearSubsets();
			memset(disabled, 1, (maxUnicodeChar+1)*sizeof(bool));

			// GetGlyphIndices doesn't support surrogate pairs
			// neither does ScriptGetCMap, so we'll have to go the 
			// long route and use ScriptItemize and ScriptShape	
			SCRIPT_CACHE sc = 0;

			for( int subset = 0; subset < numUnicodeSubsets; subset++ )
			{
				// Unicode subsets that have no defined characters are all disabled
				if( UnicodeSubsets[subset].name[0] == '(' )
					continue;

				unsigned int begin = UnicodeSubsets[subset].beginChar;
				while( begin <= UnicodeSubsets[subset].endChar )
				{
					unsigned int end = begin + 255;
					if( end > UnicodeSubsets[subset].endChar )
						end = UnicodeSubsets[subset].endChar;

					// Create a subset with at most 256 characters
					SSubset *set = new SSubset;
					set->name      = UnicodeSubsets[subset].name;
					set->charBegin = begin;
					set->charEnd   = end;
					subsets.push_back(set);

					// Determine the available characters in this set
					for( unsigned int n = begin; n <= end; n++ )
					{
						bool exists = DoesUnicodeCharExist(dc, &sc, n) > 0;

						if( !disableBoxChars || exists )
						{
							disabled[n] = false;

							// Mark the subset as available
							set->available = true;

							// Count the number of available characters
							// and update the number of selected ones
							numCharsAvailable++;
							if( selected[n] ) 
								numCharsSelected++;
						}
					}

					// Next 256 characters in the subset
					begin += 256;
				}
			}

			// Clean up the cache created by Uniscribe
			if( sc != 0 )
				ScriptFreeCache(&sc);
		}
		else
		{
			// Create the basic subset
			SSubset *set = new SSubset;
			set->name      = "";
			set->charBegin = 0;
			set->charEnd   = 255;
			subsets.push_back(set);

			memset(disabled, 0, 256*sizeof(bool));

			for( int n = 0; n < 256; n++ )
			{
				char buf[2];
				buf[0] = n;
				buf[1] = '\0';

				WORD idx;
				int r = fGetGlyphIndicesA(dc, buf, 1, &idx, GGI_MARK_NONEXISTING_GLYPHS);

				if( disableBoxChars && (r == GDI_ERROR || idx == 0xFFFF) )
					disabled[n] = true;
				else
				{
					numCharsAvailable++;
					if( selected[n] ) 
						numCharsSelected++;
				}
			}
		}
	}

	SelectObject(dc, oldFont);
	DeleteObject(font);

	ReleaseDC(0, dc);
}