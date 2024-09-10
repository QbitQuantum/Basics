int 
BadiDate::DayOfWeek( ) const
{
    return (int)ModF( (JulianDay( ) + BahaiWeek::DayOfWeekOfJD0()),
                      (long)BahaiWeek::DaysInWeek() );
}