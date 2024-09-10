// Adds an empty row at the end of the value buffer. The row will be
// marked invalid until the first value is set in the row. This will
// re-allocate the existing value buffer. If you know beforehand how
// many rows will exist in the table it is more efficient to use
// one SetNumRows(N) instead of N times AddRow()! The method returns
// the index of the newly added row. The row will be filled with
// the row attribute's default values.
int CValueTable::AddRow()
{
	if (NumRows >= AllocatedRows)
	{
		int NewNumRows = AllocatedRows + AllocatedRows;
		if (NewNumRows == 0) NewNumRows = 10;
		Realloc(RowPitch, NewNumRows);
	}

	if (Flags.Is(_TrackModifications))
	{
		if (FirstNewRowIndex > NumRows) FirstNewRowIndex = NumRows;
		RowStateBuffer[NumRows] |= NewRow;
		++NewRowsCount;
		Flags.Set(_IsModified);
	}

	//UserData.Append(NULL);

	SetRowToDefaultValues(NumRows++); // Copy to stack, then increment, then call. Intended, don't change.
	return NumRows - 1;
}