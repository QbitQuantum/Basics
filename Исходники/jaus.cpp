/*
 * Main program entry point.
 */
int main(int argc, char* argv[])
{
    std::cout << "Initializing ROS component... ";

    // ROS initialization stuff
    ros::init(argc, argv, "jaus");

    ros::NodeHandle n;

    // subscriptions
    subscriberCmdVel = n.subscribe(ROSTopicCmdVelocity, 1000, ROSVelocityCallback);
    subscriberOdom   = n.subscribe(ROSTopicOdometry, 1000, ROSOdometryCallback);

    // publications
    publisherSetLocalPose = n.advertise<nav_msgs::Odometry>(ROSTopicSetLocalPose, 1000);

    //  -- we just use std_msgs::String for waypoints for now, until we can all agree on
    //     some custom ROS messages for setting local pose, and setting waypoints...
    publisherSetWaypoints = n.advertise<std_msgs::String>(ROSTopicSetWaypoints, 1000);

    std::cout << "OK" << std::endl;

    // JAUS initialization stuff
    JAUS::Component component;
    JAUS::Subsystem* judgeSubsystem;

    std::cout << "Initializing JAUS component... ";

    if (InitializeJAUSComponent(&component) < 0)
    {
        std::cout << "Failed!" << std::endl;
        return -1;
    }

    std::cout << "OK" << std::endl;

    std::cout << "Searching for Judges' COP... ";

    if ((judgeSubsystem = DiscoverJudgeSubsystem(&component)) == NULL)
    {
        std::cout << "Failed!" << std::endl;
        return -1;
    }

    std::cout << "Success (Identification: " << judgeSubsystem->mIdentification << ")" << std::endl;

    /*
     * Set initial states for services
     */

    // Set an initial local pose
    JAUS::LocalPose localPose;
    localPose.SetX(0.0);
    localPose.SetY(0.0);
    localPose.SetTimeStamp(JAUS::Time::GetUtcTime());
    localPoseSensor->SetLocalPose(localPose);

    // Set an initial velocity state
    JAUS::VelocityState velocityState;
    velocityState.SetVelocityX(0.0);
    velocityState.SetYawRate(0.0);
    velocityState.SetTimeStamp(JAUS::Time::GetUtcTime());
    velocityStateSensor->SetVelocityState(velocityState);

    // now loop forever
    std::cout << "READY, We are now listening to ROS topics and updating current JAUS state..." << std::endl;

    JAUS::Management* managementService = (JAUS::Management*)component.GetService(JAUS::Management::Name);
    JAUS::Time::Stamp displayStatusTimeMs = JAUS::Time::GetUtcTimeMs();

    while (true) // (managementService->GetStatus() != JAUS::Management::Status::Shutdown)
    {
        if (CxUtils::GetChar() == 'q')
            break;

        if (JAUS::Time::GetUtcTimeMs() - displayStatusTimeMs > 2000)
        {
            managementService->PrintStatus(); // display a status message
            displayStatusTimeMs = JAUS::Time::GetUtcTimeMs();
        }

        ros::spinOnce(); // process ROS callbacks

        CxUtils::SleepMs(10); // save some CPU time
    }

    component.Shutdown(); // this will take care of cleanup
    return 0;
}