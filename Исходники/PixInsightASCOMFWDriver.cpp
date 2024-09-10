	uint8 PixInsightASCOMFWDriver::MaxPosition()
	{
		uint8 i = SafeArrayGetElemsize(theFWPtr2.GetProperty("Names")->parray);
		return i;
	}