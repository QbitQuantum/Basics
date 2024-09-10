void SDRThread::init() {
//#warning Debug On
//    SoapySDR_setLogLevel(SOAPY_SDR_DEBUG);
    
    SDRDeviceInfo *devInfo = deviceInfo.load();
    deviceConfig.store(wxGetApp().getConfig()->getDevice(devInfo->getDeviceId()));
    DeviceConfig *devConfig = deviceConfig.load();
    
    ppm.store(devConfig->getPPM());
    ppm_changed.store(true);
    
    std::string driverName = devInfo->getDriver();

    offset = devConfig->getOffset();
    
    SoapySDR::Kwargs args = devInfo->getDeviceArgs();
    
    wxGetApp().sdrEnumThreadNotify(SDREnumerator::SDR_ENUM_MESSAGE, std::string("Initializing device."));
    
    device = devInfo->getSoapyDevice();
    
    SoapySDR::Kwargs currentStreamArgs = combineArgs(devInfo->getStreamArgs(),streamArgs);
    stream = device->setupStream(SOAPY_SDR_RX,"CF32", std::vector<size_t>(), currentStreamArgs);
    
    int streamMTU = device->getStreamMTU(stream);
    mtuElems.store(streamMTU);
    
    std::cout << "Stream MTU: " << mtuElems.load() << std::endl << std::flush;
    
    deviceInfo.load()->setStreamArgs(currentStreamArgs);
    deviceConfig.load()->setStreamOpts(currentStreamArgs);
    
    wxGetApp().sdrEnumThreadNotify(SDREnumerator::SDR_ENUM_MESSAGE, std::string("Activating stream."));
    device->setSampleRate(SOAPY_SDR_RX,0,sampleRate.load());
    device->setFrequency(SOAPY_SDR_RX,0,"RF",frequency - offset.load());
    device->activateStream(stream);
    if (devInfo->hasCORR(SOAPY_SDR_RX, 0)) {
        hasPPM.store(true);
        device->setFrequency(SOAPY_SDR_RX,0,"CORR",ppm.load());
    } else {
        hasPPM.store(false);
    }
    if (device->hasDCOffsetMode(SOAPY_SDR_RX, 0)) {
        hasHardwareDC.store(true);
//        wxGetApp().sdrEnumThreadNotify(SDREnumerator::SDR_ENUM_MESSAGE, std::string("Found hardware DC offset correction support, internal disabled."));
        device->setDCOffsetMode(SOAPY_SDR_RX, 0, true);
    } else {
        hasHardwareDC.store(false);
    }
    
    device->setGainMode(SOAPY_SDR_RX,0,agc_mode.load());
    
    numChannels.store(getOptimalChannelCount(sampleRate.load()));
    numElems.store(getOptimalElementCount(sampleRate.load(), 30));
    if (!mtuElems.load()) {
        mtuElems.store(numElems.load());
    }
    inpBuffer.data.resize(numElems.load());
    overflowBuffer.data.resize(mtuElems.load());
    
    buffs[0] = malloc(mtuElems.load() * 4 * sizeof(float));
    numOverflow = 0;
    
    SoapySDR::ArgInfoList settingsInfo = device->getSettingInfo();
    SoapySDR::ArgInfoList::const_iterator settings_i;
    
    if (!setting_value_changed.load()) {
        settings.erase(settings.begin(), settings.end());
        settingChanged.erase(settingChanged.begin(), settingChanged.end());
    }
    
    { //enter scoped-lock
        std::lock_guard < std::mutex > lock(setting_busy);

        for (settings_i = settingsInfo.begin(); settings_i != settingsInfo.end(); settings_i++) {
            SoapySDR::ArgInfo setting = (*settings_i);
            if ((settingChanged.find(setting.key) != settingChanged.end()) && (settings.find(setting.key) != settings.end())) {
                device->writeSetting(setting.key, settings[setting.key]);
                settingChanged[setting.key] = false;
            } else {
                settings[setting.key] = device->readSetting(setting.key);
                settingChanged[setting.key] = false;
            }
        }
        setting_value_changed.store(false);

    } //leave lock guard scope
    
    updateSettings();
    
    wxGetApp().sdrThreadNotify(SDRThread::SDR_THREAD_INITIALIZED, std::string("Device Initialized."));
}