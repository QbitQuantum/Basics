Boolean DateIntervalFormat::IsThisYear(
    /* [in] */ ICalendar* c)
{
    AutoPtr<ITimeZone> timeZone;
    c->GetTimeZone((ITimeZone**)&timeZone);
    AutoPtr<ICalendar> now;
    AutoPtr<CCalendarHelper> calendarHelper;
    CCalendarHelper::AcquireSingletonByFriend((CCalendarHelper**)&calendarHelper);
    calendarHelper->GetInstance(timeZone, (ICalendar**)&now);
    return GetField(c, ICalendar::YEAR) == GetField(now, ICalendar::YEAR);
}