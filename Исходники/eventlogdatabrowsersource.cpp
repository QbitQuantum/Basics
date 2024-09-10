//-----------------------------------------------------------------------------
void EventLogDataBrowserSource::dbDrawCell (CDrawContext* context, const CRect& size, int32_t row, int32_t column, int32_t flags, CDataBrowser* browser)
{
	CColor cellColor (kWhiteCColor);
	bool oddRow = row % 2 != 0;
	if (oddRow)
	{
		cellColor = kBlackCColor;
		cellColor.alpha /= 16;
	}
	String cellValue;
	
	LogEvent& logEvent = mLogEvents.at (row);
	if (logEvent.count > 0)
	{
		if (String (LOG_ERR) == logEventSeverity[logEvent.id])
			cellColor = kRedCColor;
		else if (String (LOG_WARN) == logEventSeverity[logEvent.id])
			cellColor = kYellowCColor;
		else if (String (LOG_INFO) == logEventSeverity[logEvent.id])
			cellColor = kBlueCColor;
		
		if (oddRow)
			cellColor.alpha /= 2;
		else
			cellColor.alpha /= 3.;
	}

	context->setFillColor (cellColor);
	context->drawRect (size, kDrawFilled);

	switch (column)
	{
		case kType:
		{
			if (logEvent.count > 0)
				cellValue.printf (logEventSeverity[logEvent.id]);

			break;
		}
		case kDescription:
		{
			cellValue.assign (logEventDescriptions[row]);
			break;
		}
		case kCount:
		{
			cellValue.printf ("%d", logEvent.count);

			break;
		}
	}

	CRect cellSize (size);
	cellSize.inset (5, 0);
	context->setFont (kNormalFontSmall);
	context->setFontColor (kBlackCColor);
	context->drawString (cellValue.text8 (), cellSize, kLeftText);
}