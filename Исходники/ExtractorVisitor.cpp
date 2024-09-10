EXPORT_C void CSdpAttrIdMatchList::AddL(TAttrRange aRange)
/** Adds a range of IDs to the list.

@param aRange Range to add */
	{
	if (aRange.iStart > aRange.iEnd)
		{// Bad range
		User::Leave(KErrArgument);
		}
		
		
	// Look for insertion point (pos) in the match list. 
		
	TInt pos = 0; 	// this new item will start the list unless we find an existing
					// range for it to overlap or follow

	// If the start of the range 'aRange' is contiguous with one of the existing match list ranges
	// then the insertion point is the index of that match list range.
	// If not it is one more than the index of the match list range that
	// precedes 'aRange'.
	// N.B. The ranges are stored in ascending order

	TBool bPositionFound = EFalse;
	TBool bStartInRangeOrContiguous = EFalse;	

	// Find the first position in the list in which (or contiguous with) this range lies
	if (FindInOrContiguousWith(aRange.iStart, pos) == 0)
		{
		// the start of this new range overlaps with an existing one (returned in pos) or is contiguous with it
		bPositionFound = ETrue;
		bStartInRangeOrContiguous = ETrue;
		}	
	else
		{
		// find which range this new one will be after
		for (TInt i=iList->Count()-1; i>=0 && !bPositionFound; i-- )
			{
			if (aRange.iStart > (iList->At(i).iEnd + 1 ))
				{
				pos = i+1;
				bPositionFound = ETrue;
				}
			}
		}

	TAttrRange *insert;
	
	if (bStartInRangeOrContiguous)
		{// Don't actually insert new entry, just grow the existing entry
		insert = &iList->At(pos);
		
		// NB If the range to add has a start ID which is one less than the current start of range, 
		// the range may grow "downwards", but will never join up with the preceding range because
		// the start ID is known not to be contiguous with THAT range.
		insert->iStart = Min(insert->iStart, aRange.iStart); 
		insert->iEnd = Max(insert->iEnd, aRange.iEnd);
		}
	else
		{// Add a new entry
		iList->InsertL(pos, aRange);
		insert = &iList->At(pos);
		}

	while (pos < iList->Count()-1 && insert->IsContiguousWith(iList->At(pos+1).iStart) )
		{// There's now overlap with following item
		insert->iEnd = Max(insert->iEnd, iList->At(pos+1).iEnd);
		iList->Delete(pos+1);	// which leaves a new range to be checked at (pos+1), so no incrementing of pos is required	
		}
	__TEST_INVARIANT;
	}