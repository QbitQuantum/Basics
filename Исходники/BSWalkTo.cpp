void BSWalkTo::walkTo(Pose2D target, float speed, bool rough)
{
  if(target.translation == Vector2<>())
  {
    generateMotionRequest(target, speed);
    lastAvoidanceAngleOffset = 0;
    return;
  }

  //
  RobotPose robotPoseInv = theRobotPose.invert();
  obstacleCount = 0;

  // the field border is an obstacle
  if(theRobotPose.translation.y > leftOppCorner.y - p.fieldBorderAvoidanceDistance)
  {
    Vector2<> obstaclePos(theRobotPose.translation.x, leftOppCorner.y);
    if(obstaclePos.y < theRobotPose.translation.y + 10.f)
      obstaclePos.y = theRobotPose.translation.y + 10.f;
    obstaclePos = robotPoseInv * obstaclePos;
    addObstacle2(obstaclePos, 300.f, p.fieldBorderAvoidanceMinRadius, p.fieldBorderAvoidanceMaxRadius, p.fieldBorderAvoidanceDistance);
  }
  if(theRobotPose.translation.y < rightOppCorner.y + p.fieldBorderAvoidanceDistance)
  {
    Vector2<> obstaclePos(theRobotPose.translation.x, rightOppCorner.y);
    if(obstaclePos.y > theRobotPose.translation.y - 10.f)
      obstaclePos.y = theRobotPose.translation.y - 10.f;
    obstaclePos = robotPoseInv * obstaclePos;
    addObstacle2(obstaclePos, 300.f, p.fieldBorderAvoidanceMinRadius, p.fieldBorderAvoidanceMaxRadius, p.fieldBorderAvoidanceDistance);
  }
  if(theRobotPose.translation.x > leftOppCorner.x - p.fieldBorderAvoidanceDistance)
  {
    Vector2<> obstaclePos(leftOppCorner.x, theRobotPose.translation.y);
    if(obstaclePos.x < theRobotPose.translation.x + 10.f)
      obstaclePos.x = theRobotPose.translation.x + 10.f;
    obstaclePos = robotPoseInv * obstaclePos;
    addObstacle2(obstaclePos, 300.f, p.fieldBorderAvoidanceMinRadius, p.fieldBorderAvoidanceMaxRadius, p.fieldBorderAvoidanceDistance);
  }
  if(theRobotPose.translation.x < leftOwnCorner.x + p.fieldBorderAvoidanceDistance)
  {
    Vector2<> obstaclePos(leftOwnCorner.x, theRobotPose.translation.y);
    if(obstaclePos.x > theRobotPose.translation.x - 10.f)
      obstaclePos.x = theRobotPose.translation.x - 10.f;
    obstaclePos = robotPoseInv * obstaclePos;
    addObstacle2(obstaclePos, 300.f, p.fieldBorderAvoidanceMinRadius, p.fieldBorderAvoidanceMaxRadius, p.fieldBorderAvoidanceDistance);
  }

  // goal triangles are obstacles
  float sqrFieldBorderAvoidanceDistance = sqr(p.fieldBorderAvoidanceDistance);
  Vector2<> closestPointOnLine;
  if(getSqrDistanceToLine(goalPosts[2], Vector2<>(-1.f, 0.f), 1000.f, theRobotPose.translation, closestPointOnLine) < sqrFieldBorderAvoidanceDistance)
    addObstacle2(closestPointOnLine, 300.f, p.fieldBorderAvoidanceMinRadius, p.fieldBorderAvoidanceMaxRadius, p.fieldBorderAvoidanceDistance);
  if(getSqrDistanceToLine(goalPosts[3], Vector2<>(-1.f, 0.f), 1000.f, theRobotPose.translation, closestPointOnLine) < sqrFieldBorderAvoidanceDistance)
    addObstacle2(closestPointOnLine, 300.f, p.fieldBorderAvoidanceMinRadius, p.fieldBorderAvoidanceMaxRadius, p.fieldBorderAvoidanceDistance);

  // goal posts
  float sqrGoalPostAvoidanceDistance = p.goalPostAvoidanceDistance * p.goalPostAvoidanceDistance;
  for(int i = 0; i < 4; ++i)
    if((goalPosts[i] -  theRobotPose.translation).squareAbs() < sqrGoalPostAvoidanceDistance)
      addObstacle2(robotPoseInv * goalPosts[i], 50.f, p.goalPostAvoidanceMinRadius, p.goalPostAvoidanceMaxRadius, p.goalPostAvoidanceDistance);

  // the own penalty area is an obstacle
  if(theRobotInfo.number != 1 && theGameInfo.state == STATE_PLAYING)
  {
    if(theRobotPose.translation.x < leftPenCorner.x + p.penaltyAreaAvoidanceDistance &&
       theRobotPose.translation.y < leftPenCorner.y + p.penaltyAreaAvoidanceDistance &&
       theRobotPose.translation.y > rightPenCorner.y - p.penaltyAreaAvoidanceDistance) // is near penalty area?
    {
      // compute "obstacle" pos
      const Vector2<> supportPoint(leftPenCorner.x - leftPenCorner.y, 0.f);
      Vector2<> obstacleDir = supportPoint - theRobotPose.translation;
      obstacleDir.normalize(p.penaltyAreaAvoidanceDistance);
      Vector2<> obstaclePos = theRobotPose.translation + obstacleDir;
      if(obstaclePos.x < leftPenCorner.x &&
         obstaclePos.y < leftPenCorner.y &&
         obstaclePos.y > rightPenCorner.y)
      {
        float xoff = (leftPenCorner.x - obstaclePos.x);
        float yoff = (obstaclePos.y > 0.f ? (leftPenCorner.y - obstaclePos.y) : (obstaclePos.y - rightPenCorner.y));
        float a = std::min(xoff, yoff);
        obstacleDir *= std::max(p.penaltyAreaAvoidanceDistance - a, 1.f) * (1.f / p.penaltyAreaAvoidanceDistance);
        if(yoff < xoff)
          obstacleDir = Vector2<>(0.f, obstaclePos.y > 0.f ? -obstacleDir.abs() : obstacleDir.abs());
        else
          obstacleDir = Vector2<>(-obstacleDir.abs(), 0.f);
        obstaclePos = theRobotPose.translation + obstacleDir;
      }
      obstaclePos = robotPoseInv * obstaclePos;
      addObstacle2(obstaclePos, 300.f, p.penaltyAreaAvoidanceMinRadius, p.penaltyAreaAvoidanceMaxRadius, p.penaltyAreaAvoidanceDistance);
    }
  }

  // obstacles from ObstacleModel
  if(true)//!disableObstacleAvoidance)
    for(std::vector<ObstacleModel::Obstacle>::const_iterator it = theObstacleModel.obstacles.begin(), end = theObstacleModel.obstacles.end(); it != end; ++it)
    {
      const ObstacleModel::Obstacle& obstacle = *it;
      const float sqrAbs = obstacle.center.squareAbs();
      if(sqrAbs < sqr(p.obstacleAvoidanceDistance))
        addObstacle2(obstacle.leftCorner, obstacle.rightCorner, obstacle.center, sqrt(sqrAbs), p.obstacleAvoidanceMinRadius, p.obstacleAvoidanceMaxRadius, p.obstacleAvoidanceDistance);
    }

  // obstacles from vision
  if(true)//!disableObstacleAvoidance)
    for(std::vector<RobotsModel::Robot>::const_iterator it = theRobotsModel.robots.begin(), end = theRobotsModel.robots.end(); it != end; ++it)
    {
      const RobotsModel::Robot& robot = *it;
      if(theFrameInfo.getTimeSince(robot.timeStamp) < p.visionObstacleTimeout)
      {
        const float sqrAbs = robot.relPosOnField.squareAbs();
        const float expandLength = robot.standing ? 150.f : 300.f;
        float obstacleAvoidanceDistance = p.obstacleAvoidanceDistance/* + expandLength*/;
        if(sqrAbs < sqr(obstacleAvoidanceDistance))
        {
          //const float obstacleDistance = std::max(sqrt(sqrAbs) - expandLength, 1.f); // reducing the distance causes strange avoidance when an opponent robot is close by
          Vector2<> obstaclePos = robot.relPosOnField;
          //obstaclePos.normalize(obstacleDistance);
          addObstacle2(obstaclePos, expandLength, p.obstacleAvoidanceMinRadius, p.obstacleAvoidanceMaxRadius, p.obstacleAvoidanceDistance);
        }
      }
    }

  // and... the ball is an obstacle
  if(theFrameInfo.getTimeSince(theBallHypotheses.timeWhenDisappeared) < p.ballTimeout)
  {
    const Vector2<>& ballPosition = theBallModel.estimate.position;
    if(ballPosition.squareAbs() < sqr(p.ballAvoidanceDistance))
    {
      // calculate angle between robot and score position (from ball)
      //float alpha = acos((target.translation - ballPosition).normalize() * (-ballPosition).normalize());
      //float radius = p.ballAvoidanceMaxRadius * (alpha / pi);
      addObstacle2(ballPosition, 35.f, p.ballAvoidanceMinRadius, p.ballAvoidanceMaxRadius, p.ballAvoidanceDistance);
    }
  }

  // find out which obstacles disturb our plan
  if(rough)
  {
    float targetSqrDistance = target.translation.squareAbs();
    for(unsigned int i = 0; i < obstacleCount; ++i)
    {
      Obstacle& obstacle = obstacles[i];
      float factor = getOrthogonalProjectionFactor(Vector2<>(), target.translation, obstacle.centerPosition);
      if(factor < 0.f || factor > 1.f || (obstacle.leftPosition.squareAbs() > targetSqrDistance && obstacle.rightPosition.squareAbs() > targetSqrDistance))
        obstacle.active = false;
    }
  }

#ifndef TARGET_TOOL
  COMPLEX_DRAWING("module:BH2011BehaviorControl:BSWalkTo:Field",
  {
    for(unsigned int i = 0; i < obstacleCount; ++i)
    {
      const Obstacle& obstacle = obstacles[i];
      if(!obstacle.active)
        continue;
      Vector2<> base(obstacle.centerPosition.abs(), 0.f);
      base.rotate(obstacle.centerAngle);
      LINE("module:BH2011BehaviorControl:BSWalkTo:Field", 0, 0, base.x, base.y, 0, Drawings::ps_solid, ColorRGBA(0xff, 0, 0));
      for(float j = 0.1f; j < obstacle.openingAngle * 0.5f; j += 0.1f)
      {
        Vector2<> line = base;
        line.rotate(j);
        LINE("module:BH2011BehaviorControl:BSWalkTo:Field", 0, 0, line.x, line.y, 0, Drawings::ps_solid, ColorRGBA(0xaa, 0xaa, 0xaa));
        line = base;
        line.rotate(-j);
        LINE("module:BH2011BehaviorControl:BSWalkTo:Field", 0, 0, line.x, line.y, 0, Drawings::ps_solid, ColorRGBA(0xaa, 0xaa, 0xaa));
      }

      Vector2<> line = base;
      line.rotate(obstacle.openingAngle * 0.5f);
      LINE("module:BH2011BehaviorControl:BSWalkTo:Field", 0, 0, line.x, line.y, 0, Drawings::ps_solid, ColorRGBA(0, 0, 0));
      line = base;
      line.rotate(-obstacle.openingAngle * 0.5f);
      LINE("module:BH2011BehaviorControl:BSWalkTo:Field", 0, 0, line.x, line.y, 0, Drawings::ps_solid, ColorRGBA(0, 0, 0));
    }
  });