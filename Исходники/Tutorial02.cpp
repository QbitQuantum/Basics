int main(int argc, char* argv[])
{
    JAUS::Component component;

    // Setup identification info.  For questions about this,
    // see the previous tutorial(s).
    JAUS::Discovery* discoveryService = NULL;
    discoveryService = component.DiscoveryService();
    discoveryService->SetSubsystemIdentification(JAUS::Subsystem::Vehicle,
                                                 "Robot");
    discoveryService->SetNodeIdentification("Primary Computer");
    discoveryService->SetComponentIdentification("Baseline");

    JAUS::Address componentID(1000, 1, 2);
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
        JAUS::Management* managementService = NULL;
        managementService = component.ManagementService();
        if(managementService->GetStatus() == JAUS::Management::Status::Shutdown)
        {
            // Exit program.
            break;
        }

        if(JAUS::Time::GetUtcTimeMs() - displayStatusTimeMs > 500)
        {
            // Use the discovery service to get a list of 
            // discovered subsystems. (see below for how to clear map).
            JAUS::Subsystem::Map discoveredSubsystems;
            discoveryService->GetSubsystems(discoveredSubsystems);
            std::cout << "======================================================\n";

            JAUS::Subsystem::Map::iterator subsystem;
            // The map is indexed by the subsystem number.
            for(subsystem = discoveredSubsystems.begin();
                subsystem != discoveredSubsystems.end();
                subsystem++)
            {
                std::cout << "Subsystem: " 
                          << subsystem->first 
                          << " Identification: " 
                          << subsystem->second->mIdentification 
                          << std::endl;

                // Lets see if it has specific service we 
                // want to communicate with.  For this tutorial
                // let's check for the Liveness service, which
                // supports the Query Heartbeat Pulse and 
                // Report Heartbeat Pulse messages.
                // We can use the subsystem data structure to
                // get a list of components on the subsystem that
                // have the service, so we can send a message to it.
                JAUS::Address::List componentsWithLiveness;
                componentsWithLiveness = subsystem->second->GetComponentsWithService(JAUS::Liveness::Name);
                JAUS::Address::List::iterator c;
                for(c = componentsWithLiveness.begin();
                    c != componentsWithLiveness.end();
                    c++)
                {
                    // First, make sure it is not the 
                    // component we are using, because we
                    // want to talk to a different one.
                    if( (*c) != component.GetComponentID())
                    {
                        // Now that we have the ID of
                        // component with the Liveness
                        // service, lets send a query message
                        // and wait for the response.

                        // Setup the query message to send.
                        JAUS::QueryHeartbeatPulse query;
                        query.SetDestinationID( (*c) );
                        query.SetSourceID(component.GetComponentID());
                        
                        // This is the response message we want.
                        JAUS::ReportHeartbeatPulse response;

                        // Send and see if we got a
                        // response, but only wait up to 1 second
                        // for a response.  Default value for waiting
                        // is 100 ms.
                        std::cout << "\tSending Query to " << c->ToString() << std::endl;
                        if(component.Send(&query, &response, 1000))
                        {
                            std::cout << "\tReceived Response Message!\n\t";
                            response.Print();
                        }
                    }
                }
                // The above steps can be used to find any component
                // with a specific service you wish to communicate with.
            }

            // Make sure you delete the subsystem map when
            // you are done with it, otherwise you will have a 
            // memory leak.
            JAUS::Subsystem::DeleteSubsystemMap(discoveredSubsystems);

            displayStatusTimeMs = JAUS::Time::GetUtcTimeMs();
        }

        if(CxUtils::GetChar() == 27)
        {
            break;
        }

        CxUtils::SleepMs(1);
    }

    // Shutdown your component completely.  Any
    // services added or belonging to the component
    // will be deleted.
    component.Shutdown();

    return 0;
}