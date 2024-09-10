S32	LLFontGL::firstDrawableChar(const LLWString& utf32text, F32 max_pixels, S32 start_pos, S32 max_chars) const
{
	const S32 max_index = llmin(llmax(max_chars, start_pos + max_chars), S32(utf32text.length()));
	if (max_index <= 0 || start_pos >= max_index || max_pixels <= 0.f || start_pos < 0)
		return 0;
	
	F32 total_width = 0.0;
	S32 drawable_chars = 0;

	F32 scaled_max_pixels =	max_pixels * sScaleX;

	S32 start = llmin(start_pos, max_index - 1);
	for (S32 i = start; i >= 0; i--)
	{
		llwchar wch = utf32text[i];

		const embedded_data_t* ext_data = getEmbeddedCharData(wch);
		F32 width = 0;
		
		if(ext_data)
		{
			width = getEmbeddedCharAdvance(ext_data);
		}
		else
		{
			const LLFontGlyphInfo* fgi= mFontFreetype->getGlyphInfo(wch);

			// last character uses character width, since the whole character needs to be visible
			// other characters just use advance
			width = (i == start) 
				? (F32)(fgi->mWidth + fgi->mXBearing)  	// use actual width for last character
				: fgi->mXAdvance;						// use advance for all other characters										
		}

		if( scaled_max_pixels < (total_width + width) )
		{
			break;
		}

		total_width += width;
		drawable_chars++;

		if( max_index >= 0 && drawable_chars >= max_index )
		{
			break;
		}

		if ( i > 0 )
		{
			// kerning
			total_width += ext_data ? (EXT_KERNING * sScaleX) : mFontFreetype->getXKerning(utf32text[i - 1], wch);
		}

		// Round after kerning.
		total_width = (F32)ll_round(total_width);
	}

	if (drawable_chars == 0)
	{
		return start_pos; // just draw last character
	}
	else
	{
		// if only 1 character is drawable, we want to return start_pos as the first character to draw
		// if 2 are drawable, return start_pos and character before start_pos, etc.
		return start_pos + 1 - drawable_chars;
	}
	
}