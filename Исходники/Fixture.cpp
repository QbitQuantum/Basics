  void ceefit_call_spec FIXTURE::GetSummaryReport(DYNARRAY<SUMMARYITEM>& reportList)
  {
    SUMMARYITEM aItem;

    aItem.Title = "Counts";
    aItem.Value = CountsObj->ToString();
    reportList.Add(aItem);

    aItem.Title = "Input file";
    aItem.Value = SummaryObj->InputFile;
    reportList.Add(aItem);

    wchar_t timeChar[128];
    timeChar[0] = L'\0';
    wcsftime(timeChar, 128, L"%a %b %d %H:%M:%S %X %Y", gmtime(&SummaryObj->InputUpdate));

    aItem.Title = "Input last updated";
    aItem.Value = timeChar;
    reportList.Add(aItem);

    aItem.Title = "Output file";
    aItem.Value = SummaryObj->OutputFile;
    reportList.Add(aItem);

    timeChar[0] = L'\0';
    wcsftime(timeChar, 128, L"%a %b %d %H:%M:%S %X %Y", gmtime(&SummaryObj->RunDate.time));

    aItem.Title = "Run date";
    aItem.Value = timeChar;
    reportList.Add(aItem);

    if(SummaryObj->RunElapsedTime != null)
    {
      aItem.Title = "Run elapsed time";
      aItem.Value = SummaryObj->RunElapsedTime->ToString();
      reportList.Add(aItem);
    }

    if(SummaryObj->CountsRun != null)
    {
      aItem.Title = "counts run";
      aItem.Value = SummaryObj->CountsRun->ToString();
      reportList.Add(aItem);
    }
  }