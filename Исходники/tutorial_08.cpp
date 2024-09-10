////////////////////////////////////////////////////////////////////////////////////
///
///   \brief Simple simulation of a component that subscribes to any Local
///          Pose Sensor data on network using JTCP.
///
///   \param[in] subsystemID Subsystem ID number.
///   \param[in] nodeID Node ID number.
///
////////////////////////////////////////////////////////////////////////////////////
int RunClient(JAUS::UShort subsystemID, JAUS::Byte nodeID)
{
    JAUS::Component component;
    JAUS::Address id(subsystemID, nodeID, 1);

    if(id.IsValid() == false)
    {
        std::cout << "Invalid JAUS ID: " << id.ToString() << std::endl;
    }

    // Setup identification data.
    component.DiscoveryService()->SetSubsystemIdentification(JAUS::Subsystem::Vehicle,
                                                             "Subscriber JTCP Tutorial");

    //  Change the transport service to use JTCP
    component.AddService(new JAUS::JTCPClient());
    //((JAUS::JTCPClient*)component.TransportService())->AddConnection("10.171.190.61", JAUS::Address(subsystemID, 1, 1));
    //((JAUS::JTCPClient*)component.TransportService())->AddConnection("127.0.0.1", JAUS::Address(subsystemID, 1, 1));

    // Add support for reading Local Pose messages without having to
    // add a custom service.
    component.TransportService()->AddMessageTemplate(new JAUS::ReportLocalPose());
    component.TransportService()->AddMessageTemplate(new JAUS::QueryLocalPose());

    // Add a callback to get messages when they arrive.
    LocalPoseCallback localPoseCallback;
    component.TransportService()->RegisterCallback(JAUS::REPORT_LOCAL_POSE, &localPoseCallback);

    // Initialize component and communication.
    if(component.Initialize(id) == false)
    {
        std::cout << "Failed to initialize JAUS component with ID: " << id.ToString() << std::endl;
        return 0;
    }

    JAUS::Time printTime(true);

    while(CxUtils::GetChar() != 27 && component.ManagementService()->GetStatus() != JAUS::Management::Status::Shutdown)
    {
        // Look for any subsystems.
        JAUS::Subsystem::Map subsystems;
        JAUS::Subsystem::Map::iterator subsystem;

        component.DiscoveryService()->GetSubsystems(subsystems);

        for(subsystem = subsystems.begin();
            subsystem != subsystems.end();
            subsystem++)
        {
            // Look for local pose sensors to subscribe to.
            JAUS::Address::List sensors = subsystem->second->GetComponentsWithService(JAUS::LocalPoseSensor::Name);
            if(sensors.size() > 0)
            {
                JAUS::Address::List::iterator id;
                for(id = sensors.begin();
                    id != sensors.end();
                    id++)
                {
                    if(*id != component.GetComponentID() && 
                       component.EventsService()->HaveSubscription(JAUS::REPORT_LOCAL_POSE, *id) == false)
                    {
                        std::cout << "Found new Local Pose Sensors on " << id->ToString() << std::endl;
                        JAUS::QueryLocalPose queryLocalPose;
                        // Request all fields.
                        queryLocalPose.SetPresenceVector(queryLocalPose.GetPresenceVectorMask());
                        component.EventsService()->RequestPeriodicEvent(*id, &queryLocalPose, 5);
                    }
                }
            }
        }

        JAUS::Subsystem::DeleteSubsystemMap(subsystems);
        // Only print to screen every now and then.
        if(JAUS::Time(true) - printTime > .5)
        {
            //std::cout << "=======================================================\n";
            //component.EventsService()->PrintStatus();
            //printTime.SetCurrentTime();
        }
        // Don't overload the CPU
        CxUtils::SleepMs(1);
    }

    // Do shutdown
    component.Shutdown();

    return 0;
}