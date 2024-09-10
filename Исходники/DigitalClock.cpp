void DigitalClock::InitClock()
{
    if (mCalendar == NULL) {
        AutoPtr<ICalendarHelper> helper;
        CCalendarHelper::AcquireSingleton((ICalendarHelper**)&helper);
        helper->GetInstance((ICalendar**)&mCalendar);
    }

    mFormatChangeObserver = new FormatChangeObserver(this);
    AutoPtr<IContext> cxt;
    GetContext((IContext**)&cxt);
    AutoPtr<IContentResolver> resolver;
    cxt->GetContentResolver((IContentResolver**)&resolver);
    AutoPtr<IUriHelper> uriHelper;
    CUriHelper::AcquireSingleton((IUriHelper**)&uriHelper);
    AutoPtr<IUri> uri;
    uriHelper->Parse(String("content://settings/system"), (IUri**)&uri);
    resolver->RegisterContentObserver(uri, TRUE, mFormatChangeObserver);
    SetFormat();
}