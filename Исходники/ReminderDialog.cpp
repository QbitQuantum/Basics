wxDateTime CReminderDialog::ParseSnoozeTime(wxString strTime)
{
	// Parser function to parse something like: 1 Week 3 Days 5 Minutes.
	wxDateTime dateTime = wxDateTime::Now();
	strTime = strTime.Trim(true);
	int weeks = 0, days = 0, hours = 0, minutes = 0;
	wxRegEx reExp(wxT("\\s*(\\d+)\\s*([a-zA-Z]*)\\s*"), wxRE_ADVANCED);
	wxString strNumber;
	wxString strText;
	int nNumber = 0;
	while( reExp.Matches(strTime) )
	{
		strNumber = reExp.GetMatch(strTime, 1);
		strText = reExp.GetMatch(strTime, 2);
		strTime = strTime.Remove(0, reExp.GetMatch(strTime, 0).Length());
		strText = strText.Lower();
		try
		{
			nNumber =  boost::lexical_cast<int>(strText.c_str());
		}
		catch (boost::bad_lexical_cast &)
		{			
			nNumber = 0;
		}
		if(strText.Find(wxT("minute")) == 0)
			minutes = nNumber;
		else if(strText.Find(wxT("hour")) == 0)
			hours = nNumber;
		else if(strText.Find(wxT("day")) == 0)
			days = nNumber;
		else if(strText.Find(wxT("week")) == 0)
			weeks = nNumber;
	}
	return dateTime + GetTimeSpan(weeks, days, hours, minutes);
}