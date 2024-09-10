/*!

 */
void
TackleGenerator::generate( const WorldModel & wm )
{
    static GameTime s_update_time( 0, 0 );

    if ( s_update_time == wm.time() )
    {
        // dlog.addText( Logger::CLEAR,
        //               __FILE__": already updated" );
        return;
    }
    s_update_time = wm.time();

    clear();

    if ( wm.self().isKickable() )
    {
        // dlog.addText( Logger::CLEAR,
        //               __FILE__": kickable" );
        return;
    }

    if ( wm.self().tackleProbability() < 0.001
         && wm.self().foulProbability() < 0.001 )
    {
        // dlog.addText( Logger::CLEAR,
        //               __FILE__": never tacklable" );
        return;
    }

    if ( wm.time().stopped() > 0 )
    {
        // dlog.addText( Logger::CLEAR,
        //               __FILE__": time stopped" );
        return;
    }

    if ( wm.gameMode().type() != GameMode::PlayOn
         && ! wm.gameMode().isPenaltyKickMode() )
    {
        // dlog.addText( Logger::CLEAR,
        //               __FILE__": illegal playmode " );
        return;
    }


#ifdef DEBUG_PROFILE
    MSecTimer timer;
#endif

    calculate( wm );

#ifdef DEBUG_PROFILE
    dlog.addText( Logger::CLEAR,
                  __FILE__": PROFILE. elapsed=%.3f [ms]",
                  timer.elapsedReal() );
#endif

}