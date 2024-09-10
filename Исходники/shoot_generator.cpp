/*!

 */
void
ShootGenerator::generate( const WorldModel & wm, bool consider_shot_distance )
{
#ifdef __APPLE__
    static GameTime s_update_time( 0, 0 );
#else
    static thread_local GameTime s_update_time( 0, 0 );
#endif

    if ( s_update_time == wm.time() )
    {
        return;
    }
    s_update_time = wm.time();

    clear();

    if ( ! wm.self().isKickable()
         && wm.interceptTable()->selfReachCycle() > 1 )
    {
        return;
    }

    if ( wm.time().stopped() > 0
         || wm.gameMode().type() == GameMode::KickOff_
         // || wm.gameMode().type() == GameMode::KickIn_
         || wm.gameMode().type() == GameMode::IndFreeKick_ )
    {
        return;
    }

    const ServerParam & SP = ServerParam::i();

    if ( consider_shot_distance &&
         wm.self().pos().dist2( SP.theirTeamGoalPos() ) > std::pow( 30.0, 2 ) )
    {
#ifdef DEBUG_PRINT
      dlog.addText( Logger::SHOOT,
                    __FILE__": over shootable distance" );
#endif
      return;
    }

    M_first_ball_pos = ( wm.self().isKickable()
                         ? wm.ball().pos()
                         : wm.ball().pos() + wm.ball().vel() );

#ifdef DEBUG_PROFILE
    MSecTimer timer;
#endif

    Vector2D goal_l( SP.pitchHalfLength(), -SP.goalHalfWidth() );
    Vector2D goal_r( SP.pitchHalfLength(), +SP.goalHalfWidth() );

    goal_l.y += std::min( 1.5,
                          0.6 + goal_l.dist( M_first_ball_pos ) * 0.042 );
    goal_r.y -= std::min( 1.5,
                          0.6 + goal_r.dist( M_first_ball_pos ) * 0.042 );

    if ( wm.self().pos().x > SP.pitchHalfLength() - 1.0
         && wm.self().pos().absY() < SP.goalHalfWidth() )
    {
        goal_l.x = wm.self().pos().x + 1.5;
        goal_r.x = wm.self().pos().x + 1.5;
    }

    const int DIST_DIVS = 25;
    const double dist_step = std::fabs( goal_l.y - goal_r.y ) / ( DIST_DIVS - 1 );

#ifdef DEBUG_PRINT
    dlog.addText( Logger::SHOOT,
                  __FILE__": ===== Shoot search range=(%.1f %.1f)-(%.1f %.1f) dist_step=%.1f =====",
                  goal_l.x, goal_l.y, goal_r.x, goal_r.y, dist_step );
#endif

    for ( int i = 0; i < DIST_DIVS; ++i )
    {
        ++M_total_count;

        Vector2D target_point = goal_l;
        target_point.y += dist_step * i;

#ifdef DEBUG_PRINT
        dlog.addText( Logger::SHOOT,
                      "%d: ===== shoot target(%.2f %.2f) ===== ",
                      M_total_count,
                      target_point.x, target_point.y );
#endif
        createShoot( wm, target_point );
    }


    evaluateCourses( wm );


#ifdef DEBUG_PROFILE
    dlog.addText( Logger::SHOOT,
                  __FILE__": PROFILE %d/%d. elapsed=%.3f [ms]",
                  (int)M_courses.size(),
                  DIST_DIVS,
                  timer.elapsedReal() );
#endif

}