void LocalRobot::update()
{
  RobotConsole::update();

  // Only one thread can access *this now.
  SYNC;

  if(mode == SystemCall::logfileReplay)
  {
    if(logAcknowledged)
    {
      if(logPlayer.replay())
        logAcknowledged = false;
    }
  }
  else if(mode == SystemCall::physicalRobot)
  {
    int duration = SystemCall::getTimeSince(imageTimeStamp);
    if(duration >= 33)
    {
      imageTimeStamp = duration >= 67 ? SystemCall::getCurrentSystemTime() : imageTimeStamp + 33;
      image.timeStamp = SystemCall::getCurrentSystemTime();
    }
  }
  else if(mode == SystemCall::simulatedRobot)
  {
    if(moveOp != noMove)
    {
      if(moveOp == moveBoth)
        ctrl->moveObject(oracle.getRobot(), movePos * 0.001, moveRot * (pi / 180));
      else if(moveOp == movePosition)
        ctrl->moveObject(oracle.getRobot(), movePos * 0.001);
      else if(moveOp == moveBallPosition)
        ctrl->moveObject(oracle.getBall(), movePos * 0.001);
      moveOp = noMove;
    }

    const int imageDelay = 33;
    int duration = SystemCall::getTimeSince(imageTimeStamp);
    if(duration >= imageDelay)
    {
      imageTimeStamp = duration >= 2 * imageDelay ? SystemCall::getCurrentSystemTime() : imageTimeStamp + imageDelay;
      if(calculateImage) // If there is a PDA camera
        oracle.getImage(image);
      else
        image.timeStamp = SystemCall::getCurrentSystemTime();
      oracle.getRobotPose(robotPose);
      oracle.getBallModel(robotPose, ballModel);
    }
    else
      oracle.getRobotPose(robotPose);
    oracle.getOdometryData(robotPose, odometryData);
    oracle.getSensorData(sensorData);
    oracle.getAndSetJointData(jointRequest, jointData);    
  }

  std::string statusText;
  if(mode == SystemCall::logfileReplay)
  {
    statusText = std::string("replaying ") + logFile + " ";
    if(logPlayer.currentFrameNumber != -1)
    {
      char buf[10];
      statusText += itoa_s(logPlayer.currentFrameNumber + 1, buf, sizeof(buf), 10);
    }
    else
      statusText += "finished";
  }

  if(mode != SystemCall::logfileReplay && logPlayer.numberOfFrames != 0)
  {
    if(statusText != "")
      statusText += ", ";
    char buf[10];
    statusText += std::string("recorded ");
    statusText += itoa_s(logPlayer.numberOfFrames, buf, sizeof(buf), 10);
  }

  if(pollingFor)
  {
    statusText += statusText != "" ? ", polling for " : "polling for ";
    statusText += pollingFor;
  }

  if(!statusText.empty())
  {
    statusText = robotName.substr(robotName.find_last_of(".") + 1) + ": " + statusText;
    ctrl->printStatusText(statusText);
  }
}