/************************************************************************************
 *
* ***********************************************************************************/
bool ScopeDome::UpdateShutterStatus()
{
    int rc = readBuffer(GetAllDigitalExt, 5, digitalSensorState);
    if (rc != 0)
    {
        LOGF_ERROR("Error reading input state: %d", rc);
        return false;
    }
    // LOGF_INFO("digitalext %x %x %x %x %x", digitalSensorState[0],
    // digitalSensorState[1], digitalSensorState[2], digitalSensorState[3],
    // digitalSensorState[4]);
    SensorsS[0].s  = getInputState(IN_ENCODER);
    SensorsS[1].s  = ISS_OFF; // ?
    SensorsS[2].s  = getInputState(IN_HOME);
    SensorsS[3].s  = getInputState(IN_OPEN1);
    SensorsS[4].s  = getInputState(IN_CLOSED1);
    SensorsS[5].s  = getInputState(IN_OPEN2);
    SensorsS[6].s  = getInputState(IN_CLOSED2);
    SensorsS[7].s  = getInputState(IN_S_HOME);
    SensorsS[8].s  = getInputState(IN_CLOUDS);
    SensorsS[9].s  = getInputState(IN_CLOUD);
    SensorsS[10].s = getInputState(IN_SAFE);
    SensorsS[11].s = getInputState(IN_ROT_LINK);
    SensorsS[12].s = getInputState(IN_FREE);
    SensorsSP.s    = IPS_OK;
    IDSetSwitch(&SensorsSP, nullptr);

    DomeShutterSP.s = IPS_OK;
    IUResetSwitch(&DomeShutterSP);

    if (getInputState(IN_OPEN1) == ISS_ON) // shutter open switch triggered
    {
        if (shutterState == SHUTTER_MOVING && targetShutter == SHUTTER_OPEN)
        {
            LOGF_INFO("%s", GetShutterStatusString(SHUTTER_OPENED));
            setOutputState(OUT_OPEN1, ISS_OFF);
            shutterState = SHUTTER_OPENED;
            if (getDomeState() == DOME_UNPARKING)
                SetParked(false);
        }
        DomeShutterS[SHUTTER_OPEN].s = ISS_ON;
    }
    else if (getInputState(IN_CLOSED1) == ISS_ON) // shutter closed switch triggered
    {
        if (shutterState == SHUTTER_MOVING && targetShutter == SHUTTER_CLOSE)
        {
            LOGF_INFO("%s", GetShutterStatusString(SHUTTER_CLOSED));
            setOutputState(OUT_CLOSE1, ISS_OFF);
            shutterState = SHUTTER_CLOSED;

            if (getDomeState() == DOME_PARKING && DomeAbsPosNP.s != IPS_BUSY)
            {
                SetParked(true);
            }
        }
        DomeShutterS[SHUTTER_CLOSE].s = ISS_ON;
    }
    else
    {
        shutterState    = SHUTTER_MOVING;
        DomeShutterSP.s = IPS_BUSY;
    }
    return true;
}