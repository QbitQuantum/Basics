/*!

 */
void
CrossGenerator::generate( const WorldModel & wm )
{
    static thread_local GameTime s_update_time( -1, 0 );
    if ( s_update_time == wm.time() )
    {
        return;
    }
    s_update_time = wm.time();

    clear();

    if ( wm.time().stopped() > 0
         || wm.gameMode().isPenaltyKickMode() )
    {
        return;
    }

#ifdef DEBUG_PROFILE
    Timer timer;
#endif

    updatePasser( wm );

    if ( ! M_passer
         || ! M_first_point.isValid() )
    {
        dlog.addText( Logger::CROSS,
                      __FILE__" (generate) passer not found." );
        return;
    }

    if ( ServerParam::i().theirTeamGoalPos().dist( M_first_point ) > 35.0 )
    {
        dlog.addText( Logger::CROSS,
                      __FILE__" (generate) first point(%.1f %.1f) is too far from the goal.",
                      M_first_point.x, M_first_point.y );
        return;
    }

    updateReceivers( wm );

    if ( M_receiver_candidates.empty() )
    {
        dlog.addText( Logger::CROSS,
                      __FILE__" (generate) no receiver." );
        return;
    }

    updateOpponents( wm );

    createCourses( wm );

#ifdef DEBUG_PROFILE
    dlog.addText( Logger::CROSS,
                  __FILE__" (generate) PROFILE course_size=%d/%d elapsed %f [ms]",
                  (int)M_courses.size(),
                  M_total_count,
                  timer.elapsedReal() );
#endif
}