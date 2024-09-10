void
ChoiceFormat::applyPattern(const UnicodeString & pattern,
                           UParseError & parseError,
                           UErrorCode & status)
{
	if (U_FAILURE(status))
	{
		return;
	}

	// Clear error struct
	parseError.offset = -1;
	parseError.preContext[0] = parseError.postContext[0] = (UChar)0;

	// Perform 2 passes.  The first computes the number of limits in
	// this pattern (fCount), which is 1 more than the number of
	// literal VERTICAL_BAR characters.
	int32_t count = 1;
	int32_t i;
	for (i = 0; i < pattern.length(); ++i)
	{
		UChar c = pattern[i];
		if (c == SINGLE_QUOTE)
		{
			// Skip over the entire quote, including embedded
			// contiguous pairs of SINGLE_QUOTE.
			for (;;)
			{
				do
				{
					++i;
				}
				while (i < pattern.length() &&
				       pattern[i] != SINGLE_QUOTE);
				if ((i + 1) < pattern.length() &&
				    pattern[i + 1] == SINGLE_QUOTE)
				{
					// SINGLE_QUOTE pair; skip over it
					++i;
				}
				else
				{
					break;
				}
			}
		}
		else if (c == VERTICAL_BAR)
		{
			++count;
		}
	}

	// Allocate the required storage.
	double * newLimits = (double *) uprv_malloc(sizeof(double) * count);
	/* test for NULL */
	if (newLimits == 0)
	{
		status = U_MEMORY_ALLOCATION_ERROR;
		return;
	}
	UBool * newClosures = (UBool *) uprv_malloc(sizeof(UBool) * count);
	/* test for NULL */
	if (newClosures == 0)
	{
		status = U_MEMORY_ALLOCATION_ERROR;
		uprv_free(newLimits);
		return;
	}
	UnicodeString * newFormats = new UnicodeString[count];
	/* test for NULL */
	if (newFormats == 0)
	{
		status = U_MEMORY_ALLOCATION_ERROR;
		uprv_free(newLimits);
		uprv_free(newClosures);
		return;
	}

	// Perform the second pass
	int32_t k = 0; // index into newXxx[] arrays
	UnicodeString buf; // scratch buffer
	UBool inQuote = FALSE;
	UBool inNumber = TRUE; // TRUE before < or #, FALSE after

	for (i = 0; i < pattern.length(); ++i)
	{
		UChar c = pattern[i];
		if (c == SINGLE_QUOTE)
		{
			// Check for SINGLE_QUOTE pair indicating a literal quote
			if ((i + 1) < pattern.length() &&
			    pattern[i + 1] == SINGLE_QUOTE)
			{
				buf += SINGLE_QUOTE;
				++i;
			}
			else
			{
				inQuote = !inQuote;
			}
		}
		else if (inQuote)
		{
			buf += c;
		}
		else if (c == LESS_THAN || c == LESS_EQUAL || c == LESS_EQUAL2)
		{
			if (!inNumber || buf.length() == 0)
			{
				goto error;
			}
			inNumber = FALSE;

			double limit;
			buf.trim();
			if (!buf.compare(gPositiveInfinity, POSITIVE_INF_STRLEN))
			{
				limit = uprv_getInfinity();
			}
			else if (!buf.compare(gNegativeInfinity, NEGATIVE_INF_STRLEN))
			{
				limit = -uprv_getInfinity();
			}
			else
			{
				limit = stod(buf);
			}

			if (k == count)
			{
				// This shouldn't happen.  If it does, it means that
				// the count determined in the first pass did not
				// match the number of elements found in the second
				// pass.
				goto error;
			}
			newLimits[k] = limit;
			newClosures[k] = (c == LESS_THAN);

			if (k > 0 && limit <= newLimits[k - 1])
			{
				// Each limit must be strictly > than the previous
				// limit.  One exception: Two subsequent limits may be
				// == if the first closure is FALSE and the second
				// closure is TRUE.  This places the limit value in
				// the second interval.
				if (!(limit == newLimits[k - 1] &&
				      !newClosures[k - 1] &&
				      newClosures[k]))
				{
					goto error;
				}
			}

			buf.truncate(0);
		}
		else if (c == VERTICAL_BAR)
		{
			if (inNumber)
			{
				goto error;
			}
			inNumber = TRUE;

			newFormats[k] = buf;
			++k;
			buf.truncate(0);
		}
		else
		{
			buf += c;
		}
	}

	if (k != (count - 1) || inNumber || inQuote)
	{
		goto error;
	}
	newFormats[k] = buf;

	// Don't modify this object until the parse succeeds
	uprv_free(fChoiceLimits);
	uprv_free(fClosures);
	delete[] fChoiceFormats;
	fCount = count;
	fChoiceLimits  = newLimits;
	fClosures      = newClosures;
	fChoiceFormats = newFormats;
	return;

error:
	status = U_ILLEGAL_ARGUMENT_ERROR;
	syntaxError(pattern, i, parseError);
	uprv_free(newLimits);
	uprv_free(newClosures);
	delete[] newFormats;
	return;

}