int main(int argc, char* argv[])
{
    JAUS::Component component; 

    // Testing prioritized message data
    component.TransportService()->AddPriorityMessage(JAUS::REPORT_GLOBAL_POSE);
    
    // Add the services our component needs.  This has to
    // be done before component initialization.
    // Second, you cannot add the same service twice.

    JAUS::GlobalPoseSensor* globalPoseSensor = new JAUS::GlobalPoseSensor();
    JAUS::LocalPoseSensor* localPoseSensor = new JAUS::LocalPoseSensor();
    JAUS::VelocityStateSensor* velocityStateSensor = new JAUS::VelocityStateSensor();
    JAUS::AccelerationStateSensor* accelerationStateSensor = new JAUS::AccelerationStateSensor();
    FakeMicrocontroller* mcu = new FakeMicrocontroller();

    // Add to our component.
    component.AddService(globalPoseSensor);
    component.AddService(localPoseSensor);
    component.AddService(velocityStateSensor);
    component.AddService(accelerationStateSensor);
    component.AddService(mcu);

    // Tell our sensor services what component we want them
    // to sync there data with (i.e. who to subscribe to.
    JAUS::Address syncID(gSubsystemID, gSyncNodeID, gSyncComponentID);
    globalPoseSensor->SynchronizeToComponent(syncID);
    localPoseSensor->SynchronizeToComponent(syncID);
    velocityStateSensor->SynchronizeToComponent(syncID);
    accelerationStateSensor->SynchronizeToComponent(syncID);
    mcu->SynchronizeToComponent(syncID);

    // Example of how to use events callback
    EventCallback callback;
    component.EventsService()->RegisterCallback(&callback);


    // Try load settings files.
    // These files determine your UDP network 
    // settings, what Services to turn on/off 
    // or any Service specific settings. See the
    // example file for settings file format.
    if(component.LoadSettings("settings/services.xml") == false)
    {
        // Working directory probably not set (or not running from output directory), so
        // use default values.
        component.DiscoveryService()->SetSubsystemIdentification(JAUS::Subsystem::Vehicle,
                                                                 "Simulation");
        // Set optional identification info for this component.
        component.DiscoveryService()->SetComponentIdentification("Synchronize");
    }

    // Initialize component with component given ID.
    if(component.Initialize(JAUS::Address(gSubsystemID, gNodeID, gComponentID)) == false)
    {
        std::cout << "Failed to Initialize Component.\n";
        return 0;
    }
    
    bool foundSyncID = false;
    CxUtils::Time::Stamp printTimeMs = 0;
    while(CxUtils::GetChar() != 27)
    {
        // This is a short example code to dynamically lookup a
        // component ID for the service you want to synchronize on your
        // subsystem (like in your AI program if the services may run on different computers).
#if 0
        // Enable synchronization for each sensor.
        if(globalPoseSensor->IsSynchronizing() == false)
        {
            // Find sensor to sync to.
            JAUS::Address::List idList = component.DiscoveryService()->GetSubsystem(gSubsystemID)->GetComponentsWithService(JAUS::GlobalPoseSensor::Name);
            if(idList.size() > 0)
            {
                globalPoseSensor->SynchronizeToComponent(idList.front());
            }
        }
#endif
        if(CxUtils::Time::GetUtcTimeMs() - printTimeMs > 500)
        {
            // Print status of services.
            std::cout << "\n======================================================\n";
            globalPoseSensor->PrintStatus(); std::cout << std::endl;
            localPoseSensor->PrintStatus(); std::cout << std::endl;
            velocityStateSensor->PrintStatus(); std::cout << std::endl;
            accelerationStateSensor->PrintStatus(); std::cout << std::endl;
            mcu->PrintStatus(); std::cout << std::endl;
            printTimeMs = CxUtils::Time::GetUtcTimeMs();
        }
        CxUtils::SleepMs(1);
    }

    // Don't delete services, they are
    // deleted by the Component class.

    // Shutdown any components associated with our subsystem.
    component.Shutdown();

    return 0;
}