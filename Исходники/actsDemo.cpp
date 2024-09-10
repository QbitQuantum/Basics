int main(void)
{
  ArSerialConnection con;
  ArRobot robot;
  int ret;
  std::string str;
  ArActionLimiterForwards limiter("speed limiter near", 300, 600, 250);
  ArActionLimiterForwards limiterFar("speed limiter far", 300, 1100, 400);
  ArActionLimiterBackwards backwardsLimiter;
  ArActionConstantVelocity stop("stop", 0);
  ArActionConstantVelocity backup("backup", -200);
  ArSonarDevice sonar;
  ArACTS_1_2 acts;
  ArSonyPTZ sony(&robot);
  ArGripper gripper(&robot, ArGripper::GENIO);
  
  Acquire acq(&acts, &gripper);
  DriveTo driveTo(&acts, &gripper, &sony);
  PickUp pickUp(&acts, &gripper, &sony);

  TakeBlockToWall takeBlock(&robot, &gripper, &sony, &acq, &driveTo, &pickUp,
			    &backup);

  Aria::init();

   if (!acts.openPort(&robot))
   {
     printf("Could not connect to acts\n");
     exit(1);
   }
  
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

  sony.init();
  ArUtil::sleep(1000);
  //robot.setAbsoluteMaxTransVel(400);

  robot.setStateReflectionRefreshTime(250);
  robot.comInt(ArCommands::ENABLE, 1);
  robot.comInt(ArCommands::SOUNDTOG, 0);

  ArUtil::sleep(200);
  robot.addAction(&limiter, 100);
  robot.addAction(&limiterFar, 99);
  robot.addAction(&backwardsLimiter, 98);
  robot.addAction(&acq, 77);
  robot.addAction(&driveTo, 76);
  robot.addAction(&pickUp, 75);
  robot.addAction(&backup, 50);
  robot.addAction(&stop, 30);

  robot.run(true);
  
  Aria::shutdown();
  return 0;
}