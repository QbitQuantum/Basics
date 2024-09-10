void checkedSleep( gbxutilacfr::Stoppable* activity, const IceUtil::Time& duration, int checkIntervalMs  )
{
    assert( activity && "Null activity pointer" );

    // Handle durations less than the check interval
    if ( duration.toMilliSeconds() < checkIntervalMs )
    {
        IceUtil::ThreadControl::sleep( duration );
        return;
    }

    IceUtil::Time wakeupTime = IceUtil::Time::now() + duration;
    IceUtil::Time checkInterval = IceUtil::Time::milliSeconds( checkIntervalMs );

    while ( !activity->isStopping() && IceUtil::Time::now() < wakeupTime )
    {
        IceUtil::ThreadControl::sleep( checkInterval );
    }
}