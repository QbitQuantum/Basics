MM::DeviceDetectionStatus DiskoveryHub::DetectDevice(void )
{
    char answerTO[MM::MaxStrLength];

    if (initialized_)
        return MM::CanCommunicate;

    MM::DeviceDetectionStatus result = MM::Misconfigured;

    try
    {
        std::string portLowerCase = port_;
        for( std::string::iterator its = portLowerCase.begin(); its != portLowerCase.end(); ++its)
        {
            *its = (char)tolower(*its);
        }
        if( 0< portLowerCase.length() &&  0 != portLowerCase.compare("undefined")  && 0 != portLowerCase.compare("unknown") )
        {
            result = MM::CanNotCommunicate;
            // record the default answer time out
            GetCoreCallback()->GetDeviceProperty(port_.c_str(), "AnswerTimeout", answerTO);

            // device specific default communication parameters
            GetCoreCallback()->SetDeviceProperty(port_.c_str(), MM::g_Keyword_Handshaking, "Hardware");
            GetCoreCallback()->SetDeviceProperty(port_.c_str(), MM::g_Keyword_BaudRate, "115200" );
            GetCoreCallback()->SetDeviceProperty(port_.c_str(), MM::g_Keyword_StopBits, "1");
            GetCoreCallback()->SetDeviceProperty(port_.c_str(), "AnswerTimeout", "100.0");
            GetCoreCallback()->SetDeviceProperty(port_.c_str(), "DelayBetweenCharsMs", "0");
            // Attempt to communicate through the port
            MM::Device* pS = GetCoreCallback()->GetDevice(this, port_.c_str());
            pS->Initialize();
            PurgeComPort(port_.c_str());
            bool present = false;
            int ret = IsControllerPresent(port_, present);
            if (ret != DEVICE_OK)
                return result;
            if (present)
            {
                result = MM::CanCommunicate;
                // set the timeout to a value higher than the heartbeat frequency
                // so that the logs will not overflow with errors
                GetCoreCallback()->SetDeviceProperty(port_.c_str(),
                                                     "AnswerTimeout", "6000");
            } else
            {
                GetCoreCallback()->SetDeviceProperty(port_.c_str(), "AnswerTimeout", answerTO);
            }
            pS->Shutdown();
        }
    }
    catch(...)
    {
        LogMessage("Exception in DetectDevice!",false);
    }

    return result;
}