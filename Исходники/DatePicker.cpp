AutoPtr<ICalendar> DatePicker::GetCalendarForLocale(
    /* [in] */ ICalendar* oldCalendar,
    /* [in] */ ILocale* locale)
{
    AutoPtr<ICalendarHelper> helper;
    CCalendarHelper::AcquireSingleton((ICalendarHelper**)&helper);
    if(!oldCalendar) {
        AutoPtr<ICalendar> calendar;
        helper->GetInstance(locale, (ICalendar**)&calendar);
        return calendar;
    } else {
        Int64 currentTimeMillis;
        oldCalendar->GetTimeInMillis(&currentTimeMillis);
        AutoPtr<ICalendar> calendar;
        helper->GetInstance(locale, (ICalendar**)&calendar);
        calendar->SetTimeInMillis(currentTimeMillis);
        return calendar;
    }
}