/* we always reason about the right trajectory for the ball leave velocity
   correction for dokick */
KickToRes turnball_kick(AngleDeg target_dir, TurnDir rotate, 
		  Bool StopBall, TurnKickCommand* pCom,
		  float EndDist, float closeMarg, float kickFac)
{
  float dir;
  float dist;
  Vector btraj;

  pCom->time = -1;
  pCom->turn_neck = FALSE;
  
  DebugKick(printf("\nat turnball_kick: target_dir: %f\n", target_dir));
  LogAction4(60, "Turnball_kick: targ_dir: %.1f  dir: %d", target_dir, (int)rotate);
  
  NormalizeAngleDeg(&target_dir);
  
  //DebugKick(printf("HERE Time: %d\n", Mem->CurrentTime.t));
  /* the pos valid is not really right - if we are turning the ball and didn't
     actually see it last time, then there's a problem */
  if ( !Mem->BallPositionValid() || !Mem->BallKickable() ) {
    LogAction2(90, "turnball_kick: lost the ball");
    return KT_LostBall;
  }

  /* if the velocity isn's valid, turn to face ball */
  if ( !Mem->BallVelocityValid() ) {
    float ball_ang_from_body = Mem->BallAngleFromBody(); /* for efficiency */
    LogAction2(90, "turnball_kick: vel is not valid, looking at it");
    DebugKick(printf("turning to face ball\n"));
    if (Mem->CanSeeBallWithNeck()) {
      pCom->time = Mem->CurrentTime;
      pCom->type = CMD_kick;
      pCom->angle = ball_ang_from_body + 180;
      pCom->power = Mem->CP_stop_ball_power;

      pCom->turn_neck = TRUE;
      pCom->turn_neck_angle = Mem->LimitTurnNeckAngle(Mem->BallAngleFromNeck());
    } else {
      /* turn body to face ball, and turn neck to straight ahead */
      pCom->time = Mem->CurrentTime;
      pCom->type = CMD_turn;
	pCom->turn_neck = TRUE;
      if (fabs(ball_ang_from_body) > Mem->MaxEffectiveTurn()) {
	/* out body can't get to where we want to go */
	pCom->angle = 180; /* get our maximum effective turn */
	pCom->turn_neck_angle = ball_ang_from_body -
	  signf(ball_ang_from_body)*Mem->MaxEffectiveTurn();
      } else {
	pCom->angle = ball_ang_from_body;
	pCom->turn_neck_angle = -Mem->MyNeckRelAng();
      }
      
    }
    
    return KT_TurnedToBall;
  } 
  
  DebugKick(printf(" ball.dist: %f\t.dir: %f\n",
	 Mem->BallDistance(), Mem->BallAngle()));
  DebugKick(printf(" HERE ball.vel.x: %f\t.y: %f\tmod: %f\n",
	 Mem->BallRelativeVelocity().x, Mem->BallRelativeVelocity().y,
	 Mem->BallSpeed()));
  DebugKick(printf(" ball.rpos.x: %f\t.y: %f\n",
	 Mem->BallRelativePosition().x, Mem->BallRelativePosition().y));
  DebugKick(printf(" target_dir: %f\n", target_dir));

  if ( fabs(GetNormalizeAngleDeg(target_dir - Mem->BallAngleFromBody())) < Mem->CP_KickTo_err) {
    /* Do something to indicate we are done */
    if (!StopBall || Mem->BallSpeed() < Mem->CP_max_ignore_vel)
      return KT_DidNothing;
    LogAction2(90, "turnball_kick: we're there, stopping the ball");
    DebugKick(printf("  Stop ball kick\n"));
    dir = 0;
    dist = 0;    
    PlayerMovementCorrection(&dir, &dist);
    *pCom = dokick(dir, dist, 1.0);
    pCom->turn_neck = FALSE;
    return KT_Success;
  }

  if (rotate == TURN_AVOID) {
    rotate = RotToAvoidOpponent(target_dir + Mem->MyBodyAng());
  }
  
  if (rotate == TURN_CLOSEST) {
    rotate = RotClosest(target_dir + Mem->MyBodyAng());
  }
  
  
  if (is_straight_kick(target_dir, EndDist, closeMarg)) {
    float pow;
      
    btraj = Polar2Vector(EndDist, target_dir) - Mem->BallRelativeToBodyPosition();
    dir = btraj.dir();
    dist = btraj.mod();
    
    /* now we're goign to do some distance twiddling to get the ball to
       get to the right angle and stop */
    pow = dist / Mem->BallKickRate();
    pow = Min(pow, Mem->CP_max_turn_kick_pow);
    dist = pow * Mem->BallKickRate();
      
    LogAction4(90, "turnball_kick: striaght kick: dist %f at %f", dist, dir);
    DebugKick(printf("  Straight kick# dir: %f dist: %f\n", dir, dist));
    PlayerMovementCorrection(&dir, &dist);
    *pCom = dokick(dir, dist, 1.0);
    pCom->turn_neck = FALSE;

  } else if (Mem->BallDistance() < closeMarg) {

    /* ball is too close to do a tangent kick, so do a kick at 90 degrees */
    dir = ((int)rotate)*(-90) + Mem->BallAngleFromBody();
    dist = 2.0*sqrt(Sqr(Mem->CP_opt_ctrl_dist) - Sqr(Mem->BallDistance()));
    LogAction2(90, "turnball_kick: 90 deg kick");
    DebugKick(printf("  Close kick# dir: %f dist: %f\n", dir, dist));
    PlayerMovementCorrection(&dir, &dist);
    *pCom = dokick(dir, dist, kickFac);
    pCom->turn_neck = FALSE;

  } else {

    /* do a turning kick */
    /* we make a circle around the player of radius closeMarg
       and calculate the trajectory that goes in the right direction and is
       tangent to the circle */
    dir = 180 + Mem->BallAngleFromBody() + ((int)rotate)*ASin(closeMarg / Mem->BallDistance());
    DebugKick(printf(" ball dist: %f\tclosest_margin: %f\n",
	   Mem->BallDistance(), closeMarg));
    dist = sqrt(Sqr(Mem->BallDistance()) - Sqr(closeMarg));
    dist +=
      sqrt(Sqr(Mem->CP_opt_ctrl_dist) - Sqr(closeMarg));
    DebugKick(printf("  Turning ball# dir: %f dist: %f\n", dir, dist));
    LogAction2(90, "turnball_kick: turning kick");
    PlayerMovementCorrection(&dir, &dist);
    *pCom = dokick(dir, dist, kickFac);
    pCom->turn_neck = FALSE;

  }

  return KT_DidKick;
}