CCareerTask::CCareerTask( const char *taskName, GameEventType event, const char *weaponName, int n, bool mustLive, bool crossRounds, int id, bool isComplete )
{
    m_eventsSeen     = 0;
    m_name           = taskName;
    m_isComplete     = isComplete;
    m_event          = event;
    m_eventsNeeded   = n;
    m_mustLive       = mustLive;
    m_diedThisRound  = 0;
    m_crossRounds    = crossRounds;
    m_id             = id;
    //m_weaponId       = AliasToWeaponID( weaponName );
    //m_weaponClassId  = AliasToWeaponClass( weaponName );
    m_rescuer        = _strcmpi( taskName, "stoprescue" ) == 0;
    m_defuser        = _strcmpi( taskName, "killdefuser" ) == 0;
    m_vip            = _strcmpi( taskName, "killvip" ) == 0;

    if( event == EVENT_ALL_HOSTAGES_RESCUED )
    {
        m_mustLive    = 1;
        m_crossRounds = false;
    }

    if( m_isComplete )
    {
        MESSAGE_BEGIN( MSG_ALL, gmsgCZCareer );
            WRITE_STRING( "TASKDONE" );
            WRITE_BYTE( m_id );
        MESSAGE_END();
    }
}