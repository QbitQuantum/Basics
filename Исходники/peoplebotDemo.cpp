int main(void)
{
  ArSerialConnection con;
  ArRobot robot;
  int ret;
  std::string str;
  ArActionLimiterForwards limiter("speed limiter near", 225, 600, 250);
  ArActionLimiterForwards limiterFar("speed limiter far", 225, 1100, 400);
  ArActionTableSensorLimiter tableLimiter;
  ArActionLimiterBackwards backwardsLimiter;
  ArActionConstantVelocity stop("stop", 0);
  ArSonarDevice sonar;
  ArACTS_1_2 acts;
  ArPTZ *ptz;
  ptz = new ArVCC4(&robot, true);
  ArGripper gripper(&robot);
  
  Acquire acq(&acts, &gripper);
  DriveTo driveTo(&acts, &gripper, ptz);
  DropOff dropOff(&acts, &gripper, ptz);
  PickUp pickUp(&acts, &gripper, ptz);
  

  TakeBlockToWall takeBlock(&robot, &gripper, ptz, &acq, &driveTo, &pickUp,
			    &dropOff, &tableLimiter);

  if (!acts.openPort(&robot))
  {
    printf("Could not connect to acts, exiting\n");
    exit(0);    
  }
  Aria::init();
  
  robot.addRangeDevice(&sonar);
  //con.setBaud(38400);
  if ((ret = con.open()) != 0)
  {
    str = con.getOpenMessage(ret);
    printf("Open failed: %s\n", str.c_str());
    Aria::shutdown();
    return 1;
  }

  robot.setDeviceConnection(&con);
  if (!robot.blockingConnect())
  {
    printf("Could not connect to robot... exiting\n");
    Aria::shutdown();
    return 1;
  }

  ptz->init();
  ArUtil::sleep(8000);
  printf("### 2222\n");
  ptz->panTilt(0, -40);
  printf("### whee\n");
  ArUtil::sleep(8000);
  robot.setAbsoluteMaxTransVel(400);

  robot.setStateReflectionRefreshTime(250);
  robot.comInt(ArCommands::ENABLE, 1);
  robot.comInt(ArCommands::SOUNDTOG, 0);

  ArUtil::sleep(200);
  robot.addAction(&tableLimiter, 100);
  robot.addAction(&limiter, 99);
  robot.addAction(&limiterFar, 98);
  robot.addAction(&backwardsLimiter, 97);
  robot.addAction(&acq, 77);
  robot.addAction(&driveTo, 76);
  robot.addAction(&pickUp, 75);
  robot.addAction(&dropOff, 74);
  robot.addAction(&stop, 30);

  robot.run(true);
  
  Aria::shutdown();
  return 0;
}