void InitBCI() {
    concurrency::critical_section::scoped_lock lock(bci_mutex);

    std::cout << "Initializing BCI" << std::endl;

    if (StopAcquisition() != ID_WRONG_SEQUENCY_OF_COMMAND) {
        std::cerr << "Stopped previous data acquisition" << std::endl;
    }

    _DEVICE_INFO *devInfo;
    if (!(devInfo = GetDeviceInfo())) {
        throw("GetDeviceInfo() failed");
    }

    std::cout << "ABM Device Info:" << std::endl;
    std::cout << "Device name: " << devInfo->chDeviceName << std::endl;
    std::cout << "COM Port: " << devInfo->nCommPort << std::endl;
    std::cout << "ECG Channel: " << devInfo->nECGPos << std::endl;
    std::cout << "Number of channels: " << devInfo->nNumberOfChannel << std::endl;

    num_channels = devInfo->nNumberOfChannel;

    if (num_channels < 0) {
        std::cerr << "ABM X10 not connected" << std::endl;
        ExitProcess(1);
    }

    std::stringstream destfilepath;
    SYSTEMTIME stime;
    GetLocalTime(&stime);

    int err;


    destfilepath << "data\\" << stime.wYear << "_" << stime.wMonth << "_" << stime.wDay << "_" << stime.wHour << "_" << stime.wMinute << "_" << stime.wSecond << ".ebs";
    std::string dfp = destfilepath.str();

    char fullpath[4096] = "";
    char *pszfn = NULL;

    err = GetFullPathNameA(dfp.c_str(), sizeof(fullpath), fullpath, &pszfn);

    std::cout << "Setting destination file path to " << fullpath << std::endl;

    if (!(err = SetDestinationFile(fullpath))) {
        std::cerr << "SetDestinationFile failed! err " << err << std::endl;
        ExitProcess(1);
    }

    std::cout << "Initiating session..." << std::endl;
    if ((err = InitSession(ABM_DEVICE_X10Standard, ABM_SESSION_RAW, -1, FALSE)) != INIT_SESSION_OK) {
        std::cerr << "InitSession failed! err " << err << std::endl;
        switch (err) {
        case ID_WRONG_SEQUENCY_OF_COMMAND:
            std::cerr << "Wrong command sequence" << std::endl;
            break;
        case INIT_SESSION_NO:
            std::cerr << "Session initiation failed" << std::endl;
            break;
        case INIT_SESSION_NO_DESTFILE_FAILED:
            std::cerr << "No destination file!" << std::endl;
            break;
        }
        ExitProcess(1);
    }

    std::cout << "Getting channel map info" << std::endl;
    _CHANNELMAP_INFO channelMap;
    if (!GetChannelMapInfo(channelMap)) {
        std::cerr << "GetChannelMapInfo failed!" << std::endl;
        ExitProcess(1);
    }

    if (channelMap.nDeviceTypeCode != 0) {
        std::cerr << "ABM X10 not found! :(" << std::endl;
        ExitProcess(1);
    }

    _EEGCHANNELS_INFO& eegChannels = channelMap.stEEGChannels;
    for (int i = 0; i < channelMap.nSize; ++i) {
        std::cout << eegChannels.cChName[i] << " " << eegChannels.bChUsed[i] << " " << eegChannels.bChUsedInQualityData[i] << std::endl;
    }

    std::cout << "Starting acquisition..." << std::endl;
    if (StartAcquisition() != ACQ_STARTED_OK) {
        std::cerr << "StartAcquisition failed!" << std::endl;
        ExitProcess(1);
    }

    running = true;

    std::cout << "BCI initialization done!" << std::endl;

}