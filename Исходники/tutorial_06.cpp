int main(int argc, char* argv[])
{
    JAUS::Component component;

    // Add services to a component is done using the AddService
    // method.  Services can only be added before a 
    // component is initialized using the Initialize method.
    // Any attempt to add after will fail.  Finally, you
    // cannot add multiple of the same service.

    // Create a Global Pose Sensor service.
    JAUS::GlobalPoseSensor* globalPoseSensor = new JAUS::GlobalPoseSensor();
    // Set the update rate of the sensor (Hz).  This
    // is used to determine what type of periodic
    // events the sensor can support.
    globalPoseSensor->SetSensorUpdateRate(25);

    // Set some global pose values.
    JAUS::GlobalPose globalPose;
    globalPose.SetLatitude(34.12345);
    globalPose.SetLongitude(-116.12345);
    globalPose.SetAltitude(100);
    globalPose.SetTimeStamp(JAUS::Time(true));
    // Set the values.
    globalPoseSensor->SetGlobalPose(globalPose);

    // Add the sensor service to the component. Remember
    // this must be done before initialization.  Also,
    // the component will delete the service for us
    // automatically, so we don't have to!
    component.AddService(globalPoseSensor);

    // Setup identification info.  For questions about this,
    // see the previous tutorial(s).
    JAUS::Discovery* discoveryService = NULL;
    discoveryService = component.DiscoveryService();
    discoveryService->SetSubsystemIdentification(JAUS::Subsystem::Vehicle,
                                                 "Robot");
    discoveryService->SetNodeIdentification("Primary Computer");
    discoveryService->SetComponentIdentification("Baseline");

    JAUS::Address componentID(1000, 1, 6);
    // Initialize!
    std::cout << "Initializing component...";
    if(component.Initialize(componentID) == false)
    {
        std::cout << "Failed to initialize component [" << componentID.ToString() << "]\n";
        return 0;
    }
    std::cout << "Success!\n";

    // Now go into your main computer loop until the
    // component has been told to shutdown.
    JAUS::Time::Stamp displayStatusTimeMs = JAUS::Time::GetUtcTimeMs();
    while(true)
    {
        // To "simulate" a real sensor, lets modify
        // the latitude like the robot is moving north.
        globalPose.SetLatitude(globalPose.GetLatitude() + 0.00001);
        globalPose.SetTimeStamp(JAUS::Time(true));
        // Update the sensor with the new data.  This will
        // automatically trigger events if someone (i.e. another
        // component) is subscribing to the data from our sensor.
        // this is because the Global Pose Sensor class inherits
        // from the Events service and has implemented all the
        // methods needed to support subscriptions.
        globalPoseSensor->SetGlobalPose(globalPose);

        JAUS::Management* managementService = NULL;
        managementService = component.ManagementService();
        if(managementService->GetStatus() == JAUS::Management::Status::Shutdown)
        {
            // Exit program.
            break;
        }

        if(JAUS::Time::GetUtcTimeMs() - displayStatusTimeMs > 500)
        {
            // Print out status of the service.
            component.GetService(JAUS::GlobalPoseSensor::Name)->PrintStatus(); std::cout << std::endl;
            displayStatusTimeMs = JAUS::Time::GetUtcTimeMs();
        }

        if(CxUtils::GetChar() == 27)
        {
            break;
        }

        CxUtils::SleepMs(100);
    }

    // Shutdown your component completely.  Any
    // services added or belonging to the component
    // will be deleted.
    component.Shutdown();

    return 0;
}