void * startPhysicalModel(void * data) {
    
    int sts;
    struct timespec tm;
    modbus_mapping_t *mb_mapping = (modbus_mapping_t *)data;
    
    float tAmbient = AMBIENT_TEMP_DEG_F;
    float tHeater = HEATER_TEMP_DEG_F;
    bool heaterEnabled = false;
    bool heaterOn = HEATER_ON_STATE;
    float tHeaterTarget = HEATER_TARGET_TEMP_DEG_F;
    float tContHysteresis = HEATER_CONTROL_HYSTERESIS_DEG_F;
    float modelDelayTime_hrs = (float)(PHYSICAL_MODEL_DELAY_INTERVAL_MSEC)/
        (1000. * 60. * 60.);
    float tIncrease = 0.0;
    
    heaterEnabled = false;
    heaterOn = false;
    char * heaterEnableState;
    char * heaterElementState;
    char * displayFlag;
    bool displayCnt = true;
    
    if(data == NULL) {
        perror("Illegal modbus mapping struct.");
                exit(1);
    }
    
    while (1) {
        /* get current EPOCH time */
        //clock_gettime(CLOCK_REALTIME, &tm);
        
        usleep(PHYSICAL_MODEL_DELAY_INTERVAL_MSEC * 1000); 

        /* get any modbus registers that may have changed */
        pthread_mutex_lock(&modbusRegisterAccessLock);
        heaterEnabled = getRegisterBit(mb_mapping, HEATER_COIL_ENABLE);
        /* turn off heater if we are disabled */
        if(!heaterEnabled) {
            heaterOn = false;
        }
        tHeaterTarget = (float)(getRegisterValue(mb_mapping, 
                HEATER_WATER_TARGET_TEMP_REG)) / 10.0;
        pthread_mutex_unlock(&modbusRegisterAccessLock);
        
        /* update the model state and, if necessary, update
         modbus registers */
        tIncrease = 0.0;
        if(heaterOn) {
            /* calculate temp increase if heater is on */
            tIncrease = (HEATER_KW * HEATING_CONST) * modelDelayTime_hrs 
                * TIME_SCALING_FACTOR;
        }
        float tCoolDown = tAmbient +            
            (tHeater - tAmbient) * exp(COOLING_CONST * modelDelayTime_hrs
            * TIME_SCALING_FACTOR);
        /* water temp is sum of + and - temperature deltas*/
        tHeater = tCoolDown + tIncrease;
        
        /* update the controller state */
        if(heaterEnabled) {
            if(heaterOn) {
                if(tHeater > (tHeaterTarget + tContHysteresis)) {
                    heaterOn = false;
                }
            }
            else {
                if(tHeater < (tHeaterTarget - tContHysteresis)) {
                    heaterOn = true;
                }
            }
        }
        
        /* lock context and transfer values from the model.  Then unlock.*/
        pthread_mutex_lock(&modbusRegisterAccessLock);
        setInputRegisterValue(mb_mapping, HEATER_WATER_TEMP_REG,
            (short)(tHeater * 10.0));
        setInputRegisterBit(mb_mapping, HEATER_COIL_ENERGIZED, heaterOn);
        pthread_mutex_unlock(&modbusRegisterAccessLock);
        
        if(heaterEnabled) {
            heaterEnableState = "Heater Enabled, ";
        }
        else {
            heaterEnableState = "Heater Disabled, ";
        }
        
        if(heaterOn) {
            heaterElementState = "Heater Element On, ";
        }
        else {
            heaterElementState = "Heater Element Off, ";
        }
        
        if (displayCnt) {
            displayCnt = false;
            displayFlag = "+";
        }
        else {
            displayCnt = true;
            displayFlag = "-";
        }
        
        printf("Model Status(%s): %s%sSet Point: %5.2f, Temp: %5.2f\n",
                displayFlag,
                heaterEnableState, heaterElementState, 
                tHeaterTarget, tHeater);
    }
}