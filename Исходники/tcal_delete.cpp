void CDummyCalendarApp::AddEntryL(TInt aNumToAdd, TBool isParent, TBool isRepeat)
	{
	test.Next(_L("Adding entries"));

	TBuf<50> summary;
	TBuf<50> location;
	TBuf<50> description;

    

	iEntries.ResetAndDestroy();
	for (TInt index=0; index<aNumToAdd; index++)
		{
		TBuf8<255> buf;
		buf.Append(_L("GuidId"));
		buf.AppendNum(index);
		HBufC8* guid = buf.AllocLC();   // need to be pushed to ...

		CCalEntry::TType entryType=(index%2==0)?CCalEntry::ETodo:CCalEntry::EAppt;

		CCalEntry* entry = NULL;
		if(isParent)
			{
			entry = CreateCalEntryL(entryType, guid);
			}
		else
			{
			TTime localTime(KRecurrIdLocalTime);
			TCalTime recurrenceId;
			recurrenceId.SetTimeLocalL(localTime);
			entry = CCalEntry::NewL(entryType, guid, CCalEntry::EMethodAdd, 1, recurrenceId, CalCommon::EThisAndFuture);
			}
		CleanupStack::Pop(guid);
		iEntries.AppendL(entry);

		TInt year = -1;
		TInt month = -1;
		TInt day = -1;
		
		if (isParent)
		    {
    		year = index % 5 + 2001;    // Any year in the range: 2001 - 2005
    		month = index % 12;         
    		day = index % 28;
		    }
        else
            {
            // if this is a child entry, use the recurrence local time as the entry start time 
            // so it won't be out of range
            TCalTime recurrId = entry->RecurrenceIdL(); 
            TDateTime localTime = recurrId.TimeLocalL().DateTime();               
            year = localTime.Year();
            month = localTime.Month();
            day = localTime.Day();    
            }
		
		TTime start(TDateTime(year, (TMonth)month, day, 0, 0, 0, 0));
		TTime end(TDateTime(year, (TMonth)month, day, 0, 0, 0, 0));
		end += TTimeIntervalDays(1);

		SetEntryStartAndEndTimeL(entry,start,end);
				
		RandomText(summary);
		entry->SetSummaryL(summary);
		
		RandomText(location);
		entry->SetLocationL(location);
		
		RandomText(description);
		entry->SetDescriptionL(description);

		if(isRepeat)
			{
			//create a daily repeat rule and make sure its repeat start\end date is within the deleting time range
			TCalRRule rpt(TCalRRule::EDaily);
			rpt.SetInterval(1);
			TCalTime repeatStart;
			TCalTime repeatend;
			if(isParent)
				{
				//make sure the repeat time is within the delete time range
				repeatStart.SetTimeLocalL(TDateTime(2000, EJune, 0, 0, 0, 0, 0));
				repeatend.SetTimeLocalL(TDateTime(2006, EJune, 0, 0, 0, 0, 0));
				}
			else if (index<aNumToAdd/2)
				{
                // if this is a child entry, use the entry's recurrance time as repeating rule
                // start time 
                TCalTime recurrId = entry->RecurrenceIdL(); 
				
				// make sure the repeat time is within the delete time range for the first half entries
				repeatStart.SetTimeLocalL(recurrId.TimeLocalL());	// June 1, 2003 00:00:00
				repeatend.SetTimeLocalL(recurrId.TimeLocalL() + TTimeIntervalMonths(1));  // July 1, 2003 00:00:00
				}
			else
				{
				//make sure the repeat time is out of the delete time range for the second half entries
				repeatStart.SetTimeLocalL(TDateTime(2003, EJune, 0, 0, 0, 0, 0));
				repeatend.SetTimeLocalL(TDateTime(2007, EJune, 0, 0, 0, 0, 0));
				}

			rpt.SetDtStart(repeatStart); 
			rpt.SetUntil(repeatend);
			entry->SetRRuleL(rpt);
			}
		}
	
	TInt entriesStored(0);
	iLocalEntryView->StoreL(iEntries, entriesStored); //temp
	test(entriesStored == iEntries.Count());
	}