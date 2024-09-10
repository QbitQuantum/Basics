RSExport void RSCalendarSetFirstWeekday(RSCalendarRef calendar, RSIndex wkdy)
{
    RS_OBJC_FUNCDISPATCHV(RSCalendarGetTypeID(), RSIndex, calendar, firstWeekday);
    __RSGenericValidInstance(calendar, __RSCalendarTypeID);
    if (!calendar->_cal) __RSCalendarSetupCal(calendar);
    if (calendar->_cal)
    {
        ucal_setAttribute(calendar->_cal, UCAL_FIRST_DAY_OF_WEEK, (RSBit32)wkdy);
    }
}