int main(int argc, char **argv)
{
    SICK::Sick laser;
    MessageCallback cb;

    JAUS::Component component;
    // Add the services we want our component to have
    // beyond the core set.

    JAUS::RangeSensor* rangeSensor = new JAUS::RangeSensor();
    // Setup the configuration of a range sensing device.
    JAUS::RangeSensorConfig rangeSensorConfig;
    rangeSensorConfig.mID = 0;
    rangeSensorConfig.mName = "LIDAR";
    rangeSensorConfig.mMinRange = 0.0;
    rangeSensorConfig.mMaxRange = 9.0;                              // 9 meter range.
    rangeSensorConfig.mUnitType = JAUS::RangeSensorConfig::MM;      // Range values are in mm.
    rangeSensorConfig.mScanAngle = CxUtils::CxToRadians(180);       // [-90, 90] degrees.
    rangeSensorConfig.mAngleIncrement = CxUtils::CxToRadians(0.5);  // 0.5 degree increment.
    rangeSensor->AddRangeDevice(rangeSensorConfig);
    // Add to component.
    component.AddService(rangeSensor);

    cb.mpRangeSensor = rangeSensor;

    // Register a callback to process the received
    // messages.
    laser.RegisterCallback(&cb);

    cout << "Connecting to SICK...";
    laser.InitializeWithDefaults("/dev/ttyUSB0", 38400);
    cout << "Success!\n";


    // In this example, we are simulating a component on part of a simulated
    // robot.
    component.DiscoveryService()->SetSubsystemIdentification(JAUS::Subsystem::Vehicle,
                                                             "Simulation");
    // Initialize component component with component given ID.
    if(component.InitializeWithUniqueID(2000) == false)
    {
        std::cout << "Failed to Initialize JAUS Component.\n";
        return 0;
    }

    std::cout << "JAUS Component [" << component.GetComponentID().ToString() << "] Initialized!\n";

    while ( true )
    {
        if (CxUtils::GetChar() == 27)
        {
            break;
        }
        CxUtils::SleepMs(1);
    }

    // Make sure to shutdown the laser.
    laser.Shutdown();
    component.Shutdown();

    return 0;
}