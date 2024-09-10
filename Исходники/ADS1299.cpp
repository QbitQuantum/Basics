void ADS1299::printDeviceID(void)
{
    boolean wasRunning;
    boolean prevverbosityState = verbosity;
    if (isRunning){ stopADS(); wasRunning = true;}
        verbosity = true;
        getDeviceID();
        verbosity = prevverbosityState;
    if (wasRunning){ startADS(); }
        
}