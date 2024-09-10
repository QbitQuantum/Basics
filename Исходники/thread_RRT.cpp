void Thread_RRT::findThreadMotion(RRT_Node& start, RRT_Node& goal, Thread_Motion& bestMotion)
{
  /*motion.pos_movement.setZero();
  motion.tan_rotation.setIdentity();

  double estimated_derivs[5];
  Matrix4d startTrans;
  start.thread->getStartTransform(startTrans);
  
  for (int dir=0; dir < 3; dir++)
  {
    //move in direction
    motion.pos_movement(dir) = DISTANCE_TO_TRY;
    RRT_Node thisNodeToTry(motion.applyMotion(start.thread));
    double pos_dir_dist = goal.distanceToNode(thisNodeToTry);

    //move in other direction
    motion.pos_movement(dir) = -DISTANCE_TO_TRY;
    RRT_Node thisNodeToTryOtherDir(motion.applyMotion(start.thread));
    double neg_dir_dist = goal.distanceToNode(thisNodeToTryOtherDir);
    //double neg_dir_dist = goal.distanceToNode(start);

    estimated_derivs[dir] = (pos_dir_dist-neg_dir_dist)/(2.0*DISTANCE_TO_TRY); 

    //cleanup for next iter
    motion.pos_movement(dir) = 0.0;
  }
  std::cout << estimated_derivs[0] << " " << estimated_derivs[1] << " " << estimated_derivs[2] << std::endl;
  motion.pos_movement = Vector3d(estimated_derivs[0]/100.0, estimated_derivs[1]/100.0, estimated_derivs[2]/100.0);
*/




  /*
  Matrix4d startTrans;
  start.thread->getStartTransform(startTrans);
  double bestScore = DBL_MAX;
  Thread_Motion thisMotion;
  for (int randSampleInd=0; randSampleInd < NUM_RANDOM_SAMPLES; randSampleInd++)
  {
    //random position movement
    for (int i=0; i < 3; i++)
    {
      thisMotion.pos_movement(i) = (2.0*MAX_DISTANCE_MOVE_EACH_DIR*((double)rand()) / ((double)RAND_MAX))-MAX_DISTANCE_MOVE_EACH_DIR;
    }

    //random rotation matrix
    double rotAng1 = (2.0*MAX_ANG_TO_ROTATE*((double)rand()) / ((double)RAND_MAX)) - MAX_ANG_TO_ROTATE;
    double rotAng2 = (2.0*MAX_ANG_TO_ROTATE*((double)rand()) / ((double)RAND_MAX)) - MAX_ANG_TO_ROTATE;
    thisMotion.setRotationMatrixFromAngs(rotAng1, rotAng2);
   
    //std::cout << "pos: " << thisMotion.pos_movement << std::endl;
    //std::cout << "tan: " << thisMotion.tan_rotation << std::endl;

    RRT_Node thisMotionTried(thisMotion.applyMotion(start.thread));
    double thisScore = goal.distanceToNode(thisMotionTried);

    if (thisScore < bestScore)
    {
      bestScore = thisScore;
      bestMotion = thisMotion;
    }
    
  }
  */

  
  //find vector to get position closer
  Vector3d startEnd;
  start.thread->getWantedEndPosition(startEnd);
  Vector3d goalEnd;
  goal.thread->getWantedEndPosition(goalEnd);

  bestMotion.pos_movement = goalEnd - startEnd;

  //add some noise to movement
  bestMotion.pos_movement(0) += randomMaxAbsValue(MAX_NOISE_DISTANCE_MOVEMENT);
  bestMotion.pos_movement(1) += randomMaxAbsValue(MAX_NOISE_DISTANCE_MOVEMENT);
  bestMotion.pos_movement(2) += randomMaxAbsValue(MAX_NOISE_DISTANCE_MOVEMENT);

  //make sure vector isn't too long (that's what she said)
  double normOfVec = bestMotion.pos_movement.norm();
  if (normOfVec > MAX_DISTANCE_MOVEMENT)
  {
    bestMotion.pos_movement *= (MAX_DISTANCE_MOVEMENT/normOfVec);
  }
 
  //rotate towards other tan
  Vector3d startTan;
  start.thread->getWantedEndTangent(startTan);
  Vector3d goalTan;
  goal.thread->getWantedEndTangent(goalTan);

  Vector3d vecToRotateAbout = startTan.cross(goalTan);
  vecToRotateAbout.normalize();
  //add noise to tan
  vecToRotateAbout(0) += randomMaxAbsValue(MAX_NOISE_ROTATION_VECTOR);
  vecToRotateAbout(1) += randomMaxAbsValue(MAX_NOISE_ROTATION_VECTOR);
  vecToRotateAbout(2) += randomMaxAbsValue(MAX_NOISE_ROTATION_VECTOR);
  vecToRotateAbout.normalize();

  double angToRotate = min(MAX_ANG_TO_ROTATE, acos(startTan.dot(goalTan)));
  angToRotate += randomMaxAbsValue(MAX_NOISE_ROTATION_ANGLE);

  bestMotion.tan_rotation = Eigen::AngleAxisd( angToRotate, vecToRotateAbout);

  

  //motion.pos_movement = Vector3d(4.0, -3.5, 1.0);
  //motion.tan_rotation = Eigen::AngleAxisd (0.0, Vector3d(1.0, 0.0, 0.0));

}