void IcalInterpreter::readRecurrenceRDates(const Property inRecurrenceProperty,
                const quint64 inIntervalSecondsToEndDate,
                const DateTime inStartDateTime,
                AppointmentRecurrence* &outAppRecurrence )
{
    // only one of both for-loops is executed
    for( Interval interval : inRecurrenceProperty.m_contentIntervalVector )
    {
        DateTime start;
        DateTime end;
        start = interval.m_start;
        if( interval.m_hasDuration )
            end = interval.m_start.addSecs( interval.m_duration.toSeconds() );
        else
            end = interval.m_end;

        Parameter timeZoneParam;
        if( inRecurrenceProperty.getParameterByType( Parameter::TZIDPARAM, timeZoneParam ) )
        {
            if( timeZoneParam.m_storageType == Parameter::PST_TIMEZONE )
                start.setTimeZone( timeZoneParam.m_contentTimeZone );
        }
        RecurringFixedIntervals fixedInterval;
        fixedInterval.setInterval( start, end );
        outAppRecurrence->m_recurFixedIntervals.append( fixedInterval );
    }

    for( DateTime startTime : inRecurrenceProperty.m_contentDateTimeVector )
    {
        DateTime newStartDate;
        if( startTime.isDate() )
            newStartDate = QDateTime( startTime.date(), inStartDateTime.time() );
        else
            newStartDate = startTime;

        DateTime endTime;
        endTime = newStartDate.addSecs( inIntervalSecondsToEndDate );
        Parameter timeZoneParam;
        if( inRecurrenceProperty.getParameterByType( Parameter::TZIDPARAM, timeZoneParam ) )
        {
            if( timeZoneParam.m_storageType == Parameter::PST_TIMEZONE )
                newStartDate.setTimeZone( timeZoneParam.m_contentTimeZone );
        }
        RecurringFixedIntervals fixedInterval;
        fixedInterval.setInterval( newStartDate, endTime );
        outAppRecurrence->m_recurFixedIntervals.append( fixedInterval );
    }
}