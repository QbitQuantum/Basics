UINT16 GetClass(const UINT8* ClassTable, const UINT8* end,
				const UINT16 g)
{
	RETURN_IF_OUT_OF_BOUNDS(ClassTable+4, end);

	const UINT16 format = MDF_GetU16(ClassTable);
	if (format < 1 || format > 2)
	{
		OP_ASSERT(!"unknown class definition format");
		return 0;
	}

	if (format == 1)
	{
		RETURN_IF_OUT_OF_BOUNDS(ClassTable+6, end);
		const UINT16 gs = MDF_GetU16(ClassTable+2);
		const UINT16 count = MDF_GetU16(ClassTable+4);
		RETURN_IF_OUT_OF_BOUNDS(ClassTable + 6 + 2*count, end);
		if (g < gs || g-gs >= count)
			return 0;
		return (MDF_GetU16(ClassTable + 6 + 2*(g-gs)));
	}

	UINT16 count = MDF_GetU16(ClassTable+2);
	RETURN_IF_OUT_OF_BOUNDS(ClassTable + 4 + 6*count, end);
	UINT16 idx;
	if (BSearch(ClassTable+4, count, g, idx, Format2Compare))
		return MDF_GetU16(ClassTable + 4 + 6*idx + 4);
	return 0;
}