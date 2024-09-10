/**
 * Save the parameters of the PID into Memory.
 */
void savePID(void) {
    int pidIndex;
    // we save both NORMAL_MODE AND ROLLING_TEST_MODE
    for (pidIndex = 0; pidIndex < PID_STORED_COUNT; pidIndex++) {
        Pid* localPid = getPID(pidIndex, 0);
        internalSavePidParameter(pidIndex, EEPROM_KP, localPid->p);
        internalSavePidParameter(pidIndex, EEPROM_KI, localPid->i);
        internalSavePidParameter(pidIndex, EEPROM_KD, localPid->d);
        internalSavePidParameter(pidIndex, EEPROM_MI, localPid->maxIntegral);
    }
}