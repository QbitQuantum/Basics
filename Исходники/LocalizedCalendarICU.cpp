static unsigned getFirstDayOfWeek()
{
    ScopedDateFormat dateFormat;
    if (!dateFormat.get())
        return 0;
    unsigned firstDay = ucal_getAttribute(udat_getCalendar(dateFormat.get()), UCAL_FIRST_DAY_OF_WEEK) - UCAL_SUNDAY;
    return firstDay;
}