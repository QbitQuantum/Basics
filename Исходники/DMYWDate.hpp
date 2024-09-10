int
DMYWDate<Cal, WeekType>::DayOfWeek( ) const
{
    return ModF( (this->JulianDay( ) + Week::DayOfWeekOfJD0()),
                 (long)Week::DaysInWeek() );
}