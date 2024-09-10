/*
 * Process the parameter update from ichip we received as a response to AT+iWNXT.
 * The response usually looks like this : key="value", so the key can be isolated
 * by looking for the '=' sign and the leading/trailing '"' have to be ignored.
 */
void ADAFRUITBLE::processParameterChange(char *key) {
    PotThrottleConfiguration *acceleratorConfig = NULL;
    PotThrottleConfiguration *brakeConfig = NULL;
    MotorControllerConfiguration *motorConfig = NULL;
    bool parameterFound = true;

    char *value = strchr(key, '=');
    if (!value)
        return;

    Throttle *accelerator = DeviceManager::getInstance()->getAccelerator();
    Throttle *brake = DeviceManager::getInstance()->getBrake();
    MotorController *motorController = DeviceManager::getInstance()->getMotorController();

    if (accelerator)
        acceleratorConfig = (PotThrottleConfiguration *)accelerator->getConfiguration();
    if (brake)
        brakeConfig = (PotThrottleConfiguration *)brake->getConfiguration();
    if(motorController)
        motorConfig = (MotorControllerConfiguration *)motorController->getConfiguration();

    value[0] = 0; // replace the '=' sign with a 0
    value++;
    if (value[0] == '"')
        value++; // if the value starts with a '"', advance one character
    if (value[strlen(value) - 1] == '"')
        value[strlen(value) - 1] = 0; // if the value ends with a '"' character, replace it with 0

    if (!strcmp(key, Constants::numThrottlePots) && acceleratorConfig) {
        acceleratorConfig->numberPotMeters = atol(value);
        accelerator->saveConfiguration();
    } else if (!strcmp(key, Constants::throttleSubType) && acceleratorConfig) {
        acceleratorConfig->throttleSubType = atol(value);
        accelerator->saveConfiguration();
    } else if (!strcmp(key, Constants::throttleMin1) && acceleratorConfig) {
        acceleratorConfig->minimumLevel1 = atol(value);
        accelerator->saveConfiguration();
    } else if (!strcmp(key, Constants::throttleMin2) && acceleratorConfig) {
        acceleratorConfig->minimumLevel2 = atol(value);
        accelerator->saveConfiguration();
    } else if (!strcmp(key, Constants::throttleMax1) && acceleratorConfig) {
        acceleratorConfig->maximumLevel1 = atol(value);
        accelerator->saveConfiguration();
    } else if (!strcmp(key, Constants::throttleMax2) && acceleratorConfig) {
        acceleratorConfig->maximumLevel2 = atol(value);
        accelerator->saveConfiguration();
    } else if (!strcmp(key, Constants::throttleRegenMax) && acceleratorConfig) {
        acceleratorConfig->positionRegenMaximum = atol(value) * 10;
    } else if (!strcmp(key, Constants::throttleRegenMin) && acceleratorConfig) {
        acceleratorConfig->positionRegenMinimum = atol(value) * 10;
        accelerator->saveConfiguration();
    } else if (!strcmp(key, Constants::throttleFwd) && acceleratorConfig) {
        acceleratorConfig->positionForwardMotionStart = atol(value) * 10;
        accelerator->saveConfiguration();
    } else if (!strcmp(key, Constants::throttleMap) && acceleratorConfig) {
        acceleratorConfig->positionHalfPower = atol(value) * 10;
        accelerator->saveConfiguration();
    } else if (!strcmp(key, Constants::throttleMinRegen) && acceleratorConfig) {
        acceleratorConfig->minimumRegen = atol(value);
        accelerator->saveConfiguration();
    } else if (!strcmp(key, Constants::throttleMaxRegen) && acceleratorConfig) {
        acceleratorConfig->maximumRegen = atol(value);
        accelerator->saveConfiguration();
    } else if (!strcmp(key, Constants::throttleCreep) && acceleratorConfig) {
        acceleratorConfig->creep = atol(value);
        accelerator->saveConfiguration();
    } else if (!strcmp(key, Constants::brakeMin) && brakeConfig) {
        brakeConfig->minimumLevel1 = atol(value);
        brake->saveConfiguration();
    } else if (!strcmp(key, Constants::brakeMax) && brakeConfig) {
        brakeConfig->maximumLevel1 = atol(value);
        brake->saveConfiguration();
    } else if (!strcmp(key, Constants::brakeMinRegen) && brakeConfig) {
        brakeConfig->minimumRegen = atol(value);
        brake->saveConfiguration();
    } else if (!strcmp(key, Constants::brakeMaxRegen) && brakeConfig) {
        brakeConfig->maximumRegen = atol(value);
        brake->saveConfiguration();
    } else if (!strcmp(key, Constants::speedMax) && motorConfig) {
        motorConfig->speedMax = atol(value);
        motorController->saveConfiguration();
    } else if (!strcmp(key, Constants::torqueMax) && motorConfig) {
        motorConfig->torqueMax = atol(value) * 10;
        motorController->saveConfiguration();
    } else if (!strcmp(key, Constants::coolFan) && motorConfig) {
        motorConfig->coolFan = atol(value);
        motorController->saveConfiguration();
    } else if (!strcmp(key, Constants::coolOn) && motorConfig) {
        motorConfig->coolOn = (atol(value));
        motorController->saveConfiguration();
    } else if (!strcmp(key, Constants::coolOff) && motorConfig) {
        motorConfig->coolOff = (atol(value));
        motorController->saveConfiguration();
    } else if (!strcmp(key, Constants::prechargeR) && motorConfig) {
        motorConfig->prechargeR = atol(value);
        motorController->saveConfiguration();
    } else if (!strcmp(key, Constants::prechargeRelay) && motorConfig) {
        motorConfig->prechargeRelay = atol(value);
        motorController->saveConfiguration();
    } else if (!strcmp(key, Constants::nominalVolt) && motorConfig) {
        motorConfig->nominalVolt = (atol(value))*10;
        motorController->saveConfiguration();

    } else if (!strcmp(key, Constants::mainContactorRelay) && motorConfig) {
        motorConfig->mainContactorRelay = atol(value);
        motorController->saveConfiguration();
    } else if (!strcmp(key, Constants::brakeLight) && motorConfig) {
        motorConfig->brakeLight = atol(value);
        motorController->saveConfiguration();
    } else if (!strcmp(key, Constants::revLight) && motorConfig) {
        motorConfig->revLight = atol(value);
        motorController->saveConfiguration();
    } else if (!strcmp(key, Constants::enableIn) && motorConfig) {
        motorConfig->enableIn = atol(value);
        motorController->saveConfiguration();
    } else if (!strcmp(key, Constants::reverseIn) && motorConfig) {
        motorConfig->reverseIn = atol(value);
        motorController->saveConfiguration();
        /*  } else if (!strcmp(key, Constants::motorMode) && motorConfig) {
        motorConfig->motorMode = (MotorController::PowerMode)atoi(value);
        motorController->saveConfiguration();
        */



    } else if (!strcmp(key, "x1000")) {
        if (255==atol(value)) {
            sysPrefs->setDeviceStatus(strtol(key+1, 0, 16),true);
        }
        else {
            sysPrefs->setDeviceStatus(strtol(key+1, 0, 16), false);
        }
        //sysPrefs->forceCacheWrite();
    } else if (!strcmp(key, "x1001")) {
        if (255==atol(value)) {
            sysPrefs->setDeviceStatus(strtol(key+1, 0, 16),true);
        }
        else {
            sysPrefs->setDeviceStatus(strtol(key+1, 0, 16), false);
        }
        //sysPrefs->forceCacheWrite();
    } else if (!strcmp(key, "x1002")) {
        if (255==atol(value)) {
            sysPrefs->setDeviceStatus(strtol(key+1, 0, 16),true);
        }
        else {
            sysPrefs->setDeviceStatus(strtol(key+1, 0, 16), false);
        }
        // sysPrefs->forceCacheWrite();
    } else if (!strcmp(key, "x1031")) {
        if (255==atol(value)) {
            sysPrefs->setDeviceStatus(strtol(key+1, 0, 16), true);
        }
        else {
            sysPrefs->setDeviceStatus(strtol(key+1, 0, 16), false);
        }
        //sysPrefs->forceCacheWrite();
    } else if (!strcmp(key, "x1032")) {
        if (255==atol(value)) {
            sysPrefs->setDeviceStatus(strtol(key+1, 0, 16), true);
        }
        else {
            sysPrefs->setDeviceStatus(strtol(key+1, 0, 16), false);
        }
        //sysPrefs->forceCacheWrite();
    } else if (!strcmp(key, "x1033")) {
        if (255==atol(value)) {
            sysPrefs->setDeviceStatus(strtol(key+1, 0, 16), true);
        }
        else {
            sysPrefs->setDeviceStatus(strtol(key+1, 0, 16), false);
        }
        //sysPrefs->forceCacheWrite();
    } else if (!strcmp(key, "x1034")) {
        if (255==atol(value)) {
            sysPrefs->setDeviceStatus(strtol(key+1, 0, 16), true);
        }
        else {
            sysPrefs->setDeviceStatus(strtol(key+1, 0, 16), false);
        }
        // sysPrefs->forceCacheWrite();
    } else if (!strcmp(key, "x1010")) {
        if (255==atol(value)) {
            sysPrefs->setDeviceStatus(strtol(key+1, 0, 16), true);
        }
        else {
            sysPrefs->setDeviceStatus(strtol(key+1, 0, 16), false);
        }
        // sysPrefs->forceCacheWrite();
    } else if (!strcmp(key, "x1011")) {
        if (255==atol(value)) {
            sysPrefs->setDeviceStatus(strtol(key+1, 0, 16), true);
        }
        else {
            sysPrefs->setDeviceStatus(strtol(key+1, 0, 16), false);
        }
        //sysPrefs->forceCacheWrite();
    } else if (!strcmp(key, "x1012")) {
        if (255==atol(value)) {
            sysPrefs->setDeviceStatus(strtol(key+1, 0, 16), true);
        }
        else {
            sysPrefs->setDeviceStatus(strtol(key+1, 0, 16), false);
        }
        //sysPrefs->forceCacheWrite();
    } else if (!strcmp(key, "x1020")) {
        if (255==atol(value)) {
            sysPrefs->setDeviceStatus(strtol(key+1, 0, 16), true);
        }
        else {
            sysPrefs->setDeviceStatus(strtol(key+1, 0, 16), false);
        }
        sysPrefs->forceCacheWrite();
    } else if (!strcmp(key, "x1040")) {
        if (255==atol(value)) {
            sysPrefs->setDeviceStatus(strtol(key+1, 0, 16), true);
        }
        else {
            sysPrefs->setDeviceStatus(strtol(key+1, 0, 16), false);
        }
        // sysPrefs->forceCacheWrite();
    } else if (!strcmp(key, "x1050")) {
        if (255==atol(value)) {
            sysPrefs->setDeviceStatus(strtol(key+1, 0, 16), true);
        }
        else {
            sysPrefs->setDeviceStatus(strtol(key+1, 0, 16), false);
        }
        // sysPrefs->forceCacheWrite();
    } else if (!strcmp(key, "x2000")) {
        if (255==atol(value)) {
            sysPrefs->setDeviceStatus(strtol(key+1, 0, 16), true);
        }
        else {
            sysPrefs->setDeviceStatus(strtol(key+1, 0, 16), false);
        }
        sysPrefs->forceCacheWrite();
    } else if (!strcmp(key, "x4400")) {
        if (255==atol(value)) {
            sysPrefs->setDeviceStatus(strtol(key+1, 0, 16), true);
        }
        else {
            sysPrefs->setDeviceStatus(strtol(key+1, 0, 16), false);
        }
        // sysPrefs->forceCacheWrite();
        sysPrefs->forceCacheWrite();
    } else if (!strcmp(key, "x6000")) {
        if (255==atol(value)) {
            sysPrefs->setDeviceStatus(strtol(key+1, 0, 16), true);
        }
        else {
            sysPrefs->setDeviceStatus(strtol(key+1, 0, 16), false);
        }
        //   sysPrefs->forceCacheWrite();
    } else if (!strcmp(key, "x650")) {
        if (255==atol(value)) {
            sysPrefs->setDeviceStatus(strtol(key+1, 0, 16), true);
        }
        else {
            sysPrefs->setDeviceStatus(strtol(key+1, 0, 16), false);
        }
        // sysPrefs->forceCacheWrite();

    } else if (!strcmp(key, Constants::logLevel)) {
        extern PrefHandler *sysPrefs;
        uint8_t loglevel = atoi(value);
        Logger::setLoglevel((Logger::LogLevel)loglevel);
        sysPrefs->write(EESYS_LOG_LEVEL, loglevel);
    } else {
        parameterFound = false;
    }
    if (parameterFound) {
        Logger::info(ADABLUE, "parameter change: %s", key);
    }
    else {
        sysPrefs->forceCacheWrite();
        DeviceManager::getInstance()->updateWifi();
    }
}