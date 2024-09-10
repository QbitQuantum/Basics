/////////////////////////////////////////////////////////
/// Cooler & Filter Wheel monitoring
/////////////////////////////////////////////////////////
void ATIKCCD::TimerHit()
{
    double currentTemperature = TemperatureN[0].value;

    int flags, level, minlvl, maxlvl, setpoint;

    pthread_mutex_lock(&accessMutex);
    int rc = ArtemisCoolingInfo(hCam, &flags, &level, &minlvl, &maxlvl, &setpoint);
    pthread_mutex_unlock(&accessMutex);

    if (rc != ARTEMIS_OK)
    {
        LOGF_ERROR("Cooling Info inquiry failed (%d)", rc);
        genTimerID = SetTimer(TEMP_TIMER_MS);
        return;
    }

    LOGF_DEBUG("Cooling: flags (%d) level (%d), minlvl (%d), maxlvl (%d), setpoint (%d)", flags, level, minlvl, maxlvl, setpoint);

    int temperature = 0;
    pthread_mutex_lock(&accessMutex);
    rc = ArtemisTemperatureSensorInfo(hCam, 1, &temperature);
    pthread_mutex_unlock(&accessMutex);
    TemperatureN[0].value = temperature / 100.0;

    switch (TemperatureNP.s)
    {
        case IPS_IDLE:
        case IPS_OK:
            if (fabs(currentTemperature - TemperatureN[0].value)  > TEMP_THRESHOLD / 10.0)
            {
                IDSetNumber(&TemperatureNP, nullptr);
            }
            break;

        case IPS_ALERT:
            break;

        case IPS_BUSY:
            // If we're within threshold, let's make it BUSY ---> OK
            if (fabs(TemperatureRequest - TemperatureN[0].value)  <= TEMP_THRESHOLD)
            {
                TemperatureNP.s = IPS_OK;
            }
            IDSetNumber(&TemperatureNP, nullptr);
            break;
    }

    if (HasCooler())
    {
        bool coolerChanged = false;
        double coolerPower = static_cast<double>(level) / maxlvl * 100.0;
        if (fabs(CoolerN[0].value - coolerPower) > 0.01)
        {
            CoolerN[0].value = coolerPower;
            coolerChanged = true;
        }

        // b5 0 = normal control 1=warming up
        // b6 0 = cooling off 1 = cooling on
        if (!(flags & 0x20) && // Normal Control?
                (flags & 0x40))   // Cooling On?
        {
            if (CoolerNP.s != IPS_BUSY)
                coolerChanged = true;
            CoolerNP.s = IPS_BUSY;
        }
        // Otherwise cooler is either warming up or not active
        else
        {
            if (CoolerNP.s != IPS_IDLE)
                coolerChanged = true;
            CoolerNP.s = IPS_IDLE;
        }

        if (coolerChanged)
            IDSetNumber(&CoolerNP, nullptr);
    }

    // If filter wheel is in motion
    if (FilterSlotNP.s == IPS_BUSY)
    {
        int numFilters, moving, currentPos, targetPos;
        pthread_mutex_lock(&accessMutex);
        int rc = ArtemisFilterWheelInfo(hCam, &numFilters, &moving, &currentPos, &targetPos);
        pthread_mutex_unlock(&accessMutex);

        if (rc != ARTEMIS_OK)
        {
            LOGF_ERROR("Querying internal filter wheel failed (%d).", rc);
        }
        else
        {
            if (moving == 0 && currentPos == targetPos)
            {
                SelectFilterDone(currentPos + 1);
            }
        }

    }

    genTimerID = SetTimer(TEMP_TIMER_MS);
}