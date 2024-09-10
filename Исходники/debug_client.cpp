/*!

*/
void
DebugClient::toStr( const WorldModel & world,
                    const ActionEffector & effector )
{
    std::ostringstream ostr;

    ostr << "((debug (format-version 3)) (time "
         << world.time().cycle() << ")";


    // self
    /*
      SELF ::=  (s SIDE PLAYER_NUMBER POS_X POS_Y VEL_X VEL_Y
      BODY_DIRECTION FACE_DIRECTION  [(c "COMMENT")])
      where SIDE is 'l' or 'r'.
      where PLAYER_NUMBER is 1 to 11.
      where POS_X and POS_Y is absolute coordinate.
      where VEL_X and VEL_Y is absolute velocity.
      where BODY_DIRECTION is absolute player body direction (degree).
      where NECK_DIRECTION is body relative face direction (degree).
      This is equals to (absolute_face_direction - BODY_DIRECTION).
      where COMMENT is a string.
      Typically, it is used as information accuracy.
    */
    if ( world.self().posValid() )
    {
        ostr << " (s "
             << ( world.ourSide() == LEFT ? "l " : "r " )
             << world.self().unum() << ' '
             << ROUND(world.self().pos().x, 0.01) << ' '
             << ROUND(world.self().pos().y, 0.01) << ' '
             << ROUND(world.self().vel().x, 0.01) << ' '
             << ROUND(world.self().vel().y, 0.01) << ' '
             << ROUND(world.self().body().degree(), 0.1) << ' '
             << ROUND(world.self().neck().degree(), 0.1) << " (c \""
             << world.self().posCount() << ' '
            //<< '(' << ROUND(world.self().posError().x, 0.001)
            //<< ", " << ROUND(world.self().posError().y, 0.001) << ") "
             << world.self().velCount() << ' '
             << world.self().faceCount();
        if ( world.self().card() == YELLOW ) ostr << "y";
        ostr << "\"))";
    }

    // ball
    /*
      BALL_INFO ::=  (b POS_X POS_Y [VEL_X VEL_Y] [(c "COMMENT")])
    */
    if ( world.ball().posValid() )
    {
        ostr << " (b "
             << ROUND(world.ball().pos().x, 0.01) << ' '
             << ROUND(world.ball().pos().y, 0.01);
        if ( world.ball().velValid() )
        {
            ostr << ' ' << ROUND(world.ball().vel().x, 0.01)
                 << ' ' << ROUND(world.ball().vel().y, 0.01);
        }
        ostr << " (c \"g" << world.ball().posCount()
             << 'r' << world.ball().rposCount()
            //<< "(" << ROUND(world.ball().rpos().x, 0.01)
            // << ", " << ROUND(world.ball().rpos().y, 0.01) << ')'
             << 'v' << world.ball().velCount()
            //<< "(" << ROUND(world.ball().vel().x, 0.01)
            // << ", " << ROUND(world.ball().vel().y, 0.01) << ')'
             << "\"))";
    }

    // players
    /*
      PLAYER_INFO ::=  (TEAM [PLAYER_NUMBER] POS_X POS_Y
      [(bd BODY_DIRECTION)] [(c "COMMENT")])
      TEAM is one of follows.
      't' (teammate), 'o' (opponent),
      'u' (unknown), 'ut' (unknown teammate), 'ut' (unknown opponent).
      When TEAM is 't' or 'o', PLAYER_NUMBER must be specified.
      Otherwise PLAYER_NUMBER must not be specified.
      Body direction and comment is optional.
    */

    std::for_each( world.teammates().begin(),
                   world.teammates().end(),
                   PlayerPrinter( ostr, 't' ) );

    std::for_each( world.opponents().begin(),
                   world.opponents().end(),
                   PlayerPrinter( ostr, 'o' ) );

    std::for_each( world.unknownPlayers().begin(),
                   world.unknownPlayers().end(),
                   PlayerPrinter( ostr, 'u' ) );

    // say message
    if ( ! effector.getSayMessage().empty() )
    {
        ostr << " (say \"";
        for ( std::vector< const SayMessage * >::const_iterator it = effector.sayMessageCont().begin();
              it != effector.sayMessageCont().end();
              ++it )
        {
            (*it)->printDebug( ostr );
        }
        ostr << " {" << effector.getSayMessage() << "}\")";
    }

    // heard information
    if ( world.audioMemory().time() == world.time() )
    {
        ostr << " (hear ";
        world.audioMemory().printDebug( ostr );
        ostr << ')';
    }

    // target number
    if ( M_target_unum != Unum_Unknown )
    {
        ostr << " (target-teammate " << M_target_unum << ")";
    }

    // target point
    if ( M_target_point.isValid() )
    {
        ostr << " (target-point "
             << M_target_point.x << " " << M_target_point.y
             << ")";
    }

    // message
    if ( ! M_message.empty() )
    {
        ostr << " (message \"" << M_message << "\")";
    }

    // lines
    std::for_each( M_lines.begin(), M_lines.end(),
                   LinePrinter( ostr ) );
    // triangles
    std::for_each( M_triangles.begin(), M_triangles.end(),
                   TrianglePrinter( ostr ) );
    // rectangles
    std::for_each( M_rectangles.begin(), M_rectangles.end(),
                   RectPrinter( ostr ) );
    // circles
    std::for_each( M_circles.begin(), M_circles.end(),
                   CirclePrinter( ostr ) );

    ostr << ")";

    M_main_buffer.assign( ostr.str() );
}