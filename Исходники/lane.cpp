//===================================================================================
float laneHalfAngle (Pair passerLoc, // Position of the passing robot.
                     Pair passDestination, // location of the pass destination
                     const VisionData &field, // where everyone else is now
                     const SystemParameters &rp, // contains necessary game parameters  
                     const Pair * extraObstacle, // Check this (optional) location as an obstacle too 
                     bool checkOurRobots) //to see if we check for our robots or not...
{

  float minLaneAngle = PI/2.0f; // Initialize the lane half angle to PI/2 (a clear lane)

  // Lane parameters
  float laneLength = passerLoc.distanceTo (passDestination);
  laneLength = laneLength + rp.general.PLAYER_RADIUS + rp.general.BALL_RADIUS;
  float laneDirection = angleWithXAxis (passerLoc, passDestination);

  // Obstacle parameters
  Pair obstacleLoc;         // Obstacle centre location
  float obstacleDist;       // Distance of the obstacle centre from the passerLoc
  float obstacleDirection;  // Angle made by the segment from passerLoc to obstacle with the x-axis
  float obstacleHalfAngle;  // Half the angle subtended by the obstacle on the passer loc
  float angleWithLane1;     // Angle between the tangents drawn from passerLoc to obstacle with 
  float angleWithLane2;     // the lane direction


  // Check opponent robots first
  RobotIndex i;
  for (i = ROBOT0; i < NUM_ROBOTS; i++) {

    if (theirRobotFound (i, field, rp)) {

      // Get obstacle direction and distance from the passerLoc
      obstacleLoc = getTheirRobotLocation (i, field, rp);
      obstacleDist = passerLoc.distanceTo (obstacleLoc);
  
      // Get the direction of the segment from passerLoc to obstacle with the x-axis
      obstacleDirection = angleWithXAxis (passerLoc, obstacleLoc);
      obstacleHalfAngle = ATAN2 (rp.general.OPPONENT_RADIUS, obstacleDist);

      // Evaluate angles only if the passer loc is closer to the obtacle than the lane length
      if (obstacleDist <= laneLength) {

        // If the difference between the obstacle direction and lane direction is within the half
        // angle subtended by the obstacle on the passer loc, the lane is being blocked
        if (ABS (laneDirection - obstacleDirection) <= obstacleHalfAngle)
          return 0.0f;

        // Get the directions of the tangent to the obstacle from the passer loc and their angular
        // difference from the lane direction
        angleWithLane1 = ABS (angleDifference (obstacleDirection + obstacleHalfAngle, laneDirection));
        angleWithLane2 = ABS (angleDifference (obstacleDirection - obstacleHalfAngle, laneDirection));
      

        // Compare the angle of the tangent closer to the lane diretion
        float smallerAngle = MIN (angleWithLane1, angleWithLane2);
        if (smallerAngle < minLaneAngle)
          minLaneAngle = smallerAngle;

      }
    }

  }

  //IF WE WANT TO TAKE INTO ACCOUNT OUR OWN ROBOTS...
  if (checkOurRobots)
  {
    for (i = ROBOT0; i < NUM_ROBOTS; i++) {

      //If our robot is found, and he is not the passer or receiver => check to see if it is in the way
          if(robotFound(i, field, rp)&&(dist(i,passerLoc,field,rp)>rp.general.PLAYER_RADIUS)&&(dist(i,passDestination,field,rp)>rp.general.PLAYER_RADIUS)) {      

        // Get obstacle direction and distance from the passerLoc
        obstacleLoc = getLocation (i, field, rp);
        obstacleDist = passerLoc.distanceTo (obstacleLoc);
  
        // Get the direction of the segment from passerLoc to obstacle with the x-axis
        obstacleDirection = angleWithXAxis (passerLoc, obstacleLoc);
        obstacleHalfAngle = ATAN2 (rp.general.PLAYER_RADIUS, obstacleDist);

        // Evaluate angles only if the passer loc is closer to the obtacle than the lane length
        if (obstacleDist <= laneLength) {

          // If the difference between the obstacle direction and lane direction is within the half
          // angle subtended by the obstacle on the passer loc, the lane is being blocked
          if (ABS (laneDirection - obstacleDirection) <= obstacleHalfAngle)
            return 0.0f;

          // Get the directions of the tangent to the obstacle from the passer loc and their angular
          // difference from the lane direction
          angleWithLane1 = ABS (angleDifference (obstacleDirection + obstacleHalfAngle, laneDirection));
          angleWithLane2 = ABS (angleDifference (obstacleDirection - obstacleHalfAngle, laneDirection));
      

          // Compare the angle of the tangent closer to the lane diretion
          float smallerAngle = MIN (angleWithLane1, angleWithLane2);
          if (smallerAngle < minLaneAngle)
            minLaneAngle = smallerAngle;

        }
      }

    }
  }


  // Check the passed extra location as an obstacle having the radius the same as our robots
  if (extraObstacle) {

    // Get obstacle direction and distance from the passerLoc
    obstacleLoc = * extraObstacle;
    obstacleDist = passerLoc.distanceTo (obstacleLoc);

    // Get the direction of the segment from passerLoc to obstacle with the x-axis
    obstacleDirection = angleWithXAxis (passerLoc, obstacleLoc);
    obstacleHalfAngle = ATAN2 (rp.general.PLAYER_RADIUS, obstacleDist);

    // Evaluate angles only if the passer loc is closer to the obtacle than the lane length
    if (obstacleDist <= laneLength) {

      // If the difference between the obstacle direction and lane direction is within the half
      // angle subtended by the obstacle on the passer loc, the lane is being blocked
      if (ABS (laneDirection - obstacleDirection) <= obstacleHalfAngle)
        return 0.0f;

      // Get the directions of the tangent to the obstacle from the passer loc and their angular
      // difference from the lane direction
      angleWithLane1 = ABS (angleDifference (obstacleDirection + obstacleHalfAngle, laneDirection));
      angleWithLane2 = ABS (angleDifference (obstacleDirection - obstacleHalfAngle, laneDirection));
      

      // Compare the angle of the tangent closer to the lane diretion
      float smallerAngle = MIN (angleWithLane1, angleWithLane2);
      if (smallerAngle < minLaneAngle)
        minLaneAngle = smallerAngle;

    }
  }

  return minLaneAngle;
}